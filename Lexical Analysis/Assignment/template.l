%option noyywrap yylineno

/*
following is where include files and declare variables
*/
%{
#include<iostream>
#include<stdio.h>
#include<fstream>
using std::cout;
using std::ofstream;
ofstream fLog("log.txt");
ofstream fToken("token.txt");
%}

%%
[ \t\v]+ {}
. {fToken<<yytext<<"\n";}
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
