%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
//#include<sym_tab.h>
#define YYDEBUG 1	//enable debugging

install(char* sym_name)
{
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
%token UMINUS
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

%left GE LE EQ NE '<' '>'
%left '+' '-'
%left '*' '/'
%right UMINUS

%nonassoc UMINUS

%%

expr:
	| expr '+' term {$$=$1+$3;}

%%
int main()
{
	yyparse();
	return 0;
}
