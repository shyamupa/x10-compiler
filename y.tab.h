
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

/* Line 1676 of yacc.c  */
#line 47 "parser.y"

	int iVal;
	float fVal;
	char cVal;
	char* str;
	struct sym_record *sPtr; // pointer to position in sym_table
	union nodeTypeTag *nPtr;	 // node pointer



/* Line 1676 of yacc.c  */
#line 265 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


