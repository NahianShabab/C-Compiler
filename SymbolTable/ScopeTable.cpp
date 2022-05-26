#include"ScopeTable.h"
#include"SymbolInfo.h"
#include<string>
#include<iostream>
using std::string;
using std::cout;

ScopeTable::ScopeTable(int size,string id,ScopeTable * parent=NULL){
    this->size=size;
    table=new  SymbolInfo*[size];
    for(int i=0;i<size;i++)
        table[i]=NULL;
    this->parent=parent;
    this->id=id;
}

int ScopeTable::hashFunction(string name){
    return sdbm(name)%size;
}
unsigned long ScopeTable::sdbm(string value){
    unsigned long  hash = 0;
    for(int i=0;i<value.length();i++)
        hash=value.at(i)+(hash<<6)+(hash<<16)-hash;
    return hash;
}

bool ScopeTable::insert(string name,string type){
    int idx=hashFunction(name);
    SymbolInfo * current=table[idx];
    while (current!=NULL)
    {
        if(current->getName()==name){
            return false;
        }
        current=current->next;
    }
    SymbolInfo * n=new SymbolInfo(name,type);
    n->next=table[idx];
    table[idx]=n;
    cout<<"Inserted in ScopeTable# "<<id<<" at position: "<<idx<<", 0\n";
    return true;
}

SymbolInfo* ScopeTable::lookup(string name,int & bucketNo,int & pos){
    int idx=hashFunction(name);
    SymbolInfo * current=table[idx];
    bucketNo=idx;
    pos=0;
    while(current!=NULL){
        if(current->getName()==name)
            return current;
        current=current->next;
        pos++;
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

string ScopeTable::getId(){return id;}

void ScopeTable::incrementChildrenCount(){
    childrenCount++;
}
int ScopeTable:: getChildrenCount(){
    return childrenCount;
}
ScopeTable * ScopeTable::getParent(){
    return parent;
}

void ScopeTable::print(){
    cout<<"\n";
    cout<<"----------------------------------------------------------------\n";
    cout<<"ScopeTable # "<<id<<"\n";
    cout<<"----------------------------------------------------------------\n";
    for(int i=0;i<size;i++){
        cout<<"["<<i<<"]: ";
        SymbolInfo * current=table[i];
        while (current!=NULL){
            cout<<"<"<<current->getName()<<","<<current->getType()<<">, ";
            current=current->next;
        }
        cout<<"\n";
    }
    cout<<"----------------------------------------------------------------\n";
    cout<<"\n";
}

ScopeTable::~ScopeTable(){
    // cout<<"destructor for id: "<<id<<" called\n";
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

