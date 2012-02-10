%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include"sym_tab.h"
#include "include.h"
#define YYDEBUG 1	//enable debugging

void yyerror(char*s)  {printf("%s\n",s);}
extern int yylex();
extern char* yytext;

extern int yywrap();
install(char* sym_name)
{
	printf("installing#%s#\n",sym_name);
	sym_record* r;
	r=search(sym_name);
	if(r==NULL)	// sym_name not already in table add it
	{
		r=insert(sym_name);
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
%token VAL
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
%token UMINUS
%token ';'
%token '{'
%token '}'
%token '('
%token ')'
%token '['
%token ']'
%token ':'
%token IDENT
%token NUMBER
%type <iVal> NUMBER
%type <charPtr> IDENT
%type <iVal> Stmt E T F
%left '+' '-'
%left '*' '/'

%nonassoc UMINUS
%start Stmt
%%
Stmt	:E ';' {printf("%d\n",$1);} Stmt	
	|E ';'	{printf("%d\n",$1);}
	|VarDec ';'
	|';'
	;
E	:E '+' T 	{$$=$1+$3;/*printf("%d\n",$$)*/;}
	|T 	{$$=$1;/*printf("%d\n",$$)*/;}
	;
T	:T '*' F	{$$=$1*$3;/*printf("%d\n",$$)*/;}
	|F 	{$$=$1;/*printf("%d\n",$$)*/;}
	;
F	:'('E')' 	{$$=$2;printf("%d\n",$$);}
	|NUMBER		{$$=$1;}
	|IDENT 	{/*$$=install(yytext);*/}	
	;

VarDec	: VAL IdList 
	;

IdList	:IDENT ',' IdList {install($1);}
	|IDENT {install($1);}
	;
%%
int main()
{
	yyparse();
	return 0;
}
