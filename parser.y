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
extern yyline_no;
extern int yylex();
extern char* yytext;
extern int yywrap();
extern int yycolumn;
extern int yyleng;

/*prototypes start*/

void FreeNode(nodeType *p);	// frees node
void yyerror(char*s);  
struct sym_record* install(char* sym_name);
int generate(nodeType *n);

//char* newlabel();
//char* newtmp();
//char* concat(char* c1,char* c2);
//void dist_type(nodeType* nptr);
//nodeType* get_operand(nodeType* opnode,int index);




/*prototypes end*/

/*global variables*/

struct symbol_table* current_st=NULL;	// global current st 
int seen_func=0;
int seen_class=0;
char *CODE;
char buffer[BUFFSIZE];
int labelno = 1;
int tempno = 1;
int idno = 1;
FILE* output;			// output file
char* out_file;
nodeType* root;
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
%token ARRAY_INVOC
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
%token INTEGER FLOAT CHAR TYPE_INT TYPE_FLOAT TYPE_CHAR TYPE_BOOL TYPE_VOID
%token RETURN DEF
%token PUBLIC PRIVATE PROTECTED
%token LT GT LE GE TRUE FALSE 
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
%type <nPtr> CaseStmt
%type <nPtr> CaseStmtList
%type <nPtr> cast_Expression
%type <nPtr> conditional_Expression
%type <nPtr> CompoundStmt 
%type <nPtr> ConstExp 
%type <nPtr> ClassDeclnList
%type <nPtr> ClassDecln
%type <nPtr> ClassBody 
%type <nPtr> Defn_or_Decln
%type <nPtr> DefaultStmt
%type <nPtr> equality_Expression
%type <nPtr> exclusive_or_Expression
%type <nPtr> Expression
%type <nPtr> ExpressionStmt
%type <nPtr> FormalArg
%type <nPtr> FormalArgList
%type <nPtr> FormalArgLIST
%type <nPtr> FieldArgLIST
%type <nPtr> FieldArgList
%type <nPtr> FieldArg
%type <nPtr> FuncDefn
%type <nPtr> FuncDefnList
%type <nPtr> inclusive_or_Expression
%type <nPtr> IDENT
%type <nPtr> IdList
%type <nPtr> InitExpList
%type <nPtr> IterationStmt
%type <nPtr> JumpStmt
%type <nPtr> logical_or_Expression
%type <nPtr> logical_and_Expression
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
%type <nPtr> Type
%type <nPtr> TypeName   
%type <nPtr> unary_Expression
%type <nPtr> unary_operator
%type <nPtr> VarDec   
                   
%nonassoc IFX
%nonassoc ELSE
%left PLUS MINUS
%left MULT DIV MODULO
%left NEG
%right POW
%start Defn_or_Decln
%%
Defn_or_Decln	
	:	{
			print_header();
			if(current_st==NULL)
			{
				printf("first sym table created\n");
				current_st=new_sym_table(current_st);
				install("println");
				install("print");
				//printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			}	
		}	
	ClassDeclnList	{
				$$=$2;
				print_st(current_st);
				printf("Starting traversal:\n");
				root = $$;
				//traverse($$);
				generate($$);
				//printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				//printf("FINAL CODE:\n");
				//printf("%s\n",$$->opr.code);
			}
	;

ClassDeclnList
	:ClassDeclnList ClassDecln	{$$=opr(CLASSLIST,2,$1,$2);}
	|ClassDecln			{$$=$1;}
	
ClassDecln
	:Mods CLASS IDENT
				{
				printf("%s\n",yytext);
				struct sym_record* s=install(yytext);
				
				$3 = id(s);
				
				st_push(current_st);
				current_st=new_sym_table(current_st);
				current_st->owner_name=strdup(yytext);
				s->my_st=current_st;
				s->is_class=1;
				seen_class=1;

				}
		'(' FieldArgLIST ')'
		ClassBody ';'	
		{
				$$=opr(CLASS,4,$1,$3,$6,$8);
		}
		;						
		
FieldArgLIST : FieldArgList	{ $$ = $1;}
              | {$$= empty(EMPTY);/*empty production*/} 
	      ;	
FieldArgList	
	:FieldArgList ',' FieldArg	{$$=opr(FIELD_ARG_LIST,2,$1,$3);}
	|FieldArg	{$$=$1;}
	;
FieldArg
	: IDENT {
				struct sym_record* s = install(yytext);
				$1 = id(s);
				s->is_field=1;
			}
	 ':' Type
			{
				$$=opr(FIELD_ARG,2,$1,$4);
				 
				$1->id.symrec->type = $4->con_i.value;
			}
	;
	
Mods		
	:PUBLIC		{$$=con_i(modPUBLIC);}
	|PRIVATE	{$$=con_i(modPRIVATE);}
	|PROTECTED	{$$=con_i(modPROTECTED);}
	;

ClassBody	: '{' {seen_class = 0;} FuncDefnList '}'	{
														$$=$3;
														print_st(current_st);
														current_st=st_pop();
														}
		;

FuncDefnList
	:FuncDefnList FuncDefn	{$$ = opr(FUNC_DEF_LIST,2,$1,$2);}
	|FuncDefn		{$$ = $1;}
	;

FuncDefn
	:DEF IDENT 	{
					printf("%s\n",yytext);
					struct sym_record* s=install(yytext);
					
					s->is_proc_name=1;
					$2 = id(s);
					st_push(current_st);
					current_st=new_sym_table(current_st);
					current_st->owner_name=strdup(yytext);
					s->my_st=current_st;
					seen_func=1;
				}
	'(' FormalArgLIST ')' ':' ReturnType {insert_signature($2,$5,$8);} CompoundStmt	
														{ 												   
														$$=opr(FUNC,4,$2,$5,$8,$10);
														printf("FUNCTION MATCHED\n");
														} 
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
				s->formal=1;
			}
	 ':' Type
			{
				$$=opr(FORMAL_ARG,2,$1,$4);
				 
				$1->id.symrec->type = $4->con_i.value;
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
	|NonFuncDeclaration 	{$$=$1;}
	|AsyncStmt		{$$=$1;}
	|JumpStmt		{$$=$1;}
	;

JumpStmt
	:CONTINUE ';'		{$$=opr(CONTINUE,0);}	
	|BREAK ';'		{$$=opr(BREAK,0);}
	|RETURN ';'		{printf("In Return \n");$$=opr(RETURN,0);}
	|RETURN Expression ';'	{$$=opr(RETURN,1,$2);}
	;
	
AsyncStmt
	:ASYNC '{' postfix_Expression ';' '}'		{ $$=opr(ASYNC,2,$3);}
	;
	
CompoundStmt	
	:'{'
		{	
			if(seen_func==1)	// sym_table already made 
				seen_func=0;
			else if(seen_class==1)
				seen_class=0;
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
	| error '}'	{yyerror("error in compound stmt");}
	;
NonFuncDeclaration	:VarDec	{$$=$1;}
			;
ExpressionStmt	
	:Expression ';'	{$$=$1;}
	|';'		{$$=empty(EMPTY);}
	|Expression error ';'	{yyerror("error in exp stmt");}
	|error ';'	{yyerror("error in empty stmt");}
	;
	
SelectionStmt	
	:IF '(' Expression ')' Stmt %prec IFX	{$$=opr(IF,2,$3,$5);}
	|IF '(' Expression ')' Stmt ELSE Stmt	{$$=opr(IF_ELSE,3,$3,$5,$7);}
	|SWITCH '(' Expression ')' '{' CaseStmtList '}'		{$$=opr(SWITCH,2,$3,$6);}
	;

CaseStmtList 
	: CaseStmtList CaseStmt  DefaultStmt {$$=opr(CASE_STMT_LIST,3,$1,$2,$3);}
	| CaseStmt { $$ = $1;}

CaseStmt	
	:CASE ConstExp ':' Stmt	{printf("LLLLLLLLLLLL\n");$$=opr(CASE_STMT,2,$2,$4);}
	;

DefaultStmt
	:DEFAULT ':'	Stmt {printf("KKKKKKKKK\n"); $$ = opr(DEFAULT,1,$3);}
	|{$$ = empty(EMPTY);/*empty production*/}
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
	:EQ			{$$=con_i(EQ);}	
	|PLUS_EQ	{$$=con_i(PLUS_EQ);}
	|MINUS_EQ	{$$=con_i(MINUS_EQ);}
	|MULT_EQ	{$$=con_i(MULT_EQ);}
	|DIV_EQ		{$$=con_i(DIV_EQ);}
	;
VarDec	
	:VAR IdList ':' Type {$$=opr(VAR_DEC,2,$2,$4);dist_type($$);}
	|VAR IdList	AssOp ARRAY '[' Type ']' '(' Expression ')'	
				{
					$$ = opr(ARRAY,3,$2,$6,$9);
					dist_type($$);
				}
	|VAL IDENT	{	
					struct sym_record* s=install(yytext);
					$2 = id(s);
				}
	':' IDENT	
				{
					struct sym_record* s=search(current_st,yytext);
					$5 = id(s);
					$2->id.symrec->my_st = $5->id.symrec->my_st;
				}
	 EQ NEW IDENT 
				{
					struct sym_record* s=search(current_st,yytext);
					$9 = id(s);
				} 
	'(' InitExpList ')' 
	{
		type_check_obj($5,$9,$12);
		$$=opr(OBJ,3,$2,$9,$12);
		printf("Obj done\n");
	}
	;
InitExpList
	: conditional_Expression	{$$=$1;}
	| InitExpList ',' conditional_Expression	{$$=opr(INITEXPLIST,2,$1,$3);}
	| {$$=empty(EMPTY);}	
	;	
Type	
	:TYPE_INT	{$$=con_i(MY_INT);}	
	|TYPE_FLOAT	{$$=con_i(MY_FLOAT);}
	|TYPE_CHAR	{$$=con_i(MY_CHAR);}
	|TYPE_BOOL	{$$=con_i(MY_BOOL);}
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
						struct sym_record*s =search(current_st,yytext);
						printf("s is NULL is true = %d\n",s==NULL);					
						$$=id(s);
				}
	|ConstExp		{$$=$1;}
	|'(' Expression ')' 	{$$=$2;}
	;
ConstExp	
	:INTEGER	{$$=con_i($1);printf("INTEGERSSSSSSSSs %d\n",$1);}
	|FLOAT		{$$=con_f($1);printf("FLOATSSSSSSSSSs %lf\n",$1);}
	|CHAR		{$$=con_c($1);}
	|TRUE		{$$=con_b(1);}	
	|FALSE		{$$=con_b(0);}	
	;

Expression
	: assignment_Expression		{$$=$1;}
	| Expression ',' assignment_Expression  {$$=opr(EXP_LIST,2,$1,$3);}
	| ObjCreation
	;

assignment_Expression	
	:conditional_Expression		{$$=$1;}
	|unary_Expression AssOp assignment_Expression	{
													$$=opr(ASSIGN,3,$1,$2,$3) ;
													type_check_assign($$,$1,$3);
													/*printf("MAKING ASSIGN NODE:\n");
													printf("Unary Exp name:%s\n",$1->id.symrec->sym_name);
													printf("Assop Type:%d\n",$2->type);
													printf("Assignment Exp value:%d type:%d \n",$3->con_i.value,$3->type);													*/
													}
	;

conditional_Expression	
	:logical_or_Expression	{$$=$1;}
	|logical_or_Expression QM Expression ':' conditional_Expression	{$$=opr(TERNARY,3,$1,$3,$5);}
	;

logical_or_Expression	
	:logical_and_Expression	{$$=$1;}
	|logical_or_Expression BOOL_OR logical_and_Expression	{$$=opr(BOOL_OR,2,$1,$3);type_check_bool($$,$1,$3);}
	;

logical_and_Expression
	:inclusive_or_Expression	{$$=$1;}
	|logical_and_Expression BOOL_AND inclusive_or_Expression	{$$=opr(BOOL_AND,2,$1,$3);type_check_bool($$,$1,$3);}
	;

inclusive_or_Expression
	:exclusive_or_Expression	{$$=$1;}
	|inclusive_or_Expression BIT_OR exclusive_or_Expression		{$$=opr(BIT_OR,2,$1,$3);type_check_int($$,$1,$3);}
	;

exclusive_or_Expression
	:and_Expression	{$$=$1;}
	|exclusive_or_Expression XOR and_Expression	{$$=opr(XOR,2,$1,$3);type_check_int($$,$1,$3);}
	;

and_Expression
	:equality_Expression	{$$=$1;}
	|and_Expression BIT_AND equality_Expression	{$$=opr(BIT_AND,2,$1,$3);type_check_int($$,$1,$3);}
	;

equality_Expression
	:relational_Expression		{$$=$1;}	
	|equality_Expression BOOL_EQ relational_Expression	{$$=opr(BOOL_EQ,2,$1,$3);type_check_booleq($$,$1,$3);}
	|equality_Expression NEQ relational_Expression		{$$=opr(NEQ,2,$1,$3);type_check_booleq($$,$1,$3);}
	;

relational_Expression
	:shift_Expression	{$$=$1;}
	|relational_Expression LT shift_Expression	{$$=opr(LT,2,$1,$3);type_check_rel($$,$1,$3);}
	|relational_Expression GT shift_Expression	{$$=opr(GT,2,$1,$3);type_check_rel($$,$1,$3);}
	|relational_Expression LE shift_Expression	{$$=opr(LE,2,$1,$3);type_check_rel($$,$1,$3);}
	|relational_Expression GE shift_Expression	{$$=opr(GE,2,$1,$3);type_check_rel($$,$1,$3);}
	;

shift_Expression
	:additive_Expression						{$$ = $1;}
	|shift_Expression LSH additive_Expression			{$$=opr(LSH,2,$1,$3);type_check_shift($$,$3);}
	|shift_Expression RSH additive_Expression			{$$=opr(RSH,2,$1,$3);type_check_shift($$,$3);}
	;

additive_Expression
	:multiplicative_Expression				{$$ = $1;}
	|additive_Expression PLUS multiplicative_Expression	{$$=opr(PLUS,2,$1,$3);type_check_addmult($$,$1,$3);}
	|additive_Expression MINUS multiplicative_Expression	{$$=opr(MINUS,2,$1,$3);type_check_addmult($$,$1,$3);}
	;

multiplicative_Expression
	: cast_Expression					{$$ = $1;}
	| multiplicative_Expression MULT cast_Expression	{$$=opr(MULT,2,$1,$3);type_check_addmult($$,$1,$3);}
	| multiplicative_Expression DIV cast_Expression		{$$=opr(DIV,2,$1,$3);type_check_division($$,$1,$3);}
	| multiplicative_Expression MODULO cast_Expression		{$$=opr(MODULO,2,$1,$3);type_check_modulo($$,$1,$3);}
	;

cast_Expression
	: unary_Expression
	;

unary_Expression
	: postfix_Expression	{$$=$1;}
	| PP unary_Expression	{$$=opr(PREFIX,2,con_i(MY_PP),$2);type_check_prepostfix($$,$2);}
	| MM unary_Expression	{$$=opr(PREFIX,2,con_i(MY_MM),$2);type_check_prepostfix($$,$2);}
	| unary_operator cast_Expression	{$$=opr(CAST,2,$1,$2);type_check_cast($$,$2);}
	;
postfix_Expression
	: primary_Expression				{$$ = $1;}
	| postfix_Expression '[' Expression ']'		{$$=opr(ARRAY_INVOC,2,$1,$3);type_check_array_invoc($$,$1);}
	| postfix_Expression '('ArgExpList ')'		{$$=opr(INVOC,2,$1,$3);type_check_invoc($$,$1,$3);}
	| postfix_Expression '(' ')'			{$$=opr(INVOC,2,$1,empty(EMPTY));}
	| postfix_Expression '.' IDENT 							
	| postfix_Expression PP			{$$=opr(POSTFIX,2,$1,con_i(MY_PP));type_check_prepostfix($$,$1);}
	| postfix_Expression MM			{$$=opr(POSTFIX,2,$1,con_i(MY_MM));type_check_prepostfix($$,$1);}
	;

ArgExpList
	: conditional_Expression	{$$=$1;}
	| ArgExpList ',' conditional_Expression	{$$=opr(ARGEXPLIST,2,$1,$3);}
	;
unary_operator
	:PLUS		{$$=con_i(MY_PLUS);}
	|MINUS		{$$=con_i(MY_MINUS);}
	;


%%
int main(int argc, char** argv)
{
	char x10file[50];
	if(argc > 0)
	{
		//printf("ARG V IS %s",argv[2]);
		//printf("%s",x10file);
		
		strcpy(x10file,argv[2]);
		freopen(x10file,"r",stdin);	
		
		out_file=strdup(argv[1]);		// filename without extension
		output=fopen(strcat(argv[1],".il"),"w");		// create il file
	}
	yyparse();
	fclose(output);
	fclose(stdin);
	
	// following code runs ilasm 
	char assembler[20]="ilasm ";
	strcat(assembler,argv[1]);
	system(assembler);
	return 0;
}


void yyerror (char *s) /* Called by yyparse on error */
{
	printf ("%d:%d:error:%s at %s  \n",yyline_no,yycolumn-yyleng,s,yytext);
}







	

