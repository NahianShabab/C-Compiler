%{
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<fstream>
#include"SymbolInfo.h"
#include"NonTerminal.h"
#include"SymbolTable.h"
using namespace std;



int yyparse(void);
extern int yylex(void);
extern FILE *yyin;
extern int yylineno;
int errorCount=0;
SymbolTable * table;

ofstream fLog("log.txt");
ofstream fError("error.txt");

void yyerror(const char *s)
{
	fLog<<"Error at Line "<<yylineno<<" : "<<s<<endl;
	fError<<"Error at Line "<<yylineno<<" : "<<s<<endl;
	errorCount++;
}

void yyerror(string s){
	yyerror(s.c_str());
}

void logRule(const char * s){
	fLog<<"Line "<<yylineno<<": "<<s<<'\n';
}

void logPieceOfCode(string s){ /*logs a rule instance i.e. piece of code */
	fLog<<endl;
	fLog<<s<<endl;
	fLog<<endl;
}

%}

%union{
	SymbolInfo * symbol;
	NonTerminal * nonTerminal;
}

%token LPAREN RPAREN SEMICOLON COMMA LCURL RCURL INT FLOAT 
%token VOID LTHIRD RTHIRD FOR IF WHILE RETURN NOT INCOP DECOP
%token <symbol> ID CONST_INT PRINTLN ASSIGNOP LOGICOP RELOP ADDOP MULOP CONST_FLOAT

%nonassoc LESS_THAN_ELSE
%nonassoc ELSE

%type <nonTerminal> start program unit var_declaration func_declaration 
%type <nonTerminal> func_definition type_specifier
%type <nonTerminal> compound_statement statements statement expression_statement
%type <nonTerminal> variable argument_list arguments parameter_list declaration_list 
%type <nonTerminal> expression logic_expression rel_expression simple_expression 
%type <nonTerminal> unary_expression  term  factor

%%

start : program
	{
		//write your code in this block in all the similar blocks below
	}
	;

program : program unit 
	{
		$$=new NonTerminal();
		$$->text+=$1->text;
		$$->text+="\n";
		$$->text+=$2->text;
		logPieceOfCode($$->text);
		logRule("program : program unit");
		delete $1;
		delete $2;
	}
	| unit
	{
		

		$$=new NonTerminal();
		$$->text+=$1->text;
		logPieceOfCode($$->text);
		logRule("program : unit");
		delete $1;
	}
	;
	
unit : var_declaration
	{
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPieceOfCode($$->text);
		logRule("unit : var_declaration");
		delete $1;
	}
     | func_declaration
	 {
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPieceOfCode($$->text);
		logRule("unit : func_declaration");
		delete $1;
	 }
     | func_definition
	 {
		$$=new NonTerminal();
		$$->text+=$1->text;
		logPieceOfCode($$->text);
		logRule("unit : func_definition");
		delete $1;
	 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
		{
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="(";
			$$->text+=$4->text;
			$$->text+=")";
			$$->text+=";";
			logPieceOfCode($$->text);
			logRule("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
			delete $1;
			delete $4;

			//symbol delete
			delete $2;


		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="();";
			logPieceOfCode($$->text);
			logRule("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
			delete $1;

			//symbol delete
			delete $2;
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="(";
			$$->text+=$4->text;
			$$->text+=")";
			$$->text+=$6->text;
			logPieceOfCode($$->text);
			logRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
			delete $1;
			delete $4;
			delete $6;

			//symbol delete
			delete $2;
		}
		| type_specifier ID LPAREN RPAREN compound_statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="()";
			$$->text+=$5->text;
			logPieceOfCode($$->text);
			logRule("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
			delete $1;
			delete $5;

			//symbol delete
			delete $2;
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->text;
			$$->text+=" ";
			$$->text+=$4->getName();
			logPieceOfCode($$->text);
			logRule("parameter_list  : parameter_list COMMA type_specifier ID");
			delete $1;
			delete $3;

			//symbol delete
			delete $4;

		}
		| parameter_list COMMA type_specifier
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->text;
			logPieceOfCode($$->text);
			logRule("parameter_list  : parameter_list COMMA type_specifier");
			delete $1;
			delete $3;
		}
 		| type_specifier ID
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			logPieceOfCode($$->text);
			logRule("parameter_list  : type_specifier ID");
			delete $1;

			//symbol delete
			delete $2;
		}
		| type_specifier
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("parameter_list : type_specifier");
			delete $1;
		}
 		;

 		
compound_statement : LCURL statements RCURL
		{
			

			$$=new NonTerminal();
			$$->text+="{";
			$$->text+="\n";
			$$->text+=$2->text;
			$$->text+="\n}";
			logPieceOfCode($$->text);
			logRule("compound_statement : LCURL statements RCURL");
			delete $2;

		}
 		| LCURL RCURL
		{
			$$=new NonTerminal();
			$$->text+="{\n}";
			logPieceOfCode($$->text);
			logRule("compound_statement : LCURL RCURL");
		}
 		;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->text;
			$$->text+=";";
			logPieceOfCode($$->text);
			logRule("var_declaration : type_specifier declaration_list SEMICOLON");
			delete $1;
			delete $2;
		}
 		 ;
 		 
type_specifier	: INT
		{
			$$=new NonTerminal();
			$$->text="int";
			logPieceOfCode($$->text);
			logRule("type_specifier	: INT");
		}
 		| FLOAT
		{
			$$=new NonTerminal();
			$$->text="float";
			logPieceOfCode($$->text);
			logRule("type_specifier	: FLOAT");
		}
 		| VOID
		{
			$$=new NonTerminal();
			$$->text="void";
			logPieceOfCode($$->text);
			logRule("type_specifier	: VOID");
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->getName();
			logPieceOfCode($$->text);
			logRule("declaration_list : declaration_list COMMA ID");
			delete $1;

			//symbol delete
			delete $3;
		}
 		| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->getName();
			$$->text+="[";
			$$->text+=$5->getName();
			$$->text+="]";
			logPieceOfCode($$->text);
			logRule("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");


			delete $1;

			//symbol delete
			delete $3;
			delete $5;
		}
 		| ID
		{
			$$=new NonTerminal();
			$$->text+=$1->getName();
			logPieceOfCode($$->text);
			logRule("declaration_list : ID");
			
			//symbol delete
			delete $1;
		}
 		| ID LTHIRD CONST_INT RTHIRD
		{
			$$=new NonTerminal();
			$$->text+=$1->getName();
			$$->text+="[";
			$$->text+=$3->getName();
			$$->text+="]";
			logPieceOfCode($$->text);
			logRule("declaration_list : ID LTHIRD CONST_INT RTHIRD");

			//symbol delete
			delete $1;
			delete $3;
		}
 		;
 		  
statements : statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("statements : statement");
			delete $1;
		}
	   | statements statement
	   {
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+="\n";
			$$->text+=$2->text;
			logPieceOfCode($$->text);
			logRule("statements : statements statement");
			delete $1;
			delete $2;
	   }
	   ;
	   
statement : var_declaration
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("statement : var_declaration");
			delete $1;
		}
	  | expression_statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("statement : expression_statement");
			delete $1;
		}
	  | compound_statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("statement : compound_statement");
			delete $1;
		}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
		{
			$$=new NonTerminal();
			$$->text+="for(";
			$$->text+=$3->text;
			$$->text+=$4->text;
			$$->text+=$5->text;
			$$->text+=")\n";
			$$->text+=$7->text;
			logPieceOfCode($$->text);
			logRule("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
			delete $3;
			delete $4;
			delete $5;
			delete $7;
		}
	  | IF LPAREN expression RPAREN statement %prec LESS_THAN_ELSE
		{
			

			$$=new NonTerminal();
			$$->text+="if(";
			$$->text+=$3->text;
			$$->text+=")\n";
			$$->text+=$5->text;
			logPieceOfCode($$->text);
			logRule("statement : IF LPAREN expression RPAREN statement");
			delete $3;
			delete $5;

		}
	  | IF LPAREN expression RPAREN statement ELSE statement
		{
			$$=new NonTerminal();
			$$->text+="if(";
			$$->text+=$3->text;
			$$->text+=")\n";
			$$->text+=$5->text;
			$$->text+="else\n";
			$$->text+=$7->text;
			logPieceOfCode($$->text);
			logRule("statement :  IF LPAREN expression RPAREN statement ELSE statement");
			delete $3;delete $5;delete $7;

		}
	  | WHILE LPAREN expression RPAREN statement
		{
			$$=new NonTerminal();
			$$->text+="while(";
			$$->text+=$3->text;
			$$->text+=")\n";
			$$->text+=$5->text;
			logPieceOfCode($$->text);
			logRule("statement :  WHILE LPAREN expression RPAREN statement");
			delete $3;delete $5;
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
		{
			
			$$=new NonTerminal();
			$$->text+="printf(";
			$$->text+=$3->getName();
			$$->text+=");";

			logPieceOfCode($$->text);
			logRule("statement :  PRINTLN LPAREN ID RPAREN SEMICOLON");
			
			//symbol delete
			delete $3;
		}
	  | RETURN expression SEMICOLON
		{
			$$=new NonTerminal();
			$$->text+="return ";
			$$->text+=$2->text;
			$$->text+=";";
			logPieceOfCode($$->text);
			logRule("statement : RETURN expression SEMICOLON");
			delete $2;
		}
	  ;
	  
expression_statement 	: SEMICOLON	
		{
			

			$$=new NonTerminal();
			$$->text+=";";
			logPieceOfCode($$->text);
			logRule("expression_statement : SEMICOLON	");


		}		
			| expression SEMICOLON 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=";";
			logPieceOfCode($$->text);
			logRule("expression_statement : expression SEMICOLON ");
			delete $1;
		}
			;
	  
variable : ID 
		{
			

			$$=new NonTerminal();
			$$->text+=$1->getName();
			logPieceOfCode($$->text);
			logRule("variable : ID ");
			
			//symbol delete
			delete $1;

		}		
	 | ID LTHIRD expression RTHIRD 
		{
			$$=new NonTerminal();
			$$->text+=$1->getName();
			$$->text+="[";
			$$->text+=$3->text;
			$$->text+="]";
			logPieceOfCode($$->text);
			logRule("variable : ID LTHIRD expression RTHIRD ");
			delete $3;

			//symbol delete
			delete $1;

		}
	 ;
	 
 expression : logic_expression	
		{
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("expression : logic_expression	");
			delete $1;
		}
	   | variable ASSIGNOP logic_expression 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+="=";
			$$->text+=$3->text;
			logPieceOfCode($$->text);
			logRule("expression : variable ASSIGNOP logic_expression");
			delete $1;
			delete $3;
		}	
	   ;
			
logic_expression : rel_expression 	
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("logic_expression : rel_expression");
			delete $1;
		}
		 | rel_expression LOGICOP rel_expression 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			logPieceOfCode($$->text);
			logRule("logic_expression : rel_expression LOGICOP rel_expression");
			delete $1;
			delete $3;

			//symbol delete
			delete $2;
		}	
		 ;
			
rel_expression	: simple_expression 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("rel_expression	: simple_expression ");
			delete $1;
		}
		| simple_expression RELOP simple_expression	
		{
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			logPieceOfCode($$->text);
			logRule("rel_expression	: simple_expression RELOP simple_expression	");
			delete $1;delete $3;

			//symbol delete 
			delete $2;
		}
		;
				
simple_expression : term 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("simple_expression : term ");
			delete $1;
		}
		  | simple_expression ADDOP term 
		{
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			logPieceOfCode($$->text);
			logRule("simple_expression : simple_expression ADDOP term");
			delete $1;
			delete $3;

			//symbol delete
			delete $2;
		}
		  ;
					
term :	unary_expression
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("term :	unary_expression");
			delete $1;
		}
     |  term MULOP unary_expression
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			logPieceOfCode($$->text);
			logRule("term : term MULOP unary_expression");
			delete $1;
			delete $3;

			//symbol delete 
			delete $2;
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			$$=new NonTerminal();
			$$->text+=$1->getName();
			$$->text+=$2->text;
			logPieceOfCode($$->text);
			logRule("unary_expression : ADDOP unary_expression ");
			delete $2;

			//symbol delete
			delete $1;
		}
		 | NOT unary_expression 
		{
			$$=new NonTerminal();
			$$->text+="!";
			$$->text+=$2->text;
			logPieceOfCode($$->text);
			logRule("unary_expression : NOT unary_expression ");
			delete $2;
		}
		 | factor 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("unary_expression : factor");
			delete $1;
		}
		 ;
	
factor	: variable 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("factor	: variable ");
			delete $1;
		}
	| ID LPAREN argument_list RPAREN
		{
			

			$$=new NonTerminal();
			$$->text+=$1->getName();
			$$->text+="(";
			$$->text+=$3->text;
			$$->text+=")";
			logPieceOfCode($$->text);
			logRule("factor : ID LPAREN argument_list RPAREN");
			delete $3;

			//symbol delete
			delete $1;
		}
	| LPAREN expression RPAREN
		{
			$$=new NonTerminal();
			$$->text+="(";
			$$->text+=$2->text;
			$$->text+=")";
			logPieceOfCode($$->text);
			logRule("factor : LPAREN expression RPAREN");
			delete $2;
		}
	| CONST_INT
		{
			$$=new NonTerminal();
			$$->text+=$1->getName();
			logPieceOfCode($$->text);
			logRule("factor	: CONST_INT");

			//symbol delete
			delete $1;
		} 
	| CONST_FLOAT
		{
			$$=new NonTerminal();
			$$->text+=$1->getName();
			logPieceOfCode($$->text);
			logRule("factor	: CONST_FLOAT");

			//symbol delete
			delete $1;
		}
	| variable INCOP 
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+="++";
			logPieceOfCode($$->text);
			logRule("factor	: variable INCOP");
			delete $1;

		}
	| variable DECOP
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+="--";
			logPieceOfCode($$->text);
			logRule("factor	: variable DECOP");
			delete $1;
		}
	;
	
argument_list : arguments
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("argument_list : arguments");
			delete $1;
		}
			  |
		{
			$$=new NonTerminal();
			logPieceOfCode($$->text);
			logRule("argument_list : empty");
		};
	
arguments : arguments COMMA logic_expression
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->text;
			logPieceOfCode($$->text);
			logRule("arguments : arguments COMMA logic_expression");
			delete $1;
			delete $3;
		}
	      | logic_expression
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logPieceOfCode($$->text);
			logRule("arguments : logic_expression");
			delete $1;
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
	table=new SymbolTable(7);	
	yyin=fp;
	yyparse();

	fLog<<"Total Lines : "<<yylineno<<endl;
	fLog<<"Total Errors : "<<errorCount<<endl;

	/* delete memories*/
	delete table;

	/*close opended files*/
	fLog.close();
	fError.close();
	fclose(fp);

	return 0;
}

