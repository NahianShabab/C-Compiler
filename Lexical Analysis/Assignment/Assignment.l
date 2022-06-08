%option noyywrap

/*
following is where include files and declare variables
*/
%{
#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
using std::cout;
using std::ofstream;
using std::string;
ofstream fLog("log.txt");
ofstream fToken("token.txt");
int lineCount=1;
void logToken(string token,string lexeme=""){
    fLog<<"Line No. "<<lineCount<<": Token "<<token<<" Lexeme "<<lexeme<<" found\n";
}
void writeToken(string type,string symbol=""){
    fToken<<'<'<<type<<(symbol==""?">":(","+symbol+">"));
}
%}

%%
[ \t\v]+ {}
\n {++lineCount;}
if {
        logToken("IF","if");
        writeToken("IF");
   }   
for {
        logToken("FOR","for");
        writeToken("FOR");
    }
do {
        logToken("DO","do");
        writeToken("DO");
   }
int {
        logToken("INT","int");
        writeToken("INT"); 
    }
float {
        logToken("FLOAT","float");
        writeToken("FLOAT");
    }
void {
        logToken("VOID","void");
        writeToken("VOID");
    }
switch {
        logToken("SWITCH","switch");
        writeToken("SWITCH");
    }
default {
        logToken("DEFAULT","default");
        writeToken("DEFAULT");
    }
else {
        logToken("ELSE","else");
        writeToken("ELSE");
}
while {
        logToken("WHILE","while");
        writeToken("WHILE");
}
break {
        logToken("BREAK","break");
        writeToken("BREAK");
}
char {
        logToken("CHAR","char");
        writeToken("CHAR");
}
double {
        logToken("DOUBLE","double");
        writeToken("DOUBLE");
}
return {
        logToken("RETURN","return");
        writeToken("RETURN");
}
case {
        logToken("CASE","case");
        writeToken("CASE");
}
continue {
        logToken("CONTINUE","continue");
        writeToken("CONTINUE"); 
}



(\+|-)[1-9][0-9]* {
    string lexeme=string(yytext).substr(1);
    logToken("CONST_INT",lexeme);
    writeToken("CONST_INT",lexeme);    
}


.   {

    }
%%

int main(int argc,char * argv[]){
	if(argc!=2){
		cout<<"Enter a input file in command line\n";
		return -1;
	}
	FILE * fin=fopen(argv[1],"r");
	yyin=fin;
	yylex();
	fclose(yyin);
	fLog.close();
	fToken.close();
	return 0;
}
