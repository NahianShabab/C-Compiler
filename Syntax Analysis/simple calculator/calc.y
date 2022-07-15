%{
#include<stdio.h>
#define YYSTYPE double
int yylex(void);
void yyerror(const char *s)
{
    printf("%s\n",s);
}
extern  FILE * yyin;
%}

%token ADD SUB MUL DIV NEWLINE NUMBER LPAREN RPAREN

%%
start:
    | start line;

line: NEWLINE
    | expr NEWLINE {printf("\t%.10g\n",$1);};

expr: term {$$=$1;}
    | term ADD expr {$$=$1+$3;}
    | term SUB expr {$$=$1-$3;};

term: factor {$$=$1;}
    | term MUL factor {$$=$1*$3;}
    | term DIV factor{$$=$1/$3;};

factor: NUMBER {$$=$1;}
    | LPAREN expr RPAREN {$$=$2;};
%%
int main(int argc,char * argv[]){
    if(argc<=1){
        printf("Please provide an input file");
        exit(1);
    }
    FILE *fp;
    if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File");
		exit(1);
	}
    yyin=fp;
    yyparse();
    fclose(yyin);
    return 0;
}