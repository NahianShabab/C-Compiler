#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
    ifstream fin("code.asm");
    string note;
    while(getline(fin,note)){
        cout<<note<<"\n";
    }
    return 0;
}