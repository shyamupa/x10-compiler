%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<stdarg.h>	// for variable arguments
#include "ll_sym_table.h"	// definitions of the symbol table
#include "node_def.h"
#include"y.tab.h"
#define YYDEBUG 1	//enable debugging

extern struct sym_record sym_table;
extern yylineno;
extern int yylex();
extern char* yytext;
extern int yywrap();
typedef union nodeTypeTag nodeType;

/*prototypes*/
nodeType* id(struct sym_record* i);	// node creator function for identifiers
nodeType* con(int value); // node creator function for constants
nodeType* opr(int oper, int nops, ...);
void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name,int type);
%}
%union 
{
	int iVal;
	struct sym_record *sPtr; // pointer to position in sym_table
	union nodeTypeTag *nPtr;	 // node pointer
}
%token VAL VAR
%token IF THEN ELSE
%token FOR IN '..' WHILE CONTINUE BREAK DO
%token SWITCH CASE DEFAULT
%token INTEGER FLOAT 
%token RETURN DEF
%token CLASS THIS STRUCT NEW
%token PUBLIC PRIVATE PROTECTED
%token '!=' 
%token ';' '{' '}' '(' ')' '[' ']' ':'
%token IDENT
%token '=' '+=' '-=' '*=' '/=' PP MM
%type <iVal> INTEGER FLOAT IdList Type '=' '+=' '-=' '*=' '/=' Mods
%type <sPtr> IDENT
%type <nPtr> Stmt VarDec Expression ReturnStmt Block BlockStmts BlockInteriorStmt IfStmt WhileStmt BasicForStmt ForInit ForUpdate StmtExpList StmtExp MethodInv ArgList MethodName SwitchStmt SwitchBlock SwitchBlockGroups SwitchBlockGroup SwitchLabels SwitchLabel ConstExp ClassDecln StructDecln TypeParamsI TypeParamIList TypeParams TypeParam TypeParamList ClassBody ClassMemberDeclns ClassMemberDecln CtorDecln HasResultType CtorBody CtorBlock AssOp ObjCreation Assignment LHS PreincrementExp TypeName
%nonassoc IFX
%nonassoc ELSE
%left '+' '-'
%left '*' '/'
%left NEG
%right POW
%start StmtList
%%
StmtList	:Stmt 
		|StmtList ';' Stmt
		;
		
Stmt	:Expression ';'	
	|VarDec ';'	
	|WhileStmt ';'
	|BasicForStmt ';'
	|IfStmt ';'
	|SwitchStmt ';'
	|ReturnStmt ';'
	|Assignment	';'	
	|PreincrementExp ';'	
	|MethodInv ';'
	|ObjCreation ';'
	;

ReturnStmt	: RETURN Expression {$$=opr(RETURN,1,$2);}
		;
Block		:'{' BlockStmts '}'	{$$=$2;}
		;
BlockStmts	:BlockInteriorStmt	
		|BlockStmts BlockInteriorStmt
		;
BlockInteriorStmt	:VarDec	';'
			|Stmt
			;

IfStmt		:IF '(' Expression ')' Stmt %prec IFX	{$$=opr(IF,2,$3,$5);}
		|IF '(' Expression ')' Stmt ELSE Stmt 	{$$=opr(IF,3,$3,$5,$7);}
		;

WhileStmt	:WHILE '(' Expression ')' Stmt		{ $$ = opr(WHILE, 2, $3, $5);}
		;

BasicForStmt	:FOR '(' ForInit ';' Expression ';' ForUpdate ')' Stmt {$$=opr(FOR,4,$3,$5,$7,$9);}
ForInit		:StmtExpList	{/*$$=opr('');*/}
		;
ForUpdate	:StmtExpList	{/*$$=opr();*/}
		;

StmtExpList	:StmtExp
		|StmtExpList ',' StmtExp
		;
StmtExp		:Assignment		
		|PreincrementExp	
		|MethodInv		
		|ObjCreation		
		;
ObjCreation	:NEW TypeName '(' ArgList ')'	{$$=opr(NEW,2,$2,$4);}	
		;
TypeName	:IDENT	{$$=id($1);}
		;
PreincrementExp	:'++' IDENT	{$$=opr(PP,1,$2);}	
Assignment	:LHS AssOp Expression	{$$=opr('=',3,$1,$2,$3);}
		;
LHS		:IDENT	{$$=id($1);}
		;
AssOp		:'='	{con($1);}	
		|'+='	{con($1);}
		|'-='	{con($1);}
		|'*='	{con($1);}
		|'/='	{con($1);}
		;
MethodInv	:MethodName '(' ArgList ')'
		;
ArgList		:Expression
		|ArgList ',' Expression
		;
MethodName	:IDENT	{/*do some type check here*/}
		;
SwitchStmt		:SWITCH '(' Expression ')' SwitchBlock	{$$=opr(SWITCH,2,$3,$5);}
			;
SwitchBlock		:'{' SwitchBlockGroups SwitchLabels '}'	{/*$$=comp($2,$3);*/}
			;
SwitchBlockGroups	:SwitchBlockGroup
			|SwitchBlockGroups SwitchBlockGroup
			;
SwitchBlockGroup	:SwitchLabels BlockStmts
			;
SwitchLabels		:SwitchLabel
			|SwitchLabels SwitchLabel
			;
SwitchLabel		:CASE ConstExp ':'
			|DEFAULT ':'
			;
Expression	:ConstExp			{ $$=$1;}		
		|IDENT				{ $$=id($1);}
	  	| Expression '+' Expression	{ $$=opr('+',2,$1,$3); }
		| Expression '-' Expression	{ $$=opr('-',2,$1,$3); }
		| Expression '*' Expression	{ $$=opr('*',2,$1,$3); }
		| Expression '/' Expression	{ $$=opr('/',2,$1,$3); }
		| Expression POW Expression	{ $$=opr('^',2,$1,$3);}			
		| '-' Expression %prec NEG	{ $$=opr(NEG,1,$2); }
		| '('Expression')'		{ $$=$2; }
		;
ConstExp	:INTEGER	{$$=con($1);}
		|FLOAT		{$$=con($1);}
		;

VarDec	:Type IdList {}
	;
Type	:VAR{$$=133;}	
	|VAL{$$=134;}	
	;
IdList	:IDENT {struct sym_record* s=install(yytext,112); /*printf("type: %d",$0);*/ }
	|IdList ',' IDENT {struct sym_record* s=install(yytext,112);/*printf("type : %d",$0);*/ }
	;
	
ClassDecln 	: Mods CLASS IDENT TypeParamsI ClassBody ';'	{
								nodeType* n=id($3);
								//do some type checking here
								$$=opr(CLASS,4,$1,n,$4,$5);
								/*here $1 will contain enum type which will be handled by the traversal function*/
								}
		;						
Mods		:PUBLIC	{$$=modPUBLIC;}
		|PRIVATE	{$$=modPRIVATE;}
		|PROTECTED	{$$=modPROTECTED;}
		;
StructDecln	:STRUCT IDENT TypeParamsI ClassBody ';' {$$=opr(STRUCT,3,id($2),$3,$4);}
		;	
TypeParamsI 	: '[' TypeParamIList ']' {$$=$2;}
		|	{/* empty */}	
		;
TypeParamIList 	:IDENT	{$$=id($1);}
		| TypeParamIList ',' IDENT	{}
		| TypeParamIList ','
		;		
TypeParams 	: '[' TypeParamList ']'	{$$=$2;}
		;
TypeParamList 	: TypeParam
		| TypeParamList ',' TypeParam				
		;
TypeParam	:IDENT	{$$=id($1);}
		;
ClassBody	: '{' ClassMemberDeclns '}'	{$$=$2;}
		;
ClassMemberDeclns 	: ClassMemberDecln
			| ClassMemberDeclns ClassMemberDecln
			;
ClassMemberDecln 	: CtorDecln
			;
CtorDecln		: DEF THIS TypeParams HasResultType CtorBody	{$$=opr(DEF,3,$3,$4,$5);}
			;
HasResultType 		: ':' Type {$$=$2;}
			;
CtorBody 		: '=' CtorBlock 
			| CtorBlock
			| ';'
			;
CtorBlock 		: '{' BlockStmts '}'	{$$=$2;}
			;
%%
int main()
{
	yyparse();
	return 0;
}
nodeType* con(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(conNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeCon;
	p->con.value=value;
	return p;
}
nodeType *id(struct sym_record* i) 
{
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

struct sym_record* install(char* sym_name,int type)
{
	printf("installing %s\n",sym_name);
	struct sym_record* r;
	r=search(sym_name);
	if(r==NULL)	// sym_name not already in table add it
	{
		r=insert(sym_name);
		r->type = type;
		return r;
	}
	else	// oops the name already exists
	{
		// what to do here?? do we check scope or not
	}
}
void yyerror(char*s)  
{
	printf("%s\n",s);
	//printf("%d: %s at %s\n",yylineno,s,yytext);
}

