#pragma once
#include"ScopeTable.h"
#include"SymbolInfo.h"
#include<string>
using std::string;

class SymbolTable{
    private:
        ScopeTable * currentScope=NULL;
        int rootScopeID=0;
        int scopeTableSize;
    public:
        SymbolTable(int scopeTableSize);
        void enterScope();
        bool exitScope();
        bool insert(string name,string type);
        bool remove(string name);
        SymbolInfo * lookup(string name,string & scopeId,int & bucketNo,int & pos);
        void printCurrentScopeTable();
        void printAllScopeTable();
        ~SymbolTable();
};