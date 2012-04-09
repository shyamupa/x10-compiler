#include "generate_function.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern int in_assign;
extern int seen_bool_flow;
extern FILE* output;
int generate(nodeType *n)
{
	//printf("GENERATE BEGINS\n");
	char* _code;
	if(!n) 
	{
		printf("Empty Node\n");
		return ;
	}	
	switch(n->type)
	{
		case typeConI:
			printf("ldc.i4 %d \n",n->con_i.value);
			fprintf(output,"ldc.i4 %d \n",n->con_i.value);
			break;
		case typeConC:
			printf("ldc.i4 %c \n",n->con_c.value);
			fprintf(output,"ldc.i4 %c \n",n->con_c.value);
			break;
		case typeConF:
			printf("ldc.i4 %lf \n",n->con_f.value);
			fprintf(output,"ldc.i4 %lf \n",n->con_f.value);
			break;
		case typeConB:
			if(seen_bool_flow == 0)
			{
			printf("ldc.i4 %d \n",n->con_b.value);
			fprintf(output,"ldc.i4 %d \n",n->con_b.value);
			}
			else
			{	
				if(n->con_b.value == 1)
				{
					printf("br.s %s \n",get_T(n));
					fprintf(output,"br.s %s \n",get_T(n));
				}
				else
				{
					printf("br.s %s \n",get_F(n));
					fprintf(output,"br.s %s \n",get_F(n));
				}
			}
			break;	
		case typeId:
			if(n->id.symrec->formal != 1)
			{
			printf("ldloc %s \n",n->id.symrec->uid);
			fprintf(output,"ldloc %s \n",n->id.symrec->uid);
			}
			else
			{
				printf("ldarg %s \n",n->id.symrec->uid);
				fprintf(output,"ldarg %s \n",n->id.symrec->uid);
				
			}	
			break;
		case typeOpr:
			switch(n->opr.oper)
			{
				case ARRAY:
							printf("Matched ARRAY\n");
							ir_array_declaration(n);
							break;
				case ARRAY_INVOC:
							printf("Matched ARRAY_INVOC 1\n");
							ir_array_rhs(n);
							break;
							
				case ASYNC:
							printf("Matched ASYNC\n");
							ir_asynch_list(n);
							break;
				case ARGEXPLIST:
							printf("MATCHED ARGEXPLIST\n");
							ir_explist(n);
							break;	
				case ASSIGN:
							printf("MATCHED ASSIGN\n");
							in_assign=1;
							ir_assign(n);
							in_assign =0;
							break;
			
				case BOOL_OR:
							printf("Matched BOOL_OR\n");
							if(in_assign==1)
								ir_bool(n);
							else
							{
								seen_bool_flow = 1;
								ir_bool_flow(n);
								seen_bool_flow = 0;
							}		
							break;
				case BOOL_AND:
							printf("Matched BOOL_AND\n");
							if(in_assign==1)
								ir_bool(n);
							else
							{
								seen_bool_flow = 1;
								ir_bool_flow(n);
								seen_bool_flow = 0;
							}		
							break;
				case BOOL_EQ:
							printf("Matched BOOL_EQ\n");
							if(in_assign==1)
								ir_bool(n);
							else
							{
								seen_bool_flow = 1;
								ir_bool_flow(n);
								seen_bool_flow = 0;
							}		
							break;
				case BIT_OR:
							printf("Matched BIT_OR\n");
							ir_arithmetic(n);
							break;
				case BIT_AND:
							printf("Matched BIT_AND\n");
							ir_arithmetic(n);
							break;
				case BREAK:
							printf("Matched BREAK\n");
							ir_break(n);
							break;
				case CAST:
							printf("Matched CAST\n");
							ir_cast(n);
							break;
				case CONTINUE:
							printf("Matched CONTINUE\n");
							break;
				case CLASSLIST:
							printf("Matched CLASSLIST\n");
							ir_class_decln_list(n);
							break;
				case CLASS:
							 printf("Matched CLASS\n");
							ir_class_decln(n);
							break;
				case COMPOUND:
							 printf("Matched COMPOUND\n");
							ir_compound_stmt(n);
							break;
				
				case DIV:
							printf("Matched DIV\n");
							ir_arithmetic(n);
							break;
				case EMPTY:
							 printf("Matched EMPTY\n");
							break;
				case EXP_LIST:
							ir_explist(n);
							break;
				case FUNC_DEF_LIST:
							 printf("Matched FUNC_DEF_LIST\n");
							ir_fun_def_list(n);
							break;
				case FUNC:
							printf("Matched FUNC\n");
							ir_fun_def(n);
							fflush(stdout);
							break;
				case FORMAL_ARG_LIST:
							 printf("Matched FORMAL_ARG_LIST\n");
							 break;

				case FORMAL_ARG:
							 printf("Matched FORMAL_ARG\n");
							 break;
						 
				case SWITCH :
							 printf("Matched SWITCH\n");
							 ir_switch(n);
							 break;
				case CASE_STMT:
							 printf("Matched CASE_STMT\n");
							 ir_case_stmt(n);
							 break;
				case CASE_STMT_LIST:
							printf("Matched CASE_STMT_LIST\n");
							ir_case_stmt_list(n);
							break;
				case DEFAULT:
							printf("Matched DEFAULT\n");
							ir_default_stmt(n);					
							break;
				case FOR:
							printf("MATCHED FOR\n");
							ir_for(n);
							break;			
				case GT:
							printf("Matched GT\n");
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							break;
				case GE:
							printf("Matched GE\n");
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							break;
				case IF:
							printf("MATCHED IF\n");
							ir_if(n);
							break;
				case IF_ELSE:
							printf("MATCHED IF_ELSE\n");
							ir_if_else(n);
							break;	
				case ID_LIST:
							 printf("Matched ID_LIST\n");
							 ir_idlist(n);
							 printf("%s",_code);
							 break;
				case INVOC:
							printf("Matched INVOC\n");
							ir_fun_invoc(n);
							break;
				case LT:
							printf("Matched LT\n");
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							break;
				case LE:
							printf("Matched LE\n");
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							break;
				case LSH:
							printf("Matched LSH\n");
							ir_arithmetic(n);
							break;
				case MINUS:
							printf("Matched MINUS\n");
							ir_arithmetic(n);
							break;
				case MULT:
							printf("Matched MULT\n");
							ir_arithmetic(n);
							break;
				case NEQ:
							printf("Matched BOOL_NEQ\n");
							if(in_assign==1)
								ir_bool(n);
							else
							{
								seen_bool_flow = 1;
								ir_bool_flow(n);
								seen_bool_flow = 0;
							}		
							break;
				case PLUS:
							printf("Matched PLUS\n");
							ir_arithmetic(n);
							break;
				case POSTFIX:
							printf("Matched POSTFIX\n");
							ir_postfix(n);
							break;
				case PREFIX:
							printf("Matched PREFIX\n");
							ir_prefix(n);
							break;
				case RETURN:
							printf("Matched RETURN\n");
							ir_return(n);
							break;
				case RSH:
							printf("Matched RSH\n");
							ir_arithmetic(n);
							break;
			
				
				case STMT_LIST:
							 printf("MAtched STMT_LIST\n");		
							 ir_stmtlist(n);
							 break;
				case TERNARY:
							//_code=strdup(ir_ternary(n));
							break;
				case VAR_DEC:
							 printf("Matched VAR_DEC\n");
							 ir_var_dec(n);
							 break;
				case WHILE:
							printf("MATCHED WHILE\n");
							ir_while(n);
							break;	
				case XOR:
							printf("Matched XOR\n");
							ir_arithmetic(n);
							break;
						
				default :
					printf("entered default\n"); 
		}
			break;
		default:
			printf("entered DEFAULT\n");
	}
}	
