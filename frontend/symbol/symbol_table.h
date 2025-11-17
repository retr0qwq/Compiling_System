#ifndef __FRONTEND_SYMBOL_SYMBOL_TABLE_H__
#define __FRONTEND_SYMBOL_SYMBOL_TABLE_H__

#include <frontend/symbol/isymbol_table.h>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;
namespace FE::Sym
{
    class SymTable : public iSymTable<SymTable>
    {
        friend iSymTable<SymTable>;
        private:
        int scopeDepth = 0;
        vector<unordered_map<string, Entry*>> scopestack;

        public:
        void reset_impl();

        void              addSymbol_impl(Entry* entry, FE::AST::VarAttr& attr);
        FE::AST::VarAttr* getSymbol_impl(Entry* entry);
        void              enterScope_impl();
        void              exitScope_impl();

        bool isGlobalScope_impl();
        int  getScopeDepth_impl();
    };
}  // namespace FE::Sym

#endif  // __FRONTEND_SYMBOL_SYMBOL_TABLE_H__
