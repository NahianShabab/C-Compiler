%{
#include<iostream>
#include<fstream>
#include"SymbolInfo.h"
#include "SymbolTable.h"
#define YYSTYPE SymbolInfo*
using namespace std;

int yyparse(void);
extern int yylex(void);
extern FILE *yyin;
extern int yylineno;

SymbolTable *table;
ofstream fLog("log.txt");

void yyerror(const char *s)
{
	cout<<s<<'\n';
}

void log(const char * s){
	fLog<<"Line "<<yylineno<<": "<<s<<"\n";
}

%}

%token ID LPAREN RPAREN SEMICOLON COMMA LCURL RCURL INT FLOAT VOID LTHIRD CONST_INT RTHIRD
%token FOR IF ELSE WHILE PRINTLN RETURN ASSIGNOP LOGICOP RELOP ADDOP MULOP NOT CONST_FLOAT INCOP DECOP

%nonassoc S_IF
%nonassoc ELSE

%%
start : program
	{
		//write your code in this block in all the similar blocks below
		log("start: program");
	}
	;

program : program unit 
	{
		log("program : program unit");
	}
	| unit
	{
		log("program : unit");
	}
	;
	
unit : var_declaration
	{
		log("unit : var_declaration");
	}
     | func_declaration
	 {
		log("unit : func_declaration");
	 }
     | func_definition
	 {
		log("unit : func_definition");
	 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
		{
			log("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			log("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{
			log("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		}
		| type_specifier ID LPAREN RPAREN compound_statement
		{
			log("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			log("parameter_list  : parameter_list COMMA type_specifier ID");
		}
		| parameter_list COMMA type_specifier
		{
			log("parameter_list  : parameter_list COMMA type_specifier");
		}
 		| type_specifier ID
		{
			log("parameter_list  : type_specifier ID");
		}
		| type_specifier
		{
			log("parameter_list  : type_specifier");
		}
 		;

 		
compound_statement : LCURL statements RCURL
			{
			log("compound_statement : LCURL statements RCURL");
			}
 		    | LCURL RCURL
			{	
			log("compound_statement : LCURL RCURL");
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{
			log("var_declaration : type_specifier declaration_list SEMICOLON");
		}
 		 ;
 		 
type_specifier : INT
		{
			log("type_specifier : INT");
		}
 		| FLOAT
		{
			log("type_specifier : FLOAT");
		}
 		| VOID
		{
			log("type_specifier : VOID");
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		{
			log("declaration_list : declaration_list COMMA ID");
		}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
			log("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		}
 		  | ID
		{
			log("declaration_list : ID");
		}
 		  | ID LTHIRD CONST_INT RTHIRD
		{
			log("declaration_list : ID LTHIRD CONST_INT RTHIRD");
		}
 		  ;
 		  
statements : statement
		{
			log("statements : statement");
		}
	   | statements statement
		{
			log("statements : statements statement");
		}
	   ;
	   
statement : var_declaration
		{
			log("statement : var_declaration");
		}
	  | expression_statement
		{
			log("statement : expression_statement");
		}
	  | compound_statement
		{
			log("statement : compound_statement");
		}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
		{
			log("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		}
	  | IF LPAREN expression RPAREN statement %prec S_IF
		{
			log("statement : IF LPAREN expression RPAREN statement");
		}
	  | IF LPAREN expression RPAREN statement ELSE statement
		{
			log("statement : IF LPAREN expression RPAREN statement ELSE statement");
		}
	  | WHILE LPAREN expression RPAREN statement
		{
			log("statement : WHILE LPAREN expression RPAREN statement");
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
		{
			log("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		}
	  | RETURN expression SEMICOLON
		{
			log("statement : RETURN expression SEMICOLON");
		}
	  ; 

expression_statement : SEMICOLON	
		{
			log("expression_statement : SEMICOLON");
		}		
			| expression SEMICOLON 
		{
			log("expression_statement : expression SEMICOLON");
		}
			;
	  
variable : ID 		
		{
			log("variable : ID");
		}
	 | ID LTHIRD expression RTHIRD 
		{
			log("variable : ID LTHIRD expression RTHIRD");
		}
	 ;
	 
 expression : logic_expression	
		{
			log("expression : logic_expression");
		}
	   | variable ASSIGNOP logic_expression
		{
			log("expression : variable ASSIGNOP logic_expression");
		}
	   ;
			
logic_expression : rel_expression 	
		{
			log("logic_expression : rel_expression");
		}
		 | rel_expression LOGICOP rel_expression 
		{
			log("logic_expression : rel_expression LOGICOP rel_expression");
		}	
		 ;
			
rel_expression	: simple_expression 
		{
			log("rel_expression	: simple_expression");
		}
		| simple_expression RELOP simple_expression	
		{
			log("rel_expression	: simple_expression RELOP simple_expression");
		}
		;
				
simple_expression : term 
		{
			log("simple_expression : term");
		}
		  | simple_expression ADDOP term 
		{
			log("simple_expression : simple_expression ADDOP term");
		}
		  ;
					
term :	unary_expression
		{
			log("term :	unary_expression");
		}
     |  term MULOP unary_expression
		{
			log("term :	term MULOP unary_expression");
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			log("unary_expression : ADDOP unary_expression");
		}
		 | NOT unary_expression 
		{
			log("unary_expression : NOT unary_expression");
		}
		 | factor 
		{
			log("unary_expression : factor");
		}
		 ;
	
factor : variable 
		{
			log("factor : variable");
		}
	| ID LPAREN argument_list RPAREN
		{
			log("factor : ID LPAREN argument_list RPAREN");
		}
	| LPAREN expression RPAREN
		{
			log("factor : LPAREN expression RPAREN");
		}
	| CONST_INT
		{
			log("factor : CONST_INT");
		}
	| CONST_FLOAT
		{
			log("factor : CONST_FLOAT");
		}
	| variable INCOP 
		{
			log("factor : variable INCOP");
		}
	| variable DECOP
		{
			log("factor : variable DECOP");
		}
	;
	
argument_list : arguments
		{
			log("argument_list : arguments");
		}
			  |
			  ;
	
arguments : arguments COMMA logic_expression
		{
			log("arguments : arguments COMMA logic_expression");
		}
	      | logic_expression
		{
			log("arguments : logic_expression");
		}
	      ;
 

%%

int main(int argc,char *argv[])
{
	FILE * fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	yyin=fp;
	table=new SymbolTable(7);
	yyparse();
	delete table;
	fLog.close();
	return 0;
}