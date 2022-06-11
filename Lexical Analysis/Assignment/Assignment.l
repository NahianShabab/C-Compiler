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
using std::cout;
using std::ofstream;
using std::string;
ofstream fLog("log.txt");
ofstream fToken("token.txt");
int lineCount=1;
string character="";
string rawCharacter="";
string stringLiteral="";
string rawStringLiteral="";
string comment="";
SymbolTable symbolTable(7);
int errorCount=0;
void logToken(string token,string lexeme=""){
    fLog<<"Line no "<<yylineno<<": Token <"<<token<<"> Lexeme "<<lexeme<<" found\n\n";
}
void logError(string errorMsg){
        fLog<<"Error at line no "<<yylineno<<": "<<errorMsg<<"\n\n";
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
Float ([0-9]*[.][0-9]*(E(\+|-)?[0-9]+)?)|([0-9]+E(\+|-)?[0-9]+)
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
        writeToken("ID",yytext);
        if(symbolTable.insert(yytext,"ID")){
                symbolTable.printCurrentScopeTable(fLog);
        }
        else{
                fLog<<yytext<<" already exists in current ScopeTable\n\n";
        }
}

\/\/ {  
        comment="//";
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
        comment="/*";
        BEGIN COMMENT_MULTIPLE;
}
<COMMENT_MULTIPLE>\*\/ {
        // cout<<"Multiline Comment end\n";
        comment.append("*/");
        logToken("COMMENT",comment);
        comment="";
        BEGIN INITIAL;
}
<COMMENT_MULTIPLE><<EOF>> {
        //error
        //cout<<"Multiline comment not ended error!\n";
        logError("Unterminated Comment "+comment+"\n\n");
        comment="";
        BEGIN INITIAL;
}
<COMMENT_MULTIPLE>.|[\n] {
        comment.append(yytext);
}

[\+|-] {
        logToken("ADDOP",yytext);
        writeToken("ADDOP",yytext);
}

[*/%] {
        logToken("MULOP",yytext);
        writeToken("MULOP",yytext);
}

\+\+|-- {
        logToken("INCOP",yytext);
        writeToken("INCOP",yytext);
}

(!=)|(==)|(<=)|<|(>=)|> {
        logToken("RELOP",yytext);
        writeToken("RELOP",yytext);
}

= {
        logToken("ASSIGNOP",yytext);
        writeToken("ASSIGNOP",yytext);
}

&&|(\|\|) {
        logToken("LOGICOP",yytext);
        writeToken("LOGICOP",yytext);
}

! {
        logToken("NOT",yytext);
        writeToken("NOT",yytext);
}

\( {
        logToken("LPAREN",yytext);
        writeToken("LPAREN",yytext);
}

\) {
        logToken("RPAREN",yytext);
        writeToken("RPAREN",yytext);
}

\{ {
        logToken("LCURL",yytext);
        writeToken("LCURL",yytext);
        symbolTable.enterScope();
}

\} {
        logToken("RCURL",yytext);
        writeToken("RCURL",yytext);
        symbolTable.exitScope();
}

\[ {
        logToken("LTHIRD",yytext);
        writeToken("LTHIRD",yytext);
}
\] {
        logToken("RTHIRD",yytext);
        writeToken("RTHIRD",yytext);
}

, {
        logToken("COMMA",yytext);
        writeToken("COMMA",yytext);
}

; {
        logToken("SEMICOLON",yytext);
        writeToken("SEMICOLON",yytext);
}

[.] {   
        //error
        logToken("Single Dot\n");
}

[0-9]*[.]([0-9]*[.][0-9]*)+ {
        //error
        // cout<<"Multiple Decimal Point error!\n";
        logError("Too many decimal points "+string(yytext)+"\n\n");
}

([0-9]+.[0-9]*|[0-9]*[.][0-9]+|[0-9]+)E([0-9]*[.][0-9])+

{Float} {
        logToken("CONST_FLOAT",yytext);
        writeToken("CONST_FLOAT",yytext);
        if(symbolTable.insert(yytext,"CONST_FLOAT")){
                symbolTable.printCurrentScopeTable(fLog);
        }
        else{
                fLog<<yytext<<" already exists in current ScopeTable\n\n";
        }
}

{Integer}{Identifier} {
        //error
        // logToken("Error",yytext);
        logError("Invalid prefix on ID or invalid suffix on Number "+string(yytext)+"\n\n");
}

{Integer} {
        logToken("CONST_INT",yytext);
        writeToken("CONST_INT",yytext);
        if(symbolTable.insert(yytext,"CONST_INT")){
                symbolTable.printCurrentScopeTable(fLog);
        }
        else{
                fLog<<yytext<<" already exists in current ScopeTable\n\n";
        }
}

' {
        character="";
        rawCharacter="\'";
        BEGIN CHARACTER;
}
<CHARACTER>[\x20-\x26\x28-\x5B\x5D-\x7E] {
        character.append(yytext);
        rawCharacter.append(yytext);
        BEGIN CHARACTER_END;
}
<CHARACTER>{SpecialCharacter} {
        char ch=specialCharacterValue(yytext);
        rawCharacter.append(yytext);
        character.append(string(1,ch));
        BEGIN CHARACTER_END;
}
<CHARACTER>' {
        //error
        // cout<<"Empty character error\n";
        logError("Empty character constant error \'\'\n\n");
        BEGIN INITIAL;
}
<CHARACTER>. {
        //error
        cout<<"Invalid Character!\n";
        logError("Invalid character "+string(yytext)+"\n\n");
        BEGIN INITIAL;
}
<CHARACTER>[\n] {
        //error
        // cout<<"Character Not ended!\n";
        logError("Unterminated Character "+rawCharacter+"\n\n");
        BEGIN INITIAL;
}
<CHARACTER><<EOF>> {
        //error
        // cout<<"character not ended!\n";
        logError("Unterminated Character "+rawCharacter+"\n\n");
        BEGIN INITIAL;
}

<CHARACTER_END>' {
        // cout<<"Character end\n";
        rawCharacter.append("\'");
        if(character.size()==1){
                logToken("CONST_CHAR",rawCharacter);
                writeToken("CONST_CHAR",character);
                if(symbolTable.insert(rawCharacter,"CONST_CHAR")){
                        symbolTable.printCurrentScopeTable(fLog);
                }
                else{
                        fLog<<character<<" already exists in current ScopeTable\n\n";
                }
        }
        else{
                logError("Multi character constant error "+rawCharacter+"\n\n");
        }
        BEGIN INITIAL;
}
<CHARACTER_END>[\x20-\x26\x28-\x5B\x5D-\x7E] {
        //warning? or //error? 
        character.append(yytext);
        rawCharacter.append(yytext);
        // cout<<"MultiCharacter constant error!\n";
}
<CHARACTER_END>{SpecialCharacter} {
        //warning? or //error? 
        char ch=specialCharacterValue(yytext);
        character.append(string(1,ch));
        rawCharacter.append(yytext);
        // cout<<"MultiCharacter constant error!\n";
}
<CHARACTER_END>. {
        //error
        logError("Invalid Character "+rawCharacter+"\n\n");
        BEGIN INITIAL;
}
<CHARACTER_END>[\n] {
        //error
        logError("Unterminated Character "+rawCharacter+"\n\n");
        BEGIN INITIAL;
}
<CHARACTER_END><<EOF>> {
        //error no closing '
         logError("Unterminated Character "+rawCharacter+"\n\n");
        BEGIN INITIAL;
}


\" {
        // cout<<"String started\n";
        stringLiteral="";
        rawStringLiteral="\"";
        BEGIN STRING;
}

<STRING>[\x20-\x21\x23-\x5B\x5D-\x7E] {
        stringLiteral.append(yytext);
        rawStringLiteral.append(yytext);
}
<STRING>{SpecialCharacter} {
        char ch=specialCharacterValue(string(yytext));
        stringLiteral.append(string(1,ch));
        rawStringLiteral.append(yytext);
}
<STRING>\\[\n] {
        // apparently backslash+newline = 4 space;
        stringLiteral.append("    ");
        rawStringLiteral.append(yytext);
}

<STRING>\\. {
        //error
        logError("Unknown Escape Sequence "+rawStringLiteral+"\n\n");
        BEGIN INITIAL;
}
<STRING>\" {
        rawStringLiteral.append("\"");
        logToken("STRING",rawStringLiteral);
        writeToken("STRING",stringLiteral);
        // cout<<"String ended\n";
        BEGIN INITIAL;
}
<STRING>[\n] {
        //error
        logError("Unterminated String "+rawStringLiteral);
        BEGIN INITIAL;
}

<STRING><<EOF>> {
        //error
        logError("Unterminated String "+rawStringLiteral);
        BEGIN INITIAL;
}


<STRING>. {
        //error
        // cout<<"Unknown Character in string\n";
        // cout<<"The character is: "<<yytext<<"\n";
        logError("Unknown Character in String "+rawStringLiteral);
        BEGIN INITIAL;
}

.   {
        //error unknown character

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
