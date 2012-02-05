%{
#include<stdio.h>
%}
%token IF 
%token THEN 
%token ELSE
%token FOR
%token IN
%token ELLIPSIS
%token WHILE
%token CONTINUE
%token BREAK
%token DO
%token SWITCH
%token CASE
%token DEFAULT
%token EQ
%token GE
%token GT
%token LE
%token LT
%token PLUS
%token MINUS
%token MULT
%token DIV
%token SEMICOLON
%token LBRACE
%token RBRACE
%token LPAR
%token RPAR
%token LBOX
%token RBOX
%token COLON
%token NUMBER
%%

expr:
	NUMBER	{$$=$1;}
	| expr '+' expr	{$$=$1+$3;}
	| expr '-' expr	{$$=$1-$3;}

%%
int main()
{
	yyparse();
	return 0;
}
