#pragma once
#include<string>
#include<vector>
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