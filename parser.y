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

extern struct sym_record sym_table;
extern yylineno;
extern int yylex();
extern char* yytext;
extern int yywrap();
typedef union nodeTypeTag nodeType;	
/*prototypes start*/
nodeType* id(struct sym_record* i);	// node creator function for identifiers
nodeType* con_i(int value); // node creator function for constants integer
nodeType* con_f(float value); // node creator function for constants floats
nodeType* con_c(char value); // node creator function for constants character
nodeType* opr(int oper, int nops, ...);
void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name);
void dist_type(nodeType* nptr);
nodeType* get_operand(nodeType* opnode,int index);
void type_check_assign(nodeType* lhs, nodeType* rhs);
void type_check_relational(nodeType* lhs, nodeType* rhs);
void type_check_int(nodeType* node);
void type_check_char(nodeType* node);
void type_check_float(nodeType* node);
void type_check_division(nodeType* lhs,nodeType* rhs);
void type_check_prepostfix(nodeType* node);
void type_check_typeid(nodeType* node);
/*prototypes end*/
/*global variables*/
struct symbol_table* current_st=NULL;	// global current st 
int seen_func=0;
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
%token AT
%token ATHOME
%token ATEACH
%token ATOMIC
%token BOOL_EQ
%token BOOL_OR
%token BOOL_AND
%token BIT_AND
%token BIT_OR
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
%token LSH
%token NATIVE
%token NEQ
%token NEW
%token MY_NULL
%token OFFER
%token OFFERS
%token OPERATOR
%token PACKAGE
%token PROPERTY
%token QM
%token RSH
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
%token XOR
%token IF THEN ELSE
%token FOR IN WHILE CONTINUE BREAK DO
%token SWITCH CASE DEFAULT
%token INTEGER FLOAT CHAR TYPE_INT TYPE_FLOAT TYPE_CHAR
%token RETURN DEF
%token PUBLIC PRIVATE PROTECTED
%token BEQ LT GT LE GE TRUE FALSE 
%token ';' '{' '}' '(' ')' '[' ']' ':'
%token IDENT
%token ARRAY ELLIPSIS ASSERT
%token EQ PLUS_EQ MULT_EQ MINUS_EQ  DIV_EQ PP MM
%type <iVal> INTEGER TYPE_INT EQ PLUS_EQ MULT_EQ MINUS_EQ  DIV_EQ PP MM PLUS MINUS
%type <fVal> FLOAT TYPE_FLOAT
%type <cVal> CHAR TYPE_CHAR
%type <nPtr> assignment_Expression
%type <nPtr> and_Expression
%type <nPtr> additive_Expression
%type <nPtr> AssOp
%type <nPtr> BasicForStmt
%type <nPtr> cast_Expression
%type <nPtr> conditional_Expression
%type <nPtr> CompoundStmt 
%type <nPtr> ConstExp 
%type <nPtr> ClassDecln
%type <nPtr> ClassBody 
%type <nPtr> ClassMemberDeclns 
%type <nPtr> ClassMemberDecln 
%type <nPtr> CtorDecln 
%type <nPtr> CtorBody 
%type <nPtr> CtorBlock
%type <nPtr> Defn_or_Decln
%type <nPtr> equality_Expression
%type <nPtr> exclusive_or_Expression
%type <nPtr> Expression
%type <nPtr> ExpressionStmt
%type <nPtr> FuncDefnList 
%type <nPtr> FuncDefn 
%type <nPtr> FormalArg
%type <nPtr> FormalArgList
%type <nPtr> HasResultType
%type <nPtr> inclusive_or_Expression
%type <nPtr> IDENT
%type <nPtr> IdList
%type <nPtr> IterationStmt
%type <nPtr> logical_or_Expression
%type <nPtr> logical_and_Expression
%type <nPtr> LabeledStmt
%type <nPtr> multiplicative_Expression
%type <nPtr> Mods
%type <nPtr> NonFuncDeclaration
%type <nPtr> primary_Expression
%type <nPtr> postfix_Expression
%type <nPtr> ObjCreation
%type <nPtr> relational_Expression
%type <nPtr> shift_Expression
%type <nPtr> StmtList
%type <nPtr> Stmt 
%type <nPtr> SelectionStmt
%type <nPtr> StructDecln
%type <nPtr> Type
%type <nPtr> TypeParamsI 
%type <nPtr> TypeParamIList 
%type <nPtr> TypeParams 
%type <nPtr> TypeParam 
%type <nPtr> TypeParamList   
%type <nPtr> TypeName   
%type <nPtr> unary_Expression
%type <nPtr> unary_operator
%type <nPtr> VarDec   
                   
%nonassoc IFX
%nonassoc ELSE
%left PLUS MINUS
%left MULT DIV
%left NEG
%right POW
%start Defn_or_Decln
%%
Defn_or_Decln	
	:	{
			if(current_st==NULL)
			{
				printf("first sym table created\n");
				current_st=new_sym_table(current_st);
				printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			}	
		}	
	FuncDefnList	{$$=$2;print_st(current_st);}
	;
FuncDefnList
	:FuncDefnList FuncDefn
	|FuncDefn
	;
FuncDefn
	:DEF IDENT 	{
				// make ident point to the new sym tab
				printf("%s\n",yytext);
				struct sym_record* s=install(yytext);
				s->is_proc_name=1;
				st_push(current_st);
				current_st=new_sym_table(current_st);
				//printf("%d",current_st);
				//printf("%d",s->proc_st);
				s->proc_st=current_st;
				seen_func=1;

			}
	'(' FormalArgList ')' CompoundStmt	{$$=opr(FUN,3,$2,$5,$7);} 
	;
FormalArgList	
	:FormalArgList ',' FormalArg	{$$=opr(COMMA,2,$1,$3);}
	|FormalArg	{$$=$1;}
	;
FormalArg
	:VarDec	{$$=$1; /*THIS IS INCOMPLETE*/}
	|	{$$=NULL;}	
	;
StmtList
	:Stmt	{$$=$1;} 			
	|StmtList Stmt {$$=opr(';',2,$1,$2);}	
	;
		
Stmt	
	:ExpressionStmt		{$$=$1;}
	|IterationStmt 		{$$=$1;}
	|BasicForStmt 		{$$=$1;}
	|SelectionStmt		{$$=$1;}
	|CompoundStmt		{$$=$1;}
	|LabeledStmt		{$$=$1;}
	|NonFuncDeclaration	{$$=$1;}
	;

LabeledStmt	
	:CASE ConstExp ':' Stmt	{$$=opr(CASE,2,$2,$4);}
	|DEFAULT ':' Stmt	{$$=opr(CASE,1,$3);}
	;
		
CompoundStmt	
	:'{'
		{	
			if(seen_func==1)	// sym_table already made 
				seen_func=0;
			else	
			{
				st_push(current_st);
				current_st=new_sym_table(current_st);
			}	
		}
		 StmtList 
		{	
			print_st(current_st);
			current_st=st_pop();
		}
	  '}'	{$$=$3;}
	| error '}'	{yyerror("error in compound stmt\n");}
	;
NonFuncDeclaration	:VarDec	{$$=$1;}
			|ClassDecln  {$$=$1;}
			|StructDecln {$$=$1;}
			;
ExpressionStmt	
	:Expression ';'	{$$=$1;}
	|';'		{$$=NULL;}
	|Expression error ';'	{yyerror("error in exp stmt\n");}
	|error ';'	{yyerror("error in empty stmt");}
	;
SelectionStmt	
	:IF '(' Expression ')' Stmt %prec IFX	{$$=opr(IF,2,$3,$5);}
	|IF '(' Expression ')' Stmt ELSE Stmt	{$$=opr(IF,3,$3,$5,$7);}
	|SWITCH '(' Expression ')' Stmt	{$$=opr(SWITCH,2,$3,$5);}
	;
IterationStmt	
	:WHILE '(' Expression ')' Stmt	{ $$ = opr(WHILE, 2, $3, $5);}
	;

BasicForStmt	
	:FOR '(' Expression ';' Expression ';' Expression ')' Stmt {$$=opr(FOR,4,$3,$5,$7,$9);}
	;
ObjCreation	
	:NEW TypeName '(' Expression ')' {$$=opr(NEW,2,$2,$4);}	
	;
TypeName
	:IDENT	{$$=$1;}
	;

AssOp	
	:EQ		{$$=con_i($1);}	
	|PLUS_EQ	{$$=con_i($1);}
	|MINUS_EQ	{$$=con_i($1);}
	|MULT_EQ	{$$=con_i($1);}
	|DIV_EQ		{$$=con_i($1);}
	;
VarDec	
	:VAR IdList ':' Type {$$=opr(TYPE,2,$2,$4);dist_type($$);/*printf("%d",$$->opr.nops);*/}
	;
Type	
	:TYPE_INT	{$$=con_i(133);}	
	|TYPE_FLOAT	{$$=con_i(134);}	
	;
IdList	
	:IDENT			{struct sym_record* s=install(yytext);$$=id(s);}
	|IdList ',' IDENT 	{
				struct sym_record* s=install(yytext);$$=opr(COMMA,2,$1,id(s));
				}
	;
primary_Expression	
	:IDENT			{
					printf("%s\n",yytext);					
					struct sym_record*s =search(current_st,yytext);					
					$$=id(s);
				}
	|ConstExp		{$$=$1;}
	|'(' Expression ')' 	{$$=$2;}
	;
ConstExp	
	:INTEGER	{$$=con_i($1);}
	|FLOAT		{$$=con_f($1);}
	|CHAR		{$$=con_c($1);}

Expression
	:assignment_Expression
	|Expression ',' assignment_Expression
	|ObjCreation
	;

assignment_Expression	
	:conditional_Expression		{$$=$1;}
	|unary_Expression AssOp assignment_Expression
	{/*type_check_assign($1,$3);*/}
	;

conditional_Expression	
	:logical_or_Expression
	|logical_or_Expression QM Expression ':' conditional_Expression
	;

logical_or_Expression	
	:logical_and_Expression
	|logical_or_Expression BOOL_OR logical_and_Expression	
	;

logical_and_Expression
	:inclusive_or_Expression
	|logical_and_Expression BOOL_AND inclusive_or_Expression
	;

inclusive_or_Expression
	:exclusive_or_Expression
	|inclusive_or_Expression BIT_OR exclusive_or_Expression
	;

exclusive_or_Expression
	:and_Expression
	|exclusive_or_Expression XOR and_Expression
	;

and_Expression
	:equality_Expression
	|and_Expression BIT_AND equality_Expression
	;

equality_Expression
	:relational_Expression		{/*$$=$1;*/}	
	|equality_Expression BOOL_EQ relational_Expression	{/*$$=opr(BOOL_EQ,2,$1,$3);*/}
	|equality_Expression NEQ relational_Expression
	;

relational_Expression
	:shift_Expression
	|relational_Expression LT shift_Expression	{type_check_relational($1,$3);}
	|relational_Expression GT shift_Expression	{type_check_relational($1,$3);}
	|relational_Expression LE shift_Expression	{type_check_relational($1,$3);}
	|relational_Expression GE shift_Expression	{type_check_relational($1,$3);}
	;

shift_Expression
	:additive_Expression
	|shift_Expression LSH additive_Expression			{type_check_int($3);}
	|shift_Expression RSH additive_Expression			{type_check_int($3);}
	;

additive_Expression
	:multiplicative_Expression
	|additive_Expression PLUS multiplicative_Expression	{type_check_relational($1,$3);}
	|additive_Expression MINUS multiplicative_Expression	{type_check_relational($1,$3);}
	;

multiplicative_Expression
	: cast_Expression
	| multiplicative_Expression MULT cast_Expression	{type_check_relational($1,$3);}
	| multiplicative_Expression DIV cast_Expression			{type_check_division($1,$3);}
	;

cast_Expression
	: unary_Expression
	;

unary_Expression
	: postfix_Expression
	| PP unary_Expression	{$$=opr(PP,2,con_i($1),$2);type_check_prepostfix($2);}
	| MM unary_Expression	{$$=opr(MM,2,con_i($1),$2);type_check_prepostfix($2);}
	| unary_operator cast_Expression	{$$=$2;}
	;
postfix_Expression
	: primary_Expression
	| postfix_Expression '[' Expression ']'		{type_check_typeid($1);}
	| postfix_Expression '.' IDENT				
	| postfix_Expression PP			{type_check_prepostfix($1);}
	| postfix_Expression MM			{type_check_prepostfix($1);}
	;
unary_operator
	:PLUS		{$$=con_i($1);}
	|MINUS		{$$=con_i($1);}
	;
	
ClassDecln
	:Mods CLASS IDENT TypeParamsI ClassBody ';'	{
									//nodeType* n=id($3);
									//do some type checking here
									$$=opr(CLASS,4,$1,$3,$4,$5);
								/*here $1 will contain enum type which will be handled by the traversal function*/
								}
		;						
Mods		:PUBLIC		{$$=con_i(modPUBLIC);}
		|PRIVATE	{$$=con_i(modPRIVATE);}
		|PROTECTED	{$$=con_i(modPROTECTED);}
		;
StructDecln	:STRUCT IDENT TypeParamsI ClassBody ';' {$$=opr(STRUCT,3,$2,$3,$4);}
		;	
TypeParamsI 	: '[' TypeParamIList ']' {$$=$2;}
		|	{/* empty */}	
		;
TypeParamIList 	:IDENT	{$$=$1;}
		|TypeParamIList ',' IDENT	
		|TypeParamIList ','
		;		
TypeParams 	: '[' TypeParamList ']'	{$$=$2;}
		;
TypeParamList 	: TypeParam
		| TypeParamList ',' TypeParam				
		;
TypeParam	:IDENT	{$$=$1;}
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


nodeType* con_i(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_iNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConI;
	p->con_i.value=value;
	p->con_i.datatype=133;
	return p;
}

nodeType* con_f(float value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_fNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConF;
	p->con_f.value=value;
	p->con_f.datatype=134;
	return p;
}

nodeType* con_c(char value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_cNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConC;
	p->con_c.value=value;
	p->con_c.datatype=135;
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
	int rv=search_keywords(sym_name);
	if(rv==1)
		printf("using reserved keyword\n");
	else
	{
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
	printf("%d is the type to be assigned\n",get_operand(nptr,1)->con_i.value);
	int TypeToAssign=get_operand(nptr,1)->con_i.value;
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
	if(data_type_ptr->type==typeConI)
	{
		return data_type_ptr->con_i.datatype;	// add type fiedl in con node !!!
	}
	else if(data_type_ptr->type==typeConF)
	{
		return data_type_ptr->con_f.datatype;	// add type fiedl in con node !!!
	}
	else if(data_type_ptr->type==typeConC)
	{
		return data_type_ptr->con_c.datatype;	// add type fiedl in con node !!!
	}
	else if(data_type_ptr->type==typeId)
	{
		return data_type_ptr->id.i->type;
	}
}

void type_check_assign(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)!=get_type(rhs))
	{
		printf("type mismatch in assign\n");
		exit(0);
	}
	return;
}

void type_check_relational(nodeType* lhs,nodeType* rhs)
{	
	//printf("HELLO %d",get_type(lhs));
	if(get_type(lhs)==133 || get_type(lhs)==134)
	{
		if(get_type(rhs)==133 || get_type(rhs)==134)
		{
			return;
		}
	}
	printf("type mismatch in relational\n");
	exit(0);
}

void type_check_int(nodeType* node)
{
	if(get_type(node)!=133)
	{
		printf("type mismatch in int\n");
		exit(0);
	}
	return;
}

void type_check_float(nodeType* node)
{
	if(get_type(node)!=134)
	{
		printf("type mismatch in float\n");
		exit(0);
	}
	return;
}
void type_check_char(nodeType* node)
{
	if(get_type(node)!=135)
	{
		printf("type mismatch in char\n");
		exit(0);
	}
	return;
}

void type_check_division(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)==133 || get_type(lhs)==134)
	{
		if(get_type(rhs)==133 || get_type(rhs)==134)
		{
			if(rhs->type==typeConI)
			{
				if(rhs->con_i.value!=0)		return;
			}
			else if(rhs->type==typeConF)
			{
				if(rhs->con_f.value!=0)		return;
			}
			printf("Division by zero\n");
			exit(0);
		}
	}
	printf("type mismatch in division\n");
	exit(0);
}

void type_check_prepostfix(nodeType* node)
{
	printf("HELLO %d",get_type(node));
	if(get_type(node)!=133 && get_type(node)!=134)
	{
		printf("type mismatch in ppprefix\n");
		exit(0);
	}
	return;
}

void type_check_typeid(nodeType* node)
{
	if(node->type!=typeId)
	{
		printf("type undefined\n");
		exit(0);
	}
	return;
}
