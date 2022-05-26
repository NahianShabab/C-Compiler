#include<iostream>
#include<string>
using namespace std;

unsigned long long sdbm64(string value){
    unsigned long long hash = 0;
    for(int i=0;i<value.length();i++)
        hash=value.at(i)+(hash<<6)+(hash<<16)-hash;
    return hash;
}

unsigned long sdbm32(string value){
    unsigned long  hash = 0;
    for(int i=0;i<value.length();i++)
        hash=value.at(i)+(hash<<6)+(hash<<16)-hash;
    return hash;
}

int main(){
    cout<<sdbm64("foo")<<endl;
    cout<<sdbm32("foo")<<endl;
    return 0;
}