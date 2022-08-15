%option noyywrap
%option yylineno

/*
following is where include files and declare variables
*/
%{
#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
#include"util.h"
#include"SymbolTable.h"
#include"SymbolInfo.h"
#include"NonTerminal.h"
#include"y.tab.h"
using  namespace std;

extern YYSTYPE yylval;
extern SymbolTable * table;
extern ofstream fLog;
extern Parameter * currentParameterList;
extern void yyerror(const char *);
extern void yyerror(string);

string comment="";

int startLine=0; 
%}

%x COMMENT_SINGLE
%x COMMENT_MULTIPLE
 
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
        yylval.symbol=new SymbolInfo(yytext,"ID");
        return ID;
}

\/\/ {  
        comment="//";
        startLine=yylineno;
        BEGIN COMMENT_SINGLE;
}
<COMMENT_SINGLE>(\\[\n]) {
        comment.append(yytext);
}
<COMMENT_SINGLE>[^\n] {
        comment.append(yytext);
}
<COMMENT_SINGLE>[\n] {
        BEGIN INITIAL;
}
<COMMENT_SINGLE><<EOF>> {
        BEGIN INITIAL;
}

\/\* {
        comment="/*";
        startLine=yylineno;
        BEGIN COMMENT_MULTIPLE;
}
<COMMENT_MULTIPLE>\*\/ {
        comment.append("*/");
        BEGIN INITIAL;
}
<COMMENT_MULTIPLE><<EOF>> {
        yyerror("Unterminated Comment "+comment);
        BEGIN INITIAL;
}
<COMMENT_MULTIPLE>.|[\n] {
        comment.append(yytext);
}

[\+|-] {
        yylval.symbol=new SymbolInfo(yytext,"ADDOP");
        return ADDOP;
}

[*/%] {
        yylval.symbol=new SymbolInfo(yytext,"MULOP");
        return MULOP;

}

\+\+ {return INCOP;}
-- {return DECOP;}

(!=)|(==)|(<=)|<|(>=)|> {
        yylval.symbol=new SymbolInfo(yytext,"RELOP");
        return RELOP;
}

= {
        return ASSIGNOP;
}

&&|(\|\|) {
        yylval.symbol=new SymbolInfo(yytext,"LOGICOP");
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
        table->enterScope();
        if(currentParameterList!=NULL){
            //insert parameters here
            for(int i=0;i<currentParameterList->dataTypes.size();i++){
                if(currentParameterList->dataTypes.at(i)=="void"){
                        yyerror("void data type at parameter no "+to_string(i));
                        continue;
                }
                if(currentParameterList->names.at(i)==""){
                        continue;
                }
                SymbolInfo * s=new SymbolInfo(currentParameterList->names.at(i),"ID");
                s->variableInfo=new VariableInfo(currentParameterList->dataTypes.at(i));
                if(table->insert(s)==false){
                        yyerror("Multiple Declaration of "+s->getName());
                }
            }
        }
        table->printAllScopeTable(fLog);
        return LCURL;
}

\} {
        if(table->isRootScope()){
                yyerror("Invalid Scope");
        }else{
                table->printCurrentScopeTable(fLog);
                table->exitScope();
        }
        return RCURL;
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
        yyerror("Single Dot");
}

[0-9]*[.]([0-9]*[.][0-9]*)+ {
        yyerror("Too many decimal points "+string(yytext));
}

([0-9]+.[0-9]*|[0-9]*[.][0-9]+|[0-9]+)E(\+|-)?([0-9]*[.][0-9]*)+ {
        yyerror("Ill formed number "+string(yytext));
}

{Float} {
        yylval.symbol=new SymbolInfo(yytext,"CONST_FLOAT");
        return CONST_FLOAT;
}

{Integer}{Identifier} {
        string err="Invalid prefix on ID or invalid suffix on Number "+string(yytext);
        yyerror(err.c_str());
}

{Integer} {
        yylval.symbol=new SymbolInfo(yytext,"CONST_INT");
        return CONST_INT;
}

.  {
        yyerror("Unrecognized character : "+string(yytext));
    }
%%
