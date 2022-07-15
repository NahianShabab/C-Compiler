%option noyywrap
%{
#include "y.tab.h"
extern YYSTYPE yylval;
%}

%%
[1-9][0-9]* {sscanf(yytext,"%lf", &yylval);return NUMBER;}
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"(" {return LPAREN;}
")" {return RPAREN;}
"\n" {return NEWLINE;}
[ \t]+ {}
%%