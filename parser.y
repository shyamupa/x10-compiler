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
#define IDLIST 1342
#define FUN 1343
#define COMMA 1344
#define TYPE 1345
#define YYDEBUG 1	//enable debugging

struct symbol_table* current_st=NULL;	// global current st 
extern struct sym_record sym_table;
extern yylineno;
extern int yylex();
extern char* yytext;
extern int yywrap();
typedef union nodeTypeTag nodeType;	// 

/*prototypes start*/
nodeType* id(struct sym_record* i);	// node creator function for identifiers
nodeType* con(int value); // node creator function for constants
nodeType* opr(int oper, int nops, ...);
void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name);
void dist_type(nodeType* nptr);
nodeType* get_operand(nodeType* opnode,int index);
void type_check_assign(nodeType* lhs, nodeType* rhs);
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
%token ABSTRACT
%token AS
%token ASYNC
%token  AT
%token ATHOME
%token ATEACH
%token ATOMIC
%token CATCH
%token CLASS
%token CLOCKED
%token EXTENDS
%token FINAL
%token FINALLY
%token FINISH
%token GOTO
%token HASZERO
%token HERE
%token IMPLEMENTS
%token IMPORT
%token INSTANCEOF
%token INTERFACE
%token NATIVE
%token  OFFER
%token OFFERS
%token OPERATOR
%token PACKAGE
%token PROPERTY
%token SELF
%token STATIC
%token STRUCT
%token SUPER
%token THIS
%token THROW
%token TRANSIENT
%token TRY
%token VOID
%token WHEN
%token IF THEN ELSE
%token FOR IN WHILE CONTINUE BREAK DO
%token SWITCH CASE DEFAULT
%token INTEGER FLOAT CHAR TYPE_INT TYPE_FLOAT TYPE_CHAR
%token RETURN DEF
%token NEW
%token PUBLIC PRIVATE PROTECTED
%token NEQ BEQ LT GT LE GE TRUE FALSE 
%token ';' '{' '}' '(' ')' '[' ']' ':'
%token IDENT
%token ARRAY ELLIPSIS ASSERT
%token EQ PLUS_EQ MULT_EQ MINUS_EQ  DIV_EQ PP MM
%type <iVal> INTEGER TYPE_INT HasResultType EQ PLUS_EQ MULT_EQ MINUS_EQ  DIV_EQ Mods
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
%type <nPtr> FormalArgList
%type <nPtr> IdList
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
%type <nPtr> Type
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
					printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				}	
			}	
		FuncDefnList	{$$=$2;}
		;
FuncDefnList	: FuncDefnList FuncDefn
		|FuncDefn
		;
FuncDefn	:DEF IDENT 	{
					// make ident point to the new sym tab
					printf("%s\n",yytext);
					
				}
		'(' FormalArgList ')' Stmt	{$$=opr(FUN,3,$2,$5,$7);} 
		;
FormalArgList	:FormalArgList ',' FormalArg	{$$=opr(COMMA,2,$1,$3);}
		|FormalArg	{$$=$1;}
		;
FormalArg	:VarDec	{$$=$1; /*THIS IS INCOMPLETE*/}
		|{$$=NULL;}	
		;
StmtList	:	
		Stmt	{$$=$1;} 			
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

LabeledStmt	:CASE ConstExp ':' Stmt	{$$=opr(CASE,2,$2,$4);}
		|DEFAULT ':' Stmt	{$$=opr(CASE,1,$3);}
		;
		
CompoundStmt	:'{'
			{	
				st_push(current_st);
				current_st=new_sym_table(current_st);
				//current_st->parent=st_examine_top();
			}
			
			 StmtList 
			
			{	
				print_st(current_st);
				current_st=st_pop();
			}
		'}'	{$$=$3;}
		;
Declaration	:VarDec	{$$=$1;}
		|ClassDecln  {$$=$1;}
		|StructDecln {$$=$1;}
		;
ExpressionStmt	:Expression ';'	{$$=$1;}
		|';'	{$$=NULL;}
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

Assignment	:LHS AssOp Expression	{
						$$=opr(ASSIGN,3,$1,$2,$3);
						//type_check_assign($1,$3);
					}
		|LHS EQ	ObjCreation	{$$=$1;}
		;
LHS		:IDENT	{
				struct sym_record*s=search(current_st,yytext);
				if(s!=NULL)
				{
					printf("%s is name\n",s->sym_name);/*right now jsut searhc curr later we will serach till parent*/
					$$=id(search(current_st,yytext));/*right now jsut searhc curr later we will serach till parent*/
				}
				else
					printf("sym_name %s not found in symbol table\n",yytext);
			}
		;
AssOp		:EQ		{$$=con($1);}	
		|PLUS_EQ	{$$=con($1);}
		|MINUS_EQ	{$$=con($1);}
		|MULT_EQ	{$$=con($1);}
		|DIV_EQ		{$$=con($1);}
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
VarDec	:VAR IdList ':' Type {$$=opr(TYPE,2,$2,$4);dist_type($$);/*printf("%d",$$->opr.nops);*/}
	;
Type	:TYPE_INT	{$$=con(133);}	
	|TYPE_FLOAT	{$$=con(134);}	
	;
IdList	:IDENT	{struct sym_record* s=install(yytext);$$=id(s);}
	|IdList ',' IDENT {struct sym_record* s=install(yytext);$$=opr(COMMA,2,$1,id(s));printf("%s is last ident now\n",$$->opr.op[1]->id.i->sym_name);}
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
			| ';'	{$$=NULL;}
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
	printf("%d is the type to be assigned\n",get_operand(nptr,1)->con.value);
	int TypeToAssign=get_operand(nptr,1)->con.value;
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
	if(data_type_ptr->type==typeCon)
		return data_type_ptr->con.type;	// add type fiedl in con node !!!
	else
	{
		return (data_type_ptr->id.i)->type;
	}
}
void type_check_assign(nodeType* lhs,nodeType* rhs)
{
	if(get_type(lhs)!=get_type(rhs))
	{
		printf("type mismatch\n");
	}
}
