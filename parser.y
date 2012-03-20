%{
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
#define YYDEBUG 1	//enable debugging

struct symbol_table* current_st=NULL;	// global current st 
extern struct sym_record sym_table;
extern yylineno;
extern int yylex();
extern char* yytext;
extern int yywrap();
typedef union nodeTypeTag nodeType;

/*prototypes start*/
nodeType* id(struct sym_record* i);	// node creator function for identifiers
nodeType* con(int value); // node creator function for constants
nodeType* opr(int oper, int nops, ...);
void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name);
/*prototypes end*/
/*global variables*/
/*global variables*/
%}
%union 
{
	int iVal;
	float fVal;
	char cVal;
	char* str;
	struct sym_record *sPtr; // pointer to position in sym_table
	union nodeTypeTag *nPtr;	 // node pointer
}
%token VAL VAR
%token IF THEN ELSE
%token FOR IN WHILE CONTINUE BREAK DO
%token SWITCH CASE DEFAULT
%token INTEGER FLOAT CHAR TYPE_INT TYPE_FLOAT TYPE_CHAR
%token RETURN DEF
%token CLASS THIS STRUCT NEW
%token PUBLIC PRIVATE PROTECTED
%token NEQ BEQ LT GT LE GE TRUE FALSE 
%token ';' '{' '}' '(' ')' '[' ']' ':'
%token IDENT
%token ARRAY ELLIPSIS ASSERT
%token EQ PLUS_EQ MULT_EQ MINUS_EQ  DIV_EQ PP MM
%type <iVal> INTEGER TYPE_INT IdList HasResultType Type EQ PLUS_EQ MULT_EQ MINUS_EQ  DIV_EQ Mods
%type <fVal> FLOAT TYPE_FLOAT
%type <cVal> CHAR TYPE_CHAR
%type <sPtr> IDENT

%type <nPtr> ArgList
%type <nPtr> Assignment
%type <nPtr> AssOp
%type <nPtr> BasicForStmt
%type <nPtr> BoolExpression
%type <nPtr> CompoundStmt 
%type <nPtr> ConstExp 
%type <nPtr> ClassDecln
%type <nPtr> ClassBody 
%type <nPtr> ClassMemberDeclns 
%type <nPtr> ClassMemberDecln 
%type <nPtr> CtorDecln 
%type <nPtr> CtorBody 
%type <nPtr> CtorBlock
%type <nPtr> Declaration
%type <nPtr> Defn_or_Decln
%type <nPtr> Expression
%type <nPtr> ExpressionStmt
%type <nPtr> FuncDefnList 
%type <nPtr> FuncDefn 
%type <nPtr> ForInit 
%type <nPtr> ForUpdate
%type <nPtr> FormalArg
%type <nPtr> IterationStmt
%type <nPtr> LHS
%type <nPtr> LabeledStmt
%type <nPtr> MethodInv  MethodName
%type <nPtr> ObjCreation
%type <nPtr> PreincrementExp
%type <nPtr> PostincrementExp
%type <nPtr> StmtList
%type <nPtr> Stmt 
%type <nPtr> StmtExp 
%type <nPtr> StmtExpList
%type <nPtr> SelectionStmt
%type <nPtr> StructDecln
%type <nPtr> TypeParamsI 
%type <nPtr> TypeParamIList 
%type <nPtr> TypeParams 
%type <nPtr> TypeParam 
%type <nPtr> TypeParamList   
%type <nPtr> TypeName   
%type <nPtr> VarDec   
                   
%nonassoc IFX
%nonassoc ELSE
%left PLUS MINUS
%left MULT DIV
%left NEG
%right POW
%start Defn_or_Decln
%%
Defn_or_Decln	:	{
				if(current_st==NULL)
				{
					printf("first sym table created\n");
					current_st=new_sym_table(current_st);
				}	
			}	
		FuncDefnList
		;
FuncDefnList	: FuncDefnList FuncDefn
		|FuncDefn
		;
FuncDefn	:DEF IDENT 	{
					// make ident point to the new sym tab
					printf("%s\n",yytext);
					
				}
		'(' FormalArgList ')' Stmt 
		;
FormalArgList	:FormalArgList ',' FormalArg
		|FormalArg
		;
FormalArg	:VarDec	{$$=$1; /*THIS IS INCOMPLETE*/}
		|{$$=NULL;}	
		;
StmtList	:	
		Stmt	{$$=$1; print_st(current_st);} 			
		|StmtList Stmt {$$=opr(';',2,$1,$2);}	
		;
		
Stmt	:ExpressionStmt	{$$=$1;}
	|IterationStmt 	{$$=$1;}
	|BasicForStmt 	{$$=$1;}
	|SelectionStmt	{$$=$1;}
	|PreincrementExp{$$=$1;}
	|MethodInv 	{$$=$1;}
	|ObjCreation 	{$$=$1;}
	|CompoundStmt	{$$=$1;}
	|LabeledStmt	{$$=$1;}
	|Declaration	{$$=$1;}
	;

LabeledStmt	:IDENT ':' Stmt		
		|CASE ConstExp ':' Stmt	{$$=opr(CASE,2,$2,$4);}
		|DEFAULT ':' Stmt	{$$=opr(CASE,1,$3);}
		;
		
CompoundStmt	:'{'
			{	
				st_push(current_st);
				current_st=new_sym_table(current_st);
				current_st->parent=st_examine_top();
			}
			
			 StmtList 
			
			{	
				current_st=st_pop();
			}
		'}'
		;
Declaration	:VarDec	{$$=$1;}
		|ClassDecln  {$$=$1;}
		|StructDecln {$$=$1;}
		;
ExpressionStmt	:Expression ';'
		|';'
		;
SelectionStmt	:IF '(' Expression ')' Stmt %prec IFX	{$$=opr(IF,2,$3,$5);}
		|IF '(' Expression ')' Stmt ELSE Stmt	{$$=opr(IF,3,$3,$5,$7);}
		|SWITCH '(' Expression ')' Stmt	{$$=opr(SWITCH,2,$3,$5);}
		;
IterationStmt	:WHILE '(' Expression ')' Stmt	{ $$ = opr(WHILE, 2, $3, $5);}
		;

BasicForStmt	:FOR '(' ForInit ';' Expression ';' ForUpdate ')' Stmt {$$=opr(FOR,4,$3,$5,$7,$9);}
		;
ForInit		:StmtExpList  {$$=$1;}	
		;
ForUpdate	:StmtExpList  {$$=$1;}	
		;
StmtExpList	:StmtExp  {$$=$1;}
		|StmtExpList ',' StmtExp  {$$=opr(FOR_STMT,2,$1,$3);}
		;
StmtExp		:Assignment		{$$=$1;}	
		|PreincrementExp	{$$=$1;}
		|PostincrementExp	{$$=$1;}
		|MethodInv		{$$=$1;}	
		|ObjCreation		{$$=$1;}
		;
ObjCreation	:NEW TypeName '(' ArgList ')'	{$$=opr(NEW,2,$2,$4);}	
		;
TypeName	:IDENT	{$$=id($1);}
		;
PreincrementExp	:PP IDENT	{$$=opr(PP,2,$2,0);}	
		;
PostincrementExp:IDENT PP	{$$=opr(PP,2,$1,1);}		
Assignment	:LHS AssOp Expression	{$$=opr(ASSIGN,3,$1,$2,$3);}
		|LHS EQ	ObjCreation	{$$=$1;}
		;
LHS		:IDENT	{$$=id($1);}
		;
AssOp		:EQ	{$$=con($1);}	
		|PLUS_EQ	{$$=con($1);}
		|MINUS_EQ	{$$=con($1);}
		|MULT_EQ	{$$=con($1);}
		|DIV_EQ	{$$=con($1);}
		;
MethodInv	:MethodName '(' ArgList ')' {$$=opr(INVOC,2,$1,$3);}
		;
ArgList		:Expression
		|ArgList ',' Expression	{$$=opr(ARGS,2,$1,$3);}
		;
MethodName	:IDENT	{	
				/*search and return from st the ptr to method*/
				/*do some type check here*/
			}
		;
BoolExpression	:TRUE	{$$=con(1);}
		|FALSE	{$$=con(0);}
		;
Expression	:ConstExp			{ $$=$1;}		
		|IDENT				{ $$=id($1);}
	  	|Assignment			{$$=$1;}
		| Expression PLUS Expression	{ $$=opr(PLUS,2,$1,$3); }
		| Expression MINUS Expression	{ $$=opr(MINUS,2,$1,$3); }
		| Expression MULT Expression	{ $$=opr(MULT,2,$1,$3); }
		| Expression DIV Expression	{ $$=opr(DIV,2,$1,$3); }
		| Expression POW Expression	{ $$=opr(POW,2,$1,$3);}			
		| MINUS Expression %prec NEG	{ $$=opr(NEG,1,$2); }
		| '('Expression')'		{ $$=$2; }
		;
ConstExp	:INTEGER	{$$=con($1);}
		|FLOAT		{$$=con($1);}
		|CHAR		{$$=con($1);}
		;
VarDec	:VAR IdList ':' Type 
	;
Type	:TYPE_INT	{$$=133;}	
	|TYPE_FLOAT	{$$=134;}	
	;
IdList	:IDENT	{struct sym_record* s=install(yytext);}
	|IdList ',' IDENT {struct sym_record* s=install(yytext);}
	;

ClassDecln 	: Mods CLASS IDENT TypeParamsI ClassBody ';'	{
									nodeType* n=id($3);
									//do some type checking here
									$$=opr(CLASS,4,$1,n,$4,$5);
								/*here $1 will contain enum type which will be handled by the traversal function*/
								}
		;						
Mods		:PUBLIC		{$$=modPUBLIC;}
		|PRIVATE	{$$=modPRIVATE;}
		|PROTECTED	{$$=modPROTECTED;}
		;
StructDecln	:STRUCT IDENT TypeParamsI ClassBody ';' {$$=opr(STRUCT,3,id($2),$3,$4);}
		;	
TypeParamsI 	: '[' TypeParamIList ']' {$$=$2;}
		|	{/* empty */}	
		;
TypeParamIList 	:IDENT	{$$=id($1);}
		| TypeParamIList ',' IDENT	
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
CtorBody 		: '=' CtorBlock {$$=$2;	/*for the time being*/}
			| CtorBlock
			| ';'
			;
CtorBlock 		: '{' StmtList '}'	{$$=$2;}
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
void yyerror(char*s)  
{
	printf("%s\n",s);
	//printf("%d: %s at %s\n",yylineno,s,yytext);
}


