#include<iostream>
#include<string>
#include"ScopeTable.h"
#include"SymbolInfo.h"
#include"SymbolTable.h"
using std::cout;
using std::cin;
using std::string;

int main(){
    SymbolTable st;
    bool running=true;
    while (running){
        string cmd;
        cin>>cmd;
        if(cmd=="exit"){
            running=false;
        }
        else if(cmd=="enterScope"){
            st.enterScope();
            cout<<"entered scope\n";
        }
        else if(cmd=="exitScope"){
            st.exitScope();
            cout<<"exited scope\n";
        }
        else if(cmd=="insert"){
            string name,type;
            cin>>name>>type;
            bool success=st.insert(name,type);
            cout<<(success?"inserted":"could not insert")<<"\n";
        }else if(cmd=="remove"){
            string name;
            cin>>name;
            bool success=st.remove(name);
            cout<<(success?"removed":"could not remove")<<"\n";
        }else if(cmd=="lookup"){
            string name;
            cin>>name;
            SymbolInfo * symbol=st.lookup(name);
            if(symbol!=NULL){
                cout<<"<"<<symbol->getName()<<","<<symbol->getType()<<">\n";
            }else
                cout<<"does not exist\n";
        }else if(cmd=="printCurrentScope"){
            st.printCurrentScopeTable();
        }else if(cmd=="printAllScope"){
            st.printAllScopeTable();
        }
    };
    return 0;
}