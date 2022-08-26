#pragma once
#include<fstream>
#include<string>
using namespace std;
void writeOptimizedCode(){
	ifstream fCodeIn("code.asm");
	ofstream fOptimized("optimized_code.asm");
    string currentLine;
	while(getline(fCodeIn,currentLine)){
        if(currentLine.length()>=7 && currentLine.substr(0,4)=="PUSH"){
            string nextLine;
            if(getline(fCodeIn,nextLine)){
                if(nextLine.length()>=6 && nextLine.substr(0,3)=="POP" && nextLine.substr(4,6)==currentLine.substr(5,7)){
                    ;
                }else{
                    fOptimized<<currentLine<<'\n';
                    fOptimized<<nextLine<<'\n';
                }
            }else{
                fOptimized<<currentLine<<'\n';
                break;
            }
        }else{
            fOptimized<<currentLine<<'\n';
        }
	}
    fCodeIn.close();
    fOptimized.close();
}