
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
#include<string.h>
#include<math.h>
#include "ll_sym_table.h"		// definitions of the symbol table
#include "st_stack.h"			// sym_tab stack
#include "my_defines.h"
#include "node_def.h"
#include "helper_functions.h"
#include "y.tab.h"
#include "ir_code.h"
#include "type_checkers.h"



extern struct sym_record sym_table;
extern yyline_no;
extern int yylex();
extern char* yytext;
extern int yywrap();
extern int yycolumn;
extern int yyleng;

/*prototypes start*/

void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name);
int generate(nodeType *n);

//char* newlabel();
//char* newtmp();
//char* concat(char* c1,char* c2);
//void dist_type(nodeType* nptr);
//nodeType* get_operand(nodeType* opnode,int index);




/*prototypes end*/

/*global variables*/

struct symbol_table* current_st=NULL;	// global current st 
int seen_func=0;
int seen_class=0;
char *CODE;
char buffer[BUFFSIZE];
int labelno = 1;
int tempno = 1;
int idno = 1;
FILE* output;			// output file
char* out_file;
nodeType* root;
/*global variables*/



/* Line 189 of yacc.c  */
#line 134 "y.tab.c"

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
     TYPE_BOOL = 327,
     TYPE_VOID = 328,
     RETURN = 329,
     DEF = 330,
     PUBLIC = 331,
     PRIVATE = 332,
     PROTECTED = 333,
     LT = 334,
     GT = 335,
     LE = 336,
     GE = 337,
     TRUE = 338,
     FALSE = 339,
     IDENT = 340,
     ARRAY = 341,
     ELLIPSIS = 342,
     ASSERT = 343,
     EQ = 344,
     PLUS_EQ = 345,
     MULT_EQ = 346,
     MINUS_EQ = 347,
     DIV_EQ = 348,
     PP = 349,
     MM = 350,
     IFX = 351,
     MINUS = 352,
     PLUS = 353,
     DIV = 354,
     MULT = 355,
     NEG = 356,
     POW = 357
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
#define TYPE_BOOL 327
#define TYPE_VOID 328
#define RETURN 329
#define DEF 330
#define PUBLIC 331
#define PRIVATE 332
#define PROTECTED 333
#define LT 334
#define GT 335
#define LE 336
#define GE 337
#define TRUE 338
#define FALSE 339
#define IDENT 340
#define ARRAY 341
#define ELLIPSIS 342
#define ASSERT 343
#define EQ 344
#define PLUS_EQ 345
#define MULT_EQ 346
#define MINUS_EQ 347
#define DIV_EQ 348
#define PP 349
#define MM 350
#define IFX 351
#define MINUS 352
#define PLUS 353
#define DIV 354
#define MULT 355
#define NEG 356
#define POW 357




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 61 "parser.y"

	int iVal;
	float fVal;
	char cVal;
	char* str;
	struct sym_record *sPtr; // pointer to position in sym_table
	union nodeTypeTag *nPtr;	 // node pointer



/* Line 214 of yacc.c  */
#line 385 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 397 "y.tab.c"

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
#define YYLAST   334

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  113
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNRULES -- Number of states.  */
#define YYNSTATES  227

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      88,    89,     2,     2,   111,     2,   112,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    92,    85,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    90,     2,    91,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,     2,    87,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    13,    20,    22,
      24,    26,    27,    32,    35,    37,    38,    48,    50,    52,
      53,    57,    59,    60,    65,    67,    70,    72,    74,    76,
      78,    80,    82,    84,    86,    88,    91,    94,    97,   101,
     107,   112,   116,   117,   118,   124,   127,   129,   132,   134,
     138,   141,   147,   155,   161,   167,   177,   183,   185,   187,
     189,   191,   193,   195,   200,   202,   204,   206,   208,   210,
     212,   216,   218,   220,   224,   226,   228,   230,   232,   234,
     236,   240,   242,   244,   248,   250,   256,   258,   262,   264,
     268,   270,   274,   276,   280,   282,   286,   288,   292,   296,
     298,   302,   306,   310,   314,   316,   320,   324,   326,   330,
     334,   336,   340,   344,   346,   348,   351,   354,   357,   359,
     364,   369,   373,   377,   380,   383,   385,   389,   391
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     114,     0,    -1,    -1,   115,   116,    -1,   116,   117,    -1,
     117,    -1,    -1,   119,    18,    93,   118,   120,    85,    -1,
      76,    -1,    77,    -1,    78,    -1,    -1,    86,   121,   122,
      87,    -1,   122,   123,    -1,   123,    -1,    -1,    75,    93,
     124,    88,   126,    89,    92,   125,   135,    -1,   147,    -1,
     127,    -1,    -1,   127,   111,   128,    -1,   128,    -1,    -1,
      93,   129,    92,   147,    -1,   131,    -1,   130,   131,    -1,
     139,    -1,   141,    -1,   142,    -1,   140,    -1,   135,    -1,
     134,    -1,   138,    -1,   133,    -1,   132,    -1,    60,    85,
      -1,    61,    85,    -1,    74,    85,    -1,    74,   151,    85,
      -1,     7,    86,   166,    85,    87,    -1,    64,   150,    92,
     131,    -1,    65,    92,   131,    -1,    -1,    -1,    86,   136,
     130,   137,    87,    -1,     1,    87,    -1,   146,    -1,   151,
      85,    -1,    85,    -1,   151,     1,    85,    -1,     1,    85,
      -1,    54,    88,   151,    89,   131,    -1,    54,    88,   151,
      89,   131,    56,   131,    -1,    63,    88,   151,    89,   131,
      -1,    59,    88,   151,    89,   131,    -1,    57,    88,   151,
      85,   151,    85,   151,    89,   131,    -1,    34,   144,    88,
     151,    89,    -1,    93,    -1,    97,    -1,    98,    -1,   100,
      -1,    99,    -1,   101,    -1,     4,   148,    92,   147,    -1,
      69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,
      93,    -1,   148,   111,    93,    -1,    93,    -1,   150,    -1,
      88,   151,    89,    -1,    66,    -1,    67,    -1,    68,    -1,
      83,    -1,    84,    -1,   152,    -1,   151,   111,   152,    -1,
     143,    -1,   153,    -1,   165,   145,   152,    -1,   154,    -1,
     154,    41,   151,    92,   153,    -1,   155,    -1,   154,    13,
     155,    -1,   156,    -1,   155,    14,   156,    -1,   157,    -1,
     156,    16,   157,    -1,   158,    -1,   157,    53,   158,    -1,
     159,    -1,   158,    15,   159,    -1,   160,    -1,   159,    12,
     160,    -1,   159,    33,   160,    -1,   161,    -1,   160,    79,
     161,    -1,   160,    80,   161,    -1,   160,    81,   161,    -1,
     160,    82,   161,    -1,   162,    -1,   161,    31,   162,    -1,
     161,    42,   162,    -1,   163,    -1,   162,   106,   163,    -1,
     162,   105,   163,    -1,   164,    -1,   163,   108,   164,    -1,
     163,   107,   164,    -1,   165,    -1,   166,    -1,   102,   165,
      -1,   103,   165,    -1,   168,   164,    -1,   149,    -1,   166,
      90,   151,    91,    -1,   166,    88,   167,    89,    -1,   166,
      88,    89,    -1,   166,   112,    93,    -1,   166,   102,    -1,
     166,   103,    -1,   153,    -1,   167,   111,   153,    -1,   106,
      -1,   105,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   192,   216,   217,   221,   220,   238,   239,
     240,   243,   243,   251,   252,   256,   256,   273,   276,   277,
     280,   281,   284,   284,   298,   299,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   315,   316,   317,   318,   322,
     325,   326,   331,   343,   330,   348,   350,   353,   354,   355,
     356,   359,   360,   361,   364,   368,   371,   374,   378,   379,
     380,   381,   382,   385,   388,   389,   390,   391,   392,   395,
     396,   403,   408,   409,   412,   413,   414,   415,   416,   420,
     421,   422,   426,   427,   438,   439,   443,   444,   448,   449,
     453,   454,   458,   459,   463,   464,   468,   469,   470,   474,
     475,   476,   477,   478,   482,   483,   484,   488,   489,   490,
     494,   495,   496,   500,   504,   505,   506,   507,   510,   511,
     512,   513,   514,   515,   516,   520,   521,   524,   525
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
  "FLOAT", "CHAR", "TYPE_INT", "TYPE_FLOAT", "TYPE_CHAR", "TYPE_BOOL",
  "TYPE_VOID", "RETURN", "DEF", "PUBLIC", "PRIVATE", "PROTECTED", "LT",
  "GT", "LE", "GE", "TRUE", "FALSE", "';'", "'{'", "'}'", "'('", "')'",
  "'['", "']'", "':'", "IDENT", "ARRAY", "ELLIPSIS", "ASSERT", "EQ",
  "PLUS_EQ", "MULT_EQ", "MINUS_EQ", "DIV_EQ", "PP", "MM", "IFX", "MINUS",
  "PLUS", "DIV", "MULT", "NEG", "POW", "','", "'.'", "$accept",
  "Defn_or_Decln", "$@1", "ClassDeclnList", "ClassDecln", "$@2", "Mods",
  "ClassBody", "$@3", "FuncDefnList", "FuncDefn", "$@4", "ReturnType",
  "FormalArgLIST", "FormalArgList", "FormalArg", "$@5", "StmtList", "Stmt",
  "JumpStmt", "AsyncStmt", "LabeledStmt", "CompoundStmt", "$@6", "$@7",
  "NonFuncDeclaration", "ExpressionStmt", "SelectionStmt", "IterationStmt",
  "BasicForStmt", "ObjCreation", "TypeName", "AssOp", "VarDec", "Type",
  "IdList", "primary_Expression", "ConstExp", "Expression",
  "assignment_Expression", "conditional_Expression",
  "logical_or_Expression", "logical_and_Expression",
  "inclusive_or_Expression", "exclusive_or_Expression", "and_Expression",
  "equality_Expression", "relational_Expression", "shift_Expression",
  "additive_Expression", "multiplicative_Expression", "cast_Expression",
  "unary_Expression", "postfix_Expression", "ArgExpList", "unary_operator", 0
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
     335,   336,   337,   338,   339,    59,   123,   125,    40,    41,
      91,    93,    58,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,    44,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   113,   115,   114,   116,   116,   118,   117,   119,   119,
     119,   121,   120,   122,   122,   124,   123,   125,   126,   126,
     127,   127,   129,   128,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   133,
     134,   134,   136,   137,   135,   135,   138,   139,   139,   139,
     139,   140,   140,   140,   141,   142,   143,   144,   145,   145,
     145,   145,   145,   146,   147,   147,   147,   147,   147,   148,
     148,   149,   149,   149,   150,   150,   150,   150,   150,   151,
     151,   151,   152,   152,   153,   153,   154,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   159,   160,
     160,   160,   160,   160,   161,   161,   161,   162,   162,   162,
     163,   163,   163,   164,   165,   165,   165,   165,   166,   166,
     166,   166,   166,   166,   166,   167,   167,   168,   168
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     0,     6,     1,     1,
       1,     0,     4,     2,     1,     0,     9,     1,     1,     0,
       3,     1,     0,     4,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     3,     5,
       4,     3,     0,     0,     5,     2,     1,     2,     1,     3,
       2,     5,     7,     5,     5,     9,     5,     1,     1,     1,
       1,     1,     1,     4,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     3,     1,     5,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     1,     2,     2,     2,     1,     4,
       4,     3,     3,     2,     2,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     8,     9,    10,     3,     5,     0,
       4,     0,     6,     0,    11,     0,     0,     7,     0,     0,
      14,    15,    12,    13,     0,    19,    22,     0,    18,    21,
       0,     0,     0,     0,     0,    20,    64,    65,    66,    67,
      68,    23,     0,    17,     0,    42,    16,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,    75,    76,     0,    77,    78,    48,     0,    71,
       0,     0,   128,   127,     0,    24,    34,    33,    31,    30,
      32,    26,    29,    27,    28,    81,    46,   118,    72,     0,
      79,    82,    84,    86,    88,    90,    92,    94,    96,    99,
     104,   107,   110,   113,   114,     0,    50,    69,     0,     0,
      57,     0,     0,     0,     0,    35,    36,     0,     0,     0,
      37,     0,     0,   115,   116,    25,     0,     0,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    59,
      61,    60,    62,     0,     0,     0,   123,   124,     0,   117,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    38,    73,    44,    49,    80,    87,     0,    89,    91,
      93,    95,    97,    98,   100,   101,   102,   103,   105,   106,
     109,   108,   112,   111,    83,   121,   125,     0,     0,   122,
      63,    70,     0,     0,     0,     0,     0,     0,    40,     0,
     120,     0,   119,    39,    56,    51,     0,    54,    53,    85,
     126,     0,     0,    52,     0,     0,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    13,     9,    15,    16,    19,
      20,    24,    42,    27,    28,    29,    30,    74,    75,    76,
      77,    78,    79,    48,   126,    80,    81,    82,    83,    84,
      85,   111,   153,    86,    41,   108,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   197,   105
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -149
static const yytype_int16 yypact[] =
{
    -149,    21,   -49,  -149,  -149,  -149,  -149,   -49,  -149,    41,
    -149,   -70,  -149,   -24,  -149,   -60,   -10,  -149,    37,   -61,
    -149,  -149,  -149,  -149,    17,    39,  -149,    36,    26,  -149,
      65,    68,    39,    73,    73,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,     4,  -149,    66,  -149,  -149,  -149,   176,    35,
      71,    92,    86,    93,    94,    96,   118,   121,   123,   130,
     117,  -149,  -149,  -149,   187,  -149,  -149,  -149,   217,  -149,
     228,   228,  -149,  -149,   102,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,     2,
    -149,  -149,    -2,   198,   199,   163,   202,    77,   112,   -18,
      22,    32,  -149,    74,     5,   228,  -149,  -149,    24,   -51,
    -149,   131,   217,   217,   217,  -149,  -149,   217,   126,   176,
    -149,   -55,   -77,  -149,  -149,  -149,   133,   137,  -149,   228,
     228,   217,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,  -149,  -149,
    -149,  -149,  -149,   228,   -48,   217,  -149,  -149,   132,  -149,
    -149,    73,   134,     9,   217,   -67,   -47,   -42,   -23,   176,
    -149,  -149,  -149,  -149,  -149,  -149,   198,    27,   199,   163,
     202,    77,   112,   112,   -18,   -18,   -18,   -18,    22,    22,
      32,    32,  -149,  -149,  -149,  -149,  -149,    12,     7,  -149,
    -149,  -149,   136,    13,   176,   217,   176,   176,  -149,   228,
    -149,   228,  -149,  -149,  -149,   168,   -25,  -149,  -149,  -149,
    -149,   176,   217,  -149,    15,   176,  -149
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -149,  -149,  -149,  -149,   219,  -149,  -149,  -149,  -149,  -149,
     209,  -149,  -149,  -149,  -149,   197,  -149,  -149,   -73,  -149,
    -149,  -149,   189,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,   -32,  -149,  -149,   173,   -64,  -122,
    -148,  -149,   104,   106,   113,   111,   114,   -22,    61,     8,
      10,   -95,   -62,   138,  -149,  -149
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -44
static const yytype_int16 yytable[] =
{
     121,   125,    43,   127,   122,    44,   196,   175,   123,   124,
     159,   130,   172,   142,    18,    61,    62,    63,    61,    62,
      63,     3,   204,    12,   143,    17,    22,     4,     5,     6,
     171,   194,    65,    66,   129,    65,    66,    68,   205,   131,
      68,   195,    69,   160,   129,    69,   170,   206,   165,   166,
     167,   192,   193,   168,    70,    71,   129,    72,    73,    11,
     222,   219,    14,   220,   129,    18,   207,   177,   160,   129,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   129,   128,   129,   136,
      45,   198,   160,   154,   202,   155,   208,   154,   212,   155,
     203,   210,   214,    49,   225,    25,    50,   156,   157,    51,
     137,   156,   157,   129,   182,   183,   161,   158,   129,   209,
     106,   158,    47,   211,   129,    31,   129,   144,   145,   200,
      21,   215,    26,   217,   218,   162,    52,    32,   129,   146,
     147,   216,    36,    37,    38,    39,    40,   160,   223,   160,
     188,   189,   226,    47,   190,   191,    53,    33,   224,    54,
      34,    55,    56,    57,   107,    58,    59,    60,    61,    62,
      63,   148,   149,   150,   151,   152,    64,    49,   109,   110,
      50,   112,   113,    51,   114,    65,    66,    67,    45,   -43,
      68,   138,   139,   140,   141,    69,    61,    62,    63,   184,
     185,   186,   187,   115,    70,    71,   116,    72,    73,   119,
      52,   117,   132,    65,    66,   133,   134,   135,   169,   164,
     173,    52,   174,   213,   221,   199,    10,   201,    23,    35,
      53,    46,   118,    54,   176,    55,    56,    57,   178,    58,
      59,    60,    61,    62,    63,   180,   179,   163,     0,   181,
      64,    52,     0,    61,    62,    63,     0,     0,     0,    65,
      66,    67,    45,     0,    68,     0,     0,     0,     0,    69,
      65,    66,   120,     0,     0,    68,     0,     0,    70,    71,
      69,    72,    73,    61,    62,    63,     0,     0,     0,    70,
      71,     0,    72,    73,    61,    62,    63,     0,     0,     0,
      65,    66,     0,     0,     0,    68,     0,     0,     0,     0,
      69,    65,    66,     0,     0,     0,    68,     0,     0,    70,
      71,    69,    72,    73,     0,     0,     0,     0,     0,     0,
      70,    71,     0,    72,    73
};

static const yytype_int16 yycheck[] =
{
      64,    74,    34,     1,    68,     1,   154,   129,    70,    71,
     105,    13,    89,    31,    75,    66,    67,    68,    66,    67,
      68,     0,    89,    93,    42,    85,    87,    76,    77,    78,
      85,   153,    83,    84,   111,    83,    84,    88,    85,    41,
      88,    89,    93,   105,   111,    93,   119,    89,   112,   113,
     114,   146,   147,   117,   102,   103,   111,   105,   106,    18,
      85,   209,    86,   211,   111,    75,    89,   131,   130,   111,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   111,    85,   111,    12,
      86,   155,   154,    88,    85,    90,   169,    88,    91,    90,
     164,    89,    89,     1,    89,    88,     4,   102,   103,     7,
      33,   102,   103,   111,   136,   137,    92,   112,   111,    92,
      85,   112,    87,   111,   111,    89,   111,   105,   106,   161,
      93,   204,    93,   206,   207,   111,    34,   111,   111,   107,
     108,   205,    69,    70,    71,    72,    73,   209,   221,   211,
     142,   143,   225,    87,   144,   145,    54,    92,   222,    57,
      92,    59,    60,    61,    93,    63,    64,    65,    66,    67,
      68,    97,    98,    99,   100,   101,    74,     1,    86,    93,
       4,    88,    88,     7,    88,    83,    84,    85,    86,    87,
      88,    79,    80,    81,    82,    93,    66,    67,    68,   138,
     139,   140,   141,    85,   102,   103,    85,   105,   106,    92,
      34,    88,    14,    83,    84,    16,    53,    15,    92,    88,
      87,    34,    85,    87,    56,    93,     7,    93,    19,    32,
      54,    42,    59,    57,   130,    59,    60,    61,   132,    63,
      64,    65,    66,    67,    68,   134,   133,   109,    -1,   135,
      74,    34,    -1,    66,    67,    68,    -1,    -1,    -1,    83,
      84,    85,    86,    -1,    88,    -1,    -1,    -1,    -1,    93,
      83,    84,    85,    -1,    -1,    88,    -1,    -1,   102,   103,
      93,   105,   106,    66,    67,    68,    -1,    -1,    -1,   102,
     103,    -1,   105,   106,    66,    67,    68,    -1,    -1,    -1,
      83,    84,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      93,    83,    84,    -1,    -1,    -1,    88,    -1,    -1,   102,
     103,    93,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,   106
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   114,   115,     0,    76,    77,    78,   116,   117,   119,
     117,    18,    93,   118,    86,   120,   121,    85,    75,   122,
     123,    93,    87,   123,   124,    88,    93,   126,   127,   128,
     129,    89,   111,    92,    92,   128,    69,    70,    71,    72,
      73,   147,   125,   147,     1,    86,   135,    87,   136,     1,
       4,     7,    34,    54,    57,    59,    60,    61,    63,    64,
      65,    66,    67,    68,    74,    83,    84,    85,    88,    93,
     102,   103,   105,   106,   130,   131,   132,   133,   134,   135,
     138,   139,   140,   141,   142,   143,   146,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   168,    85,    93,   148,    86,
      93,   144,    88,    88,    88,    85,    85,    88,   150,    92,
      85,   151,   151,   165,   165,   131,   137,     1,    85,   111,
      13,    41,    14,    16,    53,    15,    12,    33,    79,    80,
      81,    82,    31,    42,   105,   106,   107,   108,    97,    98,
      99,   100,   101,   145,    88,    90,   102,   103,   112,   164,
     165,    92,   111,   166,    88,   151,   151,   151,   151,    92,
     131,    85,    89,    87,    85,   152,   155,   151,   156,   157,
     158,   159,   160,   160,   161,   161,   161,   161,   162,   162,
     163,   163,   164,   164,   152,    89,   153,   167,   151,    93,
     147,    93,    85,   151,    89,    85,    89,    89,   131,    92,
      89,   111,    91,    87,    89,   131,   151,   131,   131,   153,
     153,    56,    85,   131,   151,    89,   131
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
#line 192 "parser.y"
    {
			print_header();
			if(current_st==NULL)
			{
				printf("first sym table created\n");
				current_st=new_sym_table(current_st);
				install("println");
				//printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			}	
		}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    {
				(yyval.nPtr)=(yyvsp[(2) - (2)].nPtr);
				print_st(current_st);
				printf("Starting traversal:\n");
				root = (yyval.nPtr);
				//traverse($$);
				generate((yyval.nPtr));
				//printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				//printf("FINAL CODE:\n");
				//printf("%s\n",$$->opr.code);
			}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    {(yyval.nPtr)=opr(CLASSLIST,2,(yyvsp[(1) - (2)].nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    {
				printf("%s\n",yytext);
				struct sym_record* s=install(yytext);
				(yyvsp[(3) - (3)].nPtr) = id(s);
				st_push(current_st);
				current_st=new_sym_table(current_st);
				current_st->owner_name=strdup(yytext);
				s->my_st=current_st;
				seen_class=1;

				}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    {
				(yyval.nPtr)=opr(CLASS,3,(yyvsp[(1) - (6)].nPtr),(yyvsp[(3) - (6)].nPtr),(yyvsp[(5) - (6)].nPtr));
		}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 238 "parser.y"
    {(yyval.nPtr)=con_i(modPUBLIC);}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 239 "parser.y"
    {(yyval.nPtr)=con_i(modPRIVATE);}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 240 "parser.y"
    {(yyval.nPtr)=con_i(modPROTECTED);}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    {seen_class = 0;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    {
														(yyval.nPtr)=(yyvsp[(3) - (4)].nPtr);
														print_st(current_st);
														current_st=st_pop();
														}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    {(yyval.nPtr) = opr(FUNC_DEF_LIST,2,(yyvsp[(1) - (2)].nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 256 "parser.y"
    {
					printf("%s\n",yytext);
					struct sym_record* s=install(yytext);
					s->is_proc_name=1;
					(yyvsp[(2) - (2)].nPtr) = id(s);
					st_push(current_st);
					current_st=new_sym_table(current_st);
					current_st->owner_name=strdup(yytext);
					s->my_st=current_st;
					seen_func=1;
				}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    { 												   
														(yyval.nPtr)=opr(FUNC,4,(yyvsp[(2) - (9)].nPtr),(yyvsp[(5) - (9)].nPtr),(yyvsp[(8) - (9)].nPtr),(yyvsp[(9) - (9)].nPtr));										insert_signature((yyvsp[(2) - (9)].nPtr),(yyvsp[(5) - (9)].nPtr),(yyvsp[(8) - (9)].nPtr));
														}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 276 "parser.y"
    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 277 "parser.y"
    {(yyval.nPtr)= empty(EMPTY);/*empty production*/}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 280 "parser.y"
    {(yyval.nPtr)=opr(FORMAL_ARG_LIST,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 281 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    {
				struct sym_record* s = install(yytext);
				(yyvsp[(1) - (1)].nPtr) = id(s);
			}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 289 "parser.y"
    {
				(yyval.nPtr)=opr(FORMAL_ARG,2,(yyvsp[(1) - (4)].nPtr),(yyvsp[(4) - (4)].nPtr));
				 
				(yyvsp[(1) - (4)].nPtr)->id.symrec->type = (yyvsp[(4) - (4)].nPtr)->con_i.value;
			}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 299 "parser.y"
    {(yyval.nPtr)=opr(STMT_LIST,2,(yyvsp[(1) - (2)].nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 303 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 304 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 305 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 307 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 309 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 311 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    {(yyval.nPtr)=opr(CONTINUE,0);}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 316 "parser.y"
    {(yyval.nPtr)=opr(BREAK,0);}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {printf("In Return \n");(yyval.nPtr)=opr(RETURN,0);}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 318 "parser.y"
    {(yyval.nPtr)=opr(RETURN,1,(yyvsp[(2) - (3)].nPtr));}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 322 "parser.y"
    {(yyval.nPtr)=opr(ASYNCH,2,(yyvsp[(3) - (5)].nPtr));}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    {(yyval.nPtr)=opr(CASE,2,(yyvsp[(2) - (4)].nPtr),(yyvsp[(4) - (4)].nPtr));}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 326 "parser.y"
    {(yyval.nPtr)=opr(CASE,1,(yyvsp[(3) - (3)].nPtr));}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {	
			if(seen_func==1)	// sym_table already made 
				seen_func=0;
			else if(seen_class==1)
				seen_class=0;
			else	
			{
				st_push(current_st);
				current_st=new_sym_table(current_st);
			}	
		}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 343 "parser.y"
    {	
			print_st(current_st);
			current_st=st_pop();
		}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 347 "parser.y"
    {(yyval.nPtr)=opr(COMPOUND,1,(yyvsp[(3) - (5)].nPtr));}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 348 "parser.y"
    {yyerror("error in compound stmt");}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 350 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (2)].nPtr);}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 354 "parser.y"
    {(yyval.nPtr)=empty(EMPTY);}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 355 "parser.y"
    {yyerror("error in exp stmt");}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 356 "parser.y"
    {yyerror("error in empty stmt");}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 359 "parser.y"
    {(yyval.nPtr)=opr(IF,2,(yyvsp[(3) - (5)].nPtr),(yyvsp[(5) - (5)].nPtr));}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    {(yyval.nPtr)=opr(IF_ELSE,3,(yyvsp[(3) - (7)].nPtr),(yyvsp[(5) - (7)].nPtr),(yyvsp[(7) - (7)].nPtr));}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 361 "parser.y"
    {(yyval.nPtr)=opr(SWITCH,2,(yyvsp[(3) - (5)].nPtr),(yyvsp[(5) - (5)].nPtr));}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 364 "parser.y"
    {(yyval.nPtr) = opr(WHILE, 2, (yyvsp[(3) - (5)].nPtr), (yyvsp[(5) - (5)].nPtr));}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    {(yyval.nPtr)=opr(FOR,4,(yyvsp[(3) - (9)].nPtr),(yyvsp[(5) - (9)].nPtr),(yyvsp[(7) - (9)].nPtr),(yyvsp[(9) - (9)].nPtr));}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    {(yyval.nPtr)=opr(NEW,2,(yyvsp[(2) - (5)].nPtr),(yyvsp[(4) - (5)].nPtr));}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 374 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    {(yyval.nPtr)=con_i(EQ);}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    {(yyval.nPtr)=con_i(PLUS_EQ);}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    {(yyval.nPtr)=con_i(MINUS_EQ);}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 381 "parser.y"
    {(yyval.nPtr)=con_i(MULT_EQ);}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 382 "parser.y"
    {(yyval.nPtr)=con_i(DIV_EQ);}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 385 "parser.y"
    {(yyval.nPtr)=opr(VAR_DEC,2,(yyvsp[(2) - (4)].nPtr),(yyvsp[(4) - (4)].nPtr));dist_type((yyval.nPtr));}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 388 "parser.y"
    {(yyval.nPtr)=con_i(MY_INT);}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 389 "parser.y"
    {(yyval.nPtr)=con_i(MY_FLOAT);}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 390 "parser.y"
    {(yyval.nPtr)=con_i(MY_CHAR);}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 391 "parser.y"
    {(yyval.nPtr)=con_i(MY_BOOL);}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 392 "parser.y"
    {(yyval.nPtr)=con_i(MY_VOID);}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 395 "parser.y"
    {struct sym_record* s=install(yytext);(yyval.nPtr)=id(s);}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 396 "parser.y"
    {
				struct sym_record* s=install(yytext);
				(yyvsp[(3) - (3)].nPtr) = id(s);
				(yyval.nPtr)=opr(ID_LIST,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));
				}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 403 "parser.y"
    {
						struct sym_record*s =search(current_st,yytext);
						printf("s is NULL is true = %d\n",s==NULL);					
						(yyval.nPtr)=id(s);
				}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 408 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 409 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 412 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));printf("INTEGERSSSSSSSSs %d\n",(yyvsp[(1) - (1)].iVal));}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 413 "parser.y"
    {(yyval.nPtr)=con_f((yyvsp[(1) - (1)].fVal));printf("FLOATSSSSSSSSSs %lf\n",(yyvsp[(1) - (1)].fVal));}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 414 "parser.y"
    {(yyval.nPtr)=con_c((yyvsp[(1) - (1)].cVal));}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 415 "parser.y"
    {(yyval.nPtr)=con_b(1);}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 416 "parser.y"
    {(yyval.nPtr)=con_b(0);}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 421 "parser.y"
    {(yyval.nPtr)=opr(EXP_LIST,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 426 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 427 "parser.y"
    {
													(yyval.nPtr)=opr(ASSIGN,3,(yyvsp[(1) - (3)].nPtr),(yyvsp[(2) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)) ;
													type_check_assign((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));
													printf("MAKING ASSIGN NODE:\n");
													printf("Unary Exp name:%s\n",(yyvsp[(1) - (3)].nPtr)->id.symrec->sym_name);
													printf("Assop Type:%d\n",(yyvsp[(2) - (3)].nPtr)->type);
													printf("Assignment Exp value:%d type:%d \n",(yyvsp[(3) - (3)].nPtr)->con_i.value,(yyvsp[(3) - (3)].nPtr)->type);
													}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 438 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 439 "parser.y"
    {(yyval.nPtr)=opr(TERNARY,3,(yyvsp[(1) - (5)].nPtr),(yyvsp[(3) - (5)].nPtr),(yyvsp[(5) - (5)].nPtr));}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 443 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 444 "parser.y"
    {(yyval.nPtr)=opr(BOOL_OR,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_bool((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 448 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 449 "parser.y"
    {(yyval.nPtr)=opr(BOOL_AND,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_bool((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 453 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 454 "parser.y"
    {(yyval.nPtr)=opr(BIT_OR,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_int((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 459 "parser.y"
    {(yyval.nPtr)=opr(XOR,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_int((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 463 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    {(yyval.nPtr)=opr(BIT_AND,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_int((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 468 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 469 "parser.y"
    {(yyval.nPtr)=opr(BOOL_EQ,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_assign((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 470 "parser.y"
    {(yyval.nPtr)=opr(NEQ,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_assign((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 474 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    {(yyval.nPtr)=opr(LT,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_rel((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 476 "parser.y"
    {(yyval.nPtr)=opr(GT,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_rel((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 477 "parser.y"
    {(yyval.nPtr)=opr(LE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_rel((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 478 "parser.y"
    {(yyval.nPtr)=opr(GE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_rel((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 482 "parser.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 483 "parser.y"
    {(yyval.nPtr)=opr(LSH,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_shift((yyval.nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 484 "parser.y"
    {(yyval.nPtr)=opr(RSH,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_shift((yyval.nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 488 "parser.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 489 "parser.y"
    {(yyval.nPtr)=opr(PLUS,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_addmult((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 490 "parser.y"
    {(yyval.nPtr)=opr(MINUS,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_addmult((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 494 "parser.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 495 "parser.y"
    {(yyval.nPtr)=opr(MULT,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_addmult((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 496 "parser.y"
    {(yyval.nPtr)=opr(DIV,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));type_check_division((yyval.nPtr),(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 504 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 505 "parser.y"
    {(yyval.nPtr)=opr(PREFIX,2,con_i((yyvsp[(1) - (2)].iVal)),(yyvsp[(2) - (2)].nPtr));type_check_prepostfix((yyval.nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 506 "parser.y"
    {(yyval.nPtr)=opr(PREFIX,2,con_i((yyvsp[(1) - (2)].iVal)),(yyvsp[(2) - (2)].nPtr));type_check_prepostfix((yyval.nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 507 "parser.y"
    {(yyval.nPtr)=opr(CAST,2,(yyvsp[(1) - (2)].nPtr),(yyvsp[(2) - (2)].nPtr));}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 510 "parser.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 511 "parser.y"
    {type_check_typeid((yyvsp[(1) - (4)].nPtr));}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 512 "parser.y"
    {(yyval.nPtr)=opr(INVOC,2,(yyvsp[(1) - (4)].nPtr),(yyvsp[(3) - (4)].nPtr));type_check_invoc((yyval.nPtr),(yyvsp[(1) - (4)].nPtr),(yyvsp[(3) - (4)].nPtr));}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 513 "parser.y"
    {(yyval.nPtr)=opr(INVOC,2,(yyvsp[(1) - (3)].nPtr),empty(EMPTY));}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 515 "parser.y"
    {(yyval.nPtr)=opr(POSTFIX,2,(yyvsp[(1) - (2)].nPtr),con_i((yyvsp[(2) - (2)].iVal)));type_check_prepostfix((yyval.nPtr),(yyvsp[(1) - (2)].nPtr));}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 516 "parser.y"
    {(yyval.nPtr)=opr(POSTFIX,2,(yyvsp[(1) - (2)].nPtr),con_i((yyvsp[(2) - (2)].iVal)));type_check_prepostfix((yyval.nPtr),(yyvsp[(1) - (2)].nPtr));}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 520 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 521 "parser.y"
    {(yyval.nPtr)=opr(ARGEXPLIST,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr));}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 524 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 525 "parser.y"
    {(yyval.nPtr)=con_i((yyvsp[(1) - (1)].iVal));}
    break;



/* Line 1455 of yacc.c  */
#line 2800 "y.tab.c"
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
#line 529 "parser.y"

int main(int argc, char** argv)
{
	if(argc > 0)
	{
		out_file=strdup(argv[1]);		// filename without extension
		output=fopen(strcat(argv[1],".il"),"w");		// create il file
	}
	yyparse();
	fclose(output);
	return 0;
}


void yyerror (char *s) /* Called by yyparse on error */
{
	printf ("%d:%d:error:%s at %s  \n",yyline_no,yycolumn-yyleng,s,yytext);
}







	


