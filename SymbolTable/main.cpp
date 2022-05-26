#include<iostream>
#include<string>
#include"ScopeTable.h"
#include"SymbolInfo.h"
#include"SymbolTable.h"
using std::cout;
using std::cin;
using std::string;

int main(){
    int n;
    cin>>n;
    SymbolTable st(n);
    bool running=true;
    while (running){
        string cmd;
        cin>>cmd;
        if(cmd=="exit"){
            running=false;
        }
        else if(cmd=="S"){
            st.enterScope();
            // cout<<"entered scope\n";
        }
        else if(cmd=="E"){
            bool done=st.exitScope();
            if(!done)
                cout<<"Scope Stack is empty\n";
        }
        else if(cmd=="I"){
            string name,type;
            cin>>name>>type;
            bool success=st.insert(name,type);
            // cout<<(success?"inserted":"could not insert")<<"\n";
            if(!success)
                cout<<"could not insert\n";
        }else if(cmd=="D"){
            string name;
            cin>>name;
            bool success=st.remove(name);
            cout<<(success?"removed":"could not remove")<<"\n";
        }else if(cmd=="L"){
            string name;
            cin>>name;
            string scopeID;
            int bucketNo,pos;
            SymbolInfo * symbol=st.lookup(name,scopeID,bucketNo,pos);
            if(symbol!=NULL){
                // cout<<"<"<<symbol->getName()<<","<<symbol->getType()<<">\n";
                cout<<"Found in ScopeTable # "<<scopeID<<" at position "<<bucketNo<<", "<<pos<<"\n";
            }else
                cout<<"Not Found\n";
        }else if(cmd=="P"){
            string next;
            cin>>next;
            if(next=="C")
                st.printCurrentScopeTable();
            else if(next=="A")
                st.printAllScopeTable();
        }
    };
    return 0;
}