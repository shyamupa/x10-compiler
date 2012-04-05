#include "generate_function.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern int in_assign;
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
			break;
		case typeConC:
			printf("ldc.i4 %c \n",n->con_c.value);
			break;
		case typeConF:
			printf("ldc.i4 %lf \n",n->con_f.value);
			break;
		case typeConB:
			printf("ldc.i4 %d \n",n->con_b.value);
			break;	
		case typeId: 
			printf("ldloc %s \n",n->id.symrec->sym_name);
			break;
		case typeOpr:
			switch(n->opr.oper)
			{
				case CLASSLIST:
					printf("Matched CLASSLIST\n");
					_code=strdup(ir_class_decln_list(n));
					printf("%s",_code);
					break;
				case CLASS:
					 printf("Matched CLASS\n");
					ir_class_decln(n);
					break;

				case FUNC_DEF_LIST:
					 printf("Matched FUNC_DEF_LIST\n");
					_code =strdup(ir_fun_def_list(n));
					 printf("%s",_code);
					//concat(CODE,_code);
					break;
				case COMPOUND:
					 printf("Matched COMPOUND\n");
					ir_compound_stmt(n);
					break;
				case FUNC:
					 printf("Matched FUNC\n");
					_code = strdup(ir_fun_def(n));
					printf("%s",_code);
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
					 ir_stmtlist(n);
					 break;
				case VAR_DEC:
					 printf("Matched VAR_DEC\n");
					 ir_var_dec(n);
					 break;
				case ID_LIST:
					 printf("Matched ID_LIST\n");
					 _code=strdup(ir_idlist(n));
					 printf("%s",_code);
					 break;
				case EMPTY:
					 printf("Matched EMPTY\n");
					break;
				case EXP_LIST:
					ir_explist(n);
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
					ir_assign(n);
					break;
			
				case BOOL_OR:
					printf("Matched BOOL_OR\n");
					if(in_assign==1)
						ir_bool(n);
					else
						ir_bool_flow(n);	
					break;
				case BOOL_AND:
					printf("Matched BOOL_AND\n");
					if(in_assign==1)
						ir_bool(n);
					else
						ir_bool_flow(n);
					break;
				case BOOL_EQ:
					printf("Matched BOOL_EQ\n");
					fflush(stdout);
					if(in_assign==1)
						ir_bool(n);
					else
						ir_bool_flow(n);
					break;
				case NEQ:
					printf("Matched BOOL_NEQ\n");
					if(in_assign==1)
						ir_bool(n);
					else
						ir_bool_flow(n);
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
					if(in_assign==0)
						ir_relop(n);
					else
						ir_relop(n);	
					break;
				case GT:
					printf("Matched GT\n");
					ir_relop(n);
					break;
				case LE:
					printf("Matched LE\n");
					ir_relop(n);
					break;
				case GE:
					printf("Matched GE\n");
					ir_relop(n);
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
