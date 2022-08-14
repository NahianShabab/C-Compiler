#pragma once
#include<string>
#include<vector>


// class FunctionInfo{
//     public:
//         string returnType;
// }

class SymbolInfo{
    private:
        string name;
        string type;
    public:
        SymbolInfo(string name,string type);
        SymbolInfo * next=NULL;
        string getName();
        string getType();
};
