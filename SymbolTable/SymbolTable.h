#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include"ScopeTable.h"
#include"SymbolInfo.h"
#include<string>
using std::string;

class SymbolTable{
    private:
        ScopeTable * currentScope=NULL;
        int rootScopeID=0;
    public:
        SymbolTable();
        void enterScope();
        void exitScope();
        bool insert(string name,string type);
        bool remove(string name);
        SymbolInfo * lookup(string name);
        void printCurrentScopeTable();
        void printAllScopeTable();
        ~SymbolTable();
};

#endif