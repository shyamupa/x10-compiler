
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<stdarg.h>	// for variable arguments
#include "ll_sym_table.h"	// definitions of the symbol table
#include "st_stack.h"
#include "node_def.h"
#include"y.tab.h"
#define INVOC 1337
#define FOR_STMT 1338
#define ASSIGN 1339
#define ARGS 1340
#define CLOSURE 1341
#define IDLIST 1342
#define FUN 1343
#define COMMA 1344
#define TYPE 1345
#define YYDEBUG 1	//enable debugging

extern struct sym_record sym_table;
extern yylineno;
extern int yylex();
extern char* yytext;
extern int yywrap();
typedef union nodeTypeTag nodeType;	
/*prototypes start*/
nodeType* id(struct sym_record* i);	// node creator function for identifiers
nodeType* con_i(int value); // node creator function for constants integer
nodeType* con_f(float value); // node creator function for constants floats
nodeType* con_c(char value); // node creator function for constants character
nodeType* opr(int oper, int nops, ...);
void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name);
void dist_type(nodeType* nptr);
nodeType* get_operand(nodeType* opnode,int index);
int type_check_assign(nodeType* lhs, nodeType* rhs);
/*prototypes end*/
/*global variables*/
struct symbol_table* current_st=NULL;	// global current st 
int seen_func=0;
/*global variables*/


/* Line 189 of yacc.c  */
#line 120 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VAL = 258,
     VAR = 259,
     ABSTRACT = 260,
     AS = 261,
     ASYNC = 262,
     AT = 263,
     ATHOME = 264,
     ATEACH = 265,
     ATOMIC = 266,
     BOOL_EQ = 267,
     BOOL_OR = 268,
     BOOL_AND = 269,
     BIT_AND = 270,
     BIT_OR = 271,
     CATCH = 272,
     CLASS = 273,
     CLOCKED = 274,
     EXTENDS = 275,
     FINAL = 276,
     FINALLY = 277,
     FINISH = 278,
     GOTO = 279,
     HASZERO = 280,
     HERE = 281,
     IMPLEMENTS = 282,
     IMPORT = 283,
     INSTANCEOF = 284,
     INTERFACE = 285,
     LSH = 286,
     NATIVE = 287,
     NEQ = 288,
     NEW = 289,
     MY_NULL = 290,
     OFFER = 291,
     OFFERS = 292,
     OPERATOR = 293,
     PACKAGE = 294,
     PROPERTY = 295,
     QM = 296,
     RSH = 297,
     SELF = 298,
     STATIC = 299,
     STRUCT = 300,
     SUPER = 301,
     THIS = 302,
     THROW = 303,
     TRANSIENT = 304,
     TRY = 305,
     VOID = 306,
     WHEN = 307,
     XOR = 308,
     IF = 309,
     THEN = 310,
     ELSE = 311,
     FOR = 312,
     IN = 313,
     WHILE = 314,
     CONTINUE = 315,
     BREAK = 316,
     DO = 317,
     SWITCH = 318,
     CASE = 319,
     DEFAULT = 320,
     INTEGER = 321,
     FLOAT = 322,
     CHAR = 323,
     TYPE_INT = 324,
     TYPE_FLOAT = 325,
     TYPE_CHAR = 326,
     RETURN = 327,
     DEF = 328,
     PUBLIC = 329,
     PRIVATE = 330,
     PROTECTED = 331,
     BEQ = 332,
     LT = 333,
     GT = 334,
     LE = 335,
     GE = 336,
     TRUE = 337,
     FALSE = 338,
     IDENT = 339,
     ARRAY = 340,
     ELLIPSIS = 341,
     ASSERT = 342,
     EQ = 343,
     PLUS_EQ = 344,
     MULT_EQ = 345,
     MINUS_EQ = 346,
     DIV_EQ = 347,
     PP = 348,
     MM = 349,
     IFX = 350,
     MINUS = 351,
     PLUS = 352,
     DIV = 353,
     MULT = 354,
     NEG = 355,
     POW = 356
   };
#endif
/* Tokens.  */
#define VAL 258
#define VAR 259
#define ABSTRACT 260
#define AS 261
#define ASYNC 262
#define AT 263
#define ATHOME 264
#define ATEACH 265
#define ATOMIC 266
#define BOOL_EQ 267
#define BOOL_OR 268
#define BOOL_AND 269
#define BIT_AND 270
#define BIT_OR 271
#define CATCH 272
#define CLASS 273
#define CLOCKED 274
#define EXTENDS 275
#define FINAL 276
#define FINALLY 277
#define FINISH 278
#define GOTO 279
#define HASZERO 280
#define HERE 281
#define IMPLEMENTS 282
#define IMPORT 283
#define INSTANCEOF 284
#define INTERFACE 285
#define LSH 286
#define NATIVE 287
#define NEQ 288
#define NEW 289
#define MY_NULL 290
#define OFFER 291
#define OFFERS 292
#define OPERATOR 293
#define PACKAGE 294
#define PROPERTY 295
#define QM 296
#define RSH 297
#define SELF 298
#define STATIC 299
#define STRUCT 300
#define SUPER 301
#define THIS 302
#define THROW 303
#define TRANSIENT 304
#define TRY 305
#define VOID 306
#define WHEN 307
#define XOR 308
#define IF 309
#define THEN 310
#define ELSE 311
#define FOR 312
#define IN 313
#define WHILE 314
#define CONTINUE 315
#define BREAK 316
#define DO 317
#define SWITCH 318
#define CASE 319
#define DEFAULT 320
#define INTEGER 321
#define FLOAT 322
#define CHAR 323
#define TYPE_INT 324
#define TYPE_FLOAT 325
#define TYPE_CHAR 326
#define RETURN 327
#define DEF 328
#define PUBLIC 329
#define PRIVATE 330
#define PROTECTED 331
#define BEQ 332
#define LT 333
#define GT 334
#define LE 335
#define GE 336
#define TRUE 337
#define FALSE 338
#define IDENT 339
#define ARRAY 340
#define ELLIPSIS 341
#define ASSERT 342
#define EQ 343
#define PLUS_EQ 344
#define MULT_EQ 345
#define MINUS_EQ 346
#define DIV_EQ 347
#define PP 348
#define MM 349
#define IFX 350
#define MINUS 351
#define PLUS 352
#define DIV 353
#define MULT 354
#define NEG 355
#define POW 356




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 47 "parser.y"

	int iVal;
	float fVal;
	char cVal;
	char* str;
	struct sym_record *sPtr; // pointer to position in sym_table
	union nodeTypeTag *nPtr;	 // node pointer



/* Line 214 of yacc.c  */
#line 369 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 381 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   307

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNRULES -- Number of states.  */
#define YYNSTATES  233

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   356

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      87,    88,     2,     2,   110,     2,   111,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    91,    84,
       2,   112,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    89,     2,    90,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,    86,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    13,    21,    25,
      27,    29,    30,    32,    35,    37,    39,    41,    43,    45,
      47,    49,    54,    58,    59,    60,    66,    69,    71,    73,
      75,    78,    80,    84,    87,    93,   101,   107,   113,   123,
     129,   131,   133,   135,   137,   139,   141,   146,   148,   153,
     155,   157,   159,   163,   165,   167,   171,   173,   175,   177,
     179,   183,   185,   187,   189,   193,   195,   201,   203,   207,
     209,   213,   215,   219,   221,   225,   227,   231,   233,   237,
     241,   243,   247,   251,   255,   259,   261,   265,   269,   271,
     275,   279,   281,   285,   289,   291,   293,   296,   299,   302,
     304,   309,   313,   316,   319,   321,   323,   330,   332,   334,
     336,   342,   346,   347,   349,   353,   356,   360,   362,   366,
     368,   372,   374,   377,   379,   385,   388,   391,   393,   395
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     114,     0,    -1,    -1,   115,   116,    -1,   116,   117,    -1,
     117,    -1,    -1,    73,    92,   118,    87,   119,    88,   124,
      -1,   119,   110,   120,    -1,   120,    -1,   137,    -1,    -1,
     122,    -1,   121,   122,    -1,   128,    -1,   130,    -1,   131,
      -1,   129,    -1,   124,    -1,   123,    -1,   127,    -1,    64,
     141,    91,   122,    -1,    65,    91,   122,    -1,    -1,    -1,
      85,   125,   121,   126,    86,    -1,     1,    86,    -1,   137,
      -1,   159,    -1,   161,    -1,   142,    84,    -1,    84,    -1,
     142,     1,    84,    -1,     1,    84,    -1,    54,    87,   142,
      88,   122,    -1,    54,    87,   142,    88,   122,    56,   122,
      -1,    63,    87,   142,    88,   122,    -1,    59,    87,   142,
      88,   122,    -1,    57,    87,   142,    84,   142,    84,   142,
      88,   122,    -1,    34,   133,    87,   142,    88,    -1,    92,
      -1,    96,    -1,    97,    -1,    99,    -1,    98,    -1,   100,
      -1,   136,    87,   142,    88,    -1,    92,    -1,     4,   139,
      91,   138,    -1,    69,    -1,    70,    -1,    92,    -1,   139,
     110,    92,    -1,    92,    -1,   141,    -1,    87,   142,    88,
      -1,    66,    -1,    67,    -1,    68,    -1,   143,    -1,   142,
     110,   143,    -1,   132,    -1,   135,    -1,   144,    -1,   156,
     134,   143,    -1,   145,    -1,   145,    41,   142,    91,   144,
      -1,   146,    -1,   145,    13,   146,    -1,   147,    -1,   146,
      14,   147,    -1,   148,    -1,   147,    16,   148,    -1,   149,
      -1,   148,    53,   149,    -1,   150,    -1,   149,    15,   150,
      -1,   151,    -1,   150,    12,   151,    -1,   150,    33,   151,
      -1,   152,    -1,   151,    78,   152,    -1,   151,    79,   152,
      -1,   151,    80,   152,    -1,   151,    81,   152,    -1,   153,
      -1,   152,    31,   153,    -1,   152,    42,   153,    -1,   154,
      -1,   153,   105,   154,    -1,   153,   104,   154,    -1,   155,
      -1,   154,   107,   155,    -1,   154,   106,   155,    -1,   156,
      -1,   157,    -1,   101,   156,    -1,   102,   156,    -1,   158,
     155,    -1,   140,    -1,   157,    89,   142,    90,    -1,   157,
     111,    92,    -1,   157,   101,    -1,   157,   102,    -1,   105,
      -1,   104,    -1,   160,    18,    92,   162,   167,    84,    -1,
      74,    -1,    75,    -1,    76,    -1,    45,    92,   162,   167,
      84,    -1,    89,   163,    90,    -1,    -1,    92,    -1,   163,
     110,    92,    -1,   163,   110,    -1,    89,   165,    90,    -1,
     166,    -1,   165,   110,   166,    -1,    92,    -1,    85,   168,
      86,    -1,   169,    -1,   168,   169,    -1,   170,    -1,    73,
      47,   164,   171,   172,    -1,    91,   138,    -1,   112,   173,
      -1,   173,    -1,    84,    -1,    85,   121,    86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   183,   183,   183,   194,   195,   198,   198,   214,   215,
     218,   219,   222,   223,   227,   228,   229,   230,   231,   232,
     233,   237,   238,   243,   253,   242,   258,   260,   261,   262,
     265,   266,   267,   268,   271,   272,   273,   276,   280,   283,
     286,   290,   291,   292,   293,   294,   297,   300,   307,   310,
     311,   314,   315,   320,   325,   326,   329,   330,   331,   334,
     335,   336,   337,   341,   342,   353,   354,   358,   359,   363,
     364,   368,   369,   373,   374,   378,   379,   383,   384,   385,
     389,   390,   391,   392,   393,   397,   398,   399,   403,   404,
     405,   409,   410,   411,   415,   419,   420,   421,   422,   425,
     426,   427,   428,   429,   432,   433,   437,   444,   445,   446,
     448,   450,   451,   453,   454,   455,   457,   459,   460,   462,
     464,   466,   467,   469,   471,   473,   475,   476,   477,   479
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAL", "VAR", "ABSTRACT", "AS", "ASYNC",
  "AT", "ATHOME", "ATEACH", "ATOMIC", "BOOL_EQ", "BOOL_OR", "BOOL_AND",
  "BIT_AND", "BIT_OR", "CATCH", "CLASS", "CLOCKED", "EXTENDS", "FINAL",
  "FINALLY", "FINISH", "GOTO", "HASZERO", "HERE", "IMPLEMENTS", "IMPORT",
  "INSTANCEOF", "INTERFACE", "LSH", "NATIVE", "NEQ", "NEW", "MY_NULL",
  "OFFER", "OFFERS", "OPERATOR", "PACKAGE", "PROPERTY", "QM", "RSH",
  "SELF", "STATIC", "STRUCT", "SUPER", "THIS", "THROW", "TRANSIENT", "TRY",
  "VOID", "WHEN", "XOR", "IF", "THEN", "ELSE", "FOR", "IN", "WHILE",
  "CONTINUE", "BREAK", "DO", "SWITCH", "CASE", "DEFAULT", "INTEGER",
  "FLOAT", "CHAR", "TYPE_INT", "TYPE_FLOAT", "TYPE_CHAR", "RETURN", "DEF",
  "PUBLIC", "PRIVATE", "PROTECTED", "BEQ", "LT", "GT", "LE", "GE", "TRUE",
  "FALSE", "';'", "'{'", "'}'", "'('", "')'", "'['", "']'", "':'", "IDENT",
  "ARRAY", "ELLIPSIS", "ASSERT", "EQ", "PLUS_EQ", "MULT_EQ", "MINUS_EQ",
  "DIV_EQ", "PP", "MM", "IFX", "MINUS", "PLUS", "DIV", "MULT", "NEG",
  "POW", "','", "'.'", "'='", "$accept", "Defn_or_Decln", "$@1",
  "FuncDefnList", "FuncDefn", "$@2", "FormalArgList", "FormalArg",
  "StmtList", "Stmt", "LabeledStmt", "CompoundStmt", "$@3", "$@4",
  "NonFuncDeclaration", "ExpressionStmt", "SelectionStmt", "IterationStmt",
  "BasicForStmt", "ObjCreation", "TypeName", "AssOp", "MethodInv",
  "MethodName", "VarDec", "Type", "IdList", "primary_Expression",
  "ConstExp", "Expression", "assignment_Expression",
  "conditional_Expression", "logical_or_Expression",
  "logical_and_Expression", "inclusive_or_Expression",
  "exclusive_or_Expression", "and_Expression", "equality_Expression",
  "relational_Expression", "shift_Expression", "additive_Expression",
  "multiplicative_Expression", "cast_Expression", "unary_Expression",
  "postfix_Expression", "unary_operator", "ClassDecln", "Mods",
  "StructDecln", "TypeParamsI", "TypeParamIList", "TypeParams",
  "TypeParamList", "TypeParam", "ClassBody", "ClassMemberDeclns",
  "ClassMemberDecln", "CtorDecln", "HasResultType", "CtorBody",
  "CtorBlock", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,    59,   123,   125,    40,    41,    91,
      93,    58,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
      44,    46,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   113,   115,   114,   116,   116,   118,   117,   119,   119,
     120,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   125,   126,   124,   124,   127,   127,   127,
     128,   128,   128,   128,   129,   129,   129,   130,   131,   132,
     133,   134,   134,   134,   134,   134,   135,   136,   137,   138,
     138,   139,   139,   140,   140,   140,   141,   141,   141,   142,
     142,   142,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150,   150,
     151,   151,   151,   151,   151,   152,   152,   152,   153,   153,
     153,   154,   154,   154,   155,   156,   156,   156,   156,   157,
     157,   157,   157,   157,   158,   158,   159,   160,   160,   160,
     161,   162,   162,   163,   163,   163,   164,   165,   165,   166,
     167,   168,   168,   169,   170,   171,   172,   172,   172,   173
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     0,     7,     3,     1,
       1,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     0,     0,     5,     2,     1,     1,     1,
       2,     1,     3,     2,     5,     7,     5,     5,     9,     5,
       1,     1,     1,     1,     1,     1,     4,     1,     4,     1,
       1,     1,     3,     1,     1,     3,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     1,     2,     2,     2,     1,
       4,     3,     2,     2,     1,     1,     6,     1,     1,     1,
       5,     3,     0,     1,     3,     2,     3,     1,     3,     1,
       3,     1,     2,     1,     5,     2,     2,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     5,     6,     4,     0,
      11,     0,     0,     9,    10,    51,     0,     0,    11,     0,
       0,     0,    23,     7,     8,    49,    50,    48,    52,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    57,    58,   107,   108,   109,    31,     0,    53,     0,
       0,   105,   104,     0,    12,    19,    18,    20,    14,    17,
      15,    16,    61,    62,     0,    27,    99,    54,     0,    59,
      63,    65,    67,    69,    71,    73,    75,    77,    80,    85,
      88,    91,    94,    95,     0,    28,     0,    29,    33,    40,
       0,   112,     0,     0,     0,     0,     0,     0,     0,    53,
      96,    97,    13,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    42,    44,    43,
      45,     0,     0,   102,   103,     0,    98,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    55,    25,
       0,    32,    60,    68,     0,    70,    72,    74,    76,    78,
      79,    81,    82,    83,    84,    86,    87,    90,    89,    93,
      92,    64,     0,   101,   112,     0,   113,     0,     0,     0,
       0,     0,     0,     0,    21,    46,     0,   100,     0,    39,
     111,   115,     0,     0,   121,   123,   110,    34,     0,    37,
      36,    66,     0,   114,     0,   120,   122,     0,     0,   106,
       0,     0,    35,     0,   119,     0,   117,     0,     0,     0,
     116,     0,   125,   128,     0,     0,   124,   127,    38,   118,
       0,   126,   129
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,     9,    12,    13,    53,    54,
      55,    56,    30,   103,    57,    58,    59,    60,    61,    62,
      90,   131,    63,    64,    65,    27,    16,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   141,
     177,   211,   215,   216,   179,   193,   194,   195,   218,   226,
     227
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -98
static const yytype_int16 yypact[] =
{
     -98,    22,   -16,   -98,   -63,   -16,   -98,   -98,   -98,   -21,
      56,    -1,   -67,   -98,   -98,   -98,     8,     3,    56,   -44,
      17,    27,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     202,   -28,    23,    43,    55,    59,    60,    63,    58,    64,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   196,    69,   -50,
     -50,   -98,   -98,    94,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,    77,   -98,   -98,   -98,     0,   -98,
     -98,   -10,   151,   157,   114,   159,    20,    42,   -12,    33,
      34,   -98,     5,   -78,   -50,   -98,   158,   -98,   -98,   -98,
      88,    95,   196,   196,   196,   196,    92,   202,   -48,   -98,
     -98,   -98,   -98,    99,   196,   103,   -98,   -50,   -50,   196,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -98,   -98,   -98,   -98,
     -98,   -50,   196,   -98,   -98,    96,   -98,   -98,    97,   196,
      98,   106,   -27,   -72,   -25,    -2,   202,   -98,   -98,   -98,
       1,   -98,   -98,   151,     9,   157,   114,   159,    20,    42,
      42,   -12,   -12,   -12,   -12,    33,    33,    34,    34,   -98,
     -98,   -98,   -75,   -98,    95,     2,   -98,     6,   119,   110,
     202,   196,   202,   202,   -98,   -98,   -50,   -98,   106,   -98,
     -98,   105,   153,   -59,   -98,   -98,   -98,   145,   -71,   -98,
     -98,   -98,   120,   -98,   121,   -98,   -98,   202,   196,   -98,
     116,   118,   -98,     4,   -98,     7,   -98,   -44,   -76,   202,
     -98,   116,   -98,   -98,   202,   132,   -98,   -98,   -98,   -98,
     148,   -98,   -98
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -98,   -98,   -98,   -98,   213,   -98,   -98,   201,    -4,   -53,
     -98,   204,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,    10,    11,   -98,   -98,   187,   -45,
     -97,    40,   -98,   123,   117,   126,   127,   125,    -8,    15,
      24,    49,   -79,   -43,   -98,   -98,   -98,   -98,   -98,    67,
     -98,   -98,   -98,    21,    41,   -98,    50,   -98,   -98,   -98,
      19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const yytype_int16 yytable[] =
{
     102,   105,    98,   108,    21,   136,   100,   101,   223,   224,
     152,   132,   181,   208,   192,   187,    40,    41,    42,   120,
      14,    17,     3,   133,   134,    25,    26,   205,    14,     7,
     121,   109,   114,   135,   171,   107,   225,    47,   107,   107,
     148,   137,    99,    18,   147,   169,   170,   142,   143,   144,
     145,    49,    50,   115,    51,    52,    88,     4,    29,   150,
      11,   180,   107,   182,   154,   137,    10,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   107,   106,   107,   183,   172,    22,   185,
     189,    15,   219,   184,   175,    31,   190,   220,    11,    19,
     186,   126,   127,   128,   129,   130,   159,   160,   107,    28,
     107,   107,   107,    29,   107,    89,   191,   221,    20,   107,
     116,   117,   118,   119,    40,    41,    42,   197,    32,   199,
     200,   161,   162,   163,   164,    91,   198,   122,   123,    33,
     124,   125,    92,   137,   165,   166,    93,    94,    34,    31,
      95,    35,    11,    36,   212,    97,   -47,    37,    38,    39,
      40,    41,    42,   213,   104,   110,   228,   112,    43,    44,
      45,   167,   168,   111,   113,   139,   138,   102,    46,    22,
     -24,    47,    32,   146,   140,   149,    48,   151,   173,   174,
     176,   178,   192,    33,   196,    49,    50,   203,    51,    52,
     204,   207,    34,    31,   209,    35,    11,    36,   214,   217,
     210,    37,    38,    39,    40,    41,    42,   224,     8,    24,
     230,    23,    43,    44,    45,    96,   201,   155,   222,   202,
      32,   153,    46,    22,   232,    47,    32,   156,   158,   157,
      48,   188,   229,   206,   231,     0,     0,    33,     0,    49,
      50,     0,    51,    52,     0,     0,    34,     0,     0,    35,
       0,    36,    40,    41,    42,    37,    38,    39,    40,    41,
      42,     0,     0,     0,     0,     0,    43,    44,    45,     0,
       0,     0,     0,    47,     0,     0,    46,    22,    48,    47,
       0,     0,     0,     0,    48,     0,     0,    49,    50,     0,
      51,    52,     0,    49,    50,     0,    51,    52
};

static const yytype_int16 yycheck[] =
{
      53,     1,    47,    13,     1,    84,    49,    50,    84,    85,
     107,    89,    84,    84,    73,    90,    66,    67,    68,    31,
      10,    88,     0,   101,   102,    69,    70,    86,    18,    92,
      42,    41,    12,   111,   131,   110,   112,    87,   110,   110,
      88,    84,    92,   110,    97,   124,   125,    92,    93,    94,
      95,   101,   102,    33,   104,   105,    84,    73,    86,   104,
       4,    88,   110,    88,   109,   108,    87,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   110,    84,   110,    88,   132,    85,    88,
      88,    92,    88,   146,   139,     1,    90,    90,     4,    91,
      91,    96,    97,    98,    99,   100,   114,   115,   110,    92,
     110,   110,   110,    86,   110,    92,   110,   110,   110,   110,
      78,    79,    80,    81,    66,    67,    68,   180,    34,   182,
     183,   116,   117,   118,   119,    92,   181,   104,   105,    45,
     106,   107,    87,   186,   120,   121,    87,    87,    54,     1,
      87,    57,     4,    59,   207,    91,    87,    63,    64,    65,
      66,    67,    68,   208,    87,    14,   219,    53,    74,    75,
      76,   122,   123,    16,    15,    87,    18,   230,    84,    85,
      86,    87,    34,    91,    89,    86,    92,    84,    92,    92,
      92,    85,    73,    45,    84,   101,   102,    92,   104,   105,
      47,    56,    54,     1,    84,    57,     4,    59,    92,    91,
      89,    63,    64,    65,    66,    67,    68,    85,     5,    18,
     224,    17,    74,    75,    76,    38,   186,   110,   217,   188,
      34,   108,    84,    85,    86,    87,    34,   111,   113,   112,
      92,   174,   221,   193,   225,    -1,    -1,    45,    -1,   101,
     102,    -1,   104,   105,    -1,    -1,    54,    -1,    -1,    57,
      -1,    59,    66,    67,    68,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    87,    -1,    -1,    84,    85,    92,    87,
      -1,    -1,    -1,    -1,    92,    -1,    -1,   101,   102,    -1,
     104,   105,    -1,   101,   102,    -1,   104,   105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   114,   115,     0,    73,   116,   117,    92,   117,   118,
      87,     4,   119,   120,   137,    92,   139,    88,   110,    91,
     110,     1,    85,   124,   120,    69,    70,   138,    92,    86,
     125,     1,    34,    45,    54,    57,    59,    63,    64,    65,
      66,    67,    68,    74,    75,    76,    84,    87,    92,   101,
     102,   104,   105,   121,   122,   123,   124,   127,   128,   129,
     130,   131,   132,   135,   136,   137,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,    84,    92,
     133,    92,    87,    87,    87,    87,   141,    91,   142,    92,
     156,   156,   122,   126,    87,     1,    84,   110,    13,    41,
      14,    16,    53,    15,    12,    33,    78,    79,    80,    81,
      31,    42,   104,   105,   106,   107,    96,    97,    98,    99,
     100,   134,    89,   101,   102,   111,   155,   156,    18,    87,
      89,   162,   142,   142,   142,   142,    91,   122,    88,    86,
     142,    84,   143,   146,   142,   147,   148,   149,   150,   151,
     151,   152,   152,   152,   152,   153,   153,   154,   154,   155,
     155,   143,   142,    92,    92,   142,    92,   163,    85,   167,
      88,    84,    88,    88,   122,    88,    91,    90,   162,    88,
      90,   110,    73,   168,   169,   170,    84,   122,   142,   122,
     122,   144,   167,    92,    47,    86,   169,    56,    84,    84,
      89,   164,   122,   142,    92,   165,   166,    91,   171,    88,
      90,   110,   138,    84,    85,   112,   172,   173,   122,   166,
     121,   173,    86
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {
			if(current_st==NULL)
			{
				printf("first sym table created\n");
				current_st=new_sym_table(current_st);
				printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			}	
		}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (2)].nPtr);print_st(current_st);}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 198 "parser.y"
    {
				// make ident point to the new sym tab
				printf("%s\n",yytext);
				struct sym_record* s=install(yytext);
				s->is_proc_name=1;
				st_push(current_st);
				current_st=new_sym_table(current_st);
				//printf("%d",current_st);
				//printf("%d",s->proc_st);
				s->proc_st=current_st;
				seen_func=1;

			}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    {(yyval.nPtr)=opr(FUN,3,(yyvsp[(2) - (7)].nPtr),(yyvsp[(5) - (7)].nPtr),(yyvsp[(7) - (7)].nPtr));}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    {(yyval.nPtr)=opr(COMMA,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 215 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 218 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr); /*THIS IS INCOMPLETE*/}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 219 "parser.y"
    {(yyval.nPtr)=NULL;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 222 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 223 "parser.y"
    {(yyval.nPtr)=opr(';',2,(yyvsp[(1) - (2)].nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 227 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 230 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 231 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 232 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    {(yyval.nPtr)=opr(CASE,2,(yyvsp[(2) - (4)].nPtr),(yyvsp[(4) - (4)].nPtr));}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 238 "parser.y"
    {(yyval.nPtr)=opr(CASE,1,(yyvsp[(3) - (3)].nPtr));}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    {	
			if(seen_func==1)	// sym_table already made 
				seen_func=0;
			else	
			{
				st_push(current_st);
				current_st=new_sym_table(current_st);
			}	
		}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    {	
			print_st(current_st);
			current_st=st_pop();
		}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 257 "parser.y"
    {(yyval.nPtr)=(yyvsp[(3) - (5)].nPtr);}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {yyerror("error in compound stmt\n");}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 260 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 261 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 262 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 265 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (2)].nPtr);}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 266 "parser.y"
    {(yyval.nPtr)=NULL;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    {yyerror("error in exp stmt\n");}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 268 "parser.y"
    {yyerror("error in empty stmt");}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {(yyval.nPtr)=opr(IF,2,(yyvsp[(3) - (5)].nPtr),(yyvsp[(5) - (5)].nPtr));}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 272 "parser.y"
    {(yyval.nPtr)=opr(IF,3,(yyvsp[(3) - (7)].nPtr),(yyvsp[(5) - (7)].nPtr),(yyvsp[(7) - (7)].nPtr));}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    {(yyval.nPtr)=opr(SWITCH,2,(yyvsp[(3) - (5)].nPtr),(yyvsp[(5) - (5)].nPtr));}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 276 "parser.y"
    { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[(3) - (5)].nPtr), (yyvsp[(5) - (5)].nPtr));}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 280 "parser.y"
    {(yyval.nPtr)=opr(FOR,4,(yyvsp[(3) - (9)].nPtr),(yyvsp[(5) - (9)].nPtr),(yyvsp[(7) - (9)].nPtr),(yyvsp[(9) - (9)].nPtr));}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    {(yyval.nPtr)=opr(NEW,2,(yyvsp[(2) - (5)].nPtr),(yyvsp[(4) - (5)].nPtr));}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 291 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 293 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 294 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 297 "parser.y"
    {(yyval.nPtr)=opr(INVOC,2,(yyvsp[(1) - (4)].nPtr),(yyvsp[(3) - (4)].nPtr));}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 300 "parser.y"
    {	
				/*search and return from st the ptr to method*/
				/*do some type check here*/
		}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 307 "parser.y"
    {(yyval.nPtr)=opr(TYPE,2,(yyvsp[(2) - (4)].nPtr),(yyvsp[(4) - (4)].nPtr));dist_type((yyval.nPtr));/*printf("%d",$$->opr.nops);*/}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    {(yyval.nPtr)=con_i(133);}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 311 "parser.y"
    {(yyval.nPtr)=con_f(134);}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    {struct sym_record* s=install(yytext);(yyval.nPtr)=id(s);}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    {
				struct sym_record* s=install(yytext);(yyval.nPtr)=opr(COMMA,2,(yyvsp[(1) - (3)].nPtr),id(s));
				}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 320 "parser.y"
    {
					printf("adsad%s",yytext);					
					struct sym_record*s =install(yytext);					
					(yyval.nPtr)=id(s);
				}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 326 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 330 "parser.y"
    {(yyval.nPtr)=con_f((yyvsp[(1) - (1)].fVal));}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {(yyval.nPtr)=con_c((yyvsp[(1) - (1)].cVal));}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 341 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 342 "parser.y"
    {
										
									if(type_check_assign((yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr))==0)	
									{
										printf("Error\n");
										exit(0);
									}
								}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {/*$$=$1;*/}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 384 "parser.y"
    {/*$$=opr(BOOL_EQ,2,$1,$3);*/}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (2)].nPtr);}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 421 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (2)].nPtr);}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 422 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (2)].nPtr);}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 437 "parser.y"
    {
									//nodeType* n=id($3);
									//do some type checking here
									(yyval.nPtr)=opr(CLASS,4,(yyvsp[(1) - (6)].nPtr),(yyvsp[(3) - (6)].nPtr),(yyvsp[(4) - (6)].nPtr),(yyvsp[(5) - (6)].nPtr));
								/*here $1 will contain enum type which will be handled by the traversal function*/
								}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 444 "parser.y"
    {(yyval.nPtr)=con_i(modPUBLIC);}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 445 "parser.y"
    {(yyval.nPtr)=con_i(modPRIVATE);}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 446 "parser.y"
    {(yyval.nPtr)=con_i(modPROTECTED);}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 448 "parser.y"
    {(yyval.nPtr)=opr(STRUCT,3,(yyvsp[(2) - (5)].nPtr),(yyvsp[(3) - (5)].nPtr),(yyvsp[(4) - (5)].nPtr));}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 450 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 451 "parser.y"
    {/* empty */}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 453 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 457 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 462 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 471 "parser.y"
    {(yyval.nPtr)=opr(DEF,3,(yyvsp[(3) - (5)].nPtr),(yyvsp[(4) - (5)].nPtr),(yyvsp[(5) - (5)].nPtr));}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 473 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (2)].nPtr);}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (2)].nPtr);	/*for the time being*/}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 477 "parser.y"
    {(yyval.nPtr)=NULL;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 479 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;



/* Line 1455 of yacc.c  */
#line 2433 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 481 "parser.y"

int main()
{
	yyparse();
	return 0;
}


nodeType* con_i(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_iNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConI;
	p->con_i.value=value;
	return p;
}

nodeType* con_f(float value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_fNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConF;
	p->con_f.value=value;
	return p;
}

nodeType* con_c(char value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_cNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConC;
	p->con_c.value=value;
	return p;
}

// Having installed a ident in the symbol table we call id() with its sym_record pointer
// this creates a node for the ident which will be used in the Syntax Tree
nodeType *id(struct sym_record* i)	 
{
	//printf("name is %s\n",i->sym_name);
	nodeType *p;
	if ((p = malloc(sizeof(idNodeType))) == NULL)
		yyerror("out of memory");
	p->type = typeId;
	p->id.i = i;
	return p;
}
nodeType *opr(int oper, int nops, ...) 
{
	va_list ap;
	nodeType *p;
	size_t size;
	int i;
	size = sizeof(oprNodeType) + (nops - 1) * sizeof(nodeType*);
	if ((p = malloc(size)) == NULL)
		yyerror("out of memory");
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
		p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
	return p;
}

struct sym_record* install(char* sym_name)
{
	printf("installing %s\n",sym_name);
	struct sym_record* r;
	int rv=search_keywords(sym_name);
	if(rv==1)
		printf("using reserved keyword\n");
	else
	{
		r=search(current_st,sym_name);
		if(r==NULL)	// sym_name not already in table add it
		{
			r=insert(current_st,sym_name);
			return r;
		}
		else	// oops the name already exists
		{
		// what to do here?? do we check scope or not
		}
	}
}
void yyerror(char*s)  
{
	printf("%s\n",s);
	//printf("%d: %s at %s\n",yylineno,s,yytext);
}

// get_operand takes a nodeType of
//
nodeType* get_operand(nodeType* opnode,int index)
{
	return opnode->opr.op[index];
}
//takes a VarDec node and spread the type info 
void dist_type(nodeType* nptr)
{
	printf("%d\n",nptr->type); // should be typeOp
	printf("%d is the type to be assigned\n",get_operand(nptr,1)->con_i.value);
	int TypeToAssign=get_operand(nptr,1)->con_i.value;
	nodeType* idlist=get_operand(nptr,0);
	if(idlist->type==typeId)
		idlist->id.i->type=TypeToAssign;		
	else
	{
		while(idlist->type!=typeId)
		{
			nodeType* leftnode=get_operand(idlist,0);
			nodeType* rightnode=get_operand(idlist,1);
			rightnode->id.i->type=TypeToAssign;
			idlist=leftnode;
		}
		idlist->id.i->type=TypeToAssign;
	}	
}
int get_type(nodeType* data_type_ptr)
{
	if(data_type_ptr->type==typeConI)
	{
		return data_type_ptr->con_i.type;	// add type fiedl in con node !!!
	}
	else if(data_type_ptr->type==typeConF)
	{
		return data_type_ptr->con_f.type;	// add type fiedl in con node !!!
	}
	else if(data_type_ptr->type==typeConC)
	{
		return data_type_ptr->con_c.type;	// add type fiedl in con node !!!
	}
	else
	{
		return (data_type_ptr->id.i)->type;
	}
}
int type_check_assign(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)!=get_type(rhs))
	{
		return(0);
		//printf("type mismatch\n");
	}
	return(1);
}



