#include<iostream>
#include<string>
#include"ScopeTable.h"
#include"SymbolInfo.h"
using std::cout;
using std::string;

int main(){
    ScopeTable st(10);
    st.insert("a","identifier");
    st.insert("printf","function");

    SymbolInfo * s=st.lookup("printf");
    cout<<"name: "<<s->getName()<<", type: "<<s->getType();
    return 0;
}