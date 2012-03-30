%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
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
#define FUNC 1343
#define COMMA 1344
#define VAR_DEC 1345
#define FORMAL_ARG 1346
#define FUNC_DEF_LIST 1347
#define STMT_LIST 1348
#define FORMAL_ARG_LIST 1349
#define ID_LIST 1350
#define EMPTY 1351
#define EXP_LIST 1352
#define TERNERY 1353
#define CAST 1354
#define POSTFIX 1355
#define PREFIX 1356
#define YYDEBUG 1	//enable debugging
#define BUFFSIZE 40000

char buffer[BUFFSIZE];
int labelno = 1;
int tempno = 1;
extern struct sym_record sym_table;
extern yylineno;
extern int yylex();
extern char* yytext;
extern int yywrap();
typedef union nodeTypeTag nodeType;	

/*prototypes start*/
nodeType* id(struct sym_record* symrec);	// node creator function for identifiers
nodeType* con_i(int value); // node creator function for constants integer
nodeType* con_f(float value); // node creator function for constants floats
nodeType* con_c(char value); // node creator function for constants character
nodeType* opr(int oper, int nops, ...);
nodeType* empty(int value);
void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name);
int generate(nodeType *n);

char* newlabel();
char* newtmp();
char* concat(char* c1,char* c2);
void dist_type(nodeType* nptr);
nodeType* get_operand(nodeType* opnode,int index);

char* ir_if(nodeType* S,nodeType* E,nodeType* S1);
char* ir_ifelse(nodeType* S,nodeType* E,nodeType* S1,nodeType* S2);
char* ir_while(nodeType* S,nodeType* E,nodeType* S1);
char* ir_boolor(nodeType* E,nodeType* E1,nodeType* E2);
char* ir_booland(nodeType* E,nodeType* E1,nodeType* E2);
char* ir_boolneg(nodeType* B,nodeType* B1);
char* ir_plus(nodeType* E,nodeType* E1,nodeType* E2);
char* ir_minus(nodeType* E,nodeType* E1,nodeType* E2);
char* ir_mult(nodeType* E,nodeType* E1,nodeType* E2);
char* ir_div(nodeType* E,nodeType* E1,nodeType* E2);
char* ir_ident(nodeType* E,nodeType* id);
char* ir_compound(nodeType* E,nodeType* E1);
char* ir_negexp(nodeType* E,nodeType* E1);		/*E ->  -(E)*/
char* ir_boolrelop(nodeType* E, nodeType* E1,nodeType* E2,int value);
char* ir_truefalse(nodeType* E,int value);
char* ir_bitandorxor(nodeType* E,nodeType* E1,nodeType* E2, int value);
char* ir_shift(nodeType* S, nodeType* S1, nodeType* E, int value);
char* ir_fun_def(nodeType* n);
char* ir_fun_def_list(nodeType* n);
char* ir_var_dec(nodeType* n);
char* ir_idlist(nodeType* n);
char* ir_stmtlist(nodeType* n);

void type_check_assign(nodeType* lhs, nodeType* rhs);
void type_check_int(nodeType* node);
void type_check_addmult(nodeType* lhs, nodeType* rhs);
void type_check_rel(nodeType* lhs, nodeType* rhs);
void type_check_char(nodeType* node);
void type_check_float(nodeType* node);
void type_check_division(nodeType* lhs,nodeType* rhs);
void type_check_prepostfix(nodeType* node);
void type_check_typeid(nodeType* node);

/*prototypes end*/

/*global variables*/
struct symbol_table* current_st=NULL;	// global current st 
int seen_func=0;
char *CODE;
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
%type <iVal> INTEGER TYPE_INT EQ PLUS_EQ MULT_EQ MINUS_EQ  DIV_EQ PP MM PLUS MINUS TRUE FALSE
%type <fVal> FLOAT TYPE_FLOAT
%type <cVal> CHAR TYPE_CHAR
%type <nPtr> assignment_Expression
%type <nPtr> and_Expression
%type <nPtr> additive_Expression
%type <nPtr> AssOp
%type <nPtr> AsyncStmt
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
%type <nPtr> FormalArg
%type <nPtr> FormalArgList
%type <nPtr> FormalArgLIST
%type <nPtr> FuncDefn
%type <nPtr> FuncDefnList
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
	FuncDefnList	{
					$$=$2;
					print_st(current_st);
					printf("Starting code Gen\n");
					generate($$);
					printf("FINAL CODE:\n");
					printf("%s\n",$$->opr.code);
					}
	;
FuncDefnList
	:FuncDefnList FuncDefn	{$$ = opr(FUNC_DEF_LIST,2,$1,$2);}
	|FuncDefn	{$$ = $1;}
	;
FuncDefn
	:DEF IDENT 	{
				// make ident point to the new sym tab
				printf("%s\n",yytext);
				struct sym_record* s=install(yytext);
				s->is_proc_name=1;
				$2 = id(s);
				st_push(current_st);
				current_st=new_sym_table(current_st);
				//printf("%d",current_st);
				//printf("%d",s->proc_st);
				s->proc_st=current_st;
				seen_func=1;

			}
	'(' FormalArgLIST ')' CompoundStmt	{$$=opr(FUNC,3,$2,$5,$7);} 
	;
FormalArgLIST : FormalArgList	{ $$ = $1;}
              | {$$= empty(EMPTY);/*empty production*/} 
	      ;	
FormalArgList	
	:FormalArgList ',' FormalArg	{$$=opr(FORMAL_ARG_LIST,2,$1,$3);}
	|FormalArg	{$$=$1;}
	;
FormalArg
	: IDENT {
		struct sym_record* s = install(yytext);
		$1 = id(s);
		}
	 ':' Type{
		 $$=opr(FORMAL_ARG,2,$1,$4); /*THIS IS INCOMPLETE*/
		 $1->id.symrec->type = $4->con_i.datatype;
		 }
	;
	
	
StmtList
	:Stmt	{$$=$1;} 			
	|StmtList Stmt {$$=opr(STMT_LIST,2,$1,$2);}	
	;
		
Stmt	
	:ExpressionStmt		{$$=$1;}
	|IterationStmt 		{$$=$1;}
	|BasicForStmt 		{$$=$1;}
	|SelectionStmt		{$$=$1;}
	|CompoundStmt		{$$=$1;}
	|LabeledStmt		{$$=$1;}
	|NonFuncDeclaration	{$$=$1;}
	|AsyncStmt		{$$=$1;}
	;

AsyncStmt
	:ASYNC Stmt		{$$=opr(ASYNC,2,$2);}
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
	|';'		{$$=empty(EMPTY);}
	|Expression error ';'	{yyerror("error in exp stmt\n");}
	|error ';'	{yyerror("error in empty stmt");}
	;
SelectionStmt	
	:IF '(' Expression ')' Stmt %prec IFX	{$$=opr(IF,2,$3,$5);}
	|IF '(' Expression ')' Stmt ELSE Stmt	{$$=opr(IF,3,$3,$5,$7);}
	|SWITCH '(' Expression ')' Stmt		{$$=opr(SWITCH,2,$3,$5);}
	;
IterationStmt	
	:WHILE '(' Expression ')' Stmt			{$$ = opr(WHILE, 2, $3, $5);}
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
	:VAR IdList ':' Type {$$=opr(VAR_DEC,2,$2,$4);dist_type($$);/*printf("%d",$$->opr.nops);*/}
	;
Type	
	:TYPE_INT	{$$=con_i(133);}	
	|TYPE_FLOAT	{$$=con_i(134);}	
	;
IdList	
	:IDENT			{struct sym_record* s=install(yytext);$$=id(s);}
	|IdList ',' IDENT 	{
				struct sym_record* s=install(yytext);
				$3 = id(s);
				$$=opr(ID_LIST,2,$1,$3);
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
	|TRUE		{$$=con_i($1);}	
	|FALSE		{$$=con_i($1);}	
	;

Expression
	:assignment_Expression		{$$=$1;}
	|Expression ',' assignment_Expression  {$$=opr(EXP_LIST,2,$1,$3);}
	|ObjCreation
	;

assignment_Expression	
	:conditional_Expression		{$$=$1;}
	|unary_Expression AssOp assignment_Expression	{$$=opr(ASSIGN,2,$1,$2);type_check_assign($1,$3);}
	;

conditional_Expression	
	:logical_or_Expression	{$$=$1;}
	|logical_or_Expression QM Expression ':' conditional_Expression	{$$=opr(TERNERY,3,$1,$3,$5);}
	;

logical_or_Expression	
	:logical_and_Expression	{$$=$1;}
	|logical_or_Expression BOOL_OR logical_and_Expression	{$$=opr(BOOL_OR,2,$1,$3);}
	;

logical_and_Expression
	:inclusive_or_Expression	{$$=$1;}
	|logical_and_Expression BOOL_AND inclusive_or_Expression	{$$=opr(BOOL_AND,2,$1,$3);}
	;

inclusive_or_Expression
	:exclusive_or_Expression	{$$=$1;}
	|inclusive_or_Expression BIT_OR exclusive_or_Expression	{$$=opr(BIT_OR,2,$1,$3);}
	;

exclusive_or_Expression
	:and_Expression	{$$=$1;}
	|exclusive_or_Expression XOR and_Expression	{$$=opr(XOR,2,$1,$3);}
	;

and_Expression
	:equality_Expression	{$$=$1;}
	|and_Expression BIT_AND equality_Expression	{$$=opr(BIT_AND,2,$1,$3);}
	;

equality_Expression
	:relational_Expression		{$$=$1;}	
	|equality_Expression BOOL_EQ relational_Expression	{$$=opr(BOOL_EQ,2,$1,$3);}
	|equality_Expression NEQ relational_Expression		{$$=opr(NEQ,2,$1,$3);}
	;

relational_Expression
	:shift_Expression	{$$=$1;}
	|relational_Expression LT shift_Expression	{$$=opr(LT,2,$1,$3);type_check_rel($1,$3);}
	|relational_Expression GT shift_Expression	{$$=opr(GT,2,$1,$3);type_check_rel($1,$3);}
	|relational_Expression LE shift_Expression	{$$=opr(LE,2,$1,$3);type_check_rel($1,$3);}
	|relational_Expression GE shift_Expression	{$$=opr(GE,2,$1,$3);type_check_rel($1,$3);}
	;

shift_Expression
	:additive_Expression
	|shift_Expression LSH additive_Expression			{$$=opr(LSH,2,$1,$3);type_check_int($3);}
	|shift_Expression RSH additive_Expression			{$$=opr(RSH,2,$1,$3);type_check_int($3);}
	;

additive_Expression
	:multiplicative_Expression
	|additive_Expression PLUS multiplicative_Expression	{$$=opr(PLUS,2,$1,$3);type_check_addmult($1,$3);}
	|additive_Expression MINUS multiplicative_Expression	{$$=opr(MINUS,2,$1,$3);type_check_addmult($1,$3);}
	;

multiplicative_Expression
	: cast_Expression
	| multiplicative_Expression MULT cast_Expression	{$$=opr(MULT,2,$1,$3);type_check_addmult($1,$3);}
	| multiplicative_Expression DIV cast_Expression		{$$=opr(DIV,2,$1,$3);type_check_division($1,$3);}
	;

cast_Expression
	: unary_Expression
	;

unary_Expression
	: postfix_Expression	{$$=$1;}
	| PP unary_Expression	{$$=opr(PREFIX,2,con_i($1),$2);type_check_prepostfix($2);}
	| MM unary_Expression	{$$=opr(PREFIX,2,con_i($1),$2);type_check_prepostfix($2);}
	| unary_operator cast_Expression	{$$=opr(CAST,2,$1,$2);}
	;
postfix_Expression
	: primary_Expression
	| postfix_Expression '[' Expression ']'		{type_check_typeid($1);}
	| postfix_Expression '.' IDENT 							
	| postfix_Expression PP			{$$=opr(POSTFIX,2,$1,con_i($2));type_check_prepostfix($1);}
	| postfix_Expression MM			{$$=opr(POSTFIX,2,$1,con_i($2));type_check_prepostfix($1);}
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
nodeType *id(struct sym_record* symrec)	 
{
	//printf("name is %s\n",i->sym_name);
	nodeType *p;
	if ((p = malloc(sizeof(idNodeType))) == NULL)
		yyerror("out of memory");
	p->type = typeId;
	p->id.symrec = symrec;
	p->id.code = strdup(symrec->sym_name);
	printf("ffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
	printf("%s\n",p->id.symrec->sym_name);
	return p;
}

nodeType* empty(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(oprNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type = typeOpr;
	p->opr.oper = value;
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

int generate(nodeType *n)
{
	char* _code;
	if(!n) 
	{
		printf("Empty Node\n");
		return ;
	}	
	switch(n->type)
	{
	case typeConI:
		break;
	case typeConC:
		break;
	case typeConF:
		break;
	case typeId : 
		
			printf("Matched typeId:\n");
			//printf("%s\n",n->id.symrec->sym_name);
			printf("%s\n",n->id.code);
			//concat(CODE,n->id.code);
			break;
	case typeOpr:
		switch(n->opr.oper)
		{
			case FUNC_DEF_LIST:
			 printf("Matched FUNC_DEF_LIST\n");
			_code =strdup(ir_fun_def_list(n));
			 printf("%s",_code);
			//concat(CODE,_code);
			break;

		case FUNC:
			 printf("Matched FUNC\n");
			_code = strdup(ir_fun_def(n));
			 printf("%s",_code);
			//concat(CODE,_code);
			break;

		case FORMAL_ARG_LIST:
			 printf("Matched FORMAL_ARG_LIST\n");
			 printf("%s",_code);
			 break;

		case FORMAL_ARG:
			 printf("Matched FORMAL_ARG\n");
			 printf("%s",_code);
			 break;
		 
		case STMT_LIST:
			 printf("MAtched STMT_LIST\n");		
			 _code=strdup(ir_stmtlist(n));
			 //concat(CODE,_code);
			 printf("%s",_code);
 			 break;

		case VAR_DEC:
			 printf("Matched VAR_DEC\n");
			 _code=strdup(ir_var_dec(n));
			 //concat(CODE,_code);
			 printf("%s",_code);
			 break;

		case ID_LIST:
 			 printf("Matched ID_LIST\n");
 			 _code=strdup(ir_idlist(n));
			 //concat(CODE,_code);
			 printf("%s",_code);
			 break;
		case EMPTY:
			 printf("Matched EMPTY\n");
			 n->opr.code = strdup(" ");;
			 break;
		case EXP_LIST:
			break;
		case TERNERY:
			break;
		case POSTFIX:
			break;
		case PREFIX:
			break;
		case CAST:
			break;
		case ASSIGN:
			break;
	
		case BOOL_OR:
			break;
		case BOOL_AND:
			break;
		case BOOL_EQ:
			break;
		case NEQ:
			break;
	
		case BIT_OR:
		break;
		case BIT_AND:
		break;
	case XOR:
		break;

	case LT:
		break;
	case GT:
		break;
	case LE:
		break;
	case GE:
		break;
	
	case LSH:
		break;
	case RSH:
		break;
	
	case PLUS:
		break;
	case MINUS:
		break;
	case MULT:
		break;
	case DIV:
		break;
	
	default :
		printf("entered default\n"); 
	}
default:
	printf("entered DEFAULT\n");
}
}	

char* newlabel()
{
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"l%d:",labelno++);
	return(buffer);
}

char* newtmp()
{
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"t%d:",tempno++);
	return(buffer);
}
/*
  takes a VarDec node and spread the type info 
*/
void dist_type(nodeType* nptr)
{
	printf("%d\n",nptr->type); // should be typeOp
	printf("%d is the type to be assigned\n",get_operand(nptr,1)->con_i.value);
	int TypeToAssign=get_operand(nptr,1)->con_i.value;
	nodeType* idlist=get_operand(nptr,0);
	if(idlist->type==typeId)
		idlist->id.symrec->type=TypeToAssign;		
	else
	{
		while(idlist->type!=typeId)
		{
			nodeType* leftnode=get_operand(idlist,0);
			nodeType* rightnode=get_operand(idlist,1);
			rightnode->id.symrec->type=TypeToAssign;
			idlist=leftnode;
		}
		idlist->id.symrec->type=TypeToAssign;
	}	
}
/*
	get_type takes a data_type node ptr and returns the data type embedded in it	
*/
int get_type(nodeType* data_type_ptr)
{
	if(data_type_ptr->type==typeConI)
	{
		return data_type_ptr->con_i.datatype;	
	}
	else if(data_type_ptr->type==typeConF)
	{
		return data_type_ptr->con_f.datatype;	
	}
	else if(data_type_ptr->type==typeConC)
	{
		return data_type_ptr->con_c.datatype;	
	}
	else if(data_type_ptr->type==typeId)
	{
		return data_type_ptr->id.symrec->type;
	}
}
// get_operand takes a nodeType of
//
nodeType* get_operand(nodeType* opnode,int index)
{
	return opnode->opr.op[index];
}
	
char* concat(char* c1,char* c2)
{
	strcat(c1,"\n");
	printf("jbdsah\n");
	strcat(c1,c2);
	printf("jbdsah\n");
	return c1;
}

char* ir_if(nodeType* S,nodeType* E,nodeType* S1)
{
	bzero(buffer,BUFFSIZE);
	E->opr.T = newlabel();
	E->opr.F = S->opr.next;
	S1->opr.next = S->opr.next;
	sprintf(buffer,"%s\n%s\n%s", E->opr.code, E->opr.T, S1->opr.code);
	return(buffer);
}

char* ir_ifelse(nodeType* S,nodeType* E,nodeType* S1,nodeType* S2)
{
	bzero(buffer,BUFFSIZE);
	E->opr.T = newlabel();
	E->opr.F = newlabel();
	S1->opr.next = S->opr.next;
	S2->opr.next = S->opr.next;
	sprintf(buffer,"%s\n%s\n%s\n%s%s\n%s\n%s",E->opr.code,E->opr.T,S1->opr.code,"goto ",S->opr.next,E->opr.F,S2->opr.code);
	return(buffer);
}

char* ir_while(nodeType* S,nodeType* E,nodeType* S1)
{
	bzero(buffer,BUFFSIZE);
	S->opr.begin = newlabel();
	E->opr.T = newlabel();
	E->opr.F = S->opr.next;
	S1->opr.next = S->opr.begin;
	sprintf(buffer,"%s\n%s\n%s\n%s\n%s%s", S->opr.begin, E->opr.code, E->opr.T, S1->opr.code, "goto ", S->opr.begin);
	return(buffer);
}												

char* ir_boolor(nodeType* B,nodeType* B1,nodeType* B2)
{
	bzero(buffer,BUFFSIZE);
	B1->opr.T = B->opr.T;
	B1->opr.F = newlabel();
	B2->opr.T = B->opr.T;
	B2->opr.F = B->opr.F;
	sprintf(buffer,"",B1->opr.code,B1->opr.F,B2->opr.code);
	return(buffer);
}

char* ir_booland(nodeType* B,nodeType* B1,nodeType* B2)
{
	bzero(buffer,BUFFSIZE);
	B1->opr.T = newlabel();
	B1->opr.F = B->opr.F;
	B2->opr.T = B->opr.T;
	B2->opr.F = B->opr.F;
	sprintf(buffer,"",B1->opr.code,B1->opr.T,B2->opr.code);
	return(buffer);
}

char* ir_boolneg(nodeType* B,nodeType* B1)
{
	B1->opr.T = B->opr.F;
	B1->opr.F = B->opr.T;
	return(B->opr.code);
}

char* ir_plus(nodeType* E,nodeType* E1,nodeType* E2)
{
	bzero(buffer,BUFFSIZE);
	E->opr.place = newtmp();
	sprintf(buffer, "%s\n%s\n%s%s%s%s%s", E1->opr.code, E2->opr.code, E->opr.place, " = ", E1->opr.place, " + ", E2->opr.place);
	return(buffer);
}

char* ir_minus(nodeType* E,nodeType* E1,nodeType* E2)
{
	bzero(buffer,BUFFSIZE);
	E->opr.place = newtmp();
	sprintf(buffer, "%s\n%s\n%s%s%s%s%s", E1->opr.code, E2->opr.code, E->opr.place, " = ", E1->opr.place, " - ", E2->opr.place);
	return(buffer);
}

char* ir_mult(nodeType* E,nodeType* E1,nodeType* E2)
{
	bzero(buffer,BUFFSIZE);
	E->opr.place = newtmp();
	sprintf(buffer, "%s\n%s\n%s%s%s%s%s", E1->opr.code, E2->opr.code, E->opr.place, " = ", E1->opr.place, " + ", E2->opr.place);
	return(buffer);
}

char* ir_div(nodeType* E,nodeType* E1,nodeType* E2)
{
	bzero(buffer,BUFFSIZE);
	E->opr.place = newtmp();
	sprintf(buffer, "%s\n%s\n%s%s%s%s%s", E1->opr.code, E2->opr.code, E->opr.place, " = ", E1->opr.place, " / ", E2->opr.place);
	return(buffer);
}

char* ir_compound(nodeType* E,nodeType* E1)
{
	bzero(buffer,BUFFSIZE);
	E->opr.place = E1->opr.place;
	sprintf(buffer, "%s", E1->opr.code);
	return(buffer);
}

char* ir_ident(nodeType* E,nodeType* id)
{
	E->opr.place = id->opr.place;
	return("");
}

char* ir_pp(nodeType* E,nodeType* E1)
{
	bzero(buffer,BUFFSIZE);
	sprintf(buffer, "%s\n%s%s%s%s", E1->opr.code, E->opr.place, " = ", E1->opr.place, " + 1");
	return(buffer);
}

char* ir_mm(nodeType* E,nodeType* E1)
{
	bzero(buffer,BUFFSIZE);
	sprintf(buffer, "%s\n%s%s%s%s", E1->opr.code, E->opr.place, " = ", E1->opr.place, " - 1");
	return(buffer);
}

char* ir_negexp(nodeType* E,nodeType* E1)		/*E ->  -(E)*/
{
	bzero(buffer,BUFFSIZE);
	E->opr.place = newtmp();
	sprintf(buffer, "%s\n%s%s%s", E1->opr.code, E->opr.place, " = - ", E1->opr.place);
	return(buffer);
}


char* ir_boolrelop(nodeType* E, nodeType* E1,nodeType* E2,int value)
{	bzero(buffer,BUFFSIZE);
	switch(value)
	{
		case LT:
			sprintf(buffer, "%s\n%s\n%s%s%s%s%s%s\n%s%s", E1->opr.code, E2->opr.code, "if ", E1->opr.place, " < ", E2->opr.place, " goto ", E->opr.T, " goto ", E->opr.F);
		case GT:
			sprintf(buffer, "%s\n%s\n%s%s%s%s%s%s\n%s%s", E1->opr.code, E2->opr.code, "if ", E1->opr.place, " > ", E2->opr.place, " goto ", E->opr.T, " goto ", E->opr.F);
		case LE:
			sprintf(buffer, "%s\n%s\n%s%s%s%s%s%s\n%s%s", E1->opr.code, E2->opr.code, "if ", E1->opr.place, " <= ", E2->opr.place, " goto ", E->opr.T, " goto ", E->opr.F);
		case GE:
			sprintf(buffer, "%s\n%s\n%s%s%s%s%s%s\n%s%s", E1->opr.code, E2->opr.code, "if ", E1->opr.place, " >= ", E2->opr.place, " goto ", E->opr.T, " goto ", E->opr.F);
	}
	return(buffer);
}

char* ir_truefalse(nodeType* E,int value)
{
	bzero(buffer,BUFFSIZE);
	switch(value)
	{
	case TRUE:	
		sprintf(buffer, "%s%s", " goto ", E->opr.T);
	case FALSE:
		sprintf(buffer, "%s%s", " goto ", E->opr.F);
	}
	return(buffer);
}

char* ir_bitandorxor(nodeType* E,nodeType* E1,nodeType* E2, int value)
{
	bzero(buffer,BUFFSIZE);	
	switch(value)
	{
		case BIT_AND:
			sprintf(buffer,"%s\n%s\n%s%s%s",E1->opr.code, E2->opr.code, E1->opr.place, " & ", E2->opr.place);
		case BIT_OR:
			sprintf(buffer,"%s\n%s\n%s%s%s",E1->opr.code, E2->opr.code, E1->opr.place, " | ", E2->opr.place);
		case XOR:
			sprintf(buffer,"%s\n%s\n%s%s%s",E1->opr.code, E2->opr.code, E1->opr.place, " $ ", E2->opr.place);
	}
	return(buffer);
}

char* ir_shift(nodeType* S, nodeType* S1, nodeType* E, int value)
{	// S	->		S1	<<	E
	bzero(buffer,BUFFSIZE);	
	switch(value)
	{
		case LSH:
			sprintf(buffer, "%s\n%s\n%s%s%s", S1->opr.code, E->opr.code, S1->opr.place, " << ", E->opr.place);
		case RSH:
			sprintf(buffer, "%s\n%s\n%s%s%s", S1->opr.code, E->opr.code, S1->opr.place, " >> ", E->opr.place);
	}
	return(buffer);
}

char* ir_fun_def_list(nodeType* n)
{
	nodeType* fun_def_list = n->opr.op[0];
	nodeType* fun_def = n->opr.op[1];
	generate(fun_def_list);
	if(n->opr.oper == FUNC_DEF_LIST)
		{
		generate(fun_def);
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s", fun_def_list->opr.code, fun_def->opr.code);
		}
	else
		{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s", fun_def_list->opr.code);
		}
	n->opr.code = strdup(buffer);
	return buffer;
	
}
char* ir_fun_def(nodeType* n)
{
	
	nodeType* fun_name = n->opr.op[0];
	nodeType* formal_arguments = n->opr.op[1];
	nodeType* stmt_list = n->opr.op[2];
	//printf("hi\n");
	generate(fun_name);
	generate(formal_arguments);
	generate(stmt_list);
	//printf("pupa \n");
	//printf("1:%s\n",fun_name->id.code);
	//printf("2:%d\n",formal_arguments==NULL);
	//printf("3:%s\n",stmt_list->opr.code);
	if(formal_arguments->opr.oper != EMPTY)
		{
			bzero(buffer,BUFFSIZE);
			sprintf(buffer,"%s\n%s\n%s",fun_name->id.code , formal_arguments->opr.code , stmt_list->opr.code);
		}
	else
		{
			bzero(buffer,BUFFSIZE);
			sprintf(buffer,"%s\n%s",fun_name->id.code , stmt_list->opr.code);
		}
	n->opr.code = strdup(buffer);
	return buffer;

}

char* ir_var_dec(nodeType* n)
{
	nodeType* Idlist = n->opr.op[0];
	nodeType* Type = n->opr.op[1];
	generate(Idlist);
	//printf("ughuguguguygug\n");
	generate(Type);
	//printf("ughuguguguygug\n");
	n->opr.code = strdup(Idlist->opr.code);
	//printf("POPOPOP\n");
	return n->opr.code;
} 

char*  ir_idlist(nodeType* n)
{
	nodeType* Idlist = n->opr.op[0];
	nodeType* ident = n->opr.op[1];
	generate(Idlist);
	//printf("huhahuahuahauha\n");
	//no need to generate code for ident as it is generated during installation
	if(Idlist->type == typeOpr)
		{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s", Idlist->opr.code, ident->id.code);
		}
	else
		{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s", Idlist->id.code, ident->id.code);
		}
	n->opr.code = strdup(buffer);
	
	return buffer;
}	

char*  ir_stmtlist(nodeType* n)
{
	nodeType* Stmtlist = n->opr.op[0];
	nodeType* Stmt = n->opr.op[1];
	generate(Stmtlist);
	//printf("wjbsadoulaJSBHDONJSA\n");
	if(Stmtlist->opr.oper == STMT_LIST)
			{
			//printf("WWWjbsadoulaJSBHDONJSA\n");
			generate(Stmt);
			bzero(buffer,BUFFSIZE);
			sprintf(buffer,"%s\n%s", Stmtlist->opr.code, Stmt->opr.code);
			}
	else
		{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s", Stmtlist->opr.code);
		}
	n->opr.code = strdup(buffer);
	//printf("wjbsadoulaJSBHDONJSA\n");
	return buffer;
}	

/*
	checks type for assign opr
	type should strictly match
*/
void type_check_assign(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)!=get_type(rhs))
	{
		printf("type mismatch in assign\n");
		exit(0);
	}
	return;
}
/*
	checks type for add and mult 
	allows all 4 combos of int and float
*/
void type_check_addmult(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)==133 || get_type(lhs)==134)
	{
		if(get_type(rhs)==133 || get_type(rhs)==134)
		{
			return;
		}
	}
	printf("type mismatch in addmult\n");
	exit(0);
}

void type_check_rel(nodeType* lhs,nodeType* rhs)
{	
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
