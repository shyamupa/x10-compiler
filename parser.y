%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include"ll_sym_table.h"
#include "include.h"
#define YYDEBUG 1	//enable debugging
extern sym_record sym_table;
void yyerror(char*s)  {printf("%s\n",s);}
extern int yylex();
extern char* yytext;

extern int yywrap();
sym_record* install(char* sym_name)
{
	printf("installing#%s#\n",sym_name);
	sym_record* r;
	r=search(sym_name);
	if(r==NULL)	// sym_name not already in table add it
	{
		r=insert(sym_name);
		return r;
	}
	else	// oops the name already exists
	{
		// what to do here?? do we check scope or not
	}
}
%}
%union 
{
	int iVal;
	char* charPtr ;
	//nodeType *nPtr;
}
%token VAL VAR
%token IF 
%token THEN 
%token ELSE
%token FOR
%token IN
%token '..'
%token WHILE
%token CONTINUE
%token BREAK
%token DO
%token SWITCH
%token CASE
%token DEFAULT
%token '!=' 
%token ';''{' '}'
%token '('
%token ')'
%token '['
%token ']'
%token ':'
%token IDENT
%token NUMBER
%type <iVal> NUMBER
%type <charPtr> IDENT
%type <iVal> Stmt Expression VarDec
%left '+' '-'
%left '*' '/'
%left NEG
%right POW
%start Stmt
%%
Stmt	:Expression';' {printf("%d\n",$1);} Stmt	
	|Expression ';'	{printf("%d\n",$1);}
	|VarDec ';'
	;
Expression	:NUMBER				{ $$=$1; }
	  	| Expression '+' Expression	{ $$=$1+$3; }
		| Expression '-' Expression	{ $$=$1-$3; }
		| Expression '*' Expression	{ $$=$1*$3; }
		| Expression '/' Expression	{ $$=$1/$3; }
		| Expression POW Expression	{ $$=pow($1,$3);}			
		| '-' Expression %prec NEG	{ $$=-$2; }
		| '('Expression')'		{ $$=$2; }
		| IDENT	{
				//sym_record* s=search(yytext);
				//printf("@%s@",s->type);
				//$$=71;
			}
		;
VarDec	: Type IDENT {sym_record* s=install(yytext); s->type="Int";} IdList
	;
Type	: VAL 
	| VAR
	;
IdList	: ',' IDENT {sym_record* s=install(yytext); s->type="Int";} IdList
	|
	;
%%
int main()
{
	yyparse();
	return 0;
}
