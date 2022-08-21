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
        bool insert(SymbolInfo * s);
        bool remove(string name);
        SymbolInfo * lookup(string name);
        void printCurrentScopeTable(ofstream & fout);
        void printAllScopeTable(ofstream & fout);
        bool isRootScope();
        void deleteAllTemporaryVariable();
        ~SymbolTable();
};