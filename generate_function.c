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
	if(n==NULL) 				// empty node found
	{
		debugger("Empty Node\n");
		return ;
	}	
	switch(n->type)
	{
		case typeConI:				// integer node just load values onto stack
			debugger("ldc.i4 %d \n",n->con_i.value);
			fprintf(output,"ldc.i4 %d \n",n->con_i.value);
			break;
		case typeConC:				// char node just load values onto stack,char repr by int values for now
			debugger("ldc.i4 %c \n",n->con_c.value);
			fprintf(output,"ldc.i4 %c \n",n->con_c.value);
			break;
		case typeConF:				// float value GIGLAMESH
			debugger("ldc.r4 %lf \n",n->con_f.value);
			fprintf(output,"ldc.r4 %lf \n",n->con_f.value);
			break;
		case typeConB:
			if(seen_bool_flow == 0)				// not in bool flow so must be used in assign expr
			{
			debugger("ldc.i4 %d \n",n->con_b.value);
			fprintf(output,"ldc.i4 %d \n",n->con_b.value);
			}
			else 								// inside bool flow expr so handle T F labels
			{	
				if(n->con_b.value == 1)			// value is true so branch to true label
				{
					debugger("br.s %s \n",get_T(n));
					fprintf(output,"br.s %s \n",get_T(n));
				}
				else        					// value is false so branch to false label
				{
					debugger("br.s %s \n",get_F(n));
					fprintf(output,"br.s %s \n",get_F(n));
				}
			}
			break;	
		case typeId:
			debugger("Matched typeId\n");
			debugger("Prepost Flag is %d\n",prepost_put);
			if(n->id.symrec->is_field==1)
			{
				debugger("ldarg.0 \n");			// will be called only when inside constr
				fprintf(output,"ldarg.0 \n");
			}
			print_load_var(n);				// load the value stored in the identifier
            if(seen_bool_and_or == 1 || seen_bool_flow == 1 )
            {
                    debugger("brfalse %s\n",get_F(n));
                    fprintf(output,"brfalse %s\n",get_F(n));
                    debugger("br %s\n",get_T(n));
                    fprintf(output,"br %s\n",get_T(n));
            }
			debugger("Prepost Flag is %d\n",prepost_put);
            break;
		case typeOpr:
			switch(n->opr.oper)
			{
				case ARRAY:
							debugger("Matched ARRAY\n");
							ir_array_declaration(n);
							break;
				case ARRAY_INVOC:
							debugger("Matched ARRAY_INVOC 1\n");
							ir_array_rhs(n);
							break;
							
				case ASYNC:
							debugger("Matched ASYNC\n");
							ir_async(n);
							break;
							
				case ASYNC_LIST:
							debugger("Matched ASYNC_LIST\n");
							ir_async_stmt_list(n);
							break;
										
				case ARGEXPLIST:
							debugger("MATCHED ARGEXPLIST\n");
							ir_explist(n);
							break;	
				case ASSIGN:
							debugger("MATCHED ASSIGN\n");
							in_assign=1;
							//~ prepost_put = 1;			// set assign flag and prepost flag
							ir_assign(n);
							in_assign =0;
							//~ prepost_put = 0;			// reset assign flag and prepost flag
							break;
			
				case BOOL_OR:
							debugger("Matched BOOL_OR\n");
							if(in_assign==1)						// call normal expr like eval if in assign stmt	
								ir_bool(n);
							else  									// not in assign means inside bool flow
							{
								ir_bool_flow(n);
							}		
							break;
				case BOOL_AND:
							debugger("Matched BOOL_AND\n");
							if(in_assign==1)
								ir_bool(n);
							else 							// not in assign means inside bool flow
							{
								ir_bool_flow(n);
							}		
							break;
				case BOOL_EQ:
							debugger("Matched BOOL_EQ\n");
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
							debugger("Matched BIT_OR\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case BIT_AND:
							debugger("Matched BIT_AND\n");
							//~ prepost_put = 1;
							ir_arithmetic(n);
							//~ prepost_put = 0;
							break;
				case BREAK:
							debugger("Matched BREAK\n");
							ir_break(n);
							break;
				case CAST:
							debugger("Matched CAST\n");
							ir_cast(n);
							break;
				case CONTINUE:										// GIGLAMESH
							debugger("Matched CONTINUE\n");
							ir_continue(n);
							break;
				case CLASSLIST:
							debugger("Matched CLASSLIST\n");
							ir_class_decln_list(n);
							break;
				case CLASS:
							debugger("Matched CLASS\n");
							ir_class_decln(n);
							break;
				case COMPOUND:
							debugger("Matched COMPOUND\n");
							ir_compound_stmt(n);
							break;
				
				case DIV:
							debugger("Matched DIV\n");
							ir_arithmetic(n);
							break;
				case EMPTY:										// GIGLAMESH
							debugger("Matched EMPTY\n");
							break;
				case EXP_LIST:
							ir_explist(n);
							break;
				case FINISH:
							debugger("Matched finish\n");
							ir_finish(n);
							break;		
				case FUNC_DEF_LIST:
							 debugger("Matched FUNC_DEF_LIST\n");
							ir_fun_def_list(n);
							break;
				case FIELD:					// will enter here only when field is used as rval like a=obj.fval+1
							debugger("Matched FIELD\n");
							print_load_var(n);			// to load field of obj
							break;
				case FUNC:
							debugger("Matched FUNC\n");
							ir_fun_def(n);
							fflush(stdout);
							break;
				case FORMAL_ARG_LIST:									// GIGLAMESH
							debugger("Matched FORMAL_ARG_LIST\n");
							break;
				case FORMAL_ARG:
							debugger("Matched FORMAL_ARG\n");
							break;
				case SWITCH:
							debugger("Matched SWITCH\n");
							ir_switch(n);
							 break;
				case CASE_STMT:
							 debugger("Matched CASE_STMT\n");
							 ir_case_stmt(n);
							 break;
				case CASE_STMT_LIST:
							debugger("Matched CASE_STMT_LIST\n");
							ir_case_stmt_list(n);
							break;
				case DEFAULT:
							debugger("Matched DEFAULT\n");
							ir_default_stmt(n);					
							break;
				case FOR:
							debugger("MATCHED FOR\n");
							ir_for(n);
							break;			
				case GT:
							debugger("Matched GT\n");
							//~ prepost_put = 1;				
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							//~ prepost_put = 0;
							break;
				case GE:
							debugger("Matched GE\n");
							//~ prepost_put = 1;
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							//~ prepost_put = 0;
							break;
				case IF:
							debugger("MATCHED IF\n");
							ir_if(n);
							break;
				case IF_ELSE:
							debugger("MATCHED IF_ELSE\n");
							ir_if_else(n);
							break;	
				case ID_LIST:
							 debugger("Matched ID_LIST\n");
							 ir_idlist(n);
							 break;
				case INVOC:
							debugger("Matched INVOC\n");
							ir_fun_invoc(n);
							break;
				case LT:
							debugger("Matched LT\n");
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							break;
				case LE:
							debugger("Matched LE\n");
							if(in_assign==0)
								ir_relop_flow(n);
							else
								ir_relop(n);
							break;
				case LSH:
							debugger("Matched LSH\n");
							ir_arithmetic(n);
							break;
				case MINUS:
							debugger("Matched MINUS\n");
							ir_arithmetic(n);
							break;
				case MULT:
							debugger("Matched MULT\n");
							ir_arithmetic(n);
							break;
				case MODULO:
							debugger("Matched MODULO\n");
							ir_arithmetic(n);
							break;
				case METHOD_INVOC:
							debugger("Matched METHOD INVOC\n");
							ir_method_invoc(n);
							break;			
				case NEQ:
							debugger("Matched BOOL_NEQ\n");
							if(in_assign==1)
								ir_bool(n);
							else
							{
								ir_bool_flow(n);
							}
							break;
				case OBJ:
							debugger("Matched OBJECT\n");
							ir_obj(n);
							break;				
				case PLUS:
							debugger("Matched PLUS\n");
							ir_arithmetic(n);
							break;
				case POSTFIX:
							debugger("Matched POSTFIX\n");
							ir_postfix(n);
							break;
				case PREFIX:
							debugger("Matched PREFIX\n");
							ir_prefix(n);
							break;
				case RETURN:
							debugger("Matched RETURN\n");
							ir_return(n);
							break;
				case RSH:
							debugger("Matched RSH\n");
							ir_arithmetic(n);
							break;
			
				
				case STMT_LIST:
							 debugger("MAtched STMT_LIST\n");		
							 ir_stmtlist(n);
							 break;
				case TERNARY:
							debugger("MAtched Ternary\n");
							in_assign = 0;		
							ir_ternary(n);
							in_assign = 1;
							break;
				case VAR_DEC:
							 debugger("Matched VAR_DEC\n");
							 ir_var_dec(n);
							 break;
				case WHILE:
							debugger("MATCHED WHILE\n");
							ir_while(n);
							break;	
				case XOR:
							debugger("Matched XOR\n");
							ir_arithmetic(n);
							break;
				case INITEXPLIST:
							debugger("Matched INITEXPLIST\n");
							ir_explist(n);
							break;				
				default :
					debugger("entered default\n"); 
		}
			break;
		default:
			debugger("entered DEFAULT\n");
	}
}	
