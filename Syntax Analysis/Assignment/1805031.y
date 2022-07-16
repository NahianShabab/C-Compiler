
%{
#include<iostream>
#include<typeinfo>
#include<fstream>
#include<string>
#include"SymbolInfo.h"
#include"SymbolTable.h"
#include"NonTerminal.h"
using namespace std;

int yyparse(void);
extern int yylex(void);
extern FILE *yyin;
extern int yylineno;

SymbolTable *table;
ofstream fLog("log.txt");

void yyerror(const char *s)
{
	fLog<<s<<'\n';
}
void logNewLine(){
	fLog<<'\n';
}
void logGrammer(const char * s){
	fLog<<"Line "<<yylineno<<": "<<s<<'\n';
}

void logPiece(string s){ /*logs a rule instance i.e. piece of code */
	logNewLine();
	fLog<<s<<'\n';
	logNewLine();
}
void log(const char * s){
	fLog<<s;
}

void log(string s){
	fLog<<s;
}

void delSymbol(SymbolInfo * s){
	delete s;
}
void delNonTerminal(NonTerminal * n){
	delete n;
}

%}

%union{
	SymbolInfo * symbol;
	NonTerminal * nonTerminal;
}

%token LPAREN RPAREN SEMICOLON COMMA LCURL RCURL INT FLOAT VOID LTHIRD RTHIRD FOR IF WHILE RETURN NOT INCOP DECOP
%token <symbol> ID CONST_INT PRINTLN ASSIGNOP LOGICOP RELOP ADDOP MULOP CONST_FLOAT


%nonassoc S_IF
%nonassoc ELSE

%type <nonTerminal> start program unit var_declaration func_declaration func_definition type_specifier parameter_list
%type <nonTerminal> compound_statement statements statement declaration_list expression_statement expression 
%type <nonTerminal> variable logic_expression rel_expression simple_expression term unary_expression factor
%type <nonTerminal> argument_list arguments

%%
start : program
	{
		//write your code in this block in all the similar blocks below
		logGrammer("start: program");
		delNonTerminal($1);
	}
	;

program : program unit 
	{
		logGrammer("program : program unit");
		$$=new NonTerminal();
		$$->text+=$1->text;
		$$->text+="\n";
		$$->text+=$2->text;
		logPiece($$->text);
		delNonTerminal($1);
		delNonTerminal($2);
	}
	| unit
	{
		logGrammer("program : unit");
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPiece($$->text);
		delNonTerminal($1);
	}
	;
	
unit : var_declaration
	{
		logGrammer("unit : var_declaration");
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPiece($$->text);
		delNonTerminal($1);
	}
     | func_declaration
	 {
		logGrammer("unit : func_declaration");
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPiece($$->text);
		delNonTerminal($1);
		
	 }
     | func_definition
	 {
		logGrammer("unit : func_definition");
		$$=new NonTerminal();
		$$->text=$1->text;
		logPiece($$->text);
		delNonTerminal($1);
	 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
		{
			logGrammer("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" "+$2->getName();
			table->insert($2);
			$$->text+="(";
			$$->text+=$4->text;
			$$->text+=");";
			logPiece($$->text);

			delNonTerminal($1);
			delNonTerminal($4);
		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			logGrammer("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{
			logGrammer("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		}
		| type_specifier ID LPAREN RPAREN compound_statement
		{
			logGrammer("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" "+$2->getName();
			$$->text+="(";
			$$->text+=")";
			$$->text+=$5->text;

			table->insert($2);

			logPiece($$->text);
			delNonTerminal($1);
			delNonTerminal($5);
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			logGrammer("parameter_list  : parameter_list COMMA type_specifier ID");
		}
		| parameter_list COMMA type_specifier
		{
			logGrammer("parameter_list  : parameter_list COMMA type_specifier");
		}
 		| type_specifier ID
		{
			logGrammer("parameter_list  : type_specifier ID");
		}
		| type_specifier
		{
			logGrammer("parameter_list  : type_specifier");
		}
 		;

 		
compound_statement : LCURL statements RCURL
			{
			logGrammer("compound_statement : LCURL statements RCURL");
			}
 		    | LCURL RCURL
			{	
			logGrammer("compound_statement : LCURL RCURL");
				$$=new NonTerminal();
				$$->text+="{\n}";
				logPiece($$->text);
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{
			logGrammer("var_declaration : type_specifier declaration_list SEMICOLON");
		}
 		 ;
 		 
type_specifier : INT
		{
			logGrammer("type_specifier : INT");
			$$=new NonTerminal();
			$$->text+="int";
			logPiece($$->text);
		}
 		| FLOAT
		{
			logGrammer("type_specifier : FLOAT");
		}
 		| VOID
		{
			logGrammer("type_specifier : VOID");
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		{
			logGrammer("declaration_list : declaration_list COMMA ID");
		}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
			logGrammer("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		}
 		  | ID
		{
			logGrammer("declaration_list : ID");
		}
 		  | ID LTHIRD CONST_INT RTHIRD
		{
			logGrammer("declaration_list : ID LTHIRD CONST_INT RTHIRD");
		}
 		  ;
 		  
statements : statement
		{
			logGrammer("statements : statement");
		}
	   | statements statement
		{
			logGrammer("statements : statements statement");
		}
	   ;
	   
statement : var_declaration
		{
			logGrammer("statement : var_declaration");
		}
	  | expression_statement
		{
			logGrammer("statement : expression_statement");
		}
	  | compound_statement
		{
			logGrammer("statement : compound_statement");
		}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
		{
			logGrammer("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		}
	  | IF LPAREN expression RPAREN statement %prec S_IF
		{
			logGrammer("statement : IF LPAREN expression RPAREN statement");
		}
	  | IF LPAREN expression RPAREN statement ELSE statement
		{
			logGrammer("statement : IF LPAREN expression RPAREN statement ELSE statement");
		}
	  | WHILE LPAREN expression RPAREN statement
		{
			logGrammer("statement : WHILE LPAREN expression RPAREN statement");
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
		{
			logGrammer("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		}
	  | RETURN expression SEMICOLON
		{
			logGrammer("statement : RETURN expression SEMICOLON");
		}
	  ; 

expression_statement : SEMICOLON	
		{
			logGrammer("expression_statement : SEMICOLON");
		}		
			| expression SEMICOLON 
		{
			logGrammer("expression_statement : expression SEMICOLON");
		}
			;
	  
variable : ID 		
		{
			logGrammer("variable : ID");
		}
	 | ID LTHIRD expression RTHIRD 
		{
			logGrammer("variable : ID LTHIRD expression RTHIRD");
		}
	 ;
	 
 expression : logic_expression	
		{
			logGrammer("expression : logic_expression");
		}
	   | variable ASSIGNOP logic_expression
		{
			logGrammer("expression : variable ASSIGNOP logic_expression");
		}
	   ;
			
logic_expression : rel_expression 	
		{
			logGrammer("logic_expression : rel_expression");
		}
		 | rel_expression LOGICOP rel_expression 
		{
			logGrammer("logic_expression : rel_expression LOGICOP rel_expression");
		}	
		 ;
			
rel_expression	: simple_expression 
		{
			logGrammer("rel_expression	: simple_expression");
		}
		| simple_expression RELOP simple_expression	
		{
			logGrammer("rel_expression	: simple_expression RELOP simple_expression");
		}
		;
				
simple_expression : term 
		{
			logGrammer("simple_expression : term");
		}
		  | simple_expression ADDOP term 
		{
			logGrammer("simple_expression : simple_expression ADDOP term");
		}
		  ;
					
term :	unary_expression
		{
			logGrammer("term :	unary_expression");
		}
     |  term MULOP unary_expression
		{
			logGrammer("term :	term MULOP unary_expression");
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			logGrammer("unary_expression : ADDOP unary_expression");
		}
		 | NOT unary_expression 
		{
			logGrammer("unary_expression : NOT unary_expression");
		}
		 | factor 
		{
			logGrammer("unary_expression : factor");
		}
		 ;
	
factor : variable 
		{
			logGrammer("factor : variable");
		}
	| ID LPAREN argument_list RPAREN
		{
			logGrammer("factor : ID LPAREN argument_list RPAREN");
		}
	| LPAREN expression RPAREN
		{
			logGrammer("factor : LPAREN expression RPAREN");
		}
	| CONST_INT
		{
			logGrammer("factor : CONST_INT");
		}
	| CONST_FLOAT
		{
			logGrammer("factor : CONST_FLOAT");
		}
	| variable INCOP 
		{
			logGrammer("factor : variable INCOP");
		}
	| variable DECOP
		{
			logGrammer("factor : variable DECOP");
		}
	;
	
argument_list : arguments
		{
			logGrammer("argument_list : arguments");
		}
		|
		{
			logGrammer("argument_list : empty");
		}
		;
	
arguments : arguments COMMA logic_expression
		{
			logGrammer("arguments : arguments COMMA logic_expression");
		}
	      | logic_expression
		{
			logGrammer("arguments : logic_expression");
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