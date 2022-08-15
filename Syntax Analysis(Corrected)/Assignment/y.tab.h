/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 120 "1805031.y"

	SymbolInfo * symbol;
	NonTerminal * nonTerminal;
	Parameter * parameter;
	DeclarationList * declarationList;
	Expression * expression;
	Variable * variable;

#line 138 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
