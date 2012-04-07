
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 61 "parser.y"

	int iVal;
	float fVal;
	char cVal;
	char* str;
	struct sym_record *sPtr; // pointer to position in sym_table
	union nodeTypeTag *nPtr;	 // node pointer



/* Line 1676 of yacc.c  */
#line 267 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


