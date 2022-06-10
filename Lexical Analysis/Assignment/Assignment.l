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
using std::cout;
using std::ofstream;
using std::string;
ofstream fLog("log.txt");
ofstream fToken("token.txt");
int lineCount=1;
string character="";
string stringLiteral="";
string comment="";
void logToken(string token,string lexeme=""){
    fLog<<"Line No. "<<yylineno<<": Token "<<token<<" Lexeme "<<lexeme<<" found\n";
}
void writeToken(string type,string symbol=""){
    fToken<<'<'<<type<<(symbol==""?">":(","+symbol+">"));
}
%}
%x COMMENT_SINGLE
%x COMMENT_MULTIPLE
%x CHARACTER
%x CHARACTER_END
%x STRING
 
Identifier [a-zA-Z_][a-zA-Z_0-9]*
Float ([0-9]*[.][0-9]+(E(\+|-)?[0-9]+)?)|([0-9]+E(\+|-)?[0-9]+)
Integer [0-9]+
SpecialCharacter (\\n)|(\\t)|(\\\\)|(\\')|(\\a)|(\\f)|(\\r)|(\\b)|(\\v)|(\\0)|(\\\")

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


{Identifier} {
        logToken("ID",yytext);
}

\/\/ {  
        comment="";
        BEGIN COMMENT_SINGLE;
        // cout<<"Comment Start\n";
}
<COMMENT_SINGLE>(\\[\n]) {
        comment.append(yytext);
        // cout<<"\\+newline in comment single\n";
}
<COMMENT_SINGLE>[^\n] {
        comment.append(yytext);
        // cout<<"all text in single comment\n";
}
<COMMENT_SINGLE>[\n] {
        // cout<<"Comment End\n";
        logToken("COMMENT",comment);
        comment="";
        BEGIN INITIAL;
}
<COMMENT_SINGLE><<EOF>> {
        logToken("COMMENT",comment);
        comment="";
        BEGIN INITIAL;
}

\/\* {
        // cout<<"Multiline Comment started\n";
        comment="";
        BEGIN COMMENT_MULTIPLE;
}
<COMMENT_MULTIPLE>\*\/ {
        cout<<"Multiline Comment end\n";
        logToken("COMMENT",comment);
        comment="";
        BEGIN INITIAL;
}
<COMMENT_MULTIPLE><<EOF>> {
        cout<<"Multiline comment not ended error!\n";
        comment="";
        BEGIN INITIAL;
}
<COMMENT_MULTIPLE>.|[\n] {
        comment.append(yytext);
}

[\+|-] {
        logToken("ADDOP",yytext);
}

[*/%] {
        logToken("MULOP",yytext);
}

\+\+|-- {
        logToken("INCOP",yytext);
}

(!=)|(==)|(<=)|<|(>=)|> {
        logToken("RELOP",yytext);
}

= {
        logToken("ASSIGNOP",yytext);
}

&&|(\|\|) {
        logToken("LOGICOP",yytext);
}

! {
        logToken("NOT",yytext);
}

\( {
        logToken("LPAREN",yytext);
}

\) {
        logToken("RPAREN",yytext);
}

\{ {
        logToken("LCURL",yytext);
}

\} {
        logToken("RCURL",yytext);
}

\[ {
        logToken("LTHIRD",yytext);
}
\] {
        logToken("RTHIRD",yytext);
}

, {
        logToken("COMMA",yytext);
}

; {
        logToken("SEMICOLON",yytext);
}

[0-9]*[.]([0-9]*[.][0-9]*)+ {
        cout<<"Multiple Decimal Point error!\n";
}


{Float} {
        logToken("CONST_FLOAT",yytext);
}

{Integer}{Identifier} {
        logToken("Error",yytext);
}

{Integer} {
        logToken("CONST_INT",yytext);
}

' {
        character="";
        BEGIN CHARACTER;
}
<CHARACTER>[\x20-\x26\x28-\x5B\x5D-\x7E] {
        character.append(yytext);
        BEGIN CHARACTER_END;
}
<CHARACTER>{SpecialCharacter} {
        char ch=specialCharacterValue(yytext);
        character.append(string(1,ch));
        BEGIN CHARACTER_END;
}
<CHARACTER>' {
        cout<<"Empty character error\n";
        BEGIN INITIAL;
}
<CHARACTER>. {
        cout<<"Invalid Character!\n";
        BEGIN INITIAL;
}
<CHARACTER>[\n] {
        cout<<"Character Not ended!\n";
        BEGIN INITIAL;
}
<CHARACTER><<EOF>> {
        cout<<"character not ended!\n";
        BEGIN INITIAL;
}

<CHARACTER_END>' {
        cout<<"Character end\n";
        logToken("CONST_CHAR",character);
        character="";
        BEGIN INITIAL;
}
<CHARACTER_END>[\x20-\x26\x28-\x5B\x5D-\x7E] {
        character.append(yytext);
        cout<<"MultiCharacter constant error!\n";
}
<CHARACTER_END>{SpecialCharacter} {
        char ch=specialCharacterValue(yytext);
        character.append(string(1,ch));
}
<CHARACTER_END>. {
        cout<<"Invalid Character!\n";
        BEGIN INITIAL;
}
<CHARACTER_END>[\n] {
        cout<<"Character not ended!\n";
        BEGIN INITIAL;
}
<CHARACTER_END><<EOF>> {
        cout<<"\' not ended properly!\n";
        BEGIN INITIAL;
}


\" {
        cout<<"String started\n";
        stringLiteral="";
        BEGIN STRING;
}

<STRING>[\x20-\x21\x23-\x5B\x5D-\x7E] {
        stringLiteral.append(yytext);
}
<STRING>{SpecialCharacter} {
        char ch=specialCharacterValue(string(yytext));
        stringLiteral.append(string(1,ch));
}
<STRING>\\[\n] {
        stringLiteral.append("    ");
}

<STRING>\\. {
        cout<<"Unknown escape sequence\n";
        BEGIN INITIAL;
}
<STRING>\" {
        logToken("STRING",stringLiteral);
        stringLiteral="";
        cout<<"String ended\n";
        BEGIN INITIAL;
}
<STRING>[\n] {
        cout<<"String ended abruptly\n";
        BEGIN INITIAL;
}

<STRING><<EOF>> {
        cout<<"String ended abruptly\n";
        BEGIN INITIAL;
}


<STRING>. {
        cout<<"Unknown Character in string\n";
        cout<<"The character is: "<<yytext<<"\n";
        BEGIN INITIAL;
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
