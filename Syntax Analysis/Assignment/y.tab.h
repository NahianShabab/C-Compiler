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
    ID = 258,                      /* ID  */
    LPAREN = 259,                  /* LPAREN  */
    RPAREN = 260,                  /* RPAREN  */
    SEMICOLON = 261,               /* SEMICOLON  */
    COMMA = 262,                   /* COMMA  */
    LCURL = 263,                   /* LCURL  */
    RCURL = 264,                   /* RCURL  */
    INT = 265,                     /* INT  */
    FLOAT = 266,                   /* FLOAT  */
    VOID = 267,                    /* VOID  */
    LTHIRD = 268,                  /* LTHIRD  */
    CONST_INT = 269,               /* CONST_INT  */
    RTHIRD = 270,                  /* RTHIRD  */
    FOR = 271,                     /* FOR  */
    IF = 272,                      /* IF  */
    ELSE = 273,                    /* ELSE  */
    WHILE = 274,                   /* WHILE  */
    PRINTLN = 275,                 /* PRINTLN  */
    RETURN = 276,                  /* RETURN  */
    ASSIGNOP = 277,                /* ASSIGNOP  */
    LOGICOP = 278,                 /* LOGICOP  */
    RELOP = 279,                   /* RELOP  */
    ADDOP = 280,                   /* ADDOP  */
    MULOP = 281,                   /* MULOP  */
    NOT = 282,                     /* NOT  */
    CONST_FLOAT = 283,             /* CONST_FLOAT  */
    INCOP = 284,                   /* INCOP  */
    DECOP = 285,                   /* DECOP  */
    S_IF = 286                     /* S_IF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define LPAREN 259
#define RPAREN 260
#define SEMICOLON 261
#define COMMA 262
#define LCURL 263
#define RCURL 264
#define INT 265
#define FLOAT 266
#define VOID 267
#define LTHIRD 268
#define CONST_INT 269
#define RTHIRD 270
#define FOR 271
#define IF 272
#define ELSE 273
#define WHILE 274
#define PRINTLN 275
#define RETURN 276
#define ASSIGNOP 277
#define LOGICOP 278
#define RELOP 279
#define ADDOP 280
#define MULOP 281
#define NOT 282
#define CONST_FLOAT 283
#define INCOP 284
#define DECOP 285
#define S_IF 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
