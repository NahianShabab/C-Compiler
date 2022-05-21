#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H

#include"SymbolInfo.h"
#include<string>
using std::string;

class ScopeTable{
    private:
        int size;
        SymbolInfo ** table;
        ScopeTable * parent=NULL;
        int childrenCount=0;
        string id;
        // int (*hashFunction)(string name);
        int hashFunction(string name);
    public:
        ScopeTable(int size,string id,ScopeTable * parent);
        bool insert(string name,string type);
        SymbolInfo * lookup(string name);
        bool deleteSymbolInfo(string name);
        void print();
        string getId();
        void incrementChildrenCount();
        int getChildrenCount();
        ScopeTable * getParent();
        ~ScopeTable();
};

#endif