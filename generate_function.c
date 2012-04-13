#include "generate_function.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern int in_assign;
extern int seen_bool_flow;
extern int seen_bool_and_or;
extern int prepost_put;
extern FILE* output;
int generate(nodeType *n)
{
	char* _code;			// UNUSED
	if(!n) 				// empty node found
	{
		printf("Empty Node\n");
		return ;
	}	
	switch(n->type)
	{
		case typeConI:				// integer node just load values onto stack
			printf("ldc.i4 %d \n",n->con_i.value);
			fprintf(output,"ldc.i4 %d \n",n->con_i.value);
			break;
		case typeConC:				// char node just load values onto stack,char repr by int values for now
			printf("ldc.i4 %c \n",n->con_c.value);
			fprintf(output,"ldc.i4 %c \n",n->con_c.value);
			break;
		case typeConF:				// float value GIGLAMESH
			printf("ldc.r4 %lf \n",n->con_f.value);
			fprintf(output,"ldc.r4 %lf \n",n->con_f.value);
			break;
		case typeConB:
			if(seen_bool_flow == 0)				// not in bool flow so must be used in assign expr
			{
			printf("ldc.i4 %d \n",n->con_b.value);
			fprintf(output,"ldc.i4 %d \n",n->con_b.value);
			}
			else 								// inside bool flow expr so handle T F labels
			{	
				if(n->con_b.value == 1)			// value is true so branch to true label
				{
					printf("br.s %s \n",get_T(n));
					fprintf(output,"br.s %s \n",get_T(n));
				}
				else        					// value is false so branch to false label
				{
					printf("br.s %s \n",get_F(n));
					fprintf(output,"br.s %s \n",get_F(n));
				}
			}
			break;	
		case typeId:
			printf("Matched typeId\n");
			printf("Prepost Flag is %d\n",prepost_put);
			if(n->id.symrec->is_field==1)
			{
				printf("ldarg.0 \n");			// will be called only when inside constr
				fprintf(output,"ldarg.0 \n");
			}
			print_load_var(n);				// load the value stored in the identifier
            if(seen_bool_and_or == 1 || seen_bool_flow == 1 )
            {
                    printf("brfalse %s\n",get_F(n));
                    fprintf(output,"brfalse %s\n",get_F(n));
                    printf("br %s\n",get_T(n));
                    fprintf(output,"br %s\n",get_T(n));
            }
			printf("Prepost Flag is %d\n",prepost_put);

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
							ir_async(n);
							break;
							
				case ASYNC_LIST:
							printf("Matched ASYNC_LIST\n");
							ir_async_stmt_list(n);
							break;
										
				case ARGEXPLIST:
							printf("MATCHED ARGEXPLIST\n");
							ir_explist(n);
							break;	
				case ASSIGN:
							printf("MATCHED ASSIGN\n");
							in_assign=1;
							//~ prepost_put = 1;			// set assign flag and prepost flag
							ir_assign(n);
							in_assign =0;
							//~ prepost_put = 0;			// reset assign flag and prepost flag
							break;
			
				case BOOL_OR:
							printf("Matched BOOL_OR\n");
							if(in_assign==1)						// call normal expr like eval if in assign stmt	
								ir_bool(n);
							else  									// not in assign means inside bool flow
							{
								ir_bool_flow(n);
							}		
							break;
				case BOOL_AND:
							printf("Matched BOOL_AND\n");
							if(in_assign==1)
								ir_bool(n);
							else 							// not in assign means inside bool flow
							{
								ir_bool_flow(n);
							}		
							break;
				case BOOL_EQ:
							printf("Matched BOOL_EQ\n");
							if(in_assign==1)
								ir_bool(n);
							else 								// not in assign means inside bool flow
							{
								//~ prepost_put = 1;
								ir_bool_flow(n);
								//~ prepost_put = 0;
							}		
							break;
				case BIT_OR:
							printf("Matched BIT_OR\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case BIT_AND:
							printf("Matched BIT_AND\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case BREAK:
							printf("Matched BREAK\n");
							ir_break(n);
							break;
				case CAST:
							printf("Matched CAST\n");
							ir_cast(n);
							break;
				case CONTINUE:										// GIGLAMESH
							printf("Matched CONTINUE\n");
							ir_continue(n);
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
				case EMPTY:										// GIGLAMESH
							printf("Matched EMPTY\n");
							break;
				case EXP_LIST:
							ir_explist(n);
							break;
				case FINISH:
							printf("Matched finish\n");
							ir_finish(n);
							break;		
				case FUNC_DEF_LIST:
							 printf("Matched FUNC_DEF_LIST\n");
							ir_fun_def_list(n);
							break;
				case FIELD:					// will enter here only when field is used as rval like a=obj.fval+1
							printf("Matched FIELD\n");
							print_load_var(n);			// to load field of obj
							break;
				case FUNC:
							printf("Matched FUNC\n");
							ir_fun_def(n);
							fflush(stdout);
							break;
				case FORMAL_ARG_LIST:									// GIGLAMESH
							printf("Matched FORMAL_ARG_LIST\n");
							break;
				case FORMAL_ARG:
							printf("Matched FORMAL_ARG\n");
							break;
				case SWITCH:
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
							//~ prepost_put = 1;				
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							//~ prepost_put = 0;
							break;
				case GE:
							printf("Matched GE\n");
							//~ prepost_put = 1;
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							//~ prepost_put = 0;
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
							//~ prepost_put = 1;
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							//~ prepost_put = 0;
							break;
				case LE:
							printf("Matched LE\n");
							//~ prepost_put = 1;
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							//~ prepost_put = 0;
							break;
				case LSH:
							printf("Matched LSH\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case MINUS:
							printf("Matched MINUS\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case MULT:
							printf("Matched MULT\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case MODULO:
							printf("Matched MODULO\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case METHOD_INVOC:
							printf("Matched METHOD INVOC\n");
							ir_method_invoc(n);
							break;			
				case NEQ:
							printf("Matched BOOL_NEQ\n");
							//~ prepost_put = 1;
							if(in_assign==1)
								ir_bool(n);
							else
							{
								ir_bool_flow(n);
							}
							//~ prepost_put = 0;		
							break;
				case OBJ:
							printf("Matched OBJECT\n");
							ir_obj(n);
							break;				
				case PLUS:
							printf("Matched PLUS\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
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
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
			
				
				case STMT_LIST:
							 printf("MAtched STMT_LIST\n");		
							 ir_stmtlist(n);
							 break;
				case TERNARY:
							printf("MAtched Ternary\n");
							in_assign = 0;		
							ir_ternary(n);
							in_assign = 1;
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
				case INITEXPLIST:
							printf("Matched INITEXPLIST\n");
							ir_explist(n);
							break;				
				default :
					printf("entered default\n"); 
		}
			break;
		default:
			printf("entered DEFAULT\n");
	}
}	
