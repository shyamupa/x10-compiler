%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "ll_sym_table.h"		// definitions of the symbol table
#include "st_stack.h"			// sym_tab stack
#include "my_defines.h"
#include "node_def.h"
#include "helper_functions.h"
#include "y.tab.h"
#include "ir_code.h"
#include "type_checkers.h"



extern struct sym_record sym_table;
extern yylineno;
extern int yylex();
extern char* yytext;
extern int yywrap();


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

//char* newlabel();
//char* newtmp();
//char* concat(char* c1,char* c2);
//void dist_type(nodeType* nptr);
//nodeType* get_operand(nodeType* opnode,int index);



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
char buffer[BUFFSIZE];
int labelno = 1;
int tempno = 1;

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
%token INTEGER FLOAT CHAR TYPE_INT TYPE_FLOAT TYPE_CHAR TYPE_VOID
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
%type <nPtr> ArgExpList
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
%type <nPtr> JumpStmt
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
%type <nPtr> ReturnType
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
					printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
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
	'(' FormalArgLIST ')' ':' ReturnType CompoundStmt	{$$=opr(FUNC,4,$2,$5,$8,$9);} 
	;

ReturnType
	:Type	{$$=$1;}
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
	|JumpStmt		{$$=$1;}
	;

JumpStmt
	:CONTINUE ';'		{$$=con_i(CONTINUE);}	
	|BREAK ';'		{$$=con_i(BREAK);}
	|RETURN ';'		{$$=con_i(RETURN);}
	|RETURN Expression ';'	{$$=opr(RETURN,1,$2);}
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
	  '}'		{$$=opr(COMPOUND,1,$3);}
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
	:EQ		{$$=con_i(EQ);printf("EQ %d",EQ);}	
	|PLUS_EQ	{$$=con_i(PLUS_EQ);}
	|MINUS_EQ	{$$=con_i(MINUS_EQ);}
	|MULT_EQ	{$$=con_i(MULT_EQ);}
	|DIV_EQ		{$$=con_i(DIV_EQ);}
	;
VarDec	
	:VAR IdList ':' Type {$$=opr(VAR_DEC,2,$2,$4);dist_type($$);/*printf("%d",$$->opr.nops);*/}
	;
Type	
	:TYPE_INT	{$$=con_i(MY_INT);}	
	|TYPE_FLOAT	{$$=con_i(MY_FLOAT);}
	|TYPE_CHAR	{$$=con_i(MY_CHAR);}
	|TYPE_VOID	{$$=con_i(MY_VOID);}
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
					//printf("THIS CAN BE IT %s\n",yytext);					
					struct sym_record*s =search(current_st,yytext);					
					//printf("THIS IS TRUE %d\n",s==NULL);
					$$=id(s);
				}
	|ConstExp		{$$=$1;}
	|'(' Expression ')' 	{$$=$2;}
	;
ConstExp	
	:INTEGER	{$$=con_i($1);printf("INTEGER %d",$1);}
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
	|unary_Expression AssOp assignment_Expression	{$$=opr(ASSIGN,3,$1,$2,$3) ; /*type_check_assign($1,$3)*/;}
	;

conditional_Expression	
	:logical_or_Expression	{$$=$1;}
	|logical_or_Expression QM Expression ':' conditional_Expression	{$$=opr(TERNARY,3,$1,$3,$5);}
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
	|inclusive_or_Expression BIT_OR exclusive_or_Expression		{$$=opr(BIT_OR,2,$1,$3);}
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
	|relational_Expression LT shift_Expression	{$$=opr(LT,2,$1,$3);/*type_check_rel($1,$3)*/;}
	|relational_Expression GT shift_Expression	{$$=opr(GT,2,$1,$3);/*type_check_rel($1,$3)*/;}
	|relational_Expression LE shift_Expression	{$$=opr(LE,2,$1,$3);/*type_check_rel($1,$3)*/;}
	|relational_Expression GE shift_Expression	{$$=opr(GE,2,$1,$3);/*type_check_rel($1,$3)*/;}
	;

shift_Expression
	:additive_Expression						{$$ = $1;}
	|shift_Expression LSH additive_Expression			{$$=opr(LSH,2,$1,$3);/*type_check_int($3)*/;}
	|shift_Expression RSH additive_Expression			{$$=opr(RSH,2,$1,$3);/*type_check_int($3)*/;}
	;

additive_Expression
	:multiplicative_Expression				{$$ = $1;}
	|additive_Expression PLUS multiplicative_Expression		{$$=opr(PLUS,2,$1,$3);/*type_check_addmult($1,$3)*/;}
	|additive_Expression MINUS multiplicative_Expression	{$$=opr(MINUS,2,$1,$3);/*type_check_addmult($1,$3)*/;}
	;

multiplicative_Expression
	: cast_Expression					{$$ = $1;}
	| multiplicative_Expression MULT cast_Expression	{$$=opr(MULT,2,$1,$3);/*type_check_addmult($1,$3)*/;}
	| multiplicative_Expression DIV cast_Expression		{$$=opr(DIV,2,$1,$3);/*type_check_division($1,$3)*/;}
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
	: primary_Expression				{$$ = $1;}
	| postfix_Expression '[' Expression ']'		{type_check_typeid($1);}
	| postfix_Expression '('ArgExpList ')'		{$$=opr(INVOC,2,$1,$3);}
	| postfix_Expression '(' ')'			{$$=opr(INVOC,1,$1);}
	| postfix_Expression '.' IDENT 							
	| postfix_Expression PP			{$$=opr(POSTFIX,2,$1,con_i($2));type_check_prepostfix($1);}
	| postfix_Expression MM			{$$=opr(POSTFIX,2,$1,con_i($2));type_check_prepostfix($1);}
	;

ArgExpList
	: conditional_Expression	{$$=$1;}
	| ArgExpList ',' conditional_Expression	{$$=opr(ARGEXPLIST,2,$1,$3);}
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



void yyerror(char*s)  
{
	printf("%s\n",s);
	//printf("%d: %s at %s\n",yylineno,s,yytext);
}

int generate(nodeType *n)
{
	printf("GENERATE BEGINS\n");
	char* _code;
	if(!n) 
	{
		printf("Empty Node\n");
		return ;
	}	
	switch(n->type)
	{
	case typeConI:
		printf("MATCHED typeConI\n");
		/*if(n->con_i.datatype==133 || n->con_i.datatype == 134)
		{
			n->con_i.place = strdup(newtmp());
			bzero(buffer,BUFFSIZE);
			sprintf(buffer,"%s=%s", n->con_i.place, n->con_i.place);
			n->con_i.code =  strdup(buffer);
			
			printf("CONSTANT NUMBER CODE: %s",n->con_i.code);
		}*/
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
			 n->opr.code = strdup(" ");
			break;
		case EXP_LIST:
			//_code=strdup(ir_explist(n));
			break;
		case TERNARY:
			//_code=strdup(ir_ternary(n));
			break;
		case POSTFIX:
			//_code=strup(ir_postfix(n));
			break;
		case PREFIX:
			//_code=strup(ir_prefix(n));
			break;
		case CAST:
			//_code=strup(ir_cast(n));
			break;
		case ASSIGN:
			printf("MATCHED ASSIGN\n");
			_code=strdup(ir_assign(n));
			break;
	
		case BOOL_OR:
			printf("Matched BOOL_OR\n");
			//_code=strdup(ir_bool_(n));
			break;
		case BOOL_AND:
			printf("Matched BOOL_AND\n");
			//_code=strdup(ir_bool(n));
			break;
		case BOOL_EQ:
			printf("Matched BOOL_EQ\n");
			//_code=strdup(ir_bool(n));
			break;
		case NEQ:
			printf("Matched BOOL_NEQ\n");
			//_code=strdup(ir_bool(n));
			break;
			
		case BIT_OR:
			printf("Matched BIT_OR\n");
			_code = strdup(ir_arithmetic(n));
			break;
		case BIT_AND:
			printf("Matched BIT_AND\n");
			_code = strdup(ir_arithmetic(n));
			break;
		case XOR:
			printf("Matched XOR\n");
			_code = strdup(ir_arithmetic(n));
			break;
		case LT:
			printf("Matched LT\n");
			_code = strdup(ir_relop(n));
			printf("RELOP LT CODE:%s\n",_code);
		case GT:
			printf("Matched GT\n");
			_code = strdup(ir_relop(n));
			printf("RELOP GT CODE:%s\n",_code);
		case LE:
			printf("Matched LE\n");
			_code = strdup(ir_relop(n));
			printf("RELOP LE CODE:%s\n",_code);
		case GE:
			printf("Matched GE\n");
			_code = strdup(ir_relop(n));
			printf("RELOP GE CODE:%s\n",_code);
			break;
		case LSH:
			printf("Matched LSH\n");
			_code = strdup(ir_arithmetic(n));
			break;
		case RSH:
			printf("Matched RSH\n");
			_code = strdup(ir_arithmetic(n));
			break;
	
		case PLUS:
			printf("Matched PLUS\n");
			_code = strdup(ir_arithmetic(n));
			break;
		case MINUS:
   			printf("Matched MINUS\n");
   			_code = strdup(ir_arithmetic(n));
   			break;
		case MULT:
			printf("Matched MULT\n");
			_code = strdup(ir_arithmetic(n));
			break;
		case DIV:
			printf("Matched DIV\n");
			_code = strdup(ir_arithmetic(n));
			break;
	
		default :
			printf("entered default\n"); 
	}
	break;
default:
	printf("entered DEFAULT\n");
}
}	








	

