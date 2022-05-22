#include"SymbolTable.h"
#include"SymbolInfo.h"
#include"ScopeTable.h"
#include<string>
using std::string;

SymbolTable::SymbolTable(){

}

void SymbolTable::enterScope(){
    if(currentScope==NULL){
        currentScope=new ScopeTable(7,std::to_string(++rootScopeID),NULL);
    }
    else{
        currentScope->incrementChildrenCount();
        string id=currentScope->getId()+"."+std::to_string(currentScope->getChildrenCount());
        ScopeTable * newScope=new ScopeTable(10,id,currentScope);
        currentScope=newScope;
    }
}

void SymbolTable::exitScope(){
    ScopeTable * prevScope=currentScope->getParent();
    delete currentScope;
    currentScope=prevScope;
}

bool SymbolTable::insert(string name,string type){
    return currentScope==NULL?false:currentScope->insert(name,type);
}

bool SymbolTable:: remove(string name){
    if(currentScope!=NULL)
        return currentScope->deleteSymbolInfo(name);
    return false;
}

SymbolInfo* SymbolTable::lookup(string name){
    ScopeTable * scope=currentScope;
    while(scope!=NULL){
        SymbolInfo * symbol=scope->lookup(name);
        if(symbol!=NULL)
            return symbol;
        scope=scope->getParent();
    };
    return NULL;
}

void SymbolTable::printCurrentScopeTable(){
    if(currentScope!=NULL)
        currentScope->print();
}

void SymbolTable::printAllScopeTable(){
    ScopeTable * scope=currentScope;
    while(scope!=NULL){
        scope->print();
        scope=scope->getParent();
    };
}

SymbolTable::~SymbolTable(){
    ScopeTable * scope=currentScope;
    while(scope!=NULL){
        ScopeTable * next=scope->getParent();
        delete scope;
        scope=next;
    };
}









