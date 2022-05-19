#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H

#include"SymbolInfo.h"
#include<string>
using std::string;

class ScopeTable{
    private:
        int size;
        SymbolInfo ** table;
        // int (*hashFunction)(string name);
        int hashFunction(string name);
    public:
        ScopeTable(int size);
        bool insert(string name,string type);
        SymbolInfo * lookup(string name);
        bool deleteSymbolInfo(string name);
        void print();
        ~ScopeTable();
};

#endif