%option noyywrap
%option yylineno

%{
/*dependencies */
#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
#include"util.h"
#include"SymbolTable.h"
#include"y.tab.h"
using namespace std;

extern YYSTYPE yylval;
extern SymbolTable * table;
extern void yyerror(const char *);



/* functions and variables of scanner*/

// ofstream fLog("log.txt");
// ofstream fToken("token.txt");
// string character="";
// string rawCharacter="";
// string stringLiteral="";
// string rawStringLiteral="";
// string comment="";
int startLine=0;
// SymbolTable symbolTable(7);
int errorCount=0;
// void logToken(string token,string lexeme="",int lineNo=yylineno){
//     fLog<<"Line no "<<lineNo<<": Token <"<<token<<"> Lexeme "<<lexeme<<" found\n\n";
// }
// void logTokenString(string token,string lexeme,string insertedLexime,int lineNo){
//     fLog<<"Line no "<<lineNo<<": Token <"<<token<<"> Lexeme "<<lexeme<<" found --> <"<<token<<","<<insertedLexime<<">\n\n";    
// }
// void logError(string errorMsg,int lineNo=yylineno){
//         fLog<<"Error at line no "<<lineNo<<": "<<errorMsg<<"\n\n";
//         errorCount++;
// }
// void writeToken(string type,string symbol=""){
//     fToken<<'<'<<type<<(symbol==""?">":(","+symbol+">"));
// }
%}
 
Identifier [a-zA-Z_][a-zA-Z_0-9]*
Float ([0-9]+[.][0-9]*(E(\+|-)?[0-9]+)?)|([0-9]*[.][0-9]+(E(\+|-)?[0-9]+)?)|([0-9]+E(\+|-)?[0-9]+)
Integer [0-9]+
SpecialCharacter (\\n)|(\\t)|(\\\\)|(\\')|(\\a)|(\\f)|(\\r)|(\\b)|(\\v)|(\\0)|(\\\")

%%
[ \t\v]+ {}
\n {}

if {return IF;}   
for {return FOR;}
int {return INT;}
float {return FLOAT;}
void {return VOID;}
else {return ELSE;}
while {return WHILE;}
return {return RETURN;}
printf {return PRINTLN;}



{Identifier} {
        // logToken("ID",yytext);
        // writeToken("ID",yytext);
        // if(symbolTable.insert(yytext,"ID")){
        //         symbolTable.printAllScopeTable(fLog);
        // }
        // else{
        //         fLog<<yytext<<" already exists in current ScopeTable\n\n";
        // }
        return ID;
}

[\+|-] {
        return ADDOP;
}

[*/%] {return MULOP;

}

\+\+ {return INCOP;}

(!=)|(==)|(<=)|<|(>=)|> {
        return RELOP;
}

= {
        return ASSIGNOP;
}

&&|(\|\|) {
        return LOGICOP;
}

! {
        return NOT;
}

\( {
        return LPAREN;
}

\) {
        return RPAREN; 
}

\{ {
        return LCURL;
        // symbolTable.enterScope();
}

\} {
        return RCURL;
        // symbolTable.exitScope();
}

\[ {
        return LTHIRD;
}
\] {
        return RTHIRD;
}

, {
        return COMMA;
}

; {
        return SEMICOLON;
}

[.] {   
        //error
        // logError("Single Dot");
}

[0-9]*[.]([0-9]*[.][0-9]*)+ {
        // logError("Too many decimal points "+string(yytext));
}

([0-9]+.[0-9]*|[0-9]*[.][0-9]+|[0-9]+)E(\+|-)?([0-9]*[.][0-9]*)+ {
        // logError("Ill formed number "+string(yytext));
}

{Float} {
        // if(symbolTable.insert(yytext,"CONST_FLOAT")){
        //         symbolTable.printAllScopeTable(fLog);
        // }
        // else{
        //         fLog<<yytext<<" already exists in current ScopeTable\n\n";
        // }
        return CONST_FLOAT;
}

{Integer}{Identifier} {
        // logError("Invalid prefix on ID or invalid suffix on Number "+string(yytext));
}

{Integer} {
        // if(symbolTable.insert(yytext,"CONST_INT")){
        //         symbolTable.printAllScopeTable(fLog);
        // }
        // else{
        //         fLog<<yytext<<" already exists in current ScopeTable\n\n";
        // }
        return CONST_INT;
}


.   {
        //error unknown character
        // logError("Unrecognized character : "+string(yytext));

    }
%%

// int main(int argc,char * argv[]){
// 	if(argc!=2){
// 		cout<<"Enter a input file in command line\n";
// 		return -1;
// 	}
// 	FILE * fin=fopen(argv[1],"r");
// 	yyin=fin;
// 	yylex();
// 	fclose(yyin);

//         symbolTable.printAllScopeTable(fLog);
//         fLog<<"\n";
//         fLog<<"Total lines: "<<yylineno<<"\n";
//         fLog<<"Total errors: "<<errorCount<<"\n";
        

// 	fLog.close();
// 	fToken.close();
// 	return 0;
// }
