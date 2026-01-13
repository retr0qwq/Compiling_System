#include <backend/ra/linear_scan.h>
#include <backend/mir/m_function.h>
#include <backend/mir/m_instruction.h>
#include <backend/mir/m_block.h>
#include <backend/mir/m_defs.h>
#include <backend/target/target_reg_info.h>
#include <backend/target/target_instr_adapter.h>
#include <backend/common/cfg.h>
#include <backend/common/cfg_builder.h>
#include <utils/dynamic_bitset.h>
#include <debug.h>

#include <map>
#include <set>
#include <unordered_map>
#include <deque>
#include <algorithm>

namespace BE::RA
{
    /*
     * 线性扫描寄存器分配（Linear Scan）教学版说明
     *
     * 目标：将每个虚拟寄存器（vreg）的活跃区间映射到目标机的物理寄存器或栈槽（溢出）。
     *
     * 核心步骤（整数/浮点分开执行，流程相同）：
     * 1) 指令线性化与编号：为函数内所有指令分配全局顺序号，记录每个基本块的 [start, end) 区间，
     *    同时收集调用点（callPoints），用于偏好分配被调用者保存寄存器（callee-saved）。
     * 2) 构建 USE/DEF：枚举每条指令的使用与定义寄存器，聚合到基本块级的 USE/DEF 集合。
     * 3) 活跃性分析：在 CFG 上迭代 IN/OUT，满足 IN = USE ∪ (OUT − DEF) 直至收敛。
     * 4) 活跃区间构建：按基本块从后向前，根据 IN/OUT 与指令次序，累积每个 vreg 的若干 [start, end) 段并合并。
     * 5) 标记跨调用：若区间与任意调用点重叠（交叉），标记 crossesCall=true，以便后续优先使用被调用者保存寄存器。
     * 6) 线性扫描分配：将区间按起点排序，维护活动集合 active；到达新区间时先移除已过期区间，然后
     *    尝试选择空闲物理寄存器；若无空闲则选择一个区间溢出（常见启发：溢出“结束点更远”的区间）。
     * 7) 重写 MIR：对未分配物理寄存器的 use/def，在指令前/后插入 reload/spill，并用临时物理寄存器替换操作数。
     *
     * 提示：
     * - 通过 TargetInstrAdapter 提供的接口完成目标无关的指令读写。
     * - TargetRegInfo 提供了可分配寄存器集合、被调用者保存寄存器、保留寄存器等信息。
     */
    namespace
    {
        struct Segment
        {
            int start;
            int end;
            Segment(int s = 0, int e = 0) : start(s), end(e) {}
        };
        struct Interval
        {
            BE::Register         vreg;
            std::vector<Segment> segs;
            bool                 crossesCall = false;

            int                  physReg = -1;  // 分配的物理寄存器，-1表示未分配
            bool                 spilled = false; // 是否被溢出
            int                  spillSlot = -1; // 溢出槽的帧索引

            void addSegment(int s, int e)
            {
                if (s >= e) return;
                segs.emplace_back(s, e);
            }
            void merge() 
            { 
                if (segs.empty()) return;
                std::sort(segs.begin(), segs.end(),
                    [](const Segment& a, const Segment& b) { return a.start < b.start; });
                std::vector<Segment> merged;
                merged.push_back(segs[0]);
                for (size_t i = 1; i < segs.size(); i++)
                {
                    if (segs[i].start <= merged.back().end)
                    {
                        merged.back().end = std::max(merged.back().end, segs[i].end);
                    }
                    else
                    {
                        merged.push_back(segs[i]);
                    }
                }
                segs = std::move(merged);
            }
        };

        struct IntervalOrder
        {
            bool operator()(const Interval* a, const Interval* b) const 
            { 
                return a->segs[0].start < b->segs[0].start;
            }
        };
    }  // namespace

    static std::vector<int> buildAllocatableInt(const BE::Targeting::TargetRegInfo& ri)
    {
        std::vector<int> allocatable;
        const auto& allIntRegs = ri.intRegs();  // 获取所有整数寄存器
        const auto& reservedRegs = ri.reservedRegs();
        std::set<int> reservedSet(reservedRegs.begin(), reservedRegs.end());
        // 排除保留寄存器
        for (int reg : allIntRegs)
        {
            if (!reservedSet.count(reg)) 
                allocatable.push_back(reg);
        }
        return allocatable;
    }

    void LinearScanRA::allocateFunction(BE::Function& func, const BE::Targeting::TargetRegInfo& regInfo)
    {
        ASSERT(BE::Targeting::g_adapter && "TargetInstrAdapter is not set");

        std::map<BE::Block*, std::pair<int, int>>                                   blockRange;
        std::vector<std::pair<BE::Block*, std::deque<BE::MInstruction*>::iterator>> id2iter;
        std::set<int>                                                               callPoints;
        int                                                                         ins_id = 0;
        for (auto& [bid, block] : func.blocks)
        {
            int start = ins_id;
            for (auto it = block->insts.begin(); it != block->insts.end(); ++it, ++ins_id)
            {
                id2iter.emplace_back(block, it);
                if (BE::Targeting::g_adapter->isCall(*it)) callPoints.insert(ins_id);
            }
            blockRange[block] = {start, ins_id};
        }

        std::map<BE::Block*, std::set<BE::Register>> USE, DEF;
        for (auto& [bid, block] : func.blocks)
        {
            std::set<BE::Register> use, def;
            for (auto it = block->insts.begin(); it != block->insts.end(); ++it)
            {
                std::vector<BE::Register> uses, defs;
                BE::Targeting::g_adapter->enumUses(*it, uses);
                BE::Targeting::g_adapter->enumDefs(*it, defs);
                for (auto& d : defs)
                    if (!def.count(d)) def.insert(d);
                for (auto& u : uses)
                    if (!def.count(u)) use.insert(u);
            }
            USE[block] = std::move(use);
            DEF[block] = std::move(def);
        }

        // ============================================================================
        // 构建 CFG 后继关系
        // ============================================================================
        // 作用：搭建活跃性数据流的图结构。
        // 如何做：可直接用 MIR::CFGBuilder 生成 CFG，再转换为 succs 映射。
        BE::MIR::CFGBuilder builder(BE::Targeting::g_adapter);
        BE::MIR::CFG* cfg = builder.buildCFGForFunction(&func);
        std::map<BE::Block*, std::vector<BE::Block*>> succs;

        for (auto& [bid, block] : cfg->blocks) {
            std::vector<BE::Block*> successors;
            // 使用graph_id获取后继的block id
            if (bid < cfg->graph_id.size()) {
                for (uint32_t succ_id : cfg->graph_id[bid]) {
                    auto it = cfg->blocks.find(succ_id);
                    if (it != cfg->blocks.end())
                        successors.push_back(it->second);
                }
            }
            succs[block] = successors;
        }

        // ============================================================================
        // 活跃性分析（IN/OUT）
        // ============================================================================
        // IN[b] = USE[b] ∪ (OUT[b] − DEF[b])，OUT[b] = ⋃ IN[s]，其中 s ∈ succs[b]
        // 迭代执行上述操作直到不变为止
        std::map<BE::Block*, std::set<BE::Register>> IN, OUT;
        bool                                         changed = true;
        while (changed)
        {
            changed = false;
            for (auto& [bid, block] : func.blocks)
            {
                std::set<BE::Register> newOUT;
                for (auto* s : succs[block])
                {
                    auto it = IN.find(s);
                    if (it != IN.end()) newOUT.insert(it->second.begin(), it->second.end());
                }
                std::set<BE::Register> newIN = USE[block];

                for (auto& r : newOUT)
                    if (!DEF[block].count(r)) newIN.insert(r);

                if (!(newOUT != OUT[block] || newIN != IN[block])) continue;

                OUT[block] = std::move(newOUT);
                IN[block]  = std::move(newIN);
                changed    = true;
            }
        }

        delete cfg;

        // ============================================================================
        // 构建活跃区间（Intervals）
        // ============================================================================
        // 作用：得到每个 vreg 的若干 [start,end) 段并合并（interval.merge()）。
        // 如何做：对每个基本块，反向遍历其指令序列，根据 IN/OUT/uses/defs 更新段的开始/结束。
        std::map<BE::Register, Interval*> intervalsMap;
    
        // 先为所有虚拟寄存器创建空的Interval
        for (auto& [bid, block] : func.blocks) {
            for (auto& inst : block->insts) {
                std::vector<BE::Register> uses, defs;
                BE::Targeting::g_adapter->enumUses(inst, uses);
                BE::Targeting::g_adapter->enumDefs(inst, defs);
                
                for (auto& reg : uses) {
                    if (!intervalsMap.count(reg)) {
                        intervalsMap[reg] = new Interval{reg, {}, false};
                    }
                }
                for (auto& reg : defs) {
                    if (!intervalsMap.count(reg)) {
                        intervalsMap[reg] = new Interval{reg, {}, false};
                    }
                }
            }
        }
        
        // 为每个基本块构建活跃区间段
        for (auto& [bid, block] : func.blocks) {
            auto blockRangeIt = blockRange.find(block);
            if (blockRangeIt == blockRange.end()) continue;
            
            int blockStart = blockRangeIt->second.first;
            (void)blockStart;
            int blockEnd = blockRangeIt->second.second;
            
            // 初始化活跃集合为OUT[block]
            std::set<BE::Register> live = OUT[block];
            
            // 从后向前遍历指令
            int pos = blockEnd - 1;
            for (auto rit = block->insts.rbegin(); rit != block->insts.rend(); ++rit, --pos) {
                auto& inst = *rit;
                
                std::vector<BE::Register> uses, defs;
                BE::Targeting::g_adapter->enumUses(inst, uses);
                BE::Targeting::g_adapter->enumDefs(inst, defs);
                
                // 在指令处：先添加DEF，再添加USE（因为从后向前）
                for (auto& reg : defs) {
                    if (intervalsMap.count(reg)) {
                        intervalsMap[reg]->addSegment(pos, pos + 1);
                    }
                }
                
                // 更新活跃集合
                for (auto& reg : defs) {
                    live.erase(reg);
                }
                
                // 为当前活跃的寄存器添加区间段
                for (auto& reg : live) {
                    if (intervalsMap.count(reg)) {
                        intervalsMap[reg]->addSegment(pos, pos + 1);
                    }
                }
                
                // 添加USE到活跃集合
                for (auto& reg : uses) {
                    live.insert(reg);
                }
            }
        }
        
        // 合并每个Interval的段
        for (auto& [reg, interval] : intervalsMap) 
        {
            interval->merge();
            
            // 检查是否跨越调用点
            for (int callPos : callPoints) {
                if (interval->segs.empty()) continue;
                if (callPos >= interval->segs[0].start && callPos < interval->segs.back().end) 
                {
                    interval->crossesCall = true;
                    break;
                }
            }
        }
        
        // 收集所有Interval到向量中
        std::vector<Interval*> intervals;
        for (auto& [reg, interval] : intervalsMap) 
        {
            intervals.push_back(interval);
        }
        
        // 按起点排序
        std::sort(intervals.begin(), intervals.end(), 
                [](const Interval* a, const Interval* b) {
                    return a->segs[0].start < b->segs[0].start;
                });

        // ============================================================================
        // 线性扫描主循环（简化版，只处理整数）
        // ============================================================================
        auto allIntRegs = buildAllocatableInt(regInfo);

        // 将被调用者保存寄存器放在前面，优先分配给跨调用的区间
        std::vector<int> orderedIntRegs;

        // 首先添加被调用者保存寄存器
        const auto& calleeSavedInt = regInfo.calleeSavedIntRegs();
        const auto& reservedRegs = regInfo.reservedRegs();

        std::set<int> reservedSet(reservedRegs.begin(), reservedRegs.end());

        for (int reg : calleeSavedInt) {
            if (!reservedSet.count(reg)) {
                orderedIntRegs.push_back(reg);
            }
        }

        // 然后添加其他可分配寄存器
        for (int reg : allIntRegs) {
            if (!reservedSet.count(reg) && 
                std::find(orderedIntRegs.begin(), orderedIntRegs.end(), reg) == orderedIntRegs.end()) {
                orderedIntRegs.push_back(reg);
            }
        }

        // 活动集合，按结束时间排序
        std::set<Interval*, bool(*)(Interval*, Interval*)> active(
            [](Interval* a, Interval* b) { return a->segs.back().end < b->segs.back().end; }
        );

        // 已分配的物理寄存器集合
        std::set<int> usedPhysRegs;

        // 存储分配结果
        std::map<BE::Register, int> assignedPhys;
        std::map<BE::Register, int> spillFrameIndex;

        // 为每个Interval分配寄存器
        for (auto* interval : intervals) {
            // 从活动集合中移除已结束的Interval
            while (!active.empty() && (*active.begin())->segs.back().end <= interval->segs[0].start) {
                Interval* finished = *active.begin();
                active.erase(active.begin());
                if (finished->physReg != -1) {
                    usedPhysRegs.erase(finished->physReg);
                }
            }
            
            // 尝试分配物理寄存器
            bool allocated = false;
            const std::vector<int>* allocatable = &orderedIntRegs;  // 只使用整数寄存器列表
            
            if (allocatable) {
                // 对于跨调用的区间，优先尝试被调用者保存寄存器
                if (interval->crossesCall) {
                    for (int physReg : *allocatable) {
                        bool isCalleeSaved = std::find(calleeSavedInt.begin(), calleeSavedInt.end(), physReg) != calleeSavedInt.end();
                        if (isCalleeSaved && !usedPhysRegs.count(physReg)) {
                            // 检查是否与其他活动Interval冲突
                            bool conflict = false;
                            for (auto* activeInt : active) {
                                if (activeInt->physReg == physReg) {
                                    conflict = true;
                                    break;
                                }
                            }
                            
                            if (!conflict) {
                                // 分配成功
                                interval->physReg = physReg;
                                assignedPhys[interval->vreg] = physReg;
                                usedPhysRegs.insert(physReg);
                                active.insert(interval);
                                allocated = true;
                                break;
                            }
                        }
                    }
                }
                
                // 如果没有分配到被调用者保存寄存器，或者不是跨调用区间，尝试所有寄存器
                if (!allocated) {
                    for (int physReg : *allocatable) {
                        // 检查该物理寄存器是否被使用
                        if (!usedPhysRegs.count(physReg)) {
                            // 检查是否与其他活动Interval冲突
                            bool conflict = false;
                            for (auto* activeInt : active) {
                                if (activeInt->physReg == physReg) {
                                    conflict = true;
                                    break;
                                }
                            }
                            
                            if (!conflict) {
                                // 分配成功
                                interval->physReg = physReg;
                                assignedPhys[interval->vreg] = physReg;
                                usedPhysRegs.insert(physReg);
                                active.insert(interval);
                                allocated = true;
                                break;
                            }
                        }
                    }
                }
            }
            
            if (!allocated) {
                // 需要溢出
                interval->spilled = true;
                
                // 选择溢出哪个Interval：活动集合中结束时间最晚的
                if (!active.empty()) {
                    auto* spillCandidate = *active.rbegin(); // 结束时间最晚的
                    if (spillCandidate->segs.back().end > interval->segs.back().end) {
                        // 溢出活动集合中的Interval
                        spillCandidate->spilled = true;
                        spillCandidate->physReg = -1;
                        assignedPhys.erase(spillCandidate->vreg);
                        usedPhysRegs.erase(spillCandidate->physReg);
                        active.erase(spillCandidate);
                        
                        // 重新尝试分配当前Interval
                        for (int physReg : *allocatable) {
                            if (!usedPhysRegs.count(physReg)) {
                                interval->physReg = physReg;
                                assignedPhys[interval->vreg] = physReg;
                                usedPhysRegs.insert(physReg);
                                active.insert(interval);
                                allocated = true;
                                break;
                            }
                        }
                        
                        // 为被溢出的Interval分配溢出槽
                        if (spillCandidate->spillSlot == -1) {
                            // 分配新的溢出槽
                            static int nextSpillSlot = 0;
                            spillCandidate->spillSlot = nextSpillSlot++;
                            spillFrameIndex[spillCandidate->vreg] = spillCandidate->spillSlot;
                        }
                    }
                }
                
                // 如果当前Interval仍然没有分配，分配溢出槽
                if (!allocated) {
                    if (interval->spillSlot == -1) {
                        static int nextSpillSlot = 0;
                        interval->spillSlot = nextSpillSlot++;
                        spillFrameIndex[interval->vreg] = interval->spillSlot;
                    }
                }
            }
        }

        // ============================================================================
        // 重写 MIR（插入 reload/spill，替换 use/def）
        // ============================================================================
        // 作用：将未分配物理寄存器的 use/def 改写为使用 scratch + FILoad/FIStore（由 Adapter 注入）。
        // 如何做：
        // - 对每条指令枚举 uses：若该 vreg 分配了物理寄存器，则直接替换；
        //   否则在指令前插入 reload 到一个 scratch，然后用 scratch 替换 use。
        // - 对每条指令枚举 defs：若分配了物理寄存器则直接替换；
        //   否则先将 def 写到一个 scratch，再在指令后插入 spill 到对应 FI。

        // 遍历所有基本块和指令，处理寄存器的替换和溢出
        for (auto& [bid, block] : func.blocks) {
            // 使用迭代器遍历，以便在需要时插入指令
            for (auto it = block->insts.begin(); it != block->insts.end(); ++it) {
                auto* inst = *it;
                
                // 获取指令的use和def寄存器
                std::vector<BE::Register> uses, defs;
                BE::Targeting::g_adapter->enumUses(inst, uses);
                BE::Targeting::g_adapter->enumDefs(inst, defs);
                
                // 处理use寄存器
                std::set<BE::Register> processedUses;  // 避免重复处理同一寄存器
                for (BE::Register vreg : uses) {
                    if (processedUses.count(vreg)) continue;
                    processedUses.insert(vreg);
                    
                    if (assignedPhys.count(vreg)) {
                        BE::Targeting::g_adapter->replaceUse(inst, vreg, assignedPhys[vreg]);
                    } else if (spillFrameIndex.count(vreg)) {
                        // 需要溢出，插入reload指令并使用临时物理寄存器
                        int spillSlot = spillFrameIndex[vreg];
                        
                        // 选择临时物理寄存器（跳过被调用者保存寄存器）
                        int tempReg = -1;
                        for (int reg : orderedIntRegs) {
                            bool isCalleeSaved = std::find(calleeSavedInt.begin(), calleeSavedInt.end(), reg) != calleeSavedInt.end();
                            if (!isCalleeSaved) {
                                tempReg = reg;
                                break;
                            }
                        }
                        
                        if (tempReg == -1 && !orderedIntRegs.empty()) {
                            tempReg = orderedIntRegs[0];
                        }
                        
                        if (tempReg != -1) {

                            BE::Targeting::g_adapter->insertReloadBefore(block, it, tempReg, spillSlot);

                            BE::Targeting::g_adapter->replaceUse(inst, vreg, tempReg);
                        }
                    } else {
                        // 虚拟寄存器既没有分配物理寄存器，也没有溢出
                        
                        int tempReg = -1;
                        for (int reg : orderedIntRegs) {
                            bool isCalleeSaved = std::find(calleeSavedInt.begin(), calleeSavedInt.end(), reg) != calleeSavedInt.end();
                            if (!isCalleeSaved) {
                                tempReg = reg;
                                break;
                            }
                        }
                        
                        if (tempReg != -1) {
                            BE::Targeting::g_adapter->replaceUse(inst, vreg, tempReg);
                        }
                    }
                }
                
                // 处理def寄存器
                std::set<BE::Register> processedDefs;  // 避免重复处理同一寄存器
                for (BE::Register vreg : defs) {
                    if (processedDefs.count(vreg)) continue;
                    processedDefs.insert(vreg);
                    
                    if (assignedPhys.count(vreg)) {
                        BE::Targeting::g_adapter->replaceDef(inst, vreg, assignedPhys[vreg]);
                    } else if (spillFrameIndex.count(vreg)) {
                        // 需要溢出，插入spill指令并使用临时物理寄存器
                        int spillSlot = spillFrameIndex[vreg];
                        
                        // 选择临时物理寄存器（跳过被调用者保存寄存器）
                        int tempReg = -1;
                        for (int reg : orderedIntRegs) {
                            bool isCalleeSaved = std::find(calleeSavedInt.begin(), calleeSavedInt.end(), reg) != calleeSavedInt.end();
                            if (!isCalleeSaved) {
                                tempReg = reg;
                                break;
                            }
                        }
                        
                        if (tempReg == -1 && !orderedIntRegs.empty()) {
                            tempReg = orderedIntRegs[0];
                        }
                        
                        if (tempReg != -1) {

                            BE::Targeting::g_adapter->replaceDef(inst, vreg, tempReg);

                            BE::Targeting::g_adapter->insertSpillAfter(block, it, tempReg, spillSlot);
                        }
                    } else {
                        // 虚拟寄存器既没有分配物理寄存器，也没有溢出
                        
                        int tempReg = -1;
                        for (int reg : orderedIntRegs) {
                            bool isCalleeSaved = std::find(calleeSavedInt.begin(), calleeSavedInt.end(), reg) != calleeSavedInt.end();
                            if (!isCalleeSaved) {
                                tempReg = reg;
                                break;
                            }
                        }
                        
                        if (tempReg != -1) {
                            BE::Targeting::g_adapter->replaceDef(inst, vreg, tempReg);
                        }
                    }
                }
            }
        }

        // 清理Interval内存
        for (auto& [reg, interval] : intervalsMap) {
            delete interval;
        }
    
    }
}  // namespace BE::RA