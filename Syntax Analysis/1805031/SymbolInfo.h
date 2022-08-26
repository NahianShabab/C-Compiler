#pragma once
#include<string>
#include<vector>
using namespace std;


class FunctionInfo{
    public:
        bool isDefined;
        string returnType;
        vector<string> dataTypes;
        vector<string> names;
        FunctionInfo(bool isDefined=true){
            returnType="";
            dataTypes=vector<string>();
            names=vector<string>();
            this->isDefined=isDefined;
        }
};

class ArrayInfo{
    public:
        int size;
    ArrayInfo(int size){
        this->size=size;
    }
};

class VariableInfo{
    public:
        string dataType;
        ArrayInfo * arrayInfo=NULL;
        VariableInfo(string dType,ArrayInfo * arrayInfo=NULL){
            dataType=dType;
            this->arrayInfo=arrayInfo;
        }
        ~VariableInfo(){
            delete arrayInfo;
        }
};



class SymbolInfo{
    private:
        string name;
        string type;
    public:
        SymbolInfo(string name,string type);
        SymbolInfo * next=NULL;
        string getName();
        string getType();
        FunctionInfo * functionInfo;
        VariableInfo * variableInfo;
        ~SymbolInfo();
};
