#include"ScopeTable.h"
#include"SymbolInfo.h"
#include<string>
using std::string;

ScopeTable::ScopeTable(int size){
    this->size=size;
    table=new  SymbolInfo*[size];
    for(int i=0;i<size;i++)
        table[i]=NULL;
}

int ScopeTable::hashFunction(string name){
    return name.length()%this->size;
}

bool ScopeTable::insert(string name,string type){
    int idx=hashFunction(name);
    SymbolInfo * current=table[idx];
    while (current!=NULL)
    {
        if(current->getName()==name)
            return false;
        current=current->next;
    }
    SymbolInfo * n=new SymbolInfo(name,type);
    n->next=table[idx];
    table[idx]=n;
    return true;
}

SymbolInfo* ScopeTable::lookup(string name){
    int idx=hashFunction(name);
    SymbolInfo * current=table[idx];
    while(current!=NULL){
        if(current->getName()==name)
            return current;
        current=current->next;
    }
    return NULL;
}

bool ScopeTable::deleteSymbolInfo(string name){
    int idx=hashFunction(name);
    SymbolInfo * current=table[idx];
    SymbolInfo * prev=table[idx];
    while (current!=NULL){
        if(current->getName()==name){
            if(current==table[idx])
                table[idx]=current->next;
            else
                prev->next=current->next;
            delete current;
            return true;
        }
        prev=current;
        current=current->next;
    }
    return false;
}

ScopeTable::~ScopeTable(){
    for(int i=0;i<size;i++){
        SymbolInfo * current=table[i];
        while (current!=NULL){
            SymbolInfo * temp=current->next;
            delete current;
            current=temp;
        }
    }
    delete [] table;
}

