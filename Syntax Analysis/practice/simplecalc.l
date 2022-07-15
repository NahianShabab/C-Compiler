%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
/* Originally the following line of code was "extern double yylval"
But it didn't work, because yylval is declared as YYSTYPE 
in tab.h file, so i changed it as following
*/
%}


WS [ \t]+
%%
"A" {return ALPHA;}
"B" {return BETA;} 
"\n"      { return NEWLINE; }
{WS} { /* No action and no return */}

%%
