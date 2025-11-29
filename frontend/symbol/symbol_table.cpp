#include <frontend/symbol/symbol_table.h>
#include <debug.h>

namespace FE::Sym
{
    void SymTable::reset_impl() { 
        //TODO("Lab3-1: Reset symbol table"); 
        scopestack.clear();
        scopeDepth = -1;
    }

    void SymTable::enterScope_impl() { 
        //TODO("Lab3-1: Enter new scope");
        scopestack.push_back(unordered_map<Entry*,FE::AST::VarAttr*>());
        scopeDepth++;
     }

    void SymTable::exitScope_impl() { 
        //TODO("Lab3-1: Exit current scope");
        if (scopeDepth > -1) {
            scopestack.pop_back();
            scopeDepth--;
        }
    }

    void SymTable::addSymbol_impl(Entry* entry, FE::AST::VarAttr* attr)
    {
        //TODO("Lab3-1: Add symbol to current scope");
        auto& currentScope = scopestack.back();
        if(currentScope.find(entry) != currentScope.end()) {
            throw runtime_error("Symbol" + entry->getName() + "already exists in the current scope: ");
        }
        currentScope[entry] = attr;
    }

    FE::AST::VarAttr* SymTable::getSymbol_impl(Entry* entry)
    {
        //TODO("Lab3-1: Get symbol from symbol table");
        for (auto it = scopestack.rbegin(); it != scopestack.rend(); ++it) {
        auto search = it->find(entry);
        if (search != it->end()) {
                    return search->second;
        }
    }
    return nullptr;
    }

    bool SymTable::isGlobalScope_impl() { 
        //TODO("Lab3-1: Check if current scope is global scope"); 
        return scopeDepth == 0;}

    int SymTable::getScopeDepth_impl() { 
        //TODO("Lab3-1: Get current scope depth"); 
        return scopeDepth;
    }
}  // namespace FE::Sym
