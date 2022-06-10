%option noyywrap

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

%x STATE1
%x STATE2

%%
[ \t\v]+ {}
a {BEGIN STATE1;}
<STATE1>b {BEGIN STATE2;}
<STATE1>. {BEGIN INITIAL;}
<STATE2>c {cout<<"Found abc! \n";BEGIN INITIAL;}
<STATE2>. {BEGIN INITIAL;}
. {}
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
