%{
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
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
extern int curr_return_type;

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
int debug_flag=0;
int error_found=0;
int seen_main=0;
int seen_return=0;
int seen_loop=0;
int seen_switch=0;

/*global variables*/

%}
%union 
{
	int iVal;
	float fVal;
	char cVal;
	char* str;
	struct sym_record *sPtr; // pointer to position in sym_table
	union Gen_Node *nPtr;	 // node pointer
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
%token ';' '{' '}' '(' ')' '[' ']' ':' '.'
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
%type <nPtr> AsyncStmtList
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
%type <nPtr> FinishStmt
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
%type <nPtr> Static_or_not
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
			if(current_st==NULL)
			{
				debugger("first sym table created\n");
				current_st=new_sym_table(current_st);
				
				install("println");
				install("print");
				install("scanf");
			}	
		}	
	ClassDeclnList	
			{
				$$=$2;
				print_st(current_st);
				root = $$;
				
			}
	;

ClassDeclnList
	:ClassDeclnList ClassDecln	{$$=make_node(CLASSLIST,2,$1,$2);}
	|ClassDecln			{$$=$1;}
	
ClassDecln
	:Mods CLASS IDENT
				{
				debugger("%s\n",yytext);
				struct sym_record* s=install(yytext);
				
				$3 = make_id(s);
				
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
				$$=make_node(CLASS,4,$1,$3,$6,$8);
		}
		;						
		
FieldArgLIST 
		: FieldArgList	{ $$ = $1;}
        |				{$$= empty(EMPTY);/*empty production*/} 
	    ;	
FieldArgList	
	:FieldArgList ',' FieldArg	{$$=make_node(FIELD_ARG_LIST,2,$1,$3);}
	|FieldArg	{$$=$1;}
	;
FieldArg
	: IDENT {
				struct sym_record* s = install(yytext);
				$1 = make_id(s);
				s->is_field=1;
			}
	 ':' Type
			{
				$$=make_node(FIELD_ARG,2,$1,$4);
				 
				$1->id.symrec->type = $4->con_i.value;
			}
	;
	
Mods		
	:PUBLIC		{$$=con_i(modPUBLIC);}
	|PRIVATE	{$$=con_i(modPRIVATE);}
	|PROTECTED	{$$=con_i(modPROTECTED);}
	|			{$$=con_i(EMPTY);}
	;

ClassBody	: '{' {seen_class = 0;} FuncDefnList '}'	{
															$$=$3;
															print_st(current_st);
															current_st=st_pop();
														}
		;

FuncDefnList
	:FuncDefnList FuncDefn	{$$ = make_node(FUNC_DEF_LIST,2,$1,$2);}
	|FuncDefn		{$$ = $1;}
	;
FuncDefn
	:DEF Mods Static_or_not IDENT 	
				{
					seen_return=0;
					debugger("%s\n",yytext);
					struct sym_record* s=install(yytext);
					if(s!=NULL)
					{
						if(strcmp(yytext,"main")==0)
						{
							seen_main++;
						}
						s->is_proc_name=1;		// is a func name
						if($3->opr.oper!=EMPTY)
						{
							s->is_static=1;
						}
						$4 = make_id(s);
						assign_acc_mod($4,$2);
					
						st_push(current_st);
						current_st=new_sym_table(current_st);
						current_st->owner_name=strdup(yytext);
						s->my_st=current_st;
					
						seen_func=1;		// for compound stmt
					}
					else
					{
						$4=NULL;
					}
				}
	'(' FormalArgLIST ')' ':' ReturnType 
					{
						insert_signature($4,$7,$10);
						curr_return_type = $10->con_i.value;
					} 
	CompoundStmt	
				{ 												   
					if(seen_return==0 && $10->con_i.value!=MY_VOID)
					{
						yyerror("return missing in function");
					}
					$$=make_node(FUNC,6,$2,$3,$4,$7,$10,$12);
					debugger("FUNCTION MATCHED\n");
				} 
	;
Static_or_not
	:STATIC		{$$=con_i(STATIC);}
	|			{$$=empty(EMPTY);}
	;
ReturnType
	:Type	{$$=$1;}
	;
	
FormalArgLIST : FormalArgList	{ $$ = $1;}
              | {$$= empty(EMPTY);/*empty production*/} 
	      ;	
FormalArgList	
	:FormalArgList ',' FormalArg	{$$=make_node(FORMAL_ARG_LIST,2,$1,$3);}
	|FormalArg	{$$=$1;}
	;
FormalArg
	: IDENT {
				struct sym_record* s = install(yytext);
				$1 = make_id(s);
				s->formal=1;
			}
	 ':' Type
			{
				$$=make_node(FORMAL_ARG,2,$1,$4);
				 
				$1->id.symrec->type = $4->con_i.value;
			}
	;
	
	
StmtList
	:Stmt	{$$=$1;} 			
	|StmtList Stmt {$$=make_node(STMT_LIST,2,$1,$2);}	
	;
		
Stmt	
	:ExpressionStmt		{$$=$1;}
	|IterationStmt 		{$$=$1;}
	|BasicForStmt 		{$$=$1;}
	|SelectionStmt		{$$=$1;}
	|CompoundStmt		{$$=$1;}
	|NonFuncDeclaration	{$$=$1;}
	|AsyncStmt		{$$=$1;}
	|JumpStmt		{$$=$1;}
	|FinishStmt		{$$=$1;}
    
	;

FinishStmt
		: FINISH '{' AsyncStmtList '}' {$$ = make_node(FINISH,1,$3);}  
		;

JumpStmt
	:CONTINUE ';'		{
							$$=make_node(CONTINUE,0);
							if(seen_loop<=0)
							{
								yyerror("stray continue");
							}
						}	
	|BREAK ';'			{
							$$=make_node(BREAK,0);
							if(seen_loop<=0 && seen_switch<=0)
							{
								yyerror("stray break");
							}
						}
	|RETURN ';'				{$$=make_node(RETURN,0);seen_return=1;type_check_func_return(empty(EMPTY),1);}
	|RETURN Expression ';'	{$$=make_node(RETURN,1,$2);seen_return=1;type_check_func_return($2,2);}
	;
	
AsyncStmtList
			:AsyncStmt AsyncStmtList  {$$ = make_node(ASYNC_LIST,2,$1,$2);/* beware right recursion here*/}
			|AsyncStmt {$$ = $1;}
			;

AsyncStmt
	:ASYNC '{' postfix_Expression ';' '}' { $$=make_node(ASYNC,2,$3);}
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
	  '}'		{$$=make_node(COMPOUND,1,$3);}
	|error '}'	{yyerror("error in compound stmt");}
	;
	
NonFuncDeclaration	
	:VarDec	';' {$$=$1;}
	|VarDec error ';'	{yyerror("error in non func decln stmt");}
	;
ExpressionStmt	
	:Expression ';'			{$$=$1;}
	|';'					{$$=empty(EMPTY);}
	|Expression error ';'	{yyerror("error in exp stmt");}
	|error ';'				{yyerror("error in empty stmt");}
	;
	
SelectionStmt	
	:IF '(' Expression ')' Stmt %prec IFX				{$$=make_node(IF,2,$3,$5);}
	|IF '(' Expression ')' Stmt ELSE Stmt				{$$=make_node(IF_ELSE,3,$3,$5,$7);}
	|SWITCH '(' Expression ')' '{' {seen_switch++;} CaseStmtList '}'		{$$=make_node(SWITCH,2,$3,$7);seen_switch--;}
	;

CaseStmtList 
	:CaseStmtList CaseStmt  DefaultStmt {$$=make_node(CASE_STMT_LIST,3,$1,$2,$3);}
	|CaseStmt { $$ = $1;}

CaseStmt	
	:CASE ConstExp ':' Stmt	{$$=make_node(CASE_STMT,2,$2,$4);}
	;

DefaultStmt
	:DEFAULT ':'	Stmt	{$$ = make_node(DEFAULT,1,$3);}
	|						{$$ = empty(EMPTY);/*empty production*/}
	;

IterationStmt	
	:WHILE '(' Expression ')' {seen_loop++;}Stmt			{$$ = make_node(WHILE, 2, $3, $6);seen_loop--;}
	;

BasicForStmt	
	:FOR '(' Expression ';' Expression ';' Expression ')' {seen_loop++;}Stmt {$$=make_node(FOR,4,$3,$5,$7,$10);seen_loop--;}
	;
	
ObjCreation	
	:NEW TypeName '(' Expression ')' {$$=make_node(NEW,2,$2,$4);}	
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
	:VAR IdList ':' Type {$$=make_node(VAR_DEC,2,$2,$4);dist_type($$);}
	|VAR IdList EQ NEW ARRAY '[' Type ']' '(' Expression ')'	
				{
					$$ = make_node(ARRAY,3,$2,$7,$10);
					dist_type($$);
					type_check_array($7);
				}
	|VAL IDENT	{	
					struct sym_record* s=install(yytext);
					$2 = make_id(s);
				}
	':' IDENT	
				{
					struct sym_record* s=search(current_st,yytext);
					if(s!=NULL && s->is_class==1)
					{
						$5 = make_id(s);
						$2->id.symrec->my_st = $5->id.symrec->my_st;
					}
					else
						yyerror("Instantiating something that is not a class");	
				}
	 EQ NEW IDENT 
				{
					struct sym_record* s=search(current_st,yytext);
					if(s!=NULL && s->is_class==1)
					{
						$9 = make_id(s);
					}
					else
						yyerror("Instantiating something that is not a class");	
				} 
	'(' InitExpList ')' 
	{
		type_check_obj($5,$9,$12);
		$$=make_node(OBJ,3,$2,$9,$12);
		debugger("Obj done\n");
	}
	;
	
InitExpList
	:conditional_Expression					{$$=$1;}
	|InitExpList ',' conditional_Expression	{$$=make_node(INITEXPLIST,2,$1,$3);}
	|										{$$=empty(EMPTY);}	
	;	
Type	
	:TYPE_INT	{$$=con_i(MY_INT);}	
	|TYPE_FLOAT	{$$=con_i(MY_FLOAT);}
	|TYPE_CHAR	{$$=con_i(MY_CHAR);}
	|TYPE_BOOL	{$$=con_i(MY_BOOL);}
	|TYPE_VOID	{$$=con_i(MY_VOID);}
	;
IdList	
	:IDENT				{struct sym_record* s=install(yytext);$$=make_id(s);}
	|IdList ',' IDENT 	{
							struct sym_record* s=install(yytext);
							$3 = make_id(s);
							$$=make_node(ID_LIST,2,$1,$3);
						}
	;
primary_Expression	
	:IDENT			{
						struct sym_record* s =search(current_st,yytext);
						if(s==NULL)
						{
							yyerror("Identifier used before declaration");
						}
						else						
						{
							$$=make_id(s);
						}	
					}
	|ConstExp				{$$=$1;}
	|'(' Expression ')' 	{$$=$2;}
	;
ConstExp	
	:INTEGER	{$$=con_i($1);debugger("INTEGER VAL SEEN %d\n",$1);}
	|FLOAT		{$$=con_f($1);debugger("FLOAT VAL SEEN %lf\n",$1);}
	|CHAR		{$$=con_c($1);}
	|TRUE		{$$=con_b(1);}	
	|FALSE		{$$=con_b(0);}	
	;

Expression
	:assignment_Expression		{$$=$1;}
	|Expression ',' assignment_Expression  {$$=make_node(EXP_LIST,2,$1,$3);}
	|ObjCreation
	;

assignment_Expression	
	:conditional_Expression		{$$=$1;}
	|unary_Expression AssOp assignment_Expression	{
													$$=make_node(ASSIGN,3,$1,$2,$3) ;
													type_check_assign($$,$1,$3);
													}
	;

conditional_Expression	
	:logical_or_Expression	{$$=$1;}
	|logical_or_Expression QM Expression ':' conditional_Expression	{$$=make_node(TERNARY,3,$1,$3,$5);type_check_ternary($$,$1,$3,$5);}
	;

logical_or_Expression	
	:logical_and_Expression	{$$=$1;}
	|logical_or_Expression BOOL_OR logical_and_Expression	{$$=make_node(BOOL_OR,2,$1,$3);type_check_bool($$,$1,$3);}
	;

logical_and_Expression
	:inclusive_or_Expression	{$$=$1;}
	|logical_and_Expression BOOL_AND inclusive_or_Expression	{$$=make_node(BOOL_AND,2,$1,$3);type_check_bool($$,$1,$3);}
	;

inclusive_or_Expression
	:exclusive_or_Expression	{$$=$1;}
	|inclusive_or_Expression BIT_OR exclusive_or_Expression		{$$=make_node(BIT_OR,2,$1,$3);type_check_int($$,$1,$3);}
	;

exclusive_or_Expression
	:and_Expression	{$$=$1;}
	|exclusive_or_Expression XOR and_Expression	{$$=make_node(XOR,2,$1,$3);type_check_int($$,$1,$3);}
	;

and_Expression
	:equality_Expression	{$$=$1;}
	|and_Expression BIT_AND equality_Expression	{$$=make_node(BIT_AND,2,$1,$3);type_check_int($$,$1,$3);}
	;

equality_Expression
	:relational_Expression		{$$=$1;}	
	|equality_Expression BOOL_EQ relational_Expression	{$$=make_node(BOOL_EQ,2,$1,$3);type_check_booleq($$,$1,$3);}
	|equality_Expression NEQ relational_Expression		{$$=make_node(NEQ,2,$1,$3);type_check_booleq($$,$1,$3);}
	;

relational_Expression
	:shift_Expression	{$$=$1;}
	|relational_Expression LT shift_Expression	{$$=make_node(LT,2,$1,$3);type_check_rel($$,$1,$3);}
	|relational_Expression GT shift_Expression	{$$=make_node(GT,2,$1,$3);type_check_rel($$,$1,$3);}
	|relational_Expression LE shift_Expression	{$$=make_node(LE,2,$1,$3);type_check_rel($$,$1,$3);}
	|relational_Expression GE shift_Expression	{$$=make_node(GE,2,$1,$3);type_check_rel($$,$1,$3);}
	;

shift_Expression
	:additive_Expression						{$$ = $1;}
	|shift_Expression LSH additive_Expression	{$$=make_node(LSH,2,$1,$3);type_check_shift($$,$3);}
	|shift_Expression RSH additive_Expression	{$$=make_node(RSH,2,$1,$3);type_check_shift($$,$3);}
	;

additive_Expression
	:multiplicative_Expression								{$$ = $1;}
	|additive_Expression PLUS multiplicative_Expression		{$$=make_node(PLUS,2,$1,$3);type_check_addmult($$,$1,$3);}
	|additive_Expression MINUS multiplicative_Expression	{$$=make_node(MINUS,2,$1,$3);type_check_addmult($$,$1,$3);}
	;

multiplicative_Expression
	:cast_Expression									{$$ = $1;}
	|multiplicative_Expression MULT cast_Expression	{$$=make_node(MULT,2,$1,$3);type_check_addmult($$,$1,$3);}
	|multiplicative_Expression DIV cast_Expression		{$$=make_node(DIV,2,$1,$3);type_check_division($$,$1,$3);}
	|multiplicative_Expression MODULO cast_Expression	{$$=make_node(MODULO,2,$1,$3);type_check_modulo($$,$1,$3);}
	;

cast_Expression
	:unary_Expression
	;

unary_Expression
	:postfix_Expression					{$$=$1;}
	|PP unary_Expression				{$$=make_node(PREFIX,2,con_i(MY_PP),$2);type_check_prepostfix($$,$2);}
	|MM unary_Expression				{$$=make_node(PREFIX,2,con_i(MY_MM),$2);type_check_prepostfix($$,$2);}
	|unary_operator cast_Expression		{$$=make_node(CAST,2,$1,$2);type_check_cast($$,$2);}
	;
postfix_Expression
	:primary_Expression				{$$ = $1;}
	|postfix_Expression '[' Expression ']'
										{
											$$=make_node(ARRAY_INVOC,2,$1,$3);
											type_check_array_invoc($$,$1,$3);
										}
	|postfix_Expression '('ArgExpList ')'		
										{
											$$=make_node(INVOC,2,$1,$3);
											type_check_invoc($$,$1,$3);
										}
	|postfix_Expression '(' ')'				
										{
											$$=make_node(INVOC,2,$1,empty(EMPTY));
											type_check_invoc($$,$1,empty(EMPTY));
										}
	|postfix_Expression '.' IDENT 	{
										struct sym_record* s=search($1->id.symrec->my_st,yytext);
										
										if(s==NULL)
										{
											yyerror("field not valid");
											
										}
										else
										{
											$3=make_id(s);
										
											if(s->is_proc_name==1)
											{
												$3->id.symrec->is_field=0;
											}
											else
											{
												$3->id.symrec->is_field=1;
											}	
											$$=make_node(FIELD,2,$1,$3);
											$$->opr.datatype = s->type;
										}
									}
	|THIS '.' IDENT 				{
										struct sym_record* s=search(current_st,yytext);
										
										if(s==NULL)
										{
											yyerror("field not valid");
											
										}
										else
										{
											$3=make_id(s);
										
											if(s->is_proc_name==1)
											{
												$3->id.symrec->is_field=0;
											}
											else
											{
												$3->id.symrec->is_field=1;
											}	
											$$=make_node(FIELD,2,con_i(THIS),$3);
											$$->opr.datatype = s->type;
										}
									}																
	|postfix_Expression PP			
									{
										$$=make_node(POSTFIX,2,$1,con_i(MY_PP));
										type_check_prepostfix($$,$1);
									}
	|postfix_Expression MM			{
										$$=make_node(POSTFIX,2,$1,con_i(MY_MM));
										type_check_prepostfix($$,$1);
									}
	;

ArgExpList
	:conditional_Expression	{$$=$1;}
	|ArgExpList ',' conditional_Expression	{$$=make_node(ARGEXPLIST,2,$1,$3);}
	;
unary_operator
	:PLUS		{$$=con_i(MY_PLUS);}
	|MINUS		{$$=con_i(MY_MINUS);}
	;


%%
int main(int argc, char** argv)
{
	char x10file[50];
		
	if(argc < 3)		// something is wrong
	{
		debugger("INCORRECT USAGE\n");
		return 0;
	}
	int i,create_exe=0;
	
	for(i=1;i<argc;i++)
	{
		if(i==1)
		{
			out_file=strdup(argv[1]);						// filename without extension
		}
		if(i==2)
		{
			strcpy(x10file,argv[2]);
			freopen(x10file,"r",stdin);	
		}
		if(strcmp(argv[i],"debug")==0)
		{
			debug_flag=1;
		}
		if(strcmp(argv[i],"-x")==0)
		{
			create_exe=1;
		}
	}

	yyparse();
	
	if(seen_main!=1)
	{
		if(seen_main==0)
			yyerror("no main function found");
		else
			yyerror("multiple main definitions");	
	}
	
	if(error_found==0)
	{
		output=fopen(strcat(argv[1],".il"),"w");		// create il file
		print_header();
		generate(root);
		fclose(output);
	
		if(create_exe==1)			// 
		{
		
			// following code runs ilasm 
			char assembler[20]="ilasm ";
			strcat(assembler,argv[1]);
			system(assembler);
		}
	}	
	
	fclose(stdin);
	
	return 0;
	
}


void yyerror (char *s) /* Called by yyparse on error */
{
	error_found=1;
	printf("x-10 compiler:%d:%d:%s at %s  \n",yyline_no,yycolumn-yyleng,s,yytext);
}







	

