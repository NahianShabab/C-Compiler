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
class ParameterList : public NonTerminal{
    public:
        vector<string> dataTypes;
        vector<string> names;
        ParameterList():NonTerminal(){
            dataTypes=vector<string>();
            names=vector<string>();
        }
};

class DeclarationList:public NonTerminal{
    public:
        vector<SymbolInfo *> symbols;
        DeclarationList(){
            symbols=vector<SymbolInfo*>();
        }
};

class Expression: public NonTerminal{
    public:
        vector<SymbolInfo *> symbols;
        Expression(){
            symbols=vector<SymbolInfo*>();
        }
};
class Argument:public NonTerminal{
    public:
        vector<string> dataTypes;
        Argument(){
            dataTypes=vector<string>();
        }
};
class Variable:public NonTerminal{
    public:
        string name="";
};