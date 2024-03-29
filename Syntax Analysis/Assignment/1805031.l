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
#include"SymbolInfo.h"
#include"NonTerminal.h"
#include"y.tab.h"
using namespace std;

extern YYSTYPE yylval;
extern SymbolTable * table;
extern ofstream fLog;
extern void yyerror(const char *);
extern void yyerror(string);
extern ParameterList * currentParameterList;
extern void insertVarialblesInScope();


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
// int errorCount=0;
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
        yylval.symbol=new SymbolInfo(yytext,"ID");
        return ID;
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
        if(currentParameterList!=NULL){
                table->enterScope();
                // cout<<"Got some parameters\n";
                // cout<<"size: "<<currentParameterList->text<<'\n';
                insertVarialblesInScope();
        }
        // table->printAllScopeTable(fLog);
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
        //error
        // logError("Single Dot");
        string err="Invalid Decimal Point"+string(yytext);
        yyerror(err.c_str());
}

[0-9]*[.]([0-9]*[.][0-9]*)+ {
        // logError("Too many decimal points "+string(yytext));
        string err="Too many decimal points "+string(yytext);
        yyerror(err.c_str());
}

([0-9]+.[0-9]*|[0-9]*[.][0-9]+|[0-9]+)E(\+|-)?([0-9]*[.][0-9]*)+ {
        // logError("Ill formed number "+string(yytext));
        string err="Ill Formed Number "+string(yytext);
        yyerror(err.c_str());
}

{Float} {
        // if(symbolTable.insert(yytext,"CONST_FLOAT")){
        //         symbolTable.printAllScopeTable(fLog);
        // }
        // else{
        //         fLog<<yytext<<" already exists in current ScopeTable\n\n";
        // }
        yylval.symbol=new SymbolInfo(yytext,"CONST_FLOAT");
        return CONST_FLOAT;
}

{Integer}{Identifier} {
        // logError("Invalid prefix on ID or invalid suffix on Number "+string(yytext));
        string err="Invalid prefix on ID or invalid suffix on Number "+string(yytext);
        yyerror(err.c_str());
}

{Integer} {
        // if(symbolTable.insert(yytext,"CONST_INT")){
        //         symbolTable.printAllScopeTable(fLog);
        // }
        // else{
        //         fLog<<yytext<<" already exists in current ScopeTable\n\n";
        // }
        yylval.symbol=new SymbolInfo(yytext,"CONST_INT");
        return CONST_INT;
}


.   {
        //error unknown character
        // logError("Unrecognized character : "+string(yytext));
        string err=string("Unrecognized character ")+string(yytext);
        yyerror(err.c_str());

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
