#ifndef __FRONTEND_SYMBOL_SYMBOL_ENTRY_H__
#define __FRONTEND_SYMBOL_SYMBOL_ENTRY_H__

#include <string>
#include <unordered_map>

namespace FE::Sym
{
    class Entry
    {
        friend class EntryDeleter;

      private:
        static std::unordered_map<std::string, Entry*> entryMap; 
        static void                                    clear();

      public:
        static Entry* getEntry(std::string name);

      private:
        Entry(std::string name = "NULL");
        ~Entry() = default;
        std::string name;
        FE::AST::VarAttr* varAttr = nullptr;
      public:
        const std::string& getName();
        void               setVarAttr(FE::AST::VarAttr* attr) { varAttr = attr; }
        FE::AST::VarAttr*  getVarAttr() { return varAttr; }
    };

    class EntryDeleter
    {
      private:
        EntryDeleter();
        ~EntryDeleter();

      public:
        EntryDeleter(const EntryDeleter&)                   = delete;
        EntryDeleter&        operator=(const EntryDeleter&) = delete;
        static EntryDeleter& getInstance();
    };
}  // namespace FE::Sym

#endif  // __FRONTEND_SYMBOL_SYMBOL_ENTRY_H__
