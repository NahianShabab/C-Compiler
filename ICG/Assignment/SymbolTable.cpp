#include"SymbolTable.h"
#include"SymbolInfo.h"
#include"ScopeTable.h"
#include<string>
#include<iostream>
#include<fstream>
using std::ofstream;
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
    // cout<<"New ScopeTable with id "<<currentScope->getId()<<" created\n";
}

bool SymbolTable::isRootScope(){
    return currentScope==NULL?false:currentScope->getParent()==NULL;
}
void SymbolTable::deleteAllTemporaryVariable(){
    try{
    if(currentScope!=NULL){
        currentScope->deleteAllTemporaryVariable();
    }
    }catch(std::length_error e){
        cout<<e.what();
    }
}

bool SymbolTable::exitScope(){
    if(isRootScope()){
        return false;
    }
    if(currentScope!=NULL){
        // cout<<"ScopeTable with id "<<currentScope->getId()<<" removed\n";
        ScopeTable * prevScope=currentScope->getParent();
        delete currentScope;
        currentScope=prevScope;
        return true;
    }
    return false;
}

bool SymbolTable::insert(SymbolInfo * s){
    if(currentScope==NULL)
        enterScope();
    return currentScope->insert(s);
}

bool SymbolTable:: remove(string name){
    if(currentScope!=NULL)
        return currentScope->deleteSymbolInfo(name);
    return false;
}
/* scopeId,bucketNo and pos are the location of the searched symbol if found*/
SymbolInfo* SymbolTable::lookup(string name){
    ScopeTable * scope=currentScope;
    while(scope!=NULL){
        SymbolInfo * symbol=scope->lookup(name);
        if(symbol!=NULL){
            return symbol;
        }
        scope=scope->getParent();
    };
    return NULL;
}

void SymbolTable::printCurrentScopeTable(ofstream & fout){
    if(currentScope!=NULL)
        currentScope->print(fout);
}

void SymbolTable::printAllScopeTable(ofstream & fout){
    ScopeTable * scope=currentScope;
    while(scope!=NULL){
        scope->print(fout);
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









