
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
	fLog<<"Error at line "<<yylineno<<" : "<<s<<endl;
	fError<<"Error at line "<<yylineno<<" : "<<s<<endl<<endl;
	errorCount++;
}
void yyerror(string s){
	yyerror(s.c_str());
}
void logNewLine(){
	fLog<<endl;
}
void logGrammer(const char * s){
	fLog<<"Line "<<yylineno<<": "<<s<<endl;
}

void logPiece(string s){ /*logs a rule instance i.e. piece of code */
	logNewLine();
	fLog<<s<<endl;
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

bool compareFunctions(SymbolInfo * s1,SymbolInfo * s2){
	FunctionInfo * f1=s1->functionInfo;
	FunctionInfo * f2=s2->functionInfo;
	if(f1->returnType!=f2->returnType)
		return false;
	if(f1->dataTypes.size()!=f2->dataTypes.size())
		return false;
	for(int i=0;i<f1->dataTypes.size();i++){
		if(f1->dataTypes.at(i)!=f2->dataTypes.at(i))
			return false;
	}
	return true;
}

bool checkExpressionType(Expression * e,string type){
	for(SymbolInfo * s:e->symbols){
		if(s->functionInfo!=NULL && s->functionInfo->returnType!=type){
			return false;
		}else if(s->variableInfo!=NULL && s->variableInfo->dataType!=type){
			return false;
		}else if(type=="int" && s->getType()!="CONST_INT"){
			return false;
		}else if(type=="float" && s->getType()!="CONST_FLOAT"){
			return false;
		}
	}
	return true;
}
ParameterList * currentParameterList=NULL;
void insertVarialblesInScope(){
	if(currentParameterList==NULL)
		return;
	vector<string> pDataTypes=currentParameterList->dataTypes;
	vector<string> pNames=currentParameterList->names;
	for(int i=0;i<pDataTypes.size();i++){
		if(i>=pNames.size()|| pNames.at(i)=="")
			continue;
		SymbolInfo * s=new SymbolInfo(pNames.at(i),"ID");
		s->variableInfo=new VariableInfo(pDataTypes.at(i));
		table->insert(s);
	}
	currentParameterList=NULL;
}

%}

%union{
	SymbolInfo * symbol;
	NonTerminal * nonTerminal;
	ParameterList * parameterList;
	DeclarationList * declarationList;
	Expression * expression;
	Argument * argument;
	Variable * variable;
}

%token LPAREN RPAREN SEMICOLON COMMA LCURL RCURL INT FLOAT VOID LTHIRD RTHIRD FOR IF WHILE RETURN NOT INCOP DECOP
%token <symbol> ID CONST_INT PRINTLN ASSIGNOP LOGICOP RELOP ADDOP MULOP CONST_FLOAT


%nonassoc S_IF
%nonassoc ELSE

%type <nonTerminal> start program unit var_declaration func_declaration func_definition type_specifier 
%type <nonTerminal> compound_statement statements statement expression_statement  
%type <variable> variable 
%type <argument> argument_list arguments
%type<parameterList> parameter_list
%type<declarationList> declaration_list 
%type<expression> expression logic_expression rel_expression simple_expression unary_expression  term  factor


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
			// cout<<"here at 1 "<<$2->getName()<<'\n';
			$2->functionInfo=new FunctionInfo(false);
			$2->functionInfo->returnType=$1->text;
			$2->functionInfo->dataTypes=$4->dataTypes;
			$2->functionInfo->names=$4->names;
			SymbolInfo * s=table->lookup($2->getName());
			if(s!=NULL){
				if(s->functionInfo!=NULL){ /*if s is a function*/
					if(s->functionInfo->isDefined){ /*There already exists a definition*/
						if(compareFunctions($2,s)){ /*definition and declaration match*/
							logGrammer("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
							$$=new NonTerminal();
							$$->text+=$1->text;
							$$->text+=" "+$2->getName();
							$$->text+="(";
							$$->text+=$4->text;
							$$->text+=");";
							logPiece($$->text);
							delete $2;
						}else{ /* declared function do not match with definition*/
							yyerror("Declared Function \""+$2->getName()+"\" does not match previous definition");
							delete $2;
						}
					}else{ /*previous one was declaration,replace it*/
						table->remove($2->getName());
						table->insert($2);
						logGrammer("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
						$$=new NonTerminal();
						$$->text+=$1->text;
						$$->text+=" "+$2->getName();
						$$->text+="(";
						$$->text+=$4->text;
						$$->text+=");";
						logPiece($$->text);
					}
				}else{
					yyerror("Function name "+$2->getName()+" conflicts with existing variable");
					delete $2;
				}
			}else{
				table->insert($2);
				logGrammer("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
				$$=new NonTerminal();
				$$->text+=$1->text;
				$$->text+=" "+$2->getName();
				$$->text+="(";
				$$->text+=$4->text;
				$$->text+=");";
				logPiece($$->text);
			}
			delete $1;delete $4;
		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{	
			$2->functionInfo=new FunctionInfo(false);
			$2->functionInfo->returnType=$1->text;
			SymbolInfo * s=table->lookup($2->getName());
			if(s!=NULL){
				if(s->functionInfo!=NULL){
					if(s->functionInfo->isDefined){
						if(compareFunctions($2,s)){ /*definition and declaration match*/
							logGrammer("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
							$$=new NonTerminal();
							$$->text=$1->text+" "+$2->getName()+"();";
							logPiece($$->text);
							delete $2;
						}else{ /* declared function do not match with definition*/
							yyerror("Declared Function \""+$2->getName()+"\" does not match previous definition");
							delete $2;
						}
					}else{
						table->remove($2->getName());
						table->insert($2);
						logGrammer("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
						$$=new NonTerminal();
						$$->text=$1->text+" "+$2->getName()+"();";
						table->insert($2);
						logPiece($$->text);
					}
				}else{
					yyerror("Function name "+$2->getName()+" conflicts with existing variable");
					delete $2;
				}
			}else{
				
				logGrammer("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
				$$=new NonTerminal();
				$$->text=$1->text+" "+$2->getName()+"();";
				logPiece($$->text);
				table->insert($2);
			}
			deleteNonTerminal($1);
			
		}
	
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{
			logGrammer("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
			$$=new NonTerminal();
			$$->text=$1->text+" "+$2->getName()+"("+$4->text+")"+$6->text;
			// table->insert($2);
			logPiece($$->text);
			
			$2->functionInfo=new FunctionInfo(true);
			$2->functionInfo->dataTypes=$4->dataTypes;
			$2->functionInfo->names=$4->names;

			SymbolInfo * s=table->lookup($2->getName());

			if(s!=NULL){
				if(s->functionInfo!=NULL){
					if(s->functionInfo->isDefined){
						yyerror("Function \""+$2->getName()+"\" already defined");
						delete $2;
					}else{
						if(compareFunctions(s,$2)){
							table->remove($2->getName());
							table->insert($2);
						}else{
							yyerror("Function \""+$2->getName()+"\" conflicts with previous declaration");
							delete $2;
						}
					}
				}else{
					yyerror("Function name "+$2->getName()+" conflicts with existing variable");
					delete $2;
				}
			}else{
				table->insert($2);
			}

			deleteNonTerminal($1);
			delete $4;
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
			logPiece($$->text);

			$2->functionInfo=new FunctionInfo(true);
			$2->functionInfo->returnType=$1->text;
			SymbolInfo * s=table->lookup($2->getName());

			if(s!=NULL){
				if(s->functionInfo!=NULL){
					if(s->functionInfo->isDefined){
						yyerror("Function \""+$2->getName()+"\" already defined");
						delete $2;
					}else{
						if(compareFunctions(s,$2)){
							table->remove($2->getName());
							table->insert($2);
						}else{
							yyerror("Function \""+$2->getName()+"\" conflicts with previous declaration");
							delete $2;
						}
					}
				}else{
					yyerror("Function name "+$2->getName()+" conflicts with existing variable");
					delete $2;
				}
			}else{
				table->insert($2);
			}

			deleteNonTerminal($1);
			deleteNonTerminal($5);
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			logGrammer("parameter_list  : parameter_list COMMA type_specifier ID");
			$$=new ParameterList(); 
			$$->text=$1->text+","+$3->text+" "+$4->getName();
			logPiece($$->text);

			$$->dataTypes=$1->dataTypes;
			$$->names=$1->names;

			$$->dataTypes.push_back($3->text);
			$$->names.push_back($4->getName());
			currentParameterList=$$;

			delete $1;
			deleteNonTerminal($3);
			delete $4;
		}
		| parameter_list COMMA type_specifier
		{
			logGrammer("parameter_list  : parameter_list COMMA type_specifier");
			$$=new ParameterList();
			$$->text=$1->text+","+$3->text;
			logPiece($$->text);

			$$->dataTypes=$1->dataTypes;
			$$->names=$1->names;

			$$->dataTypes.push_back($3->text);
			$$->names.push_back("");
			currentParameterList=$$;

			delete $1;
			deleteNonTerminal($3);
		}
 		| type_specifier ID
		{
			logGrammer("parameter_list  : type_specifier ID");
			$$=new ParameterList();
			$$->text=$1->text+" "+$2->getName();
			logPiece($$->text);
			
			$$->dataTypes.push_back($1->text);
			$$->names.push_back($2->getName());
			currentParameterList=$$;
			delete $1;
		}
		| type_specifier
		{
			logGrammer("parameter_list  : type_specifier");
			$$=new ParameterList();
			$$->text=$1->text;
			logPiece($$->text);

			$$->dataTypes.push_back($1->text);
			$$->names.push_back("");
			currentParameterList=$$;
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
			

			for(int i=0;i<$2->symbols.size();i++){
				SymbolInfo * s=$2->symbols.at(i);
				if(table->lookup(s->getName())!=NULL){
					yyerror("Multiple declaration of "+s->getName());
					delete s;
				}else{
					s->variableInfo->dataType=$1->text;
					table->insert(s);
				}
			}

			delete $2;
			deleteNonTerminal($1);
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
			$$=new DeclarationList();
			$$->text=$1->text+","+$3->getName();
			logPiece($$->text);
			
			$$->symbols=$1->symbols;
			$3->variableInfo=new VariableInfo("int");
			$$->symbols.push_back($3);

			delete $1;

		}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
			logGrammer("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
			$$=new DeclarationList();
			$$->text=$1->text+","+$3->getName()+"["+$5->getName()+"]";
			logPiece($$->text);

			$$->symbols=$1->symbols;
			$3->variableInfo=new VariableInfo("int",new ArrayInfo(std::stoi($5->getName())));
			$$->symbols.push_back($3);

			delete $1;
			delete $5;
		}
 		  | ID
		{
			logGrammer("declaration_list : ID");
			$$=new DeclarationList();
			$$->text=$1->getName();
			logPiece($$->text);

			$1->variableInfo=new VariableInfo("int");
			$$->symbols.push_back($1);
		}
 		  | ID LTHIRD CONST_INT RTHIRD
		{
			logGrammer("declaration_list : ID LTHIRD CONST_INT RTHIRD");
			$$=new DeclarationList();
			$$->text=$1->getName()+"["+$3->getName()+"]";
			logPiece($$->text);

			$1->variableInfo=new VariableInfo("int",new ArrayInfo(std::stoi($3->getName())));
			$$->symbols.push_back($1);

			delete $3;

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
			logGrammer("variable : ID");
			$$=new Variable();
			$$->text=$1->getName();
			logPiece($$->text);
			SymbolInfo * v=table->lookup($1->getName());
			if(v==NULL){
				yyerror("Undeclared Variable "+$1->getName());
			}else if (v->variableInfo==NULL){
				yyerror(v->getName()+" is not a variable");
			}else{
				$$->name=v->getName();
			}
			delete $1;
		}
	 | ID LTHIRD expression RTHIRD 
		{	
			// cout<<"here\n";
			logGrammer("variable : ID LTHIRD expression RTHIRD");
			/*DEBUG_LATER SYMBOL_TABLE*/
			$$=new Variable();
			$$->text=$1->getName()+"["+$3->text+"]";
			logPiece($$->text);

			SymbolInfo * v=table->lookup($1->getName());
			if(v==NULL){
				yyerror("Undeclared Variable "+$1->getName());
			}else if (v->variableInfo==NULL){
				yyerror(v->getName()+" is not a variable");
			}else if(v->variableInfo->arrayInfo==NULL){
				yyerror(v->getName()+" is not an array");
			}else{
				if(checkExpressionType($3,"int")==false){
					yyerror("Expression inside third brackets not an integer");	
				}
				$$->name=v->getName();
			}
			delete $1;
			delete $3;
			// cout<<"here again\n";
		}
	 ;
	 
 expression : logic_expression	
		{
			logGrammer("expression : logic_expression");
			$$=new Expression();
			$$->text=$1->text;
			logPiece($$->text);

			$$->symbols=$1->symbols;

			delete $1;
		}
	   | variable ASSIGNOP logic_expression
		{
			logGrammer("expression : variable ASSIGNOP logic_expression");
			$$=new Expression();
			$$->text=$1->text+"="+$3->text;
			logPiece($$->text);
			$$->symbols=$3->symbols;

			SymbolInfo * v=table->lookup($1->text);
			if(v==NULL)
				yyerror("Undeclared Variable in expression "+$1->text);
			else if(v->variableInfo==NULL){
				yyerror("Assignment to non-variable identifier");
			}
			else{
				if(checkExpressionType($3,v->variableInfo->dataType)){
					$$->symbols.push_back(v);
				}else{
					yyerror("Type Mismatch");
				}
			}

			deleteNonTerminal($1);
			delete $3;
		}
	   ;
			
logic_expression : rel_expression 	
		{
			logGrammer("logic_expression : rel_expression");
			$$=new Expression();
			$$->text=$1->text;
			logPiece($$->text);

			$$->symbols=$1->symbols;

			delete $1;
		}
		 | rel_expression LOGICOP rel_expression 
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("logic_expression : rel_expression LOGICOP rel_expression");
			$$=new Expression();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);

			$$->symbols=$1->symbols;
			$$->symbols.insert($$->symbols.end(),$3->symbols.begin(),$3->symbols.end());
			if(!checkExpressionType($1,"int") || !checkExpressionType($3,"int")){
				yyerror("Logical Expression Must Evaluate to Integer");
			}
			delete $1;delete $3;
			delete $2;
		}	
		 ;
			
rel_expression	: simple_expression 
		{
			logGrammer("rel_expression	: simple_expression");
			$$=new Expression();
			$$->text=$1->text;
			logPiece($$->text);

			$$->symbols=$1->symbols;
			// if(checkExpressionType($1,"int")==false){
			// 	yyerror("Relational Expression Must Evaluate to Integer");
			// }
			delete $1;
		}
		| simple_expression RELOP simple_expression	
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("rel_expression	: simple_expression RELOP simple_expression");
			$$=new Expression();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);

			$$->symbols=$1->symbols;
			$$->symbols.insert($$->symbols.end(),$3->symbols.begin(),$3->symbols.end());
			if(checkExpressionType($1,"int")==false){
				yyerror("Relational Expression Must Evaluate to Integer");
			}
			if(checkExpressionType($3,"int")==false){
				yyerror("Relational Expression Must Evaluate to Integer");
			}
			delete $1;delete $3;
			delete $2;
		}
		;
				
simple_expression : term 
		{
			logGrammer("simple_expression : term");
			$$=new Expression();
			$$->text=$1->text;
			logPiece($$->text);
			$$->symbols=$1->symbols;
			delete($1);
		}
		  | simple_expression ADDOP term 
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("simple_expression : simple_expression ADDOP term");
			$$=new Expression();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);
			$$->symbols=$1->symbols;
			$$->symbols.insert($$->symbols.end(),$3->symbols.begin(),$3->symbols.end());
			delete $1;
			delete $3 ;
			delete $2;
		}
		  ;
					
term :	unary_expression
		{
			logGrammer("term :	unary_expression");
			$$=new Expression();
			$$->text=$1->text;
			logPiece($$->text);
			$$->symbols=$1->symbols;
			delete $1;
		}
     |  term MULOP unary_expression
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("term :	term MULOP unary_expression");
			$$=new Expression();
			$$->text=$1->text+$2->getName()+$3->text;
			logPiece($$->text);
			$$->symbols=$1->symbols;
			$$->symbols.insert($$->symbols.end(),$3->symbols.begin(),$3->symbols.end());
			delete $1;
			delete $3;
			delete $2;
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("unary_expression : ADDOP unary_expression");
			$$=new Expression();
			$$->text=$1->getName()+$2->text;
			logPiece($$->text);
			$$->symbols=$2->symbols;
			delete $2;
			delete $1;
		}
		 | NOT unary_expression 
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("unary_expression : NOT unary_expression");
			$$=new Expression();
			$$->text="!"+$2->text;
			logPiece($$->text);
			$$->symbols=$2->symbols;
			delete $2;
		}
		 | factor 
		{
			logGrammer("unary_expression : factor");
			$$=new Expression();
			$$->text=$1->text;
			logPiece($$->text);
			$$->symbols=$1->symbols;
			delete $1;
		}
		 ;
	
factor : variable 
		{
			logGrammer("factor : variable");
			$$=new Expression();
			$$->text=$1->text;
			logPiece($$->text);
			SymbolInfo * v=table->lookup($1->name);
			if(v==NULL){
				yyerror("Undeclared variable "+v->getName());
			}else if(v->variableInfo==NULL){
				yyerror(v->getName()+" is not a variable");
			}else{
				$$->symbols.push_back(v);
			}
			delete $1;
		}
	| ID LPAREN argument_list RPAREN
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("factor : ID LPAREN argument_list RPAREN");
			$$=new Expression();
			$$->text=$1->getName()+"("+$3->text+")";
			logPiece($$->text);
			SymbolInfo * f=table->lookup($1->getName());
			if(f==NULL){
				yyerror("Undeclared or Undefined Function "+$1->getName());
			}else if(f->functionInfo==NULL){
				yyerror($1->getName()+" is not a function");
			}else{
				if($3->dataTypes.size()<f->functionInfo->dataTypes.size()){
					yyerror("Too few Arguments for function "+f->getName());
				}else if($3->dataTypes.size()>f->functionInfo->dataTypes.size()){
					yyerror("Too Many Arguments for function "+f->getName());
				}else{
					for(int i=0;i<$3->dataTypes.size();i++){
						if($3->dataTypes.at(i)!=f->functionInfo->dataTypes.at(i)){
							yyerror(i+"th Argument mismatch of function "+$3->text);
						}
					}
					$$->symbols.push_back(f);
				}
			}
			delete $3;
			delete $1;
			
		}
	| LPAREN expression RPAREN
		{
			logGrammer("factor : LPAREN expression RPAREN");
			$$=new Expression();
			$$->text="("+$2->text+")";
			logPiece($$->text);
			$$->symbols=$2->symbols;
			delete $2;
		}
	| CONST_INT
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("factor : CONST_INT");
			$$=new Expression();
			$$->text=$1->getName();
			logPiece($$->text);
			$$->symbols.push_back($1);
		}
	| CONST_FLOAT
		{
			/*DEBUG_LATER SYMBOL_TABLE*/
			logGrammer("factor : CONST_FLOAT");
			$$=new Expression();
			$$->text=$1->getName();
			logPiece($$->text);
			$$->symbols.push_back($1);
		}
	| variable INCOP 
		{
			logGrammer("factor : variable INCOP");
			$$=new Expression();
			$$->text=$1->text+"++";
			logPiece($$->text);
			SymbolInfo * v=table->lookup($1->name);
			if(v==NULL){
				yyerror("Undeclared Variable "+$1->name);
			}else{
				if(v->variableInfo==NULL){
					yyerror(v->getName()+" is not a variable");
				}else{
					$$->symbols.push_back(v);
				}
			}
			delete $1;
		}
	| variable DECOP
		{
			logGrammer("factor : variable DECOP");
			$$->text=$1->text+"--";
			logPiece($$->text);
			SymbolInfo * v=table->lookup($1->name);
			if(v==NULL){
				yyerror("Undeclared Variable "+$1->name);
			}else{
				if(v->variableInfo==NULL){
					yyerror(v->getName()+" is not a variable");
				}else{
					$$->symbols.push_back(v);
				}
			}
			delete($1);
		}
	;
	
argument_list : arguments
		{
			logGrammer("argument_list : arguments");
			$$=new Argument();
			$$->text=$1->text;
			logPiece($$->text);
			$$->dataTypes=$1->dataTypes;
			delete($1);
		}
		|
		{
			logGrammer("argument_list : empty");
			$$=new Argument();
			$$->text="";
		}
		;
	
arguments : arguments COMMA logic_expression
		{
			logGrammer("arguments : arguments COMMA logic_expression");
			$$=new Argument();
			$$->text=$1->text+","+$3->text;
			logPiece($$->text);
			$$->dataTypes=$1->dataTypes;
			string dataType="int";
			for(SymbolInfo * s:$3->symbols){
				if(s->functionInfo!=NULL){
					if(s->functionInfo->returnType=="float"){
						dataType="float";
					}
				}else if(s->variableInfo!=NULL){
					if(s->variableInfo->dataType=="float"){
						dataType="float";
					}
				}else if(s->getType()=="CONST_FLOAT"){
					dataType="float";
				}
			}
			$$->dataTypes.push_back(dataType);
			delete($1);
			delete($3);
		}
	      | logic_expression
		{
			logGrammer("arguments : logic_expression");
			$$=new Argument();
			$$->text=$1->text;
			logPiece($$->text);
			string dataType="int";
			for(SymbolInfo * s:$1->symbols){
				if(s->functionInfo!=NULL){
					if(s->functionInfo->returnType=="float"){
						dataType="float";
					}
				}else if(s->variableInfo!=NULL){
					if(s->variableInfo->dataType=="float"){
						dataType="float";
					}
				}else if(s->getType()=="CONST_FLOAT"){
					dataType="float";
				}
			}
			$$->dataTypes.push_back(dataType);
			delete($1);
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