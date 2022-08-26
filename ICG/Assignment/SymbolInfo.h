#pragma once
#include<string>
#include<vector>
using namespace std;


class FunctionInfo{
    public:
    string returnType;
    vector<string> paramDataTypes;
    bool isDefined;
    FunctionInfo(string returnType,bool isDefined,vector<string> paramDataTypes=vector<string>()){
        this->returnType=returnType;
        this->isDefined=isDefined;
        this->paramDataTypes=paramDataTypes;
    }
};

class ArrayInfo{
    public:
    int size;
    ArrayInfo(int s){
        this->size=s;
    }  
};

class VariableInfo{
    public:
    string dataType;
    ArrayInfo * arrayInfo=NULL;
    int stackEntry;
    bool global=false;
    string tempName;
    bool isParameter=false;
    VariableInfo(string dataType,ArrayInfo * arrayInfo=NULL){
        this->dataType=dataType;
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
        FunctionInfo * functionInfo=NULL;
        VariableInfo * variableInfo=NULL;
        ~SymbolInfo(){
            delete functionInfo;
            delete variableInfo;
        }
};
