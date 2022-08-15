#pragma once
#include<string>
#include<vector>
#include"SymbolInfo.h"
using namespace std;

class NonTerminal{
    public:
        string text;
        NonTerminal(){
            text=string();
        }
};

class Parameter:public NonTerminal{
    public:
        vector<string> dataTypes=vector<string>();
        vector<string> names=vector<string>(); 
};

class DeclarationList:public NonTerminal{
    public:
        vector<SymbolInfo *> symbols=vector<SymbolInfo *>();
};