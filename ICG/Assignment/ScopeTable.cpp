#include"ScopeTable.h"
#include"SymbolInfo.h"
#include<string>
#include<iostream>
#include<fstream>
using std::string;
using std::cout;
using std::ofstream;
extern void writeASM(string);
extern int stackCount;
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

bool ScopeTable::insert(SymbolInfo * s){
    if(s==NULL)
        return false;
    int idx=hashFunction(s->getName());
    SymbolInfo * current=table[idx];
    while (current!=NULL)
    { 
        if(current->getName()==s->getName()){
            // cout<<name<<" already exists in current Scopetable\n";
            return false;
        }
        current=current->next;
    }
    s->next=table[idx];
    table[idx]=s;
    // cout<<"Inserted in ScopeTable# "<<id<<" at position: "<<idx<<", 0\n";
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
    int pos=0;
    while (current!=NULL){
        if(current->getName()==name){
            if(current==table[idx])
                table[idx]=current->next;
            else
                prev->next=current->next;
            delete current;
            // cout<<"Deleted Entry "<<idx<<" , "<<pos<<" from current Scopetable"<<"\n";
            return true;
        }
        prev=current;
        current=current->next;
        pos++;
    }
    // cout<<name<<" not found in current Scope table\n";
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

void ScopeTable::print(ofstream & fout){
    // cout<<"\n";
    // cout<<"----------------------------------------------------------------\n";
    fout<<"ScopeTable # "<<id<<endl;
    // cout<<"----------------------------------------------------------------\n";
    for(int i=0;i<size;i++){
        SymbolInfo * current=table[i];
        bool printNewLine=false;
        if(current!=NULL){
            fout<<i<<" --> ";
            printNewLine=true;
        }
        while (current!=NULL){
            fout<<" ["<<current->getName()<<" : ";
            if(current->functionInfo!=NULL){
                fout<<"FUNCTION,"<<"RETURNS "<<current->functionInfo->returnType<<"] ";
            }else if(current->variableInfo!=NULL){
                fout<<"VARIABLE,";
                if(current->variableInfo->arrayInfo!=NULL){
                    fout<<current->variableInfo->dataType<<" ARRAY] ";
                }else{
                    fout<<current->variableInfo->dataType<<", StackEntry: "<<current->variableInfo->stackEntry<<"] ";
                }
            }else{
                fout<<"OTHER] ";
            }
            current=current->next;
        }
        if(printNewLine)
            fout<<endl;
    }
    // cout<<"----------------------------------------------------------------\n";
    fout<<endl;
}

ScopeTable::~ScopeTable(){
    for(int i=0;i<size;i++){
        SymbolInfo * current=table[i];
        while (current!=NULL){
            SymbolInfo * temp=current->next;
            if(current->variableInfo!=NULL){
                --stackCount;
                writeASM("POP AX");
            }
            delete current;
            current=temp;
        }
    }
    delete [] table;
}

