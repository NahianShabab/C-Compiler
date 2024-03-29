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

class Expression:public NonTerminal{
    public:
        bool forceInteger=false;
        vector<SymbolInfo *> symbols=vector<SymbolInfo *>();
        int stackEntry;
        // ~Expression(){
        //     for(SymbolInfo * s:symbols){
        //         if(s->functionInfo==NULL && s->variableInfo==NULL){
        //             delete s;
        //         }
        //     }
        // }
};

class Variable:public NonTerminal{
    public:
        SymbolInfo * symbol=NULL;
        // int elementNo; // if the variable is array, the element being addressed
};

class Argument:public NonTerminal{
    public:
        vector<string> dataTypes=vector<string>();
};

class While{
    public:
    string whileLabel;
    string nextLabel;
};

class If:public NonTerminal{
    public:
    string elseLabel;
    string nextLabel;
};

class For{
    public:
    string nextLabel;
    string checkLabel;
    string incrementLabel;
    string statementLabel;
};
