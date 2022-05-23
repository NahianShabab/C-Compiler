#include<iostream>
#include<string>
#include"ScopeTable.h"
#include"SymbolInfo.h"
#include"SymbolTable.h"
using std::cout;
using std::cin;
using std::string;

int main(){
    SymbolTable st(7);
    bool running=true;
    while (running){
        string cmd;
        cin>>cmd;
        if(cmd=="exit"){
            running=false;
        }
        else if(cmd=="S"){
            st.enterScope();
            cout<<"entered scope\n";
        }
        else if(cmd=="E"){
            bool done=st.exitScope();
            if(done)
                cout<<"exited scope\n";
            else
                cout<<"scope stack is empty\n";
        }
        else if(cmd=="I"){
            string name,type;
            cin>>name>>type;
            bool success=st.insert(name,type);
            cout<<(success?"inserted":"could not insert")<<"\n";
        }else if(cmd=="D"){
            string name;
            cin>>name;
            bool success=st.remove(name);
            cout<<(success?"removed":"could not remove")<<"\n";
        }else if(cmd=="L"){
            string name;
            cin>>name;
            SymbolInfo * symbol=st.lookup(name);
            if(symbol!=NULL){
                cout<<"<"<<symbol->getName()<<","<<symbol->getType()<<">\n";
            }else
                cout<<"does not exist\n";
        }else if(cmd=="PC"){
            st.printCurrentScopeTable();
        }else if(cmd=="PA"){
            st.printAllScopeTable();
        }
    };
    return 0;
}