#pragma once
#include<string>
using std::string;

class SymbolInfo{
    private:
        string name;
        string type;
    public:
        SymbolInfo(string name,string type);
        SymbolInfo * next=NULL;
        string getName();
        string getType();
};
