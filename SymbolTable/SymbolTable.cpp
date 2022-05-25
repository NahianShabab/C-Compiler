#include"SymbolTable.h"
#include"SymbolInfo.h"
#include"ScopeTable.h"
#include<string>
#include<iostream>
using std::string;
using std::cout;

SymbolTable::SymbolTable(int scopeTableSize){
    this->scopeTableSize=scopeTableSize;
    enterScope();
}

void SymbolTable::enterScope(){
    if(currentScope==NULL){
        currentScope=new ScopeTable(scopeTableSize,std::to_string(++rootScopeID),NULL);
    }
    else{
        currentScope->incrementChildrenCount();
        string id=currentScope->getId()+"."+std::to_string(currentScope->getChildrenCount());
        ScopeTable * newScope=new ScopeTable(scopeTableSize,id,currentScope);
        currentScope=newScope;
    }
    cout<<"New ScopeTable with id "<<currentScope->getId()<<" created\n";
}

bool SymbolTable::exitScope(){
    if(currentScope!=NULL){
        cout<<"ScopeTable with id "<<currentScope->getId()<<" removed\n";
        ScopeTable * prevScope=currentScope->getParent();
        delete currentScope;
        currentScope=prevScope;
        return true;
    }
    return false;
}

bool SymbolTable::insert(string name,string type){
    return currentScope==NULL?false:currentScope->insert(name,type);
}

bool SymbolTable:: remove(string name){
    if(currentScope!=NULL)
        return currentScope->deleteSymbolInfo(name);
    return false;
}
/* scopeId,bucketNo and pos are the location of the searched symbol if found*/
SymbolInfo* SymbolTable::lookup(string name,string & scopeId,int & bucketNo,int & pos){
    ScopeTable * scope=currentScope;
    while(scope!=NULL){
        SymbolInfo * symbol=scope->lookup(name,bucketNo,pos);
        if(symbol!=NULL){
            scopeId=scope->getId();
            return symbol;
        }
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









