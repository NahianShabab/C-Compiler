
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
int errorCount=0;

SymbolTable *table;
ofstream fLog("log.txt");
ofstream fError("error.txt");

void yyerror(const char *s)
{
	fLog<<"Error at line "<<yylineno<<" : "<<s<<'\n';
	fError<<"Error at line "<<yylineno<<" : "<<s<<"\n\n";
	errorCount++;
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

void deleteSymbol(SymbolInfo * s){
	delete s;
}
void deleteNonTerminal(NonTerminal * n){
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
		deleteNonTerminal($1);
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
		deleteNonTerminal($1);
		deleteNonTerminal($2);
	}
	| unit
	{
		logGrammer("program : unit");
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPiece($$->text);
		deleteNonTerminal($1);
	}
	;
	
unit : var_declaration
	{
		logGrammer("unit : var_declaration");
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPiece($$->text);
		deleteNonTerminal($1);
	}
     | func_declaration
	 {
		logGrammer("unit : func_declaration");
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPiece($$->text);
		deleteNonTerminal($1);
		
	 }
     | func_definition
	 {
		logGrammer("unit : func_definition");
		$$=new NonTerminal();
		$$->text=$1->text;
		logPiece($$->text);
		deleteNonTerminal($1);
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

			deleteNonTerminal($1);
			deleteNonTerminal($4);
		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			logGrammer("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
			$$=new NonTerminal();
			$$->text=$1->text+" "+$2->getName()+"();";
			table->insert($2);
			logPiece($$->text);
			deleteNonTerminal($1);
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{
			logGrammer("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
			$$=new NonTerminal();
			$$->text=$1->text+" "+$2->getName()+"("+$4->text+")"+$6->text;
			table->insert($2);
			logPiece($$->text);
			deleteNonTerminal($1);
			deleteNonTerminal($4);
			deleteNonTerminal($6);
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
			deleteNonTerminal($1);
			deleteNonTerminal($5);
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			logGrammer("parameter_list  : parameter_list COMMA type_specifier ID");
			$$=new NonTerminal();
			$$->text=$1->text+","+$3->text+" "+$4->getName();
			table->insert($4);
			logPiece($$->text);

			deleteNonTerminal($1);
			deleteNonTerminal($3);
		}
		| parameter_list COMMA type_specifier
		{
			logGrammer("parameter_list  : parameter_list COMMA type_specifier");
			$$=new NonTerminal();
			$$->text=$1->text+","+$3->text;
			logPiece($$->text);

			deleteNonTerminal($1);
			deleteNonTerminal($3);
		}
 		| type_specifier ID
		{
			logGrammer("parameter_list  : type_specifier ID");
			$$=new NonTerminal();
			$$->text=$1->text+" "+$2->getName();
			table->insert($2);
			logPiece($$->text);

			deleteNonTerminal($1);
		}
		| type_specifier
		{
			logGrammer("parameter_list  : type_specifier");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
 		;

 		
compound_statement : LCURL statements RCURL
			{
				logGrammer("compound_statement : LCURL statements RCURL");
				$$=new NonTerminal();
				$$->text="{\n"+$2->text+"\n}";
				logPiece($$->text);
				deleteNonTerminal($2);
			}
 		    | LCURL RCURL
			{	
			logGrammer("compound_statement : LCURL RCURL");
				$$=new NonTerminal();
				$$->text="{\n}";
				logPiece($$->text);
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{
			logGrammer("var_declaration : type_specifier declaration_list SEMICOLON");
			$$=new NonTerminal();
			$$->text=$1->text+" "+$2->text+";";
			logPiece($$->text);
			deleteNonTerminal($1);
			deleteNonTerminal($2);
		}
 		 ;
 		 
type_specifier : INT
		{
			logGrammer("type_specifier : INT");
			$$=new NonTerminal();
			$$->text="int";
			logPiece($$->text);
		}
 		| FLOAT
		{
			logGrammer("type_specifier : FLOAT");
			$$=new NonTerminal();
			$$->text="float";
			logPiece($$->text);
		}
 		| VOID
		{
			logGrammer("type_specifier : VOID");
			$$=new NonTerminal();
			$$->text="void";
			logPiece($$->text);
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		{
			logGrammer("declaration_list : declaration_list COMMA ID");
			$$=new NonTerminal();
			$$->text=$1->text+","+$3->getName();
			table->insert($3);
			logPiece($$->text);
			deleteNonTerminal($1);
		}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
			logGrammer("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
			$$=new NonTerminal();
			$$->text=$1->text+","+$3->getName()+"["+$5->getName()+"]";
			table->insert($3);
			table->insert($5);
			logPiece($$->text);
			deleteNonTerminal($1);
		}
 		  | ID
		{
			logGrammer("declaration_list : ID");
			$$=new NonTerminal();
			$$->text=$1->getName();
			table->insert($1);
			logPiece($$->text);
		}
 		  | ID LTHIRD CONST_INT RTHIRD
		{
			logGrammer("declaration_list : ID LTHIRD CONST_INT RTHIRD");
			$$=new NonTerminal();
			$$->text=$1->getName()+"["+$3->getName()+"]";
			table->insert($1);
			table->insert($3);
			logPiece($$->text);
		}
 		  ;
 		  
statements : statement
		{
			logGrammer("statements : statement");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	   | statements statement
		{
			logGrammer("statements : statements statement");
			$$=new NonTerminal();
			$$->text=$1->text+"\n"+$2->text;
			logPiece($$->text);
			deleteNonTerminal($1);
			deleteNonTerminal($2);
		}
	   ;
	   
statement : var_declaration
		{
			logGrammer("statement : var_declaration");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	  | expression_statement
		{
			logGrammer("statement : expression_statement");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	  | compound_statement
		{
			logGrammer("statement : compound_statement");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
		{
			logGrammer("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
			$$=new NonTerminal();
			$$->text="for("+$3->text+$4->text+$5->text+")\n"+$7->text;
			logPiece($$->text);
			deleteNonTerminal($3);
			deleteNonTerminal($4);
			deleteNonTerminal($5);
			deleteNonTerminal($7);
		}
	  | IF LPAREN expression RPAREN statement %prec S_IF
		{
			logGrammer("statement : IF LPAREN expression RPAREN statement");
			$$=new NonTerminal();
			$$->text="if("+$3->text+")\n"+$5->text;
			logPiece($$->text);
			deleteNonTerminal($3);
			deleteNonTerminal($5);
		}
	  | IF LPAREN expression RPAREN statement ELSE statement
		{
			logGrammer("statement : IF LPAREN expression RPAREN statement ELSE statement");
			$$=new NonTerminal();
			$$->text="if("+$3->text+")\n"+$5->text+"\nelse"+$7->text;
			logPiece($$->text);
			deleteNonTerminal($3);
			deleteNonTerminal($5);
			deleteNonTerminal($7);
		}
	  | WHILE LPAREN expression RPAREN statement
		{
			logGrammer("statement : WHILE LPAREN expression RPAREN statement");
			$$=new NonTerminal();
			$$->text="while("+$3->text+")\n"+$5->text;
			logPiece($$->text);
			deleteNonTerminal($3);
			deleteNonTerminal($5);
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
		{
			logGrammer("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
			$$=new NonTerminal();
			
			/*DEBUG_LATER SYMBOL_TABLE*/
			/*
!!!!!!!!!!!!!! NOTE : function call to printf, do not insert to table
			*/

			$$->text="printf("+$3->getName()+");";
			delete $3;
			
			logPiece($$->text);
		}
	  | RETURN expression SEMICOLON
		{
			logGrammer("statement : RETURN expression SEMICOLON");
			$$=new NonTerminal();
			$$->text="return "+$2->text+";";
			logPiece($$->text);
			deleteNonTerminal($2);
		}
	  ; 

expression_statement : SEMICOLON	
		{
			logGrammer("expression_statement : SEMICOLON");
			$$=new NonTerminal();
			$$->text=";";
			logPiece($$->text);
		}		
			| expression SEMICOLON 
		{
			logGrammer("expression_statement : expression SEMICOLON");
			$$=new NonTerminal();
			$$->text=$1->text+";";
			logPiece($$->text);
			deleteNonTerminal($1);
		}
			;
	  
variable : ID 		
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("variable : ID");
			$$=new NonTerminal();
			$$->text=$1->getName();
			logPiece($$->text);
			delete $1;
		}
	 | ID LTHIRD expression RTHIRD 
		{
			logGrammer("variable : ID LTHIRD expression RTHIRD");
			/*DEBUG_LATER SYMBOL_TABLE*/
			$$=new NonTerminal();
			$$->text=$1->getName()+"["+$3->text+"]";
			logPiece($$->text);
			delete $1;
			deleteNonTerminal($3);
		}
	 ;
	 
 expression : logic_expression	
		{
			logGrammer("expression : logic_expression");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	   | variable ASSIGNOP logic_expression
		{
			logGrammer("expression : variable ASSIGNOP logic_expression");
			$$=new NonTerminal();
			$$->text=$1->text+"="+$3->text;
			logPiece($$->text);
			deleteNonTerminal($1);
			deleteNonTerminal($3);
		}
	   ;
			
logic_expression : rel_expression 	
		{
			logGrammer("logic_expression : rel_expression");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
		 | rel_expression LOGICOP rel_expression 
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("logic_expression : rel_expression LOGICOP rel_expression");
			$$=new NonTerminal();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);
			deleteNonTerminal($1);deleteNonTerminal($3);
			delete $2;
		}	
		 ;
			
rel_expression	: simple_expression 
		{
			logGrammer("rel_expression	: simple_expression");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
		| simple_expression RELOP simple_expression	
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("rel_expression	: simple_expression RELOP simple_expression");
			$$=new NonTerminal();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);
			deleteNonTerminal($1);deleteNonTerminal($3);
			delete $2;
		}
		;
				
simple_expression : term 
		{
			logGrammer("simple_expression : term");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
		  | simple_expression ADDOP term 
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("simple_expression : simple_expression ADDOP term");
			$$=new NonTerminal();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);
			deleteNonTerminal($1);
			deleteNonTerminal($3);
			delete $2;
		}
		  ;
					
term :	unary_expression
		{
			logGrammer("term :	unary_expression");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
     |  term MULOP unary_expression
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("term :	term MULOP unary_expression");
			$$=new NonTerminal();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);
			deleteNonTerminal($1);
			deleteNonTerminal($3);
			delete $2;
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("unary_expression : ADDOP unary_expression");
			$$=new NonTerminal();
			$$->text=$1->getName()+$2->text;
			logPiece($$->text);
			deleteNonTerminal($2);
			delete $1;
		}
		 | NOT unary_expression 
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("unary_expression : NOT unary_expression");
			$$=new NonTerminal();
			$$->text="!"+$2->text;
			logPiece($$->text);
			deleteNonTerminal($2);
		}
		 | factor 
		{
			logGrammer("unary_expression : factor");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
		 ;
	
factor : variable 
		{
			logGrammer("factor : variable");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	| ID LPAREN argument_list RPAREN
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("factor : ID LPAREN argument_list RPAREN");
			$$=new NonTerminal();
			$$->text=$1->getName()+"("+$3->text+")";
			logPiece($$->text);
			deleteNonTerminal($3);
			delete $1;
			
		}
	| LPAREN expression RPAREN
		{
			logGrammer("factor : LPAREN expression RPAREN");
			$$=new NonTerminal();
			$$->text="("+$2->text+")";
			logPiece($$->text);
			deleteNonTerminal($2);
		}
	| CONST_INT
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("factor : CONST_INT");
			$$=new NonTerminal();
			$$->text=$1->getName();
			logPiece($$->text);
			delete $1;
		}
	| CONST_FLOAT
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("factor : CONST_FLOAT");
			$$=new NonTerminal();
			$$->text=$1->getName();
			logPiece($$->text);
			delete $1;
		}
	| variable INCOP 
		{
			logGrammer("factor : variable INCOP");
			$$=new NonTerminal();
			$$->text=$1->text+"++";
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	| variable DECOP
		{
			logGrammer("factor : variable DECOP");
			$$->text=$1->text+"--";
			logPiece($$->text);
			deleteNonTerminal($1);
		}
	;
	
argument_list : arguments
		{
			logGrammer("argument_list : arguments");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
		}
		|
		{
			logGrammer("argument_list : empty");
			$$=new NonTerminal();
			$$->text="";
		}
		;
	
arguments : arguments COMMA logic_expression
		{
			logGrammer("arguments : arguments COMMA logic_expression");
			$$=new NonTerminal();
			$$->text=$1->text+","+$3->text;
			logPiece($$->text);
			deleteNonTerminal($1);
			deleteNonTerminal($3);
		}
	      | logic_expression
		{
			logGrammer("arguments : logic_expression");
			$$=new NonTerminal();
			$$->text=$1->text;
			logPiece($$->text);
			deleteNonTerminal($1);
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
	logNewLine();
	table->printAllScopeTable(fLog);
	logNewLine();

	fLog<<"Total Lines : "<<yylineno<<'\n';
	fLog<<"Total Errors : "<<errorCount<<'\n';

	/*Wrap up and free memories*/
	delete table;
	fLog.close();
	fError.close();
	return 0;
}