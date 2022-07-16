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
#line 2 "1805031.y"

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


#line 122 "y.tab.c"

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
    S_IF = 285,                    /* S_IF  */
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
#define S_IF 285
#define ELSE 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 53 "1805031.y"

	SymbolInfo * symbol;
	NonTerminal * nonTerminal;

#line 242 "y.tab.c"

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
  YYSYMBOL_S_IF = 30,                      /* S_IF  */
  YYSYMBOL_ELSE = 31,                      /* ELSE  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_start = 33,                     /* start  */
  YYSYMBOL_program = 34,                   /* program  */
  YYSYMBOL_unit = 35,                      /* unit  */
  YYSYMBOL_func_declaration = 36,          /* func_declaration  */
  YYSYMBOL_func_definition = 37,           /* func_definition  */
  YYSYMBOL_parameter_list = 38,            /* parameter_list  */
  YYSYMBOL_compound_statement = 39,        /* compound_statement  */
  YYSYMBOL_var_declaration = 40,           /* var_declaration  */
  YYSYMBOL_type_specifier = 41,            /* type_specifier  */
  YYSYMBOL_declaration_list = 42,          /* declaration_list  */
  YYSYMBOL_statements = 43,                /* statements  */
  YYSYMBOL_statement = 44,                 /* statement  */
  YYSYMBOL_expression_statement = 45,      /* expression_statement  */
  YYSYMBOL_variable = 46,                  /* variable  */
  YYSYMBOL_expression = 47,                /* expression  */
  YYSYMBOL_logic_expression = 48,          /* logic_expression  */
  YYSYMBOL_rel_expression = 49,            /* rel_expression  */
  YYSYMBOL_simple_expression = 50,         /* simple_expression  */
  YYSYMBOL_term = 51,                      /* term  */
  YYSYMBOL_unary_expression = 52,          /* unary_expression  */
  YYSYMBOL_factor = 53,                    /* factor  */
  YYSYMBOL_argument_list = 54,             /* argument_list  */
  YYSYMBOL_arguments = 55                  /* arguments  */
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

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
       0,    71,    71,    79,    90,   100,   108,   117,   127,   138,
     144,   148,   167,   171,   175,   179,   186,   190,   199,   205,
     212,   216,   222,   226,   230,   234,   240,   244,   250,   254,
     258,   262,   266,   270,   274,   278,   282,   288,   292,   298,
     302,   308,   312,   318,   322,   328,   332,   338,   342,   348,
     352,   358,   362,   366,   372,   376,   380,   384,   388,   392,
     396,   402,   407,   412,   416
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
  "CONST_FLOAT", "S_IF", "ELSE", "$accept", "start", "program", "unit",
  "func_declaration", "func_definition", "parameter_list",
  "compound_statement", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     131,   -69,   -69,   -69,    17,   131,   -69,   -69,   -69,   -69,
      -8,   -69,   -69,     7,    55,    43,    -2,   -69,    36,    21,
      44,    48,    63,    66,   -69,    72,   -69,    60,   131,   -69,
     -69,    69,     0,   -69,   -69,    89,    93,    94,     0,     0,
      13,   -69,   104,     0,   -69,   -69,   -69,    87,    95,   -69,
     -69,    11,   109,   -69,    90,    45,    92,   -69,   -69,   -69,
     -69,   107,   122,   125,    37,     0,     0,   139,    65,   -69,
       0,     0,   115,   -69,   134,   -69,   -69,   -69,   -69,     0,
     -69,     0,     0,     0,     0,   -69,   -69,   -69,    37,   143,
     144,   -69,   -69,   145,   146,   137,   147,   -69,   -69,   126,
      92,   -69,     0,   116,   116,   -69,     0,   -69,   149,   151,
     127,   -69,   -69,   -69,   116,   116,   -69,   -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    19,    20,    21,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    24,     0,     0,     0,    18,     0,     0,
       0,    15,     0,    22,     9,     0,    11,     0,     0,    14,
      25,     0,     0,    37,    17,     0,     0,     0,     0,     0,
      39,    57,     0,     0,    58,    30,    28,     0,     0,    26,
      29,    54,     0,    41,    43,    45,    47,    49,    53,     8,
      10,    13,     0,     0,     0,     0,     0,     0,    54,    52,
      62,     0,     0,    51,    24,    16,    27,    59,    60,     0,
      38,     0,     0,     0,     0,    12,    23,    56,     0,     0,
       0,    36,    64,     0,    61,     0,     0,    42,    44,    46,
      48,    50,     0,     0,     0,    55,     0,    40,     0,     0,
      32,    34,    63,    35,     0,     0,    31,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   -69,   152,   -69,   -69,   -69,    -4,    51,     9,
     -69,   -69,   -41,   -52,   -38,   -32,   -68,    75,    77,    78,
     -35,   -69,   -69,   -69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    20,    45,    46,    47,
      14,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    93,    94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      63,    68,    92,    32,    69,    68,    67,    76,    73,    10,
      15,    97,    88,    13,    10,    26,    70,    11,    39,    16,
      22,    40,    41,    60,    21,    71,    24,    43,    25,    44,
      77,    78,    68,    89,    90,    79,   102,    61,   112,    95,
      32,    68,    33,    68,    68,    68,    68,    19,    27,   101,
      28,     9,     1,     2,     3,    39,     9,    23,    40,    41,
      17,    18,   110,   111,    43,    59,    44,    25,    68,    29,
     109,    82,    83,   116,   117,    32,    30,    33,    31,    25,
      34,     1,     2,     3,    77,    78,    35,    36,    37,    38,
      39,    62,    64,    40,    41,    42,    65,    66,    32,    43,
      33,    44,    25,    75,     1,     2,     3,    72,    74,    35,
      36,    37,    38,    39,    80,    81,    40,    41,    42,    32,
      84,    33,    43,    25,    44,     1,     2,     3,    85,    87,
      35,    36,    37,    38,    39,    86,    96,    40,    41,    42,
       1,     2,     3,    43,    91,    44,    16,   103,   104,   105,
     107,   108,   106,    83,   113,   114,    98,    12,   115,    99,
       0,   100
};

static const yytype_int8 yycheck[] =
{
      32,    39,    70,     3,    39,    43,    38,    48,    43,     0,
       3,    79,    64,    21,     5,    19,     3,     0,    18,    12,
      22,    21,    22,    27,    15,    12,     5,    27,     7,    29,
      19,    20,    70,    65,    66,    24,    88,    28,   106,    71,
       3,    79,     5,    81,    82,    83,    84,     4,     4,    84,
       6,     0,     9,    10,    11,    18,     5,    21,    21,    22,
       5,     6,   103,   104,    27,     5,    29,     7,   106,    21,
     102,    26,    27,   114,   115,     3,    13,     5,    12,     7,
       8,     9,    10,    11,    19,    20,    14,    15,    16,    17,
      18,    22,     3,    21,    22,    23,     3,     3,     3,    27,
       5,    29,     7,     8,     9,    10,    11,     3,    21,    14,
      15,    16,    17,    18,     5,    25,    21,    22,    23,     3,
      28,     5,    27,     7,    29,     9,    10,    11,    21,     4,
      14,    15,    16,    17,    18,    13,    21,    21,    22,    23,
       9,    10,    11,    27,     5,    29,    12,     4,     4,     4,
      13,     4,     6,    27,     5,     4,    81,     5,    31,    82,
      -1,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    10,    11,    33,    34,    35,    36,    37,    40,
      41,     0,    35,    21,    42,     3,    12,     5,     6,     4,
      38,    41,    22,    21,     5,     7,    39,     4,     6,    21,
      13,    12,     3,     5,     8,    14,    15,    16,    17,    18,
      21,    22,    23,    27,    29,    39,    40,    41,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,     5,
      39,    41,    22,    47,     3,     3,     3,    47,    46,    52,
       3,    12,     3,    52,    21,     8,    44,    19,    20,    24,
       5,    25,    26,    27,    28,    21,    13,     4,    45,    47,
      47,     5,    48,    54,    55,    47,    21,    48,    49,    50,
      51,    52,    45,     4,     4,     4,     6,    13,     4,    47,
      44,    44,    48,     5,     4,    31,    44,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    36,    36,
      37,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      41,    41,    42,    42,    42,    42,    43,    43,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    55,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     3,     2,     3,     1,
       1,     1,     3,     6,     1,     4,     1,     2,     1,     1,
       1,     7,     5,     7,     5,     5,     3,     1,     2,     1,
       4,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     2,     2,     1,     1,     4,     3,     1,     1,     2,
       2,     1,     0,     3,     1
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
  case 2: /* start: program  */
#line 72 "1805031.y"
        {
		//write your code in this block in all the similar blocks below
		logGrammer("start: program");
		delNonTerminal((yyvsp[0].nonTerminal));
	}
#line 1365 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 80 "1805031.y"
        {
		logGrammer("program : program unit");
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[-1].nonTerminal)->text;
		(yyval.nonTerminal)->text+="\n";
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logPiece((yyval.nonTerminal)->text);
		delNonTerminal((yyvsp[-1].nonTerminal));
		delNonTerminal((yyvsp[0].nonTerminal));
	}
#line 1380 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 91 "1805031.y"
        {
		logGrammer("program : unit");
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logPiece((yyval.nonTerminal)->text);
		delNonTerminal((yyvsp[0].nonTerminal));
	}
#line 1392 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 101 "1805031.y"
        {
		logGrammer("unit : var_declaration");
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logPiece((yyval.nonTerminal)->text);
		delNonTerminal((yyvsp[0].nonTerminal));
	}
#line 1404 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 109 "1805031.y"
         {
		logGrammer("unit : func_declaration");
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;
		logPiece((yyval.nonTerminal)->text);
		delNonTerminal((yyvsp[0].nonTerminal));
		
	 }
#line 1417 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 118 "1805031.y"
         {
		logGrammer("unit : func_definition");
		(yyval.nonTerminal)=new NonTerminal();
		(yyval.nonTerminal)->text=(yyvsp[0].nonTerminal)->text;
		logPiece((yyval.nonTerminal)->text);
		delNonTerminal((yyvsp[0].nonTerminal));
	 }
#line 1429 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 128 "1805031.y"
                {
			logGrammer("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-5].nonTerminal)->text;
			(yyval.nonTerminal)->text+=" "+(yyvsp[-4].symbol)->getName();


			logPiece((yyval.nonTerminal)->text);
			delNonTerminal((yyvsp[-5].nonTerminal));
		}
#line 1444 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 139 "1805031.y"
                {
			logGrammer("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		}
#line 1452 "y.tab.c"
    break;

  case 10: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement  */
#line 145 "1805031.y"
                {
			logGrammer("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		}
#line 1460 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 149 "1805031.y"
                {
			logGrammer("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+=(yyvsp[-4].nonTerminal)->text;
			(yyval.nonTerminal)->text+=" "+(yyvsp[-3].symbol)->getName();
			(yyval.nonTerminal)->text+="(";
			(yyval.nonTerminal)->text+=")";
			(yyval.nonTerminal)->text+=(yyvsp[0].nonTerminal)->text;

			table->insert((yyvsp[-3].symbol));

			logPiece((yyval.nonTerminal)->text);
			delNonTerminal((yyvsp[-4].nonTerminal));
			delNonTerminal((yyvsp[0].nonTerminal));
		}
#line 1480 "y.tab.c"
    break;

  case 12: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 168 "1805031.y"
                {
			logGrammer("parameter_list  : parameter_list COMMA type_specifier ID");
		}
#line 1488 "y.tab.c"
    break;

  case 13: /* parameter_list: parameter_list COMMA type_specifier  */
#line 172 "1805031.y"
                {
			logGrammer("parameter_list  : parameter_list COMMA type_specifier");
		}
#line 1496 "y.tab.c"
    break;

  case 14: /* parameter_list: type_specifier ID  */
#line 176 "1805031.y"
                {
			logGrammer("parameter_list  : type_specifier ID");
		}
#line 1504 "y.tab.c"
    break;

  case 15: /* parameter_list: type_specifier  */
#line 180 "1805031.y"
                {
			logGrammer("parameter_list  : type_specifier");
		}
#line 1512 "y.tab.c"
    break;

  case 16: /* compound_statement: LCURL statements RCURL  */
#line 187 "1805031.y"
                        {
			logGrammer("compound_statement : LCURL statements RCURL");
			}
#line 1520 "y.tab.c"
    break;

  case 17: /* compound_statement: LCURL RCURL  */
#line 191 "1805031.y"
                        {	
			logGrammer("compound_statement : LCURL RCURL");
				(yyval.nonTerminal)=new NonTerminal();
				(yyval.nonTerminal)->text+="{\n}";
				logPiece((yyval.nonTerminal)->text);
			}
#line 1531 "y.tab.c"
    break;

  case 18: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 200 "1805031.y"
                {
			logGrammer("var_declaration : type_specifier declaration_list SEMICOLON");
		}
#line 1539 "y.tab.c"
    break;

  case 19: /* type_specifier: INT  */
#line 206 "1805031.y"
                {
			logGrammer("type_specifier : INT");
			(yyval.nonTerminal)=new NonTerminal();
			(yyval.nonTerminal)->text+="int";
			logPiece((yyval.nonTerminal)->text);
		}
#line 1550 "y.tab.c"
    break;

  case 20: /* type_specifier: FLOAT  */
#line 213 "1805031.y"
                {
			logGrammer("type_specifier : FLOAT");
		}
#line 1558 "y.tab.c"
    break;

  case 21: /* type_specifier: VOID  */
#line 217 "1805031.y"
                {
			logGrammer("type_specifier : VOID");
		}
#line 1566 "y.tab.c"
    break;

  case 22: /* declaration_list: declaration_list COMMA ID  */
#line 223 "1805031.y"
                {
			logGrammer("declaration_list : declaration_list COMMA ID");
		}
#line 1574 "y.tab.c"
    break;

  case 23: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 227 "1805031.y"
                {
			logGrammer("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		}
#line 1582 "y.tab.c"
    break;

  case 24: /* declaration_list: ID  */
#line 231 "1805031.y"
                {
			logGrammer("declaration_list : ID");
		}
#line 1590 "y.tab.c"
    break;

  case 25: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 235 "1805031.y"
                {
			logGrammer("declaration_list : ID LTHIRD CONST_INT RTHIRD");
		}
#line 1598 "y.tab.c"
    break;

  case 26: /* statements: statement  */
#line 241 "1805031.y"
                {
			logGrammer("statements : statement");
		}
#line 1606 "y.tab.c"
    break;

  case 27: /* statements: statements statement  */
#line 245 "1805031.y"
                {
			logGrammer("statements : statements statement");
		}
#line 1614 "y.tab.c"
    break;

  case 28: /* statement: var_declaration  */
#line 251 "1805031.y"
                {
			logGrammer("statement : var_declaration");
		}
#line 1622 "y.tab.c"
    break;

  case 29: /* statement: expression_statement  */
#line 255 "1805031.y"
                {
			logGrammer("statement : expression_statement");
		}
#line 1630 "y.tab.c"
    break;

  case 30: /* statement: compound_statement  */
#line 259 "1805031.y"
                {
			logGrammer("statement : compound_statement");
		}
#line 1638 "y.tab.c"
    break;

  case 31: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 263 "1805031.y"
                {
			logGrammer("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		}
#line 1646 "y.tab.c"
    break;

  case 32: /* statement: IF LPAREN expression RPAREN statement  */
#line 267 "1805031.y"
                {
			logGrammer("statement : IF LPAREN expression RPAREN statement");
		}
#line 1654 "y.tab.c"
    break;

  case 33: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 271 "1805031.y"
                {
			logGrammer("statement : IF LPAREN expression RPAREN statement ELSE statement");
		}
#line 1662 "y.tab.c"
    break;

  case 34: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 275 "1805031.y"
                {
			logGrammer("statement : WHILE LPAREN expression RPAREN statement");
		}
#line 1670 "y.tab.c"
    break;

  case 35: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 279 "1805031.y"
                {
			logGrammer("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		}
#line 1678 "y.tab.c"
    break;

  case 36: /* statement: RETURN expression SEMICOLON  */
#line 283 "1805031.y"
                {
			logGrammer("statement : RETURN expression SEMICOLON");
		}
#line 1686 "y.tab.c"
    break;

  case 37: /* expression_statement: SEMICOLON  */
#line 289 "1805031.y"
                {
			logGrammer("expression_statement : SEMICOLON");
		}
#line 1694 "y.tab.c"
    break;

  case 38: /* expression_statement: expression SEMICOLON  */
#line 293 "1805031.y"
                {
			logGrammer("expression_statement : expression SEMICOLON");
		}
#line 1702 "y.tab.c"
    break;

  case 39: /* variable: ID  */
#line 299 "1805031.y"
                {
			logGrammer("variable : ID");
		}
#line 1710 "y.tab.c"
    break;

  case 40: /* variable: ID LTHIRD expression RTHIRD  */
#line 303 "1805031.y"
                {
			logGrammer("variable : ID LTHIRD expression RTHIRD");
		}
#line 1718 "y.tab.c"
    break;

  case 41: /* expression: logic_expression  */
#line 309 "1805031.y"
                {
			logGrammer("expression : logic_expression");
		}
#line 1726 "y.tab.c"
    break;

  case 42: /* expression: variable ASSIGNOP logic_expression  */
#line 313 "1805031.y"
                {
			logGrammer("expression : variable ASSIGNOP logic_expression");
		}
#line 1734 "y.tab.c"
    break;

  case 43: /* logic_expression: rel_expression  */
#line 319 "1805031.y"
                {
			logGrammer("logic_expression : rel_expression");
		}
#line 1742 "y.tab.c"
    break;

  case 44: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 323 "1805031.y"
                {
			logGrammer("logic_expression : rel_expression LOGICOP rel_expression");
		}
#line 1750 "y.tab.c"
    break;

  case 45: /* rel_expression: simple_expression  */
#line 329 "1805031.y"
                {
			logGrammer("rel_expression	: simple_expression");
		}
#line 1758 "y.tab.c"
    break;

  case 46: /* rel_expression: simple_expression RELOP simple_expression  */
#line 333 "1805031.y"
                {
			logGrammer("rel_expression	: simple_expression RELOP simple_expression");
		}
#line 1766 "y.tab.c"
    break;

  case 47: /* simple_expression: term  */
#line 339 "1805031.y"
                {
			logGrammer("simple_expression : term");
		}
#line 1774 "y.tab.c"
    break;

  case 48: /* simple_expression: simple_expression ADDOP term  */
#line 343 "1805031.y"
                {
			logGrammer("simple_expression : simple_expression ADDOP term");
		}
#line 1782 "y.tab.c"
    break;

  case 49: /* term: unary_expression  */
#line 349 "1805031.y"
                {
			logGrammer("term :	unary_expression");
		}
#line 1790 "y.tab.c"
    break;

  case 50: /* term: term MULOP unary_expression  */
#line 353 "1805031.y"
                {
			logGrammer("term :	term MULOP unary_expression");
		}
#line 1798 "y.tab.c"
    break;

  case 51: /* unary_expression: ADDOP unary_expression  */
#line 359 "1805031.y"
                {
			logGrammer("unary_expression : ADDOP unary_expression");
		}
#line 1806 "y.tab.c"
    break;

  case 52: /* unary_expression: NOT unary_expression  */
#line 363 "1805031.y"
                {
			logGrammer("unary_expression : NOT unary_expression");
		}
#line 1814 "y.tab.c"
    break;

  case 53: /* unary_expression: factor  */
#line 367 "1805031.y"
                {
			logGrammer("unary_expression : factor");
		}
#line 1822 "y.tab.c"
    break;

  case 54: /* factor: variable  */
#line 373 "1805031.y"
                {
			logGrammer("factor : variable");
		}
#line 1830 "y.tab.c"
    break;

  case 55: /* factor: ID LPAREN argument_list RPAREN  */
#line 377 "1805031.y"
                {
			logGrammer("factor : ID LPAREN argument_list RPAREN");
		}
#line 1838 "y.tab.c"
    break;

  case 56: /* factor: LPAREN expression RPAREN  */
#line 381 "1805031.y"
                {
			logGrammer("factor : LPAREN expression RPAREN");
		}
#line 1846 "y.tab.c"
    break;

  case 57: /* factor: CONST_INT  */
#line 385 "1805031.y"
                {
			logGrammer("factor : CONST_INT");
		}
#line 1854 "y.tab.c"
    break;

  case 58: /* factor: CONST_FLOAT  */
#line 389 "1805031.y"
                {
			logGrammer("factor : CONST_FLOAT");
		}
#line 1862 "y.tab.c"
    break;

  case 59: /* factor: variable INCOP  */
#line 393 "1805031.y"
                {
			logGrammer("factor : variable INCOP");
		}
#line 1870 "y.tab.c"
    break;

  case 60: /* factor: variable DECOP  */
#line 397 "1805031.y"
                {
			logGrammer("factor : variable DECOP");
		}
#line 1878 "y.tab.c"
    break;

  case 61: /* argument_list: arguments  */
#line 403 "1805031.y"
                {
			logGrammer("argument_list : arguments");
		}
#line 1886 "y.tab.c"
    break;

  case 62: /* argument_list: %empty  */
#line 407 "1805031.y"
                {
			logGrammer("argument_list : empty");
		}
#line 1894 "y.tab.c"
    break;

  case 63: /* arguments: arguments COMMA logic_expression  */
#line 413 "1805031.y"
                {
			logGrammer("arguments : arguments COMMA logic_expression");
		}
#line 1902 "y.tab.c"
    break;

  case 64: /* arguments: logic_expression  */
#line 417 "1805031.y"
                {
			logGrammer("arguments : logic_expression");
		}
#line 1910 "y.tab.c"
    break;


#line 1914 "y.tab.c"

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

#line 423 "1805031.y"


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
