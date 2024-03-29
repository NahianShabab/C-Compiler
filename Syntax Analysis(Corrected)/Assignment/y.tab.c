/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "1805031.y"

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
Parameter * currentParameterList=NULL;

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

// //temp function
// void printParameterList(Parameter * p,string fName){
// 	fLog<<"Parameters of "<<fName<<" are :"<<endl;
// 	for(int i=0;i<p->dataTypes.size();i++){
// 		fLog<<p->names.at(i)<<" : "<<p->dataTypes.at(i)<<endl;
// 	}
// }

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



#line 216 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LPAREN = 258,                  /* LPAREN  */
    RPAREN = 259,                  /* RPAREN  */
    SEMICOLON = 260,               /* SEMICOLON  */
    COMMA = 261,                   /* COMMA  */
    LCURL = 262,                   /* LCURL  */
    RCURL = 263,                   /* RCURL  */
    INT = 264,                     /* INT  */
    FLOAT = 265,                   /* FLOAT  */
    VOID = 266,                    /* VOID  */
    LTHIRD = 267,                  /* LTHIRD  */
    RTHIRD = 268,                  /* RTHIRD  */
    FOR = 269,                     /* FOR  */
    IF = 270,                      /* IF  */
    WHILE = 271,                   /* WHILE  */
    RETURN = 272,                  /* RETURN  */
    NOT = 273,                     /* NOT  */
    INCOP = 274,                   /* INCOP  */
    DECOP = 275,                   /* DECOP  */
    ID = 276,                      /* ID  */
    CONST_INT = 277,               /* CONST_INT  */
    PRINTLN = 278,                 /* PRINTLN  */
    ASSIGNOP = 279,                /* ASSIGNOP  */
    LOGICOP = 280,                 /* LOGICOP  */
    RELOP = 281,                   /* RELOP  */
    ADDOP = 282,                   /* ADDOP  */
    MULOP = 283,                   /* MULOP  */
    CONST_FLOAT = 284,             /* CONST_FLOAT  */
    LESS_THAN_ELSE = 285,          /* LESS_THAN_ELSE  */
    ELSE = 286                     /* ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LPAREN 258
#define RPAREN 259
#define SEMICOLON 260
#define COMMA 261
#define LCURL 262
#define RCURL 263
#define INT 264
#define FLOAT 265
#define VOID 266
#define LTHIRD 267
#define RTHIRD 268
#define FOR 269
#define IF 270
#define WHILE 271
#define RETURN 272
#define NOT 273
#define INCOP 274
#define DECOP 275
#define ID 276
#define CONST_INT 277
#define PRINTLN 278
#define ASSIGNOP 279
#define LOGICOP 280
#define RELOP 281
#define ADDOP 282
#define MULOP 283
#define CONST_FLOAT 284
#define LESS_THAN_ELSE 285
#define ELSE 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 146 "1805031.y"

	SymbolInfo * symbol;
	NonTerminal * nonTerminal;
	Parameter * parameter;
	DeclarationList * declarationList;
	Expression * expression;
	Variable * variable;
	Argument * argument;

#line 341 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LPAREN = 3,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 4,                     /* RPAREN  */
  YYSYMBOL_SEMICOLON = 5,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 6,                      /* COMMA  */
  YYSYMBOL_LCURL = 7,                      /* LCURL  */
  YYSYMBOL_RCURL = 8,                      /* RCURL  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_VOID = 11,                      /* VOID  */
  YYSYMBOL_LTHIRD = 12,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 13,                    /* RTHIRD  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_WHILE = 16,                     /* WHILE  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_NOT = 18,                       /* NOT  */
  YYSYMBOL_INCOP = 19,                     /* INCOP  */
  YYSYMBOL_DECOP = 20,                     /* DECOP  */
  YYSYMBOL_ID = 21,                        /* ID  */
  YYSYMBOL_CONST_INT = 22,                 /* CONST_INT  */
  YYSYMBOL_PRINTLN = 23,                   /* PRINTLN  */
  YYSYMBOL_ASSIGNOP = 24,                  /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 25,                   /* LOGICOP  */
  YYSYMBOL_RELOP = 26,                     /* RELOP  */
  YYSYMBOL_ADDOP = 27,                     /* ADDOP  */
  YYSYMBOL_MULOP = 28,                     /* MULOP  */
  YYSYMBOL_CONST_FLOAT = 29,               /* CONST_FLOAT  */
  YYSYMBOL_LESS_THAN_ELSE = 30,            /* LESS_THAN_ELSE  */
  YYSYMBOL_ELSE = 31,                      /* ELSE  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_start = 33,                     /* start  */
  YYSYMBOL_34_1 = 34,                      /* $@1  */
  YYSYMBOL_program = 35,                   /* program  */
  YYSYMBOL_unit = 36,                      /* unit  */
  YYSYMBOL_func_declaration = 37,          /* func_declaration  */
  YYSYMBOL_func_definition = 38,           /* func_definition  */
  YYSYMBOL_parameter_list = 39,            /* parameter_list  */
  YYSYMBOL_compound_statement = 40,        /* compound_statement  */
  YYSYMBOL_var_declaration = 41,           /* var_declaration  */
  YYSYMBOL_type_specifier = 42,            /* type_specifier  */
  YYSYMBOL_declaration_list = 43,          /* declaration_list  */
  YYSYMBOL_statements = 44,                /* statements  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_expression_statement = 46,      /* expression_statement  */
  YYSYMBOL_variable = 47,                  /* variable  */
  YYSYMBOL_expression = 48,                /* expression  */
  YYSYMBOL_logic_expression = 49,          /* logic_expression  */
  YYSYMBOL_rel_expression = 50,            /* rel_expression  */
  YYSYMBOL_simple_expression = 51,         /* simple_expression  */
  YYSYMBOL_term = 52,                      /* term  */
  YYSYMBOL_unary_expression = 53,          /* unary_expression  */
  YYSYMBOL_factor = 54,                    /* factor  */
  YYSYMBOL_argument_list = 55,             /* argument_list  */
  YYSYMBOL_arguments = 56                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   175,   175,   175,   181,   193,   206,   215,   224,   237,
     266,   292,   323,   351,   380,   399,   418,   435,   450,   460,
     493,   501,   509,   519,   536,   566,   576,   599,   608,   624,
     633,   646,   655,   690,   714,   738,   758,   772,   794,   804,
     818,   841,   881,   894,   924,   935,   960,   971,   997,  1007,
    1033,  1043,  1073,  1091,  1108,  1120,  1132,  1166,  1179,  1187,
    1196,  1210,  1224,  1234,  1241,  1259
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LPAREN", "RPAREN",
  "SEMICOLON", "COMMA", "LCURL", "RCURL", "INT", "FLOAT", "VOID", "LTHIRD",
  "RTHIRD", "FOR", "IF", "WHILE", "RETURN", "NOT", "INCOP", "DECOP", "ID",
  "CONST_INT", "PRINTLN", "ASSIGNOP", "LOGICOP", "RELOP", "ADDOP", "MULOP",
  "CONST_FLOAT", "LESS_THAN_ELSE", "ELSE", "$accept", "start", "$@1",
  "program", "unit", "func_declaration", "func_definition",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -70,    10,    55,   -70,   -70,   -70,   -70,    55,   -70,   -70,
     -70,   -70,    -2,   -70,    12,    66,    47,    -9,   -70,    21,
      62,   136,    34,    15,    19,   -70,    72,   -70,    71,    55,
     -70,   -70,    38,     0,   -70,   -70,    88,    89,   104,     0,
       0,    14,   -70,   105,     0,   -70,   -70,   -70,    93,    95,
     -70,   -70,    28,   110,   -70,   103,    58,    92,   -70,   -70,
     -70,   -70,   108,   122,   132,    32,     0,     0,   139,    77,
     -70,     0,     0,   120,   -70,   134,   -70,   -70,   -70,   -70,
       0,   -70,     0,     0,     0,     0,   -70,   -70,   -70,    32,
     143,   144,   -70,   -70,   145,   146,   137,   147,   -70,   -70,
     126,    92,   -70,     0,   116,   116,   -70,     0,   -70,   149,
     151,   125,   -70,   -70,   -70,   116,   116,   -70,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    20,    21,    22,     3,     5,     7,
       8,     6,     0,     4,    25,     0,     0,     0,    19,     0,
       0,     0,    16,     0,    23,    10,     0,    12,     0,     0,
      15,    26,     0,     0,    38,    18,     0,     0,     0,     0,
       0,    40,    58,     0,     0,    59,    31,    29,     0,     0,
      27,    30,    55,     0,    42,    44,    46,    48,    50,    54,
       9,    11,    14,     0,     0,     0,     0,     0,     0,    55,
      53,    63,     0,     0,    52,    25,    17,    28,    60,    61,
       0,    39,     0,     0,     0,     0,    13,    24,    57,     0,
       0,     0,    37,    65,     0,    62,     0,     0,    43,    45,
      47,    49,    51,     0,     0,     0,    56,     0,    41,     0,
       0,    33,    35,    64,    36,     0,     0,    32,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   -70,   150,   -70,   -70,   -70,    -8,    23,
       7,   -70,   -70,   -42,   -49,   -39,   -33,   -69,    76,    78,
      75,   -36,   -70,   -70,   -70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     7,     8,     9,    10,    21,    46,    47,
      48,    15,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    94,    95
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    69,    93,    33,    70,    69,    68,    77,    74,    12,
       3,    98,    27,    23,    12,    16,    89,    71,    40,    14,
      61,    41,    42,    22,    17,    11,    72,    44,    31,    45,
      11,    32,    69,    90,    91,    33,    62,    34,   113,    96,
     103,    69,    24,    69,    69,    69,    69,    78,    79,   102,
      40,    20,    80,    41,    42,    30,     4,     5,     6,    44,
      63,    45,   111,   112,     4,     5,     6,    25,    69,    26,
     110,    18,    19,   117,   118,    33,    60,    34,    26,    26,
      35,     4,     5,     6,    83,    84,    36,    37,    38,    39,
      40,    65,    66,    41,    42,    43,    78,    79,    33,    44,
      34,    45,    26,    76,     4,     5,     6,    67,    73,    36,
      37,    38,    39,    40,    75,    81,    41,    42,    43,    33,
      85,    34,    44,    26,    45,     4,     5,     6,    82,    86,
      36,    37,    38,    39,    40,    87,    88,    41,    42,    43,
      28,    97,    29,    44,    92,    45,    17,   104,   105,   106,
     108,   109,   107,    84,   114,   115,   116,    13,    99,   101,
       0,   100
};

static const yytype_int8 yycheck[] =
{
      33,    40,    71,     3,    40,    44,    39,    49,    44,     2,
       0,    80,    20,    22,     7,     3,    65,     3,    18,    21,
      28,    21,    22,    16,    12,     2,    12,    27,    13,    29,
       7,    12,    71,    66,    67,     3,    29,     5,   107,    72,
      89,    80,    21,    82,    83,    84,    85,    19,    20,    85,
      18,     4,    24,    21,    22,    21,     9,    10,    11,    27,
      22,    29,   104,   105,     9,    10,    11,     5,   107,     7,
     103,     5,     6,   115,   116,     3,     5,     5,     7,     7,
       8,     9,    10,    11,    26,    27,    14,    15,    16,    17,
      18,     3,     3,    21,    22,    23,    19,    20,     3,    27,
       5,    29,     7,     8,     9,    10,    11,     3,     3,    14,
      15,    16,    17,    18,    21,     5,    21,    22,    23,     3,
      28,     5,    27,     7,    29,     9,    10,    11,    25,    21,
      14,    15,    16,    17,    18,    13,     4,    21,    22,    23,
       4,    21,     6,    27,     5,    29,    12,     4,     4,     4,
      13,     4,     6,    27,     5,     4,    31,     7,    82,    84,
      -1,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,    34,     0,     9,    10,    11,    35,    36,    37,
      38,    41,    42,    36,    21,    43,     3,    12,     5,     6,
       4,    39,    42,    22,    21,     5,     7,    40,     4,     6,
      21,    13,    12,     3,     5,     8,    14,    15,    16,    17,
      18,    21,    22,    23,    27,    29,    40,    41,    42,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
       5,    40,    42,    22,    48,     3,     3,     3,    48,    47,
      53,     3,    12,     3,    53,    21,     8,    45,    19,    20,
      24,     5,    25,    26,    27,    28,    21,    13,     4,    46,
      48,    48,     5,    49,    55,    56,    48,    21,    49,    50,
      51,    52,    53,    46,     4,     4,     4,     6,    13,     4,
      48,    45,    45,    49,     5,     4,    31,    45,    45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    34,    33,    35,    35,    36,    36,    36,    37,
      37,    38,    38,    39,    39,    39,    39,    40,    40,    41,
      42,    42,    42,    43,    43,    43,    43,    44,    44,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    46,    46,
      47,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     6,
       5,     6,     5,     4,     3,     2,     1,     3,     2,     3,
       1,     1,     1,     3,     6,     1,     4,     1,     2,     1,
       1,     1,     7,     5,     7,     5,     5,     3,     1,     2,
       1,     4,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     2,     2,     1,     1,     4,     3,     1,     1,
       2,     2,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 175 "1805031.y"
        {fLog<<"At first";}
#line 1461 "y.tab.c"
    break;

  case 3: /* start: $@1 program  */
#line 176 "1805031.y"
        {
		//write your code in this block in all the similar blocks below
	}
#line 1469 "y.tab.c"
    break;

  case 4: /* program: program unit  */
#line 182 "1805031.y"
        {
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[-1].nonTerminal)->text;
		(yyval.nonTerminal)->text+="\n";
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logRule("program : program unit");
		logPieceOfCode((yyval.nonTerminal)->text);
		
		delete (yyvsp[-1].nonTerminal);
		delete (yyvsp[0].nonTerminal);
	}
#line 1485 "y.tab.c"
    break;

  case 5: /* program: unit  */
#line 194 "1805031.y"
        {
		

		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logRule("program : unit");
		logPieceOfCode((yyval.nonTerminal)->text);
		
		delete (yyvsp[0].nonTerminal);
	}
#line 1500 "y.tab.c"
    break;

  case 6: /* unit: var_declaration  */
#line 207 "1805031.y"
        {
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logRule("unit : var_declaration");
		logPieceOfCode((yyval.nonTerminal)->text);
		
		delete (yyvsp[0].nonTerminal);
	}
#line 1513 "y.tab.c"
    break;

  case 7: /* unit: func_declaration  */
#line 216 "1805031.y"
         {
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logRule("unit : func_declaration");
		logPieceOfCode((yyval.nonTerminal)->text);
		
		delete (yyvsp[0].nonTerminal);
	 }
#line 1526 "y.tab.c"
    break;

  case 8: /* unit: func_definition  */
#line 225 "1805031.y"
         {
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logRule("unit : func_definition");
		logPieceOfCode((yyval.nonTerminal)->text);
		
		delete (yyvsp[0].nonTerminal);
	 }
#line 1539 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 238 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-5].nonTerminal)->text;
			(yyval.nonTerminal)->text+=" ";
			(yyval.nonTerminal)->text+=(yyvsp[-4].symbol)->getName();
			(yyval.nonTerminal)->text+="(";
			(yyval.nonTerminal)->text+=(yyvsp[-2].parameter)->text;
			(yyval.nonTerminal)->text+=")";
			(yyval.nonTerminal)->text+=";";
			logRule("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
			logPieceOfCode((yyval.nonTerminal)->text);
			currentParameterList=NULL;

			(yyvsp[-4].symbol)->functionInfo=new FunctionInfo((yyvsp[-5].nonTerminal)->text,false,(yyvsp[-2].parameter)->dataTypes);
			SymbolInfo * oldSymbol=table->lookup((yyvsp[-4].symbol)->getName());
			if(oldSymbol==NULL)
				table->insert((yyvsp[-4].symbol));
			else if(oldSymbol->functionInfo==NULL){
				yyerror("function "+(yyvsp[-4].symbol)->getName()+" conflicts with prevoius non-function symbol");
				delete (yyvsp[-4].symbol);
			}
			else
				compareFunction((yyvsp[-4].symbol),oldSymbol);

			delete (yyvsp[-5].nonTerminal);
			delete (yyvsp[-2].parameter);

		}
#line 1572 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 267 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-4].nonTerminal)->text;
			(yyval.nonTerminal)->text+=" ";
			(yyval.nonTerminal)->text+=(yyvsp[-3].symbol)->getName();
			(yyval.nonTerminal)->text+="();";
			logRule("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
			logPieceOfCode((yyval.nonTerminal)->text);

			(yyvsp[-3].symbol)->functionInfo=new FunctionInfo((yyvsp[-4].nonTerminal)->text,false);
			SymbolInfo * oldSymbol=table->lookup((yyvsp[-3].symbol)->getName());
			if(oldSymbol==NULL)
				table->insert((yyvsp[-3].symbol));
			else if(oldSymbol->functionInfo==NULL){
				yyerror("function "+(yyvsp[-3].symbol)->getName()+" conflicts with prevoius non-function symbol");
				delete (yyvsp[-3].symbol);
			}
			else
				compareFunction((yyvsp[-3].symbol),oldSymbol);			
			
			delete (yyvsp[-4].nonTerminal);

		}
#line 1600 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement  */
#line 293 "1805031.y"
                {
			

			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-5].nonTerminal)->text;
			(yyval.nonTerminal)->text+=" ";
			(yyval.nonTerminal)->text+=(yyvsp[-4].symbol)->getName();
			(yyval.nonTerminal)->text+="(";
			(yyval.nonTerminal)->text+=(yyvsp[-2].parameter)->text;
			(yyval.nonTerminal)->text+=")";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			currentParameterList=NULL;

			(yyvsp[-4].symbol)->functionInfo=new FunctionInfo((yyvsp[-5].nonTerminal)->text,true,(yyvsp[-2].parameter)->dataTypes);
			SymbolInfo * oldSymbol=table->lookup((yyvsp[-4].symbol)->getName());
			if(oldSymbol==NULL)
				table->insert((yyvsp[-4].symbol));
			else if(oldSymbol->functionInfo==NULL){
				yyerror("function "+(yyvsp[-4].symbol)->getName()+" conflicts with prevoius non-function symbol");
				delete (yyvsp[-4].symbol);
			}
			else
				compareFunction((yyvsp[-4].symbol),oldSymbol);
			
			delete (yyvsp[-5].nonTerminal);
			delete (yyvsp[-2].parameter);
			delete (yyvsp[0].nonTerminal);
		}
#line 1635 "y.tab.c"
    break;

  case 12: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 324 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-4].nonTerminal)->text;
			(yyval.nonTerminal)->text+=" ";
			(yyval.nonTerminal)->text+=(yyvsp[-3].symbol)->getName();
			(yyval.nonTerminal)->text+="()";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
			logPieceOfCode((yyval.nonTerminal)->text);

			(yyvsp[-3].symbol)->functionInfo=new FunctionInfo((yyvsp[-4].nonTerminal)->text,true);
			SymbolInfo * oldSymbol=table->lookup((yyvsp[-3].symbol)->getName());
			if(oldSymbol==NULL)
				table->insert((yyvsp[-3].symbol));
			else if(oldSymbol->functionInfo==NULL){
				yyerror("function "+(yyvsp[-3].symbol)->getName()+" conflicts with prevoius non-function symbol");
				delete (yyvsp[-3].symbol);
			}
			else
				compareFunction((yyvsp[-3].symbol),oldSymbol);
			
			delete (yyvsp[-4].nonTerminal);
			delete (yyvsp[0].nonTerminal);
		}
#line 1664 "y.tab.c"
    break;

  case 13: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 352 "1805031.y"
                {
			

			(yyval.parameter)=new Parameter();
			(yyval.parameter)->text+=(yyvsp[-3].parameter)->text;
			(yyval.parameter)->text+=",";
			(yyval.parameter)->text+=(yyvsp[-1].nonTerminal)->text;
			(yyval.parameter)->text+=" ";
			(yyval.parameter)->text+=(yyvsp[0].symbol)->getName();
			logRule("parameter_list  : parameter_list COMMA type_specifier ID");
			logPieceOfCode((yyval.parameter)->text);
			

			(yyval.parameter)->dataTypes=(yyvsp[-3].parameter)->dataTypes;
			(yyval.parameter)->names=(yyvsp[-3].parameter)->names;
			(yyval.parameter)->dataTypes.push_back((yyvsp[-1].nonTerminal)->text);
			(yyval.parameter)->names.push_back((yyvsp[0].symbol)->getName());
			
			currentParameterList=(yyval.parameter);


			delete (yyvsp[-3].parameter);
			delete (yyvsp[-1].nonTerminal);

			//symbol delete
			delete (yyvsp[0].symbol);

		}
#line 1697 "y.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA type_specifier  */
#line 381 "1805031.y"
                {
			(yyval.parameter)=new Parameter();
			(yyval.parameter)->text+=(yyvsp[-2].parameter)->text;
			(yyval.parameter)->text+=",";
			(yyval.parameter)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("parameter_list  : parameter_list COMMA type_specifier");
			logPieceOfCode((yyval.parameter)->text);
			
			(yyval.parameter)->dataTypes=(yyvsp[-2].parameter)->dataTypes;
			(yyval.parameter)->names=(yyvsp[-2].parameter)->names;
			(yyval.parameter)->dataTypes.push_back((yyvsp[0].nonTerminal)->text);
			(yyval.parameter)->names.push_back("");

			currentParameterList=(yyval.parameter);

			delete (yyvsp[-2].parameter);
			delete (yyvsp[0].nonTerminal);
		}
#line 1720 "y.tab.c"
    break;

  case 15: /* parameter_list: type_specifier ID  */
#line 400 "1805031.y"
                {
			(yyval.parameter)=new Parameter();
			(yyval.parameter)->text+=(yyvsp[-1].nonTerminal)->text;
			(yyval.parameter)->text+=" ";
			(yyval.parameter)->text+=(yyvsp[0].symbol)->getName();
			logRule("parameter_list  : type_specifier ID");
			logPieceOfCode((yyval.parameter)->text);
			
			(yyval.parameter)->dataTypes.push_back((yyvsp[-1].nonTerminal)->text);
			(yyval.parameter)->names.push_back((yyvsp[0].symbol)->getName());

			currentParameterList=(yyval.parameter);

			delete (yyvsp[-1].nonTerminal);

			//symbol delete
			delete (yyvsp[0].symbol);
		}
#line 1743 "y.tab.c"
    break;

  case 16: /* parameter_list: type_specifier  */
#line 419 "1805031.y"
                {
			(yyval.parameter)=new Parameter();
			(yyval.parameter)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("parameter_list : type_specifier");
			logPieceOfCode((yyval.parameter)->text);
			
			(yyval.parameter)->dataTypes.push_back((yyvsp[0].nonTerminal)->text);
			(yyval.parameter)->names.push_back("");

			currentParameterList=(yyval.parameter);

			delete (yyvsp[0].nonTerminal);
		}
#line 1761 "y.tab.c"
    break;

  case 17: /* compound_statement: LCURL statements RCURL  */
#line 436 "1805031.y"
                {
			

			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="{";
			(yyval.nonTerminal)->text+="\n";
			(yyval.nonTerminal)->text+=(yyvsp[-1].nonTerminal)->text;
			(yyval.nonTerminal)->text+="\n}";
			logRule("compound_statement : LCURL statements RCURL");
			logPieceOfCode((yyval.nonTerminal)->text);
			
			delete (yyvsp[-1].nonTerminal);

		}
#line 1780 "y.tab.c"
    break;

  case 18: /* compound_statement: LCURL RCURL  */
#line 451 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="{\n}";
			logRule("compound_statement : LCURL RCURL");
			logPieceOfCode((yyval.nonTerminal)->text);
			
		}
#line 1792 "y.tab.c"
    break;

  case 19: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 461 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-2].nonTerminal)->text;
			(yyval.nonTerminal)->text+=" ";
			(yyval.nonTerminal)->text+=(yyvsp[-1].declarationList)->text;
			(yyval.nonTerminal)->text+=";";
			logRule("var_declaration : type_specifier declaration_list SEMICOLON");
			logPieceOfCode((yyval.nonTerminal)->text);
			
			// insert declared variables in symbol table
			if((yyvsp[-2].nonTerminal)->text=="void"){
				yyerror("Variable type cannot be void");
				// delete all the symbols in declaration list
				for(SymbolInfo * s: (yyvsp[-1].declarationList)->symbols){
					delete s;
				}
			}else{
				for(SymbolInfo * s:(yyvsp[-1].declarationList)->symbols){
					s->variableInfo->dataType=(yyvsp[-2].nonTerminal)->text;
					if(table->insert(s)==false){
						yyerror("Multiple declaration of "+s->getName());
						delete s;
					}
				}
			}


			delete (yyvsp[-2].nonTerminal);
			delete (yyvsp[-1].declarationList);
		}
#line 1827 "y.tab.c"
    break;

  case 20: /* type_specifier: INT  */
#line 494 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text="int";
			logRule("type_specifier	: INT");
			logPieceOfCode((yyval.nonTerminal)->text);
			
		}
#line 1839 "y.tab.c"
    break;

  case 21: /* type_specifier: FLOAT  */
#line 502 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text="float";
			logRule("type_specifier	: FLOAT");
			logPieceOfCode((yyval.nonTerminal)->text);
			
		}
#line 1851 "y.tab.c"
    break;

  case 22: /* type_specifier: VOID  */
#line 510 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text="void";
			logRule("type_specifier	: VOID");
			logPieceOfCode((yyval.nonTerminal)->text);
			
		}
#line 1863 "y.tab.c"
    break;

  case 23: /* declaration_list: declaration_list COMMA ID  */
#line 520 "1805031.y"
                {
			(yyval.declarationList)=new DeclarationList();
			(yyval.declarationList)->text+=(yyvsp[-2].declarationList)->text;
			(yyval.declarationList)->text+=",";
			(yyval.declarationList)->text+=(yyvsp[0].symbol)->getName();
			logRule("declaration_list : declaration_list COMMA ID");
			logPieceOfCode((yyval.declarationList)->text);
			
			(yyval.declarationList)->symbols=(yyvsp[-2].declarationList)->symbols;

			(yyvsp[0].symbol)->variableInfo=new VariableInfo("int");
			(yyval.declarationList)->symbols.push_back((yyvsp[0].symbol));


			delete (yyvsp[-2].declarationList);
		}
#line 1884 "y.tab.c"
    break;

  case 24: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 537 "1805031.y"
                {
			

			(yyval.declarationList)=new DeclarationList();
			(yyval.declarationList)->text+=(yyvsp[-5].declarationList)->text;
			(yyval.declarationList)->text+=",";
			(yyval.declarationList)->text+=(yyvsp[-3].symbol)->getName();
			(yyval.declarationList)->text+="[";
			(yyval.declarationList)->text+=(yyvsp[-1].symbol)->getName();
			(yyval.declarationList)->text+="]";
			logRule("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
			logPieceOfCode((yyval.declarationList)->text);
			
			(yyval.declarationList)->symbols=(yyvsp[-5].declarationList)->symbols;

			if(stoi((yyvsp[-1].symbol)->getName())<=0){
				yyerror("Invalid array size "+(yyvsp[-1].symbol)->getName()+" in declaration of variable "+(yyvsp[-3].symbol)->getName());
				delete (yyvsp[-3].symbol);
			}
			else{
				(yyvsp[-3].symbol)->variableInfo=new VariableInfo("int",new ArrayInfo(stoi((yyvsp[-1].symbol)->getName())));
				(yyval.declarationList)->symbols.push_back((yyvsp[-3].symbol));
			}

			delete (yyvsp[-5].declarationList);

			//symbol delete
			delete (yyvsp[-1].symbol);//const_int
		}
#line 1918 "y.tab.c"
    break;

  case 25: /* declaration_list: ID  */
#line 567 "1805031.y"
                {
			(yyval.declarationList)=new DeclarationList();
			(yyval.declarationList)->text+=(yyvsp[0].symbol)->getName();
			logRule("declaration_list : ID");
			logPieceOfCode((yyval.declarationList)->text);

			(yyvsp[0].symbol)->variableInfo=new VariableInfo("int");
			(yyval.declarationList)->symbols.push_back((yyvsp[0].symbol));
		}
#line 1932 "y.tab.c"
    break;

  case 26: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 577 "1805031.y"
                {
			(yyval.declarationList)=new DeclarationList();
			(yyval.declarationList)->text+=(yyvsp[-3].symbol)->getName();
			(yyval.declarationList)->text+="[";
			(yyval.declarationList)->text+=(yyvsp[-1].symbol)->getName();
			(yyval.declarationList)->text+="]";
			logRule("declaration_list : ID LTHIRD CONST_INT RTHIRD");
			logPieceOfCode((yyval.declarationList)->text);

			if(stoi((yyvsp[-1].symbol)->getName())<=0){
				yyerror("Invalid array size "+(yyvsp[-1].symbol)->getName()+" in declaration of variable "+(yyvsp[-3].symbol)->getName());
				delete (yyvsp[-3].symbol);
			}
			else{
				(yyvsp[-3].symbol)->variableInfo=new VariableInfo("int",new ArrayInfo(stoi((yyvsp[-1].symbol)->getName())));
				(yyval.declarationList)->symbols.push_back((yyvsp[-3].symbol));
			}
			//symbol delete
			delete (yyvsp[-1].symbol); //const_int
		}
#line 1957 "y.tab.c"
    break;

  case 27: /* statements: statement  */
#line 600 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statements : statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			
			delete (yyvsp[0].nonTerminal);
		}
#line 1970 "y.tab.c"
    break;

  case 28: /* statements: statements statement  */
#line 609 "1805031.y"
           {
			

			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-1].nonTerminal)->text;
			(yyval.nonTerminal)->text+="\n";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statements : statements statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			
			delete (yyvsp[-1].nonTerminal);
			delete (yyvsp[0].nonTerminal);
	   }
#line 1988 "y.tab.c"
    break;

  case 29: /* statement: var_declaration  */
#line 625 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statement : var_declaration");
			logPieceOfCode((yyval.nonTerminal)->text);
			
			delete (yyvsp[0].nonTerminal);
		}
#line 2001 "y.tab.c"
    break;

  case 30: /* statement: expression_statement  */
#line 634 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[0].expression)->text;
			logRule("statement : expression_statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			for(SymbolInfo * s:(yyvsp[0].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			delete (yyvsp[0].expression);
		}
#line 2018 "y.tab.c"
    break;

  case 31: /* statement: compound_statement  */
#line 647 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statement : compound_statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			
			delete (yyvsp[0].nonTerminal);
		}
#line 2031 "y.tab.c"
    break;

  case 32: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 656 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="for(";
			(yyval.nonTerminal)->text+=(yyvsp[-4].expression)->text;
			(yyval.nonTerminal)->text+=(yyvsp[-3].expression)->text;
			(yyval.nonTerminal)->text+=(yyvsp[-2].expression)->text;
			(yyval.nonTerminal)->text+=")\n";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
			logPieceOfCode((yyval.nonTerminal)->text);


			for(SymbolInfo * s:(yyvsp[-4].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}

			for(SymbolInfo * s:(yyvsp[-3].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			for(SymbolInfo * s:(yyvsp[-2].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			
			delete (yyvsp[-4].expression);
			delete (yyvsp[-3].expression);
			delete (yyvsp[-2].expression);
			delete (yyvsp[0].nonTerminal);
		}
#line 2070 "y.tab.c"
    break;

  case 33: /* statement: IF LPAREN expression RPAREN statement  */
#line 691 "1805031.y"
                {
			

			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="if(";
			(yyval.nonTerminal)->text+=(yyvsp[-2].expression)->text;
			(yyval.nonTerminal)->text+=")\n";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statement : IF LPAREN expression RPAREN statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			if(expHasVoidFunc((yyvsp[-2].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}
			for(SymbolInfo * s:(yyvsp[-2].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			
			delete (yyvsp[-2].expression);
			delete (yyvsp[0].nonTerminal);

		}
#line 2098 "y.tab.c"
    break;

  case 34: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 715 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="if(";
			(yyval.nonTerminal)->text+=(yyvsp[-4].expression)->text;
			(yyval.nonTerminal)->text+=")\n";
			(yyval.nonTerminal)->text+=(yyvsp[-2].nonTerminal)->text;
			(yyval.nonTerminal)->text+="else\n";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statement :  IF LPAREN expression RPAREN statement ELSE statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			if(expHasVoidFunc((yyvsp[-4].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}

			for(SymbolInfo * s:(yyvsp[-4].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			
			delete (yyvsp[-4].expression);delete (yyvsp[-2].nonTerminal);delete (yyvsp[0].nonTerminal);

		}
#line 2126 "y.tab.c"
    break;

  case 35: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 739 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="while(";
			(yyval.nonTerminal)->text+=(yyvsp[-2].expression)->text;
			(yyval.nonTerminal)->text+=")\n";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
			logRule("statement :  WHILE LPAREN expression RPAREN statement");
			logPieceOfCode((yyval.nonTerminal)->text);
			if(expHasVoidFunc((yyvsp[-2].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}
			for(SymbolInfo * s:(yyvsp[-2].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			
			delete (yyvsp[-2].expression);delete (yyvsp[0].nonTerminal);
		}
#line 2150 "y.tab.c"
    break;

  case 36: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 759 "1805031.y"
                {
			
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="printf(";
			(yyval.nonTerminal)->text+=(yyvsp[-2].symbol)->getName();
			(yyval.nonTerminal)->text+=");";
			logRule("statement :  PRINTLN LPAREN ID RPAREN SEMICOLON");
			logPieceOfCode((yyval.nonTerminal)->text);
			if(table->lookup((yyvsp[-2].symbol)->getName())==NULL){
				yyerror("Undeclared Variable "+(yyvsp[-2].symbol)->getName());
			}
			delete (yyvsp[-2].symbol);
		}
#line 2168 "y.tab.c"
    break;

  case 37: /* statement: RETURN expression SEMICOLON  */
#line 773 "1805031.y"
                {
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="return ";
			(yyval.nonTerminal)->text+=(yyvsp[-1].expression)->text;
			(yyval.nonTerminal)->text+=";";
			logRule("statement : RETURN expression SEMICOLON");
			logPieceOfCode((yyval.nonTerminal)->text);
			if(expHasVoidFunc((yyvsp[-1].expression))){
				yyerror("void-returning function cannot be part of expression");
			}

			for(SymbolInfo * s:(yyvsp[-1].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}
			
			delete (yyvsp[-1].expression);
		}
#line 2192 "y.tab.c"
    break;

  case 38: /* expression_statement: SEMICOLON  */
#line 795 "1805031.y"
                {
			

			(yyval.expression)=new Expression();
			(yyval.expression)->text+=";";
			logRule("expression_statement : SEMICOLON	");
			logPieceOfCode((yyval.expression)->text);

		}
#line 2206 "y.tab.c"
    break;

  case 39: /* expression_statement: expression SEMICOLON  */
#line 805 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-1].expression)->text;
			(yyval.expression)->text+=";";
			logRule("expression_statement : expression SEMICOLON ");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[-1].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[-1].expression)->forceInteger;

			delete (yyvsp[-1].expression);
		}
#line 2222 "y.tab.c"
    break;

  case 40: /* variable: ID  */
#line 819 "1805031.y"
                {
			

			(yyval.variable)=new Variable();
			(yyval.variable)->text+=(yyvsp[0].symbol)->getName();
			logRule("variable : ID ");
			logPieceOfCode((yyval.variable)->text);
			SymbolInfo * symbol=table->lookup((yyvsp[0].symbol)->getName());
			if(symbol==NULL){
				yyerror("Undeclared Variable "+(yyvsp[0].symbol)->getName());
			}else if(symbol->variableInfo==NULL){
				yyerror((yyvsp[0].symbol)->getName()+" is not a variable");
			}
			else if(symbol->variableInfo->arrayInfo!=NULL){
				yyerror((yyvsp[0].symbol)->getName()+" is an array, cannot be used without indexing");
			}else{
				(yyval.variable)->symbol=symbol;
			}

			delete (yyvsp[0].symbol);

		}
#line 2249 "y.tab.c"
    break;

  case 41: /* variable: ID LTHIRD expression RTHIRD  */
#line 842 "1805031.y"
                {
			(yyval.variable)=new Variable();
			(yyval.variable)->text+=(yyvsp[-3].symbol)->getName();
			(yyval.variable)->text+="[";
			(yyval.variable)->text+=(yyvsp[-1].expression)->text;
			(yyval.variable)->text+="]";
			logRule("variable : ID LTHIRD expression RTHIRD ");
			logPieceOfCode((yyval.variable)->text);
			// task: check if expression evaluates to int
			if(getTypeOfExpression((yyvsp[-1].expression))!="int"){
				yyerror("Type of array index must be integer");
			}

			SymbolInfo * symbol=table->lookup((yyvsp[-3].symbol)->getName());
			if(symbol==NULL){
				yyerror("Undeclared Variable "+(yyvsp[-3].symbol)->getName());
			}else if(symbol->variableInfo==NULL){
				yyerror((yyvsp[-3].symbol)->getName()+" is not a variable");
			}
			else if(symbol->variableInfo->arrayInfo==NULL){
				yyerror((yyvsp[-3].symbol)->getName()+" is not an array");
			}else{
				(yyval.variable)->symbol=symbol;
			}
			if(expHasVoidFunc((yyvsp[-1].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}
			for(SymbolInfo * s:(yyvsp[-1].expression)->symbols){
				if(s->functionInfo==NULL && s->variableInfo==NULL){
					delete s;
				}
			}

			delete (yyvsp[-1].expression);
			delete (yyvsp[-3].symbol);

		}
#line 2291 "y.tab.c"
    break;

  case 42: /* expression: logic_expression  */
#line 882 "1805031.y"
                {
			

			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("expression : logic_expression	");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;

			delete (yyvsp[0].expression);
		}
#line 2308 "y.tab.c"
    break;

  case 43: /* expression: variable ASSIGNOP logic_expression  */
#line 895 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-2].variable)->text;
			(yyval.expression)->text+="=";
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("expression : variable ASSIGNOP logic_expression");
			logPieceOfCode((yyval.expression)->text);

			if((yyvsp[-2].variable)->symbol!=NULL){
				if((yyvsp[-2].variable)->symbol->variableInfo->dataType=="int" && getTypeOfExpression((yyvsp[0].expression))=="float"){
					yyerror("Type Mismatch, assigning "+
					getTypeOfExpression((yyvsp[0].expression))+" value to variable of type "
					+(yyvsp[-2].variable)->symbol->variableInfo->dataType);
				}
				
			}
			if(expHasVoidFunc((yyvsp[0].expression))){
				yyerror("void-returning function cannot be part of expression");
			}
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;


			
			delete (yyvsp[-2].variable);
			delete (yyvsp[0].expression);
		}
#line 2340 "y.tab.c"
    break;

  case 44: /* logic_expression: rel_expression  */
#line 925 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("logic_expression : rel_expression");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;

			delete (yyvsp[0].expression);
		}
#line 2355 "y.tab.c"
    break;

  case 45: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 936 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-2].expression)->text;
			(yyval.expression)->text+=(yyvsp[-1].symbol)->getName();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("logic_expression : rel_expression LOGICOP rel_expression");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[-2].expression)->symbols;
			for(SymbolInfo * s:(yyvsp[0].expression)->symbols){
				(yyval.expression)->symbols.push_back(s);
			}
			(yyval.expression)->forceInteger=true;
			if(expHasVoidFunc((yyvsp[-2].expression)) ||expHasVoidFunc((yyvsp[0].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}
			
			delete (yyvsp[-2].expression);
			delete (yyvsp[0].expression);

			//symbol delete
			delete (yyvsp[-1].symbol);
		}
#line 2382 "y.tab.c"
    break;

  case 46: /* rel_expression: simple_expression  */
#line 961 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("rel_expression	: simple_expression ");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;

			delete (yyvsp[0].expression);
		}
#line 2397 "y.tab.c"
    break;

  case 47: /* rel_expression: simple_expression RELOP simple_expression  */
#line 972 "1805031.y"
                {
			

			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-2].expression)->text;
			(yyval.expression)->text+=(yyvsp[-1].symbol)->getName();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("rel_expression	: simple_expression RELOP simple_expression	");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[-2].expression)->symbols;
			for(SymbolInfo * s:(yyvsp[0].expression)->symbols){
				(yyval.expression)->symbols.push_back(s);
			}
			(yyval.expression)->forceInteger=true;
			if(expHasVoidFunc((yyvsp[-2].expression)) ||expHasVoidFunc((yyvsp[0].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}
			
			delete (yyvsp[-2].expression);delete (yyvsp[0].expression);

			//symbol delete 
			delete (yyvsp[-1].symbol);
		}
#line 2425 "y.tab.c"
    break;

  case 48: /* simple_expression: term  */
#line 998 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("simple_expression : term ");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;
			delete (yyvsp[0].expression);
		}
#line 2439 "y.tab.c"
    break;

  case 49: /* simple_expression: simple_expression ADDOP term  */
#line 1008 "1805031.y"
                {
			

			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-2].expression)->text;
			(yyval.expression)->text+=(yyvsp[-1].symbol)->getName();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("simple_expression : simple_expression ADDOP term");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[-2].expression)->symbols;
			for(SymbolInfo * s:(yyvsp[0].expression)->symbols){
				(yyval.expression)->symbols.push_back(s);
			}
			(yyval.expression)->forceInteger=(yyvsp[-2].expression)->forceInteger && (yyvsp[0].expression)->forceInteger;

			if(expHasVoidFunc((yyvsp[-2].expression)) ||expHasVoidFunc((yyvsp[0].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}
			
			delete (yyvsp[-2].expression);
			delete (yyvsp[0].expression);
			delete (yyvsp[-1].symbol);
		}
#line 2467 "y.tab.c"
    break;

  case 50: /* term: unary_expression  */
#line 1034 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("term :	unary_expression");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;
			delete (yyvsp[0].expression);
		}
#line 2481 "y.tab.c"
    break;

  case 51: /* term: term MULOP unary_expression  */
#line 1044 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-2].expression)->text;
			(yyval.expression)->text+=(yyvsp[-1].symbol)->getName();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("term : term MULOP unary_expression");
			logPieceOfCode((yyval.expression)->text);
			if((yyvsp[-1].symbol)->getName()=="%" &&(getTypeOfExpression((yyvsp[-2].expression))!="int" || 
			getTypeOfExpression((yyvsp[0].expression))!="int")){
				yyerror("Modulus operator needs integer operands");
			}
			(yyval.expression)->symbols=(yyvsp[-2].expression)->symbols;
			for(SymbolInfo * s:(yyvsp[0].expression)->symbols){
				(yyval.expression)->symbols.push_back(s);
			}
			if((yyvsp[-1].symbol)->getName()=="*")
				(yyval.expression)->forceInteger=(yyvsp[-2].expression)->forceInteger && (yyvsp[0].expression)->forceInteger;
			else
				(yyval.expression)->forceInteger=true;

			if(expHasVoidFunc((yyvsp[-2].expression)) ||expHasVoidFunc((yyvsp[0].expression)) ){
				yyerror("void-returning function cannot be part of expression");
			}
			delete (yyvsp[-2].expression);
			delete (yyvsp[0].expression);
			delete (yyvsp[-1].symbol);
		}
#line 2513 "y.tab.c"
    break;

  case 52: /* unary_expression: ADDOP unary_expression  */
#line 1074 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-1].symbol)->getName();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("unary_expression : ADDOP unary_expression ");
			logPieceOfCode((yyval.expression)->text);

			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;

			if(expHasVoidFunc((yyvsp[0].expression))){
				yyerror("void-returning function cannot be part of expression");
			}
			
			delete (yyvsp[0].expression);
			delete (yyvsp[-1].symbol);
		}
#line 2535 "y.tab.c"
    break;

  case 53: /* unary_expression: NOT unary_expression  */
#line 1092 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+="!";
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("unary_expression : NOT unary_expression ");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[0].expression)->forceInteger;

			if(expHasVoidFunc((yyvsp[0].expression))){
				yyerror("void-returning function cannot be part of expression");
			}


			delete (yyvsp[0].expression);
		}
#line 2556 "y.tab.c"
    break;

  case 54: /* unary_expression: factor  */
#line 1109 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].expression)->text;
			logRule("unary_expression : factor");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[0].expression)->symbols;

			delete (yyvsp[0].expression);
		}
#line 2570 "y.tab.c"
    break;

  case 55: /* factor: variable  */
#line 1121 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].variable)->text;
			logRule("factor	: variable ");
			logPieceOfCode((yyval.expression)->text);
			if((yyvsp[0].variable)->symbol!=NULL){
				(yyval.expression)->symbols.push_back((yyvsp[0].variable)->symbol);
			}

			delete (yyvsp[0].variable);
		}
#line 2586 "y.tab.c"
    break;

  case 56: /* factor: ID LPAREN argument_list RPAREN  */
#line 1133 "1805031.y"
                {
			

			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-3].symbol)->getName();
			(yyval.expression)->text+="(";
			(yyval.expression)->text+=(yyvsp[-1].argument)->text;
			(yyval.expression)->text+=")";
			logRule("factor : ID LPAREN argument_list RPAREN");
			logPieceOfCode((yyval.expression)->text);
			SymbolInfo * symbol=table->lookup((yyvsp[-3].symbol)->getName());
			if(symbol==NULL){
				yyerror((yyvsp[-3].symbol)->getName()+" is undeclared");
			}else if(symbol->functionInfo==NULL){
				yyerror((yyvsp[-3].symbol)->getName()+" is not a function");
			}
			//else if(symbol->functionInfo->returnType=="void"){
			// 		yyerror("void-returning function "+symbol->getName()+" cannot be part of expression");
			// }
			else if((yyvsp[-1].argument)->dataTypes.size()!=symbol->functionInfo->paramDataTypes.size()){
				yyerror("Argument Size Mismatch");
				(yyval.expression)->symbols.push_back(symbol);
			}else{
				for(int i=0;i<(yyvsp[-1].argument)->dataTypes.size();i++){
					if((yyvsp[-1].argument)->dataTypes.at(i)!=symbol->functionInfo->paramDataTypes.at(i)){
						yyerror("Argument no "+to_string(i)+" type mismatch");
					}
				}
				(yyval.expression)->symbols.push_back(symbol);
			}
			delete (yyvsp[-1].argument);
			delete (yyvsp[-3].symbol);
		}
#line 2624 "y.tab.c"
    break;

  case 57: /* factor: LPAREN expression RPAREN  */
#line 1167 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+="(";
			(yyval.expression)->text+=(yyvsp[-1].expression)->text;
			(yyval.expression)->text+=")";
			logRule("factor : LPAREN expression RPAREN");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols=(yyvsp[-1].expression)->symbols;
			(yyval.expression)->forceInteger=(yyvsp[-1].expression)->forceInteger;
			
			delete (yyvsp[-1].expression);
		}
#line 2641 "y.tab.c"
    break;

  case 58: /* factor: CONST_INT  */
#line 1180 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].symbol)->getName();
			logRule("factor	: CONST_INT");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols.push_back((yyvsp[0].symbol));
		}
#line 2653 "y.tab.c"
    break;

  case 59: /* factor: CONST_FLOAT  */
#line 1188 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[0].symbol)->getName();
			logRule("factor	: CONST_FLOAT");
			logPieceOfCode((yyval.expression)->text);
			(yyval.expression)->symbols.push_back((yyvsp[0].symbol));

		}
#line 2666 "y.tab.c"
    break;

  case 60: /* factor: variable INCOP  */
#line 1197 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-1].variable)->text;
			(yyval.expression)->text+="++";
			logRule("factor	: variable INCOP");
			logPieceOfCode((yyval.expression)->text);
			if((yyvsp[-1].variable)->symbol!=NULL){
				(yyval.expression)->symbols.push_back((yyvsp[-1].variable)->symbol);
			}

			delete (yyvsp[-1].variable);

		}
#line 2684 "y.tab.c"
    break;

  case 61: /* factor: variable DECOP  */
#line 1211 "1805031.y"
                {
			(yyval.expression)=new Expression();
			(yyval.expression)->text+=(yyvsp[-1].variable)->text;
			(yyval.expression)->text+="--";
			logRule("factor	: variable DECOP");
			logPieceOfCode((yyval.expression)->text);
			if((yyvsp[-1].variable)->symbol!=NULL){
				(yyval.expression)->symbols.push_back((yyvsp[-1].variable)->symbol);
			}
			delete (yyvsp[-1].variable);
		}
#line 2700 "y.tab.c"
    break;

  case 62: /* argument_list: arguments  */
#line 1225 "1805031.y"
                {
			(yyval.argument)=new Argument();
			(yyval.argument)->text+=(yyvsp[0].argument)->text;
			logRule("argument_list : arguments");
			logPieceOfCode((yyval.argument)->text);
			(yyval.argument)->dataTypes=(yyvsp[0].argument)->dataTypes;
			delete (yyvsp[0].argument);
		}
#line 2713 "y.tab.c"
    break;

  case 63: /* argument_list: %empty  */
#line 1234 "1805031.y"
                {
			(yyval.argument)=new Argument();
			logRule("argument_list : empty");
			logPieceOfCode((yyval.argument)->text);
			
		}
#line 2724 "y.tab.c"
    break;

  case 64: /* arguments: arguments COMMA logic_expression  */
#line 1242 "1805031.y"
                {
			(yyval.argument)=new Argument();
			(yyval.argument)->text+=(yyvsp[-2].argument)->text;
			(yyval.argument)->text+=",";
			(yyval.argument)->text+=(yyvsp[0].expression)->text;
			logRule("arguments : arguments COMMA logic_expression");
			logPieceOfCode((yyval.argument)->text);
			(yyval.argument)->dataTypes=(yyvsp[-2].argument)->dataTypes;
			(yyval.argument)->dataTypes.push_back(getTypeOfExpression((yyvsp[0].expression)));

			//task : before deleting expression, free symbols that are not 
			//in the symbol table

			delete (yyvsp[-2].argument);
			delete (yyvsp[0].expression);

		}
#line 2746 "y.tab.c"
    break;

  case 65: /* arguments: logic_expression  */
#line 1260 "1805031.y"
                {
			(yyval.argument)=new Argument();
			(yyval.argument)->text+=(yyvsp[0].expression)->text;
			logRule("arguments : logic_expression");
			logPieceOfCode((yyval.argument)->text);
			(yyval.argument)->dataTypes.push_back(getTypeOfExpression((yyvsp[0].expression)));

			delete (yyvsp[0].expression);
		}
#line 2760 "y.tab.c"
    break;


#line 2764 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1272 "1805031.y"

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

	//symbol table print
	table->printAllScopeTable(fLog);

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

