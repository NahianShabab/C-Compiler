#include<iostream>
#include<string>
#include"ScopeTable.h"
#include"SymbolInfo.h"
#include"SymbolTable.h"
#include<fstream>
using std::cout;
using std::string;
using std::ifstream;

int main(){
    ifstream fin("input.txt");
    int n;
    fin>>n;
    SymbolTable st(n);
    bool running=true;
    while (running && !fin.eof()){
        string cmd;
        fin>>cmd;
        if(cmd=="exit"){
            running=false;
        }
        else if(cmd=="S"){
            st.enterScope();
        }
        else if(cmd=="E"){
            bool done=st.exitScope();
            if(!done)
                cout<<"Scope Stack is empty\n";
        }
        else if(cmd=="I"){
            string name,type;
            fin>>name>>type;
            bool success=st.insert(name,type);
        }else if(cmd=="D"){
            string name;
            fin>>name;
            bool success=st.remove(name);
        }else if(cmd=="L"){
            string name;
            fin>>name;
            string scopeID;
            int bucketNo,pos;
            SymbolInfo * symbol=st.lookup(name,scopeID,bucketNo,pos);
            if(symbol!=NULL){
                cout<<"Found in ScopeTable # "<<scopeID<<" at position "<<bucketNo<<", "<<pos<<"\n";
            }else
                cout<<name<<" not found\n";
        }else if(cmd=="P"){
            string next;
            fin>>next;
            if(next=="C")
                st.printCurrentScopeTable();
            else if(next=="A")
                st.printAllScopeTable();
        }
    };
    fin.close();
    return 0;
}