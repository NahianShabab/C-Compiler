%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s){
	printf("%s\n",s);
}

int yylex(void);

%}

%token NEWLINE ALPHA BETA


%%
start:exp NEWLINE {printf("Start found!");}

exp:ALPHA exp
    |BETA
%%

int main()
{
    yyparse();
    exit(0);
}
