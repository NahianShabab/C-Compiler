#pragma once

#include"SymbolInfo.h"
#include<string>
#include<fstream>
using std::ofstream;
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
        unsigned long sdbm(string str);
    public:
        ScopeTable(int size,string id,ScopeTable * parent);
        bool insert(SymbolInfo * s);
        SymbolInfo * lookup(string name,int & bucketNo,int & position);
        bool deleteSymbolInfo(string name);
        void print(ofstream & fout);
        string getId();
        void incrementChildrenCount();
        int getChildrenCount();
        ScopeTable * getParent();
        ~ScopeTable();
};
