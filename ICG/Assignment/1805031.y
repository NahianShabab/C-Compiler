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
#include"writeOptimized.h"
using namespace std;



int yyparse(void);
extern int yylex(void);
extern FILE *yyin;
extern int yylineno;
int errorCount=0;
SymbolTable * table;
Parameter * currentParameterList=NULL;
int stackCount=0;
int labelCount=0;
int tempCount=0;
int asmLineCount=0;
bool isMainFunction=false; // is the current function being analyzed the main function?
// useful to skip "return" statement in main function

ofstream fLog("log.txt");
ofstream fError("error.txt");
ofstream fCode("code.asm");
ofstream fASM("ASM.asm");
ofstream fData("data.asm"); // for storing global data
// ofstream fOptimized("optimized_code.asm");

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
string stkPos(int stackEntry ){
	return to_string((stackCount-stackEntry)*2);
}
string arrStkPos(int stackEntry,int elementNo){
	return to_string((stackCount-stackEntry)*2+elementNo*2);
}

string newLabel()
{
	string lb="L"+to_string(++labelCount);
	return lb;
}

string newTemp(){
	string temp="T"+to_string(++tempCount);
	return temp;
}

void addGlobal(string name,int arrSize=-1){ //if arrSize negative then it's just one variable
	if(arrSize==-1)
		fData<<name<<" DW ?"<<endl;
	else
		fData<<name<<" DW "<<arrSize<<" DUP (?)"<<endl;
}

void compareFunction(SymbolInfo * newFunction,SymbolInfo * oldFunction){
	if(newFunction->functionInfo->isDefined && oldFunction->functionInfo->isDefined){
		yyerror("Multiple Definition of function "+newFunction->getName());
		delete newFunction;
		return;
	}
	if(newFunction->functionInfo->isDefined && !oldFunction->functionInfo->isDefined){
		if(newFunction->functionInfo->returnType!=oldFunction->functionInfo->returnType){
			yyerror("Return type of function "+newFunction->getName()+" does not match declaration");
		}
		if(newFunction->functionInfo->paramDataTypes.size()!=oldFunction->functionInfo->
		paramDataTypes.size()){
			yyerror("Parameter count mismatch of function "+newFunction->getName()+" with declaration");
		}
		for(unsigned int i=0;i<newFunction->functionInfo->paramDataTypes.size();i++){
			string d1=newFunction->functionInfo->paramDataTypes.at(i);
			string d2=oldFunction->functionInfo->paramDataTypes.at(i);
			if(d1!=d2){
				yyerror("Parameter "+to_string(i)+" type mismatch of function "+newFunction->getName()+" with declaration");
			}
		}
		table->remove(oldFunction->getName());
		table->insert(newFunction);
	}
	else if(!newFunction->functionInfo->isDefined && oldFunction->functionInfo->isDefined){
		if(newFunction->functionInfo->returnType!=oldFunction->functionInfo->returnType){
			yyerror("Return type of declared function "+newFunction->getName()+" does not match definition");
		}
		if(newFunction->functionInfo->paramDataTypes.size()!=oldFunction->functionInfo->
		paramDataTypes.size()){
			yyerror("Parameter count mismatch of declared function "+newFunction->getName()+" with definition");
		}
		for(unsigned int i=0;i<newFunction->functionInfo->paramDataTypes.size();i++){
			string d1=newFunction->functionInfo->paramDataTypes.at(i);
			string d2=oldFunction->functionInfo->paramDataTypes.at(i);
			if(d1!=d2){
				yyerror("Parameter "+to_string(i)+" type mismatch of declared function "+newFunction->getName()+" with definition");
			}
		}
		delete newFunction;
	}

	if(!newFunction->functionInfo->isDefined && !oldFunction->functionInfo->isDefined){
		if(newFunction->functionInfo->returnType!=oldFunction->functionInfo->returnType){
			yyerror("Return type of declared function "+newFunction->getName()+" does not match previous declaration");
		}
		if(newFunction->functionInfo->paramDataTypes.size()!=oldFunction->functionInfo->
		paramDataTypes.size()){
			yyerror("Parameter count mismatch of declared function "+newFunction->getName()+" with previous declaration");
		}
		for(unsigned int i=0;i<newFunction->functionInfo->paramDataTypes.size();i++){
			string d1=newFunction->functionInfo->paramDataTypes.at(i);
			string d2=oldFunction->functionInfo->paramDataTypes.at(i);
			if(d1!=d2){
				yyerror("Parameter "+to_string(i)+" type mismatch of declared function "+newFunction->getName()+"with previous declaration");
			}
		}
		delete newFunction;
	}

}

string getTypeOfExpression(Expression * expression){
	string dataType="int";
	if(expression->forceInteger==true){
		return "int";
	}
	for(SymbolInfo * s:expression->symbols){
		if(s->functionInfo!=NULL && s->functionInfo->returnType=="float"){
			dataType="float";
		}else if(s->variableInfo!=NULL && s->variableInfo->dataType=="float"){
			dataType="float";
		}else if(s->getType()=="CONST_FLOAT"){
			dataType="float";
		}
	}
	return dataType;
}

bool expHasVoidFunc(Expression * expression){
	for(SymbolInfo * s:expression->symbols){
		if(s->functionInfo!=NULL && s->functionInfo->returnType=="void"){
			return true;
		}
	}
	return false;
}

void writeASM(string s){
	fASM<<s<<endl;
	asmLineCount++;
}
void asmComment(string s){
	fASM<<";"<<s<<endl;
	asmLineCount++;
}



%}

%union{
	SymbolInfo * symbol;
	NonTerminal * nonTerminal;
	Parameter * parameter;
	DeclarationList * declarationList;
	Expression * expression;
	Variable * variable;
	Argument * argument;
	While * whileControl;
	If * ifControl;
	For * forControl;
}

%token LPAREN RPAREN SEMICOLON COMMA LCURL RCURL INT FLOAT 
%token VOID LTHIRD RTHIRD RETURN NOT INCOP DECOP
%token <symbol> ID CONST_INT PRINTLN ASSIGNOP LOGICOP RELOP ADDOP MULOP CONST_FLOAT PRINTCHAR
%token <whileControl> WHILE
%token <ifControl> IF
%token <forControl> FOR

%nonassoc LESS_THAN_ELSE
%nonassoc ELSE

%type <nonTerminal> start program unit var_declaration func_declaration 
%type <nonTerminal> func_definition type_specifier
%type <nonTerminal> compound_statement statements statement 
%type <parameter> parameter_list
%type <ifControl> if_expression
%type <declarationList> declaration_list
%type <variable> variable
%type <expression> unary_expression term  factor expression logic_expression 
%type <expression> rel_expression simple_expression expression_statement
%type <argument> argument_list arguments

%%

start :program
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
		logRule("program : program unit");
		logPieceOfCode($$->text);
		
		delete $1;
		delete $2;
	}
	| unit
	{
		

		$$=new NonTerminal();
		$$->text+=$1->text;
		logRule("program : unit");
		logPieceOfCode($$->text);
		
		delete $1;
	}
	;
	
unit : var_declaration
	{
		$$=new NonTerminal();
		$$->text+=$1->text;
		logRule("unit : var_declaration");
		logPieceOfCode($$->text);
		
		delete $1;
	}
     | func_declaration
	 {
		$$=new NonTerminal();
		$$->text+=$1->text;
		logRule("unit : func_declaration");
		logPieceOfCode($$->text);
		
		delete $1;
	 }
     | func_definition
	 {
		$$=new NonTerminal();
		$$->text+=$1->text;
		logRule("unit : func_definition");
		logPieceOfCode($$->text);
		
		delete $1;
	 }
     ;



func_declaration : type_specifier ID LPAREN  parameter_list RPAREN SEMICOLON
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="(";
			$$->text+=$4->text;
			$$->text+=")";
			$$->text+=";";
			logRule("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
			logPieceOfCode($$->text);
			currentParameterList=NULL;

			$2->functionInfo=new FunctionInfo($1->text,false,$4->dataTypes);
			SymbolInfo * oldSymbol=table->lookup($2->getName());
			if(oldSymbol==NULL)
				table->insert($2);
			else if(oldSymbol->functionInfo==NULL){
				yyerror("function "+$2->getName()+" conflicts with prevoius non-function symbol");
				delete $2;
			}
			else
				compareFunction($2,oldSymbol);

			delete $1;
			delete $4;

		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="();";
			logRule("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
			logPieceOfCode($$->text);

			$2->functionInfo=new FunctionInfo($1->text,false);
			SymbolInfo * oldSymbol=table->lookup($2->getName());
			if(oldSymbol==NULL)
				table->insert($2);
			else if(oldSymbol->functionInfo==NULL){
				yyerror("function "+$2->getName()+" conflicts with prevoius non-function symbol");
				delete $2;
			}
			else
				compareFunction($2,oldSymbol);			
			
			delete $1;

		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN
{	
	$2->functionInfo=new FunctionInfo($1->text,true,$4->dataTypes);
	SymbolInfo * oldSymbol=table->lookup($2->getName());
	if(oldSymbol==NULL)
		table->insert($2);
	else if(oldSymbol->functionInfo==NULL){
		yyerror("function "+$2->getName()+" conflicts with prevoius non-function symbol");
		delete $2;
	}
	else
		compareFunction($2,oldSymbol);

	writeASM($2->getName()+" PROC");writeASM("");
	if($2->getName()=="main"){
		writeASM("MOV AX,@DATA");
		writeASM("MOV DS,AX");
		isMainFunction=true;
	}else{
		isMainFunction=false;
	}
	table->enterScope();
        if(currentParameterList!=NULL && $2->getName()!="main"){
            //insert parameters here
            for(int i=0;i<currentParameterList->dataTypes.size();i++){
                if(currentParameterList->dataTypes.at(i)=="void"){
                        yyerror("void data type at parameter no "+to_string(i));
                        continue;
                }
                if(currentParameterList->names.at(i)==""){
                        continue;
                }
                SymbolInfo * s=new SymbolInfo(currentParameterList->names.at(i),"ID");
                s->variableInfo=new VariableInfo(currentParameterList->dataTypes.at(i));
                if(table->insert(s)==false){
                        yyerror("Multiple Declaration of "+s->getName());
                }else{
					s->variableInfo->stackEntry=stackCount-1-(currentParameterList->dataTypes.size()-i-1);
					s->variableInfo->isParameter=true;
				}
            }
        }
        table->printAllScopeTable(fLog);
        currentParameterList=NULL;
}
compound_statement
{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="(";
			$$->text+=$4->text;
			$$->text+=")";
			$$->text+=$7->text;
			logRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
			logPieceOfCode($$->text);
			if(table->isRootScope()){
                yyerror("Invalid Scope");
        	}else{
                table->printCurrentScopeTable(fLog);
                table->exitScope();
        	}

			if($2->getName()=="main"){
				writeASM("MOV AX,4CH");
				writeASM("INT 21H");
			}else{
				if($1->text=="void"){
					table->deleteAllTemporaryVariable();
					writeASM("RET");
				}
			}
			writeASM("");
			writeASM($2->getName()+" ENDP");
			writeASM("");
			if($2->getName()=="main"){
				writeASM("END main");
			}
			
			delete $1;
			delete $4;
			delete $7;
		}
		| type_specifier ID LPAREN RPAREN
		
		{
		    $2->functionInfo=new FunctionInfo($1->text,true);
			SymbolInfo * oldSymbol=table->lookup($2->getName());
			if(oldSymbol==NULL)
				table->insert($2);
			else if(oldSymbol->functionInfo==NULL){
				yyerror("function "+$2->getName()+" conflicts with prevoius non-function symbol");
				delete $2;
			}
			else
				compareFunction($2,oldSymbol);
		writeASM($2->getName()+" PROC");
		writeASM("");
		if($2->getName()=="main"){
			writeASM("MOV AX,@DATA");
			writeASM("MOV DS,AX");
			isMainFunction=true;
		}else{
			isMainFunction=false;
		}
		table->enterScope();
		}

		 compound_statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			$$->text+="(";
			$$->text+=")";
			$$->text+=$6->text;
			logRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
			logPieceOfCode($$->text);
			if(table->isRootScope()){
                yyerror("Invalid Scope");
        	}else{
                table->printCurrentScopeTable(fLog);
                table->exitScope();
        	}
			
			
			if($2->getName()=="main"){
				writeASM("MOV AX,4CH");
				writeASM("INT 21H");
			}else{
				if($1->text=="void"){
					writeASM("RET");
				}
			}
			writeASM("");
			writeASM($2->getName()+" ENDP");
			writeASM("");
			if($2->getName()=="main"){
				writeASM("END main");
			}
		
			
			delete $1;
			delete $6;
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			

			$$=new Parameter();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->text;
			$$->text+=" ";
			$$->text+=$4->getName();
			logRule("parameter_list  : parameter_list COMMA type_specifier ID");
			logPieceOfCode($$->text);
			

			$$->dataTypes=$1->dataTypes;
			$$->names=$1->names;
			$$->dataTypes.push_back($3->text);
			$$->names.push_back($4->getName());
			
			currentParameterList=$$;


			delete $1;
			delete $3;

			//symbol delete
			delete $4;

		}
		| parameter_list COMMA type_specifier
		{
			$$=new Parameter();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->text;
			logRule("parameter_list  : parameter_list COMMA type_specifier");
			logPieceOfCode($$->text);
			
			$$->dataTypes=$1->dataTypes;
			$$->names=$1->names;
			$$->dataTypes.push_back($3->text);
			$$->names.push_back("");

			currentParameterList=$$;

			delete $1;
			delete $3;
		}
 		| type_specifier ID
		{
			$$=new Parameter();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->getName();
			logRule("parameter_list  : type_specifier ID");
			logPieceOfCode($$->text);
			
			$$->dataTypes.push_back($1->text);
			$$->names.push_back($2->getName());

			currentParameterList=$$;

			delete $1;

			//symbol delete
			delete $2;
		}
		| type_specifier
		{
			$$=new Parameter();
			$$->text+=$1->text;
			logRule("parameter_list : type_specifier");
			logPieceOfCode($$->text);
			
			$$->dataTypes.push_back($1->text);
			$$->names.push_back("");

			currentParameterList=$$;

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
			logRule("compound_statement : LCURL statements RCURL");
			logPieceOfCode($$->text);
			
			delete $2;

		}
 		| LCURL RCURL
		{
			$$=new NonTerminal();
			$$->text+="{\n}";
			logRule("compound_statement : LCURL RCURL");
			logPieceOfCode($$->text);
			
		}
 		;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{	
			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+=" ";
			$$->text+=$2->text;
			$$->text+=";";
			logRule("var_declaration : type_specifier declaration_list SEMICOLON");
			logPieceOfCode($$->text);
			asmComment($$->text);
			// insert declared variables in symbol table
			if($1->text=="void"){
				yyerror("Variable type cannot be void");
				// delete all the symbols in declaration list
				for(SymbolInfo * s: $2->symbols){
					delete s;
				}
			}else{
				for(SymbolInfo * s:$2->symbols){
					s->variableInfo->dataType=$1->text;
					if(table->insert(s)==false){
						yyerror("Multiple declaration of "+s->getName());
						delete s;
					}else{
						//to do: handle array
						if(table->isRootScope()){
							s->variableInfo->global=true;
							s->variableInfo->tempName=newTemp();
							if(s->variableInfo->arrayInfo==NULL)
								addGlobal(s->variableInfo->tempName);
							else
								addGlobal(s->variableInfo->tempName,s->variableInfo->arrayInfo->size);
						}else{
							if(s->variableInfo->arrayInfo!=NULL){ //its an array
								for(int i=1;i<=s->variableInfo->arrayInfo->size;i++){
									writeASM("PUSH AX");
									++stackCount;
								}
								s->variableInfo->stackEntry=stackCount;
							}else{
								writeASM("PUSH AX");
								s->variableInfo->stackEntry=++stackCount;
							}
						}
					}
				}
			}


			delete $1;
			delete $2;
		}
 		 ;
 		 
type_specifier	: INT
		{
			$$=new NonTerminal();
			$$->text="int";
			logRule("type_specifier	: INT");
			logPieceOfCode($$->text);
			
		}
 		| FLOAT
		{
			$$=new NonTerminal();
			$$->text="float";
			logRule("type_specifier	: FLOAT");
			logPieceOfCode($$->text);
			
		}
 		| VOID
		{
			$$=new NonTerminal();
			$$->text="void";
			logRule("type_specifier	: VOID");
			logPieceOfCode($$->text);
			
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		{
			$$=new DeclarationList();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->getName();
			logRule("declaration_list : declaration_list COMMA ID");
			logPieceOfCode($$->text);
			
			$$->symbols=$1->symbols;

			$3->variableInfo=new VariableInfo("int");
			$$->symbols.push_back($3);


			delete $1;
		}
 		| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
			

			$$=new DeclarationList();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->getName();
			$$->text+="[";
			$$->text+=$5->getName();
			$$->text+="]";
			logRule("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
			logPieceOfCode($$->text);
			
			$$->symbols=$1->symbols;

			if(stoi($5->getName())<=0){
				yyerror("Invalid array size "+$5->getName()+" in declaration of variable "+$3->getName());
				delete $3;
			}
			else{
				$3->variableInfo=new VariableInfo("int",new ArrayInfo(stoi($5->getName())));
				$$->symbols.push_back($3);
			}

			delete $1;

			//symbol delete
			delete $5;//const_int
		}
 		| ID
		{
			$$=new DeclarationList();
			$$->text+=$1->getName();
			logRule("declaration_list : ID");
			logPieceOfCode($$->text);

			$1->variableInfo=new VariableInfo("int");
			$$->symbols.push_back($1);
		}
 		| ID LTHIRD CONST_INT RTHIRD
		{
			$$=new DeclarationList();
			$$->text+=$1->getName();
			$$->text+="[";
			$$->text+=$3->getName();
			$$->text+="]";
			logRule("declaration_list : ID LTHIRD CONST_INT RTHIRD");
			logPieceOfCode($$->text);

			if(stoi($3->getName())<=0){
				yyerror("Invalid array size "+$3->getName()+" in declaration of variable "+$1->getName());
				delete $1;
			}
			else{
				$1->variableInfo=new VariableInfo("int",new ArrayInfo(stoi($3->getName())));
				$$->symbols.push_back($1);
			}
			//symbol delete
			delete $3; //const_int
		}
 		;
 		  
statements : statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logRule("statements : statement");
			logPieceOfCode($$->text);
			
			delete $1;
		}
	   | statements statement
	   {
			

			$$=new NonTerminal();
			$$->text+=$1->text;
			$$->text+="\n";
			$$->text+=$2->text;
			logRule("statements : statements statement");
			logPieceOfCode($$->text);
			
			delete $1;
			delete $2;
	   }
	   ;
if_expression: IF  LPAREN expression RPAREN 
{
	$1=new If();
	$1->elseLabel=newLabel();
	$1->nextLabel=newLabel();
	writeASM("POP AX");writeASM("CMP AX,0");
	writeASM("JE "+$1->elseLabel);
	asmComment("if");
	--stackCount;
}
statement
{	
	$$=new If();
	$$->elseLabel=$1->elseLabel;
	$$->nextLabel=$1->nextLabel;
	$$->text+="if(";
	$$->text+=$3->text;
	$$->text+=")\n";
	$$->text+=$6->text;
	if(expHasVoidFunc($3) ){
		yyerror("void-returning function cannot be part of expression");
	}
	for(SymbolInfo * s:$3->symbols){
		if(s->functionInfo==NULL && s->variableInfo==NULL){
			delete s;
		}
	}
	writeASM("JMP "+$$->nextLabel);
	writeASM($$->elseLabel+":");
	writeASM("");
	delete $1;
	delete $3;
	delete $6;
};

statement : var_declaration
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logRule("statement : var_declaration");
			logPieceOfCode($$->text);
			
			delete $1;
		}
	  | expression_statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logRule("statement : expression_statement");
			logPieceOfCode($$->text);
			for(SymbolInfo * s:$1->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			delete $1;
		}
	  | compound_statement
		{
			$$=new NonTerminal();
			$$->text+=$1->text;
			logRule("statement : compound_statement");
			logPieceOfCode($$->text);
			
			delete $1;
		}
		//YOURE NEXT 
	  | FOR {
		$1=new For();
		$1->nextLabel=newLabel();
		$1->checkLabel=newLabel();
		$1->incrementLabel=newLabel();
		$1->statementLabel=newLabel();
		// writeASM(forLabel+": ");
		// writeASM("for");
	  } 
	   LPAREN expression_statement{
		// writeASM(";condition block of for loop");
		writeASM($1->checkLabel+":");		
	   } expression_statement
	   {	
			//this expression statement's value was popped in ax.
			// writeASM("CMP AX,0");
			// writeASM("JE "+$1->nextLabel);
			writeASM("CMP AX,0");
			writeASM("JE "+$1->nextLabel);
			writeASM("JMP "+$1->statementLabel);
			// writeASM(";increment block of for loop");
			writeASM($1->incrementLabel+":");
	   } expression{
		writeASM("POP AX");
		--stackCount;
		writeASM("JMP "+$1->checkLabel);
		// writeASM(";statement block of for loop");
		writeASM($1->statementLabel+":");
	   }RPAREN statement
	  {
			$$=new NonTerminal();
			$$->text+="for(";
			$$->text+=$4->text;
			$$->text+=$6->text;
			$$->text+=$8->text;
			$$->text+=")\n";
			$$->text+=$11->text;
			logRule("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
			logPieceOfCode($$->text);


			for(SymbolInfo * s:$4->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}

			for(SymbolInfo * s:$6->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			for(SymbolInfo * s:$8->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			//expression's 
			// writeASM("POP AX");
			writeASM("JMP "+$1->incrementLabel);
			writeASM($1->nextLabel+":");

			delete $1;
			delete $4;
			delete $6;
			delete $8;
			delete $11;
		}
	  | if_expression %prec LESS_THAN_ELSE
		{
			

			$$=new NonTerminal();
			$$->text=$1->text;
			logRule("statement : IF LPAREN expression RPAREN statement");
			logPieceOfCode($$->text);
			writeASM($1->nextLabel+":");
			writeASM("");
			
			delete $1;

		}
	  | if_expression ELSE {
		asmComment("else");
	  } statement 
		{
			$$=new NonTerminal();
			$$->text=$1->text;
			$$->text+="else\n";
			$$->text+=$4->text;
			logRule("statement :  IF LPAREN expression RPAREN statement ELSE statement");
			logPieceOfCode($$->text);
			writeASM($1->nextLabel+":");
			writeASM("");
			
			delete $1;delete $4;

		}
	  | WHILE {
			string label=newLabel();
			writeASM(label+": ");
			writeASM("");
			$1=new While();
			$1->whileLabel=label;
			asmComment("while");
			$1->nextLabel=newLabel();

	  } LPAREN expression RPAREN 
	  {
		writeASM("POP AX");
		writeASM("CMP AX,0");
		writeASM("JE "+$1->nextLabel);
		--stackCount;
	  }
	  
	  statement
		{
			$$=new NonTerminal();
			$$->text+="while(";
			$$->text+=$4->text;
			$$->text+=")\n";
			$$->text+=$7->text;
			logRule("statement :  WHILE LPAREN expression RPAREN statement");
			logPieceOfCode($$->text);
			if(expHasVoidFunc($4) ){
				yyerror("void-returning function cannot be part of expression");
			}
			for(SymbolInfo * s:$4->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			writeASM("JMP "+$1->whileLabel);
			writeASM($1->nextLabel+":");
			writeASM("");
			delete $1;
			delete $4;delete $7;
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
		{
			
			$$=new NonTerminal();
			$$->text+="println(";
			$$->text+=$3->getName();
			$$->text+=")";
			asmComment($$->text);
			$$->text+=";";
			logRule("statement :  PRINTLN LPAREN ID RPAREN SEMICOLON");
			logPieceOfCode($$->text);
			SymbolInfo * s=table->lookup($3->getName());
			if(s==NULL){
				yyerror("Undeclared Variable "+$3->getName());
			}else if(s->variableInfo==NULL){
				yyerror(s->getName()+" is not a variable");
			}else if(s->variableInfo->arrayInfo!=NULL){
				yyerror(s->getName()+" is an array, cannot print array");
			}else{
				if(s->variableInfo->global){
					writeASM("PUSH "+s->variableInfo->tempName);
					writeASM("CALL PRINTLN");
				}else{
					writeASM("MOV BP,SP");
					writeASM("MOV AX,[BP+"+stkPos(s->variableInfo->stackEntry)+"]");
					writeASM("PUSH AX");
					writeASM("CALL PRINTLN");
				}
			}
			delete $3;
		}
	  |PRINTCHAR LPAREN ID RPAREN SEMICOLON
		{
			
			$$=new NonTerminal();
			$$->text+="princhar(";
			$$->text+=$3->getName();
			$$->text+=")";
			asmComment($$->text);
			$$->text+=";";
			logRule("statement :  PRINTCHAR LPAREN ID RPAREN SEMICOLON");
			logPieceOfCode($$->text);
			SymbolInfo * s=table->lookup($3->getName());
			if(s==NULL){
				yyerror("Undeclared Variable "+$3->getName());
			}else if(s->variableInfo==NULL){
				yyerror(s->getName()+" is not a variable");
			}else if(s->variableInfo->arrayInfo!=NULL){
				yyerror(s->getName()+" is an array, cannot print array");
			}else{
				if(s->variableInfo->global){
					writeASM("PUSH "+s->variableInfo->tempName);
					writeASM("CALL PRINTCHAR");
				}else{
					writeASM("MOV BP,SP");
					writeASM("MOV AX,[BP+"+stkPos(s->variableInfo->stackEntry)+"]");
					writeASM("PUSH AX");
					writeASM("CALL PRINTCHAR");
				}
			}
			delete $3;
		}
	  | RETURN expression SEMICOLON
		{
			$$=new NonTerminal();
			$$->text+="return ";
			$$->text+=$2->text;
			asmComment($$->text);
			$$->text+=";";
			logRule("statement : RETURN expression SEMICOLON");
			logPieceOfCode($$->text);
			if(expHasVoidFunc($2)){
				yyerror("void-returning function cannot be part of expression");
			}

			for(SymbolInfo * s:$2->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			if(isMainFunction==false){
				writeASM("POP BX"); //BX HAS EXPRESSION
				--stackCount;
				table->deleteAllTemporaryVariable();
				writeASM("POP AX"); //AX HAS IP //FALSE
				--stackCount;
				writeASM("PUSH BX");
				++stackCount;
				writeASM("PUSH AX"); // Switching IP and EXPRESSION
				++stackCount;
				writeASM("RET");
			}
			delete $2;
		}
	  ;
	  
expression_statement 	: SEMICOLON	
		{
			

			$$=new Expression();
			$$->text+=";";
			logRule("expression_statement : SEMICOLON	");
			logPieceOfCode($$->text);
			writeASM("MOV BX,1"); // For for loops with empty second expressions

		}		
			| expression SEMICOLON 
		{
			$$=new Expression();
			$$->text+=$1->text;
			$$->text+=";";
			logRule("expression_statement : expression SEMICOLON ");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			$$->forceInteger=$1->forceInteger;

			writeASM("POP AX"); /*expression statement's value is popped in ax.
			this value is nedded for FOR loops' 2nd expression_statement.
			 A bit tricky/risky since 
			im storing this in a temporary registar instead of a reliable storage. However
			since ax is not being accessed in the FOR loop when it is further needed, 
			this should work.
			*/
			--stackCount;

			delete $1;
		}
			;
	  
variable : ID 
		{
			

			$$=new Variable();
			$$->text+=$1->getName();
			logRule("variable : ID ");
			logPieceOfCode($$->text);
			SymbolInfo * symbol=table->lookup($1->getName());
			if(symbol==NULL){
				yyerror("Undeclared Variable "+$1->getName());
			}else if(symbol->variableInfo==NULL){
				yyerror($1->getName()+" is not a variable");
			}
			else if(symbol->variableInfo->arrayInfo!=NULL){
				yyerror($1->getName()+" is an array, cannot be used without indexing");
			}else{
				$$->symbol=symbol;
			}

			delete $1;

		}		
	 | ID LTHIRD expression RTHIRD 
		{
			$$=new Variable();
			$$->text+=$1->getName();
			$$->text+="[";
			$$->text+=$3->text;
			$$->text+="]";
			logRule("variable : ID LTHIRD expression RTHIRD ");
			logPieceOfCode($$->text);
			// task: check if expression evaluates to int
			if(getTypeOfExpression($3)!="int"){
				yyerror("Type of array index must be integer");
			}

			SymbolInfo * symbol=table->lookup($1->getName());
			if(symbol==NULL){
				yyerror("Undeclared Variable "+$1->getName());
			}else if(symbol->variableInfo==NULL){
				yyerror($1->getName()+" is not a variable");
			}
			else if(symbol->variableInfo->arrayInfo==NULL){
				yyerror($1->getName()+" is not an array");
			}else{
				$$->symbol=symbol;
			}
			if(expHasVoidFunc($3) ){
				yyerror("void-returning function cannot be part of expression");
			}
			for(SymbolInfo * s:$3->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}

			delete $3;
			delete $1;

		}
	 ;
	 
 expression : logic_expression	
		{
			

			$$=new Expression();
			$$->text+=$1->text;
			logRule("expression : logic_expression	");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			$$->forceInteger=$1->forceInteger;
			$$->stackEntry=$1->stackEntry;

			delete $1;
		}
	   | variable ASSIGNOP logic_expression 
		{
			$$=new Expression();
			$$->text+=$1->text;
			$$->text+="=";
			$$->text+=$3->text;
			asmComment($$->text);
			logRule("expression : variable ASSIGNOP logic_expression");
			logPieceOfCode($$->text);

			if($1->symbol!=NULL){
				if($1->symbol->variableInfo->dataType=="int" && getTypeOfExpression($3)=="float"){
					yyerror("Type Mismatch, assigning "+
					getTypeOfExpression($3)+" value to variable of type "
					+$1->symbol->variableInfo->dataType);
				}
				
			}
			if(expHasVoidFunc($3)){
				yyerror("void-returning function cannot be part of expression");
			}
			$$->symbols=$3->symbols;
			$$->forceInteger=$3->forceInteger;
			if($1->symbol->variableInfo->global==false){
				if($1->symbol->variableInfo->arrayInfo!=NULL){
					writeASM("POP CX"); //expression is cx
					writeASM("POP AX"); // index in ax
					stackCount-=2;
					writeASM("MOV BP,SP");
					writeASM("MOV BX,2");
					writeASM("MUL BX");
					writeASM("ADD AX,"+stkPos($1->symbol->variableInfo->stackEntry));
					writeASM("ADD BP,AX");
					writeASM("MOV [BP],CX");
					writeASM("PUSH CX");
					$$->stackEntry=++stackCount;
				}else{
					writeASM("POP AX");
					--stackCount;
					writeASM("MOV BP,SP");
					writeASM("MOV [BP+"+stkPos($1->symbol->variableInfo->stackEntry)+"],AX");
					writeASM("PUSH AX");
					$$->stackEntry=++stackCount;
				}
			}else{
				if($1->symbol->variableInfo->arrayInfo!=NULL){
					writeASM("POP CX"); //cx has right side expression value
					--stackCount;
					writeASM("POP AX"); //ax has array index no
					--stackCount;
					writeASM("MOV BX,2");
					writeASM("MUL BX");
					writeASM("LEA SI,"+$1->symbol->variableInfo->tempName);

					writeASM("ADD SI,AX");
					writeASM("MOV [SI],CX");
					writeASM("PUSH CX");
					$$->stackEntry=++stackCount;
				}else{
					writeASM("POP AX");
					writeASM("MOV "+$1->symbol->variableInfo->tempName+",AX");
					writeASM("PUSH "+$1->symbol->variableInfo->tempName);
					$$->stackEntry=stackCount;
				}
			}
			// writeASM("POP AX \n MOV BP,SP");
			// stackCount--;
			// writeASM("MOV [BP+"+stkPos($1->symbol->variableInfo->stackEntry)
			// +"],AX \n PUSH AX");
			// stackCount++;
			// $$->stackEntry=$3->stackEntry;

			
			delete $1;
			delete $3;
		}	
	   ;
			
logic_expression : rel_expression 	
		{
			$$=new Expression();
			$$->text+=$1->text;
			logRule("logic_expression : rel_expression");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			$$->forceInteger=$1->forceInteger;
			$$->stackEntry=$1->stackEntry;

			delete $1;
		}
		 | rel_expression LOGICOP rel_expression 
		{
			$$=new Expression();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			asmComment($$->text);
			logRule("logic_expression : rel_expression LOGICOP rel_expression");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			for(SymbolInfo * s:$3->symbols){
				$$->symbols.push_back(s);
			}
			$$->forceInteger=true;
			if(expHasVoidFunc($1) ||expHasVoidFunc($3) ){
				yyerror("void-returning function cannot be part of expression");
			}
			if($2->getName()=="&&"){
				writeASM("POP BX");
				writeASM("POP AX");
				string nextLabel=newLabel();
				string falseLabel=newLabel();
				writeASM("CMP AX,0");
				writeASM("JE "+falseLabel);
				writeASM("CMP BX,0");
				writeASM("JE "+falseLabel);
				writeASM("PUSH 1");
				writeASM("JMP "+nextLabel);
				writeASM(falseLabel+": ");
				writeASM("PUSH 0");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}else if($2->getName()=="||"){
				writeASM("POP BX");
				writeASM("POP AX");
				string nextLabel=newLabel();
				string trueLabel=newLabel();
				writeASM("CMP AX,0");
				writeASM("JNE "+trueLabel);
				writeASM("CMP BX,0");
				writeASM("JNE "+trueLabel);
				writeASM("PUSH 0");
				writeASM("JMP "+nextLabel);
				writeASM(trueLabel+": ");
				writeASM("PUSH 1");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}
			
			delete $1;
			delete $3;

			//symbol delete
			delete $2;
		}	
		 ;
			
rel_expression	: simple_expression 
		{
			$$=new Expression();
			$$->text+=$1->text;
			logRule("rel_expression	: simple_expression ");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			$$->forceInteger=$1->forceInteger;
			$$->stackEntry=$1->stackEntry;

			delete $1;
		}
		| simple_expression RELOP simple_expression	
		{
			$$=new Expression();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			asmComment($$->text);
			logRule("rel_expression	: simple_expression RELOP simple_expression	");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			for(SymbolInfo * s:$3->symbols){
				$$->symbols.push_back(s);
			}
			$$->forceInteger=true;
			if(expHasVoidFunc($1) ||expHasVoidFunc($3) ){
				yyerror("void-returning function cannot be part of expression");
			}
			if($2->getName()=="=="){
				string nextLabel=newLabel();
				string unequalLabel=newLabel();
				writeASM("POP AX"); //AX HAS RIGHT OP
				writeASM("POP BX"); //BX HAS LEFT OP
				writeASM("CMP AX,BX");
				writeASM("JNE "+unequalLabel);
				writeASM("PUSH 1");
				writeASM("JMP "+nextLabel);
				writeASM(unequalLabel+": ");
				writeASM("PUSH 0");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}else if($2->getName()=="!="){
				string nextLabel=newLabel();
				string equalLabel=newLabel();
				writeASM("POP AX"); //AX HAS RIGHT OP
				writeASM("POP BX"); //BX HAS LEFT OP
				writeASM("CMP AX,BX");
				writeASM("JE "+equalLabel);
				writeASM("PUSH 1");
				writeASM("JMP "+nextLabel);
				writeASM(equalLabel+": ");
				writeASM("PUSH 0");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}else if($2->getName()=="<="){
				string nextLabel=newLabel();
				string greaterLabel=newLabel();
				writeASM("POP AX"); //AX HAS RIGHT OP
				writeASM("POP BX"); //BX HAS LEFT OP
				writeASM("CMP BX,AX");
				writeASM("JG "+greaterLabel);
				writeASM("PUSH 1");
				writeASM("JMP "+nextLabel);
				writeASM(greaterLabel+": ");
				writeASM("PUSH 0");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}
			else if($2->getName()==">="){
				string nextLabel=newLabel();
				string lesserLabel=newLabel();
				writeASM("POP AX"); //AX HAS RIGHT OP
				writeASM("POP BX"); //BX HAS LEFT OP
				writeASM("CMP BX,AX");
				writeASM("JL "+lesserLabel);
				writeASM("PUSH 1");
				writeASM("JMP "+nextLabel);
				writeASM(lesserLabel+": ");
				writeASM("PUSH 0");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}else if($2->getName()==">"){
				string nextLabel=newLabel();
				string notGreaterLabel=newLabel();
				writeASM("POP AX"); //AX HAS RIGHT OP
				writeASM("POP BX"); //BX HAS LEFT OP
				writeASM("CMP BX,AX");
				writeASM("JLE "+notGreaterLabel);
				writeASM("PUSH 1");
				writeASM("JMP "+nextLabel);
				writeASM(notGreaterLabel+": ");
				writeASM("PUSH 0");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}else if($2->getName()=="<"){
				string nextLabel=newLabel();
				string notLesserLabel=newLabel();
				writeASM("POP AX"); //AX HAS RIGHT OP
				writeASM("POP BX"); //BX HAS LEFT OP
				writeASM("CMP BX,AX");
				writeASM("JGE "+notLesserLabel);
				writeASM("PUSH 1");
				writeASM("JMP "+nextLabel);
				writeASM(notLesserLabel+": ");
				writeASM("PUSH 0");
				writeASM(nextLabel+": ");
				$$->stackEntry=--stackCount;
			}
			delete $1;delete $3;

			//symbol delete 
			delete $2;
		}
		;
				
simple_expression : term 
		{
			$$=new Expression();
			$$->text+=$1->text;
			logRule("simple_expression : term ");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			$$->forceInteger=$1->forceInteger;
			$$->stackEntry=$1->stackEntry;
			delete $1;
		}
		  | simple_expression ADDOP term 
		{
			

			$$=new Expression();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			asmComment($$->text);
			logRule("simple_expression : simple_expression ADDOP term");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			for(SymbolInfo * s:$3->symbols){
				$$->symbols.push_back(s);
			}
			$$->forceInteger=$1->forceInteger && $3->forceInteger;

			if(expHasVoidFunc($1) ||expHasVoidFunc($3) ){
				yyerror("void-returning function cannot be part of expression");
			}
			if($2->getName()=="+"){
				writeASM("POP AX");
				writeASM("POP BX");
				writeASM("ADD AX,BX");
				writeASM("PUSH AX");				
			}else{
				writeASM("POP AX");
				writeASM("POP BX");
				writeASM("SUB BX,AX");
				writeASM("PUSH BX");
			}
			$$->stackEntry=--stackCount;
			
			delete $1;
			delete $3;
			delete $2;
		}
		  ;
					
term :	unary_expression
		{
			$$=new Expression();
			$$->text+=$1->text;
			logRule("term :	unary_expression");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			$$->forceInteger=$1->forceInteger;
			$$->stackEntry=$1->stackEntry;
			delete $1;
		}
     |  term MULOP unary_expression
		{
			$$=new Expression();
			$$->text+=$1->text;
			$$->text+=$2->getName();
			$$->text+=$3->text;
			asmComment($$->text);
			logRule("term : term MULOP unary_expression");
			logPieceOfCode($$->text);
			if($2->getName()=="%" &&(getTypeOfExpression($1)!="int" || 
			getTypeOfExpression($3)!="int")){
				yyerror("Modulus operator needs integer operands");
			}
			$$->symbols=$1->symbols;
			for(SymbolInfo * s:$3->symbols){
				$$->symbols.push_back(s);
			}
			if($2->getName()!="%")
				$$->forceInteger=$1->forceInteger && $3->forceInteger;
			else
				$$->forceInteger=true;

			if(expHasVoidFunc($1) ||expHasVoidFunc($3) ){
				yyerror("void-returning function cannot be part of expression");
			}
			if($2->getName()=="*"){
				writeASM("POP AX");
				writeASM("POP BX");
				writeASM("MUL BX");
				writeASM("PUSH AX");
				$$->stackEntry=--stackCount;
			}else if($2->getName()=="/"){
				writeASM("POP BX"); //bx has divisor
				writeASM("POP AX"); //ax has dividend
				writeASM("XOR DX,DX");
				writeASM("IDIV BX");
				writeASM("PUSH AX");
				$$->stackEntry=--stackCount;
			}else if($2->getName()=="%"){
				writeASM("POP BX"); //bx has divisor
				writeASM("POP AX"); //ax has dividend
				writeASM("XOR DX,DX");
				writeASM("IDIV BX");
				writeASM("PUSH DX");
				$$->stackEntry=--stackCount;
			}
			delete $1;
			delete $3;
			delete $2;
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			$$=new Expression();
			$$->text+=$1->getName();
			$$->text+=$2->text;
			asmComment($$->text);
			logRule("unary_expression : ADDOP unary_expression ");
			logPieceOfCode($$->text);

			$$->symbols=$2->symbols;
			$$->forceInteger=$2->forceInteger;
			if($1->getName()=="-"){
				writeASM("POP AX");
				writeASM("NEG AX");
				writeASM("PUSH AX");
			}
			$$->stackEntry=$2->stackEntry;

			if(expHasVoidFunc($2)){
				yyerror("void-returning function cannot be part of expression");
			}
			
			delete $2;
			delete $1;
		}
		 | NOT unary_expression 
		{
			$$=new Expression();
			$$->text+="!";
			$$->text+=$2->text;
			asmComment($$->text);
			logRule("unary_expression : NOT unary_expression ");
			logPieceOfCode($$->text);
			$$->symbols=$2->symbols;
			$$->forceInteger=$2->forceInteger;

			if(expHasVoidFunc($2)){
				yyerror("void-returning function cannot be part of expression");
			}
			writeASM("POP AX");
			string zeroLabel=newLabel();
			string nextLabel=newLabel();
			writeASM("CMP AX,0");
			writeASM("JE "+zeroLabel);
			writeASM("MOV AX,0");
			writeASM("JMP "+nextLabel);
			writeASM(zeroLabel+": ");
			writeASM("MOV AX,1");
			writeASM(nextLabel+": ");
			writeASM("PUSH AX");
			$$->stackEntry=stackCount;

			delete $2;
		}
		 | factor 
		{
			$$=new Expression();
			$$->text+=$1->text;
			logRule("unary_expression : factor");
			logPieceOfCode($$->text);
			$$->symbols=$1->symbols;
			$$->stackEntry=$1->stackEntry;

			delete $1;
		}
		 ;
	
factor	: variable 
		{	
			asmComment($$->text);
			$$=new Expression();
			$$->text+=$1->text;
			logRule("factor	: variable ");
			logPieceOfCode($$->text);
			if($1->symbol!=NULL){
				$$->symbols.push_back($1->symbol);
				if($1->symbol->variableInfo->global==false){
					if($1->symbol->variableInfo->arrayInfo!=NULL){
						writeASM("POP AX");
						writeASM("MOV BX,2");
						writeASM("MUL BX");
						--stackCount;
						writeASM("ADD AX,"+stkPos($1->
						symbol->variableInfo->stackEntry));
						writeASM("MOV BP,SP");
						writeASM("ADD BP,AX");
						writeASM("MOV AX,[BP]");
						writeASM("PUSH AX");
						$$->stackEntry=++stackCount;
					}else{
						writeASM("MOV BP,SP");
						writeASM("MOV AX,[BP+"+stkPos($1->symbol->variableInfo->stackEntry)+"]");
						writeASM("PUSH AX");
						$$->stackEntry=++stackCount;
					}
				}else{
					if($1->symbol->variableInfo->arrayInfo!=NULL){
						writeASM("POP AX ");
						writeASM("MOV BX,2 ");
						writeASM("MUL BX");
						writeASM("LEA SI,"+$1->symbol->variableInfo->tempName);
						writeASM("ADD SI,AX"); 
						writeASM("MOV AX,[SI]");
						writeASM("PUSH AX");
						$$->stackEntry=stackCount;
					}else{
						writeASM("PUSH "+$1->symbol->variableInfo->tempName);
						$$->stackEntry=++stackCount;
					}

				}
				// writeASM("MOV BP,SP\nMOV AX,[BP+"+stkPos($1->symbol->variableInfo->stackEntry)
				// +"]\nPUSH AX");
				// $$->stackEntry=++stackCount;
			}

			delete $1;
		}
	| ID LPAREN argument_list RPAREN
		{
			

			$$=new Expression();
			$$->text+=$1->getName();
			$$->text+="(";
			$$->text+=$3->text;
			$$->text+=")";
			asmComment($$->text);
			logRule("factor : ID LPAREN argument_list RPAREN");
			logPieceOfCode($$->text);
			SymbolInfo * symbol=table->lookup($1->getName());
			if(symbol==NULL){
				yyerror($1->getName()+" is undeclared");
			}else if(symbol->functionInfo==NULL){
				yyerror($1->getName()+" is not a function");
			}
			//else if(symbol->functionInfo->returnType=="void"){
			// 		yyerror("void-returning function "+symbol->getName()+" cannot be part of expression");
			// }
			else if($3->dataTypes.size()!=symbol->functionInfo->paramDataTypes.size()){
				yyerror("Argument Size Mismatch");
				$$->symbols.push_back(symbol);
			}else{
				for(int i=0;i<$3->dataTypes.size();i++){
					if($3->dataTypes.at(i)!=symbol->functionInfo->paramDataTypes.at(i)){
						yyerror("Argument no "+to_string(i)+" type mismatch");
					}
				}
				$$->symbols.push_back(symbol);
			}
			++stackCount; // increment due to IP being inserted in stack
			writeASM("CALL "+$1->getName());
			if(symbol->functionInfo->returnType=="void"){ //because non-void has 
			 --stackCount;
			}
			if(symbol->functionInfo->returnType=="int"){
			//after return from call, stackCount should be unchanged,because IP is popped but
			//return value is stored in stack top
				writeASM("POP BX"); //save the return value
				--stackCount;
			}
			// now pop all the arguments in the stack
			for(int i=1;i<=$3->dataTypes.size();i++){
				writeASM("POP AX");
				--stackCount;
			}
			//push the return value
			if(symbol->functionInfo->returnType=="int"){
				writeASM("PUSH BX");
				++stackCount;
			}else{ //push a garbage value for void function, I KNOW I KNOW, SAME STUFF IN BOTH 
			// IF & ELSE BLOCKS!!! BUT I KINDOF LIKE TO SEPARATE THIS... 
				writeASM("PUSH BX");
				++stackCount;
			}
			$$->stackEntry=stackCount;
			delete $3;
			delete $1;
		}
	| LPAREN expression RPAREN
		{
			$$=new Expression();
			$$->text+="(";
			$$->text+=$2->text;
			$$->text+=")";
			logRule("factor : LPAREN expression RPAREN");
			logPieceOfCode($$->text);
			$$->symbols=$2->symbols;
			$$->forceInteger=$2->forceInteger;
			$$->stackEntry=$2->stackEntry;

			delete $2;
		}
	| CONST_INT
		{
			$$=new Expression();
			$$->text+=$1->getName();
			asmComment($$->text);
			logRule("factor	: CONST_INT");
			logPieceOfCode($$->text);
			$$->symbols.push_back($1);
			writeASM("MOV AX,"+$1->getName());
			writeASM("PUSH AX");
			$$->stackEntry=++stackCount;
		} 
	| CONST_FLOAT
		{
			$$=new Expression();
			$$->text+=$1->getName();
			asmComment($$->text);
			logRule("factor	: CONST_FLOAT");
			logPieceOfCode($$->text);
			$$->symbols.push_back($1);


		}
	| variable INCOP 
		{
			$$=new Expression();
			$$->text+=$1->text;
			$$->text+="++";
			asmComment($$->text);
			logRule("factor	: variable INCOP");
			logPieceOfCode($$->text);
			if($1->symbol!=NULL){
				$$->symbols.push_back($1->symbol);
				if($1->symbol->variableInfo->global==false){
					if($1->symbol->variableInfo->arrayInfo!=NULL){
						writeASM("POP AX");
						writeASM("MOV BX,2");
						writeASM("MUL BX");
						--stackCount;
						writeASM("ADD AX,"+stkPos($1->
						symbol->variableInfo->stackEntry));
						writeASM("MOV BP,SP");
						writeASM("ADD BP,AX");
						writeASM("MOV AX,[BP]");
						writeASM("MOV BX,AX");
						writeASM("INC AX");
						writeASM("MOV [BP],AX");
						writeASM("PUSH BX"); // INC THE NUMBER BUT PUSH ORIGINAL VALUE
						$$->stackEntry=++stackCount;
					}else{
						writeASM("MOV BP,SP");
						writeASM("MOV AX,[BP+"+stkPos($1->symbol->variableInfo->stackEntry)+"]");
						writeASM("MOV BX,AX");
						writeASM("INC AX");
						writeASM("MOV [BP+"+stkPos($1->symbol->variableInfo->stackEntry)+"],AX"); 
						writeASM("PUSH BX");
						$$->stackEntry=++stackCount;
					}
				}else{
					if($1->symbol->variableInfo->arrayInfo!=NULL){
						writeASM("POP AX");
						writeASM("MOV BX,2");
						writeASM("MUL BX");
						writeASM("LEA SI,"+$1->symbol->variableInfo->tempName);
						writeASM("ADD SI,AX");
						writeASM("MOV AX,[SI]");
						writeASM("INC [SI]");
						writeASM("PUSH AX");
						$$->stackEntry=stackCount;	
					}else{
						writeASM("MOV AX,"+$1->symbol->variableInfo->tempName);
						writeASM("INC "+$1->symbol->variableInfo->tempName);
						writeASM("PUSH AX");
						$$->stackEntry=++stackCount;
					}

				}
			}
			delete $1;
		}
	| variable DECOP
		{
			$$=new Expression();
			$$->text+=$1->text;
			$$->text+="--";
			asmComment($$->text);
			logRule("factor	: variable DECOP");
			logPieceOfCode($$->text);
			if($1->symbol!=NULL){
				$$->symbols.push_back($1->symbol);
				if($1->symbol->variableInfo->global==false){
					if($1->symbol->variableInfo->arrayInfo!=NULL){
						writeASM("POP AX");
						writeASM("MOV BX,2");
						writeASM("MUL BX");
						--stackCount;
						writeASM("ADD AX,"+stkPos($1->
						symbol->variableInfo->stackEntry));
						writeASM("MOV BP,SP");
						writeASM("ADD BP,AX");
						writeASM("MOV AX,[BP]");
						writeASM("MOV BX,AX");
						writeASM("DEC AX");
						writeASM("MOV [BP],AX");
						writeASM("PUSH BX");
						$$->stackEntry=++stackCount;
					}else{
						writeASM("MOV BP,SP");
						writeASM("MOV AX,[BP+"+stkPos($1->symbol->variableInfo->stackEntry)+"]");
						writeASM("MOV BX,AX"); 
						writeASM("DEC AX");
						writeASM("MOV [BP+"+stkPos($1->symbol->variableInfo->stackEntry)+"],AX"); 
						writeASM("PUSH BX");
						$$->stackEntry=++stackCount;
					}
				}else{
					if($1->symbol->variableInfo->arrayInfo!=NULL){
						writeASM("POP AX");
						writeASM("MOV BX,2");
						writeASM("MUL BX");
						writeASM("LEA SI,"+$1->symbol->variableInfo->tempName);
						writeASM("ADD SI,AX");
						writeASM("MOV AX,[SI]");
						writeASM("DEC [SI]");
						writeASM("PUSH AX");
						$$->stackEntry=stackCount;	
					}else{
						writeASM("MOV AX,"+$1->symbol->variableInfo->tempName);
						writeASM("DEC "+$1->symbol->variableInfo->tempName);
						writeASM("PUSH AX");
						$$->stackEntry=++stackCount;
					}

				}
			}
			delete $1;
		}
	;
	
argument_list : arguments
		{
			$$=new Argument();
			$$->text+=$1->text;
			logRule("argument_list : arguments");
			logPieceOfCode($$->text);
			$$->dataTypes=$1->dataTypes;
			delete $1;
		}
			  |
		{
			$$=new Argument();
			logRule("argument_list : empty");
			logPieceOfCode($$->text);
			
		};
	
arguments : arguments COMMA logic_expression
		{
			$$=new Argument();
			$$->text+=$1->text;
			$$->text+=",";
			$$->text+=$3->text;
			logRule("arguments : arguments COMMA logic_expression");
			logPieceOfCode($$->text);
			$$->dataTypes=$1->dataTypes;
			$$->dataTypes.push_back(getTypeOfExpression($3));

			//task : before deleting expression, free symbols that are not 
			//in the symbol table

			delete $1;
			delete $3;

		}
	      | logic_expression
		{
			$$=new Argument();
			$$->text+=$1->text;
			logRule("arguments : logic_expression");
			logPieceOfCode($$->text);
			$$->dataTypes.push_back(getTypeOfExpression($1));

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
	fData<<".DATA"<<endl;
	yyparse();

	//symbol table print
	table->printAllScopeTable(fLog);

	fLog<<"Total Lines : "<<yylineno<<endl;
	fLog<<"Total Errors : "<<errorCount<<endl;

	/* delete memories*/
	delete table;

	/*close opended files*/
	fLog.close();
	fError.close();
	fData.close();
	fASM.close();

	fCode<<".MODEL SMALL\n.STACK 100H\n"<<endl;
	//append data.asm to code.asm
	ifstream fDataIn("data.asm");
	while(!fDataIn.eof()){
		char c;
		fDataIn>>noskipws>>c;
		fCode<<c;
	}
	fDataIn.close();

	//append ASM.asm to code.asm
	fCode<<".CODE\n";
	// append println function
	ifstream fPrintlnIn("println.asm");
	fCode<<"\n";
	while(!fPrintlnIn.eof()){
		char c;
		fPrintlnIn>>noskipws>>c;
		fCode<<c;
	}
	fPrintlnIn.close();

	ifstream fASMIn("ASM.asm");
	while(!fASMIn.eof()){
		char c;
		fASMIn>>noskipws>>c;
		fCode<<c;
	}
	fASMIn.close();
	fCode.close();

	if(errorCount>0){
		//delete the code
		fCode.open("code.asm");
		fCode.close();
		ifstream fOptimized("optimized_code.asm");
		fOptimized.close();
	}else{
		writeOptimizedCode();
	}
	
	fclose(fp);
	return 0;
}

