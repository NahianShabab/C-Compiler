#include"SymbolInfo.h"
#include<string>
using std::string;

SymbolInfo::SymbolInfo(string name,string type){
    this->name=name;
    this->type=type;
    this->functionInfo=NULL;
    this->variableInfo=NULL;
}

string SymbolInfo::getName(){return name;}

string SymbolInfo::getType(){return type;}

SymbolInfo::~SymbolInfo(){
    delete functionInfo;
    delete variableInfo;
}