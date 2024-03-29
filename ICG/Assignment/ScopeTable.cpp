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
                fout<<current->variableInfo->dataType;
                if(current->variableInfo->arrayInfo!=NULL){
                    fout<<current->variableInfo->dataType<<" ARRAY,";
                }else{
                    fout<<",";
                }
                if(current->variableInfo->global==false){
                    fout<<" StackEntry: "<<current->variableInfo->stackEntry<<"]";
                }else{
                    fout<<" TempName: "<<current->variableInfo->tempName<<"]";
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

void ScopeTable::deleteAllTemporaryVariable(){
    for(int i=0;i<size;i++){
        SymbolInfo * current=table[i];
        while (current!=NULL){
            SymbolInfo * temp=current->next;
            // cout<<"scope here a\n";
            if(current->variableInfo!=NULL && current->variableInfo->global==false){
                // cout<<"scope here b\n";
                if(current->variableInfo->arrayInfo!=NULL){
                    // cout<<"scope here c\n";
                    for(int i=1;i<=current->variableInfo->arrayInfo->size;i++){
                        // cout<<"scope here d\n";
                        writeASM("POP AX");
                        --stackCount;
                    }
                    // cout<<"scope here e\n";
                }
                else{
                    // cout<<"scope here f\n";
                    if(current->variableInfo->isParameter==false){
                        // cout<<"scope here g\n";
                        --stackCount;
                        writeASM("POP AX");
                    }
                    // cout<<"scope here h\n";
                }
                // cout<<"scope here i\n";
            }
            // cout<<"scope here j\n";
            // delete current;
            // cout<<"scope here k\n";
            current=temp;
            // cout<<"scope here l\n";
        }
        // cout<<"scope here m\n";
    }
    // cout<<"scope here n\n";
}

ScopeTable::~ScopeTable(){
    for(int i=0;i<size;i++){
        SymbolInfo * current=table[i];
        while (current!=NULL){
            SymbolInfo * temp=current->next;
            // if(current->variableInfo!=NULL && current->variableInfo->global==false){
            //     if(current->variableInfo->arrayInfo!=NULL){
            //         for(int i=1;i<=current->variableInfo->arrayInfo->size;i++){
            //             writeASM("POP AX");
            //             --stackCount;
            //         }
            //     }
            //     else{
            //         if(current->variableInfo->isParameter==false){
            //             --stackCount;
            //             writeASM("POP AX");
            //         }
            //     }
            // }
            delete current;
            current=temp;
        }
    }
    delete [] table;
}

