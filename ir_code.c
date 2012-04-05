#include "ir_code.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern int generate(nodeType *n);

int main_found=0;
int main_was_found=0;
int in_assign=0;
// Working correctly
char* ir_class_decln(nodeType* n)
{
	nodeType* mod=get_operand(n,0);
	nodeType* class_name=get_operand(n,1);
	nodeType* body=get_operand(n,2);
	printf(".class ");
	switch(mod->con_i.value)
	{
		case modPUBLIC:
				printf("public "); 
				break;
		case modPRIVATE:
				printf("private "); 
				break;
		case modPROTECTED:
				printf("protected "); 
				break;				
	}
	printf("auto ansi beforefieldinit "); 
	printf("%s ",class_name->id.symrec->sym_name);
	printf("extends [mscorlib]System.Object\n");
	printf("{\n");
    printf(".method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed \n");
    printf("{\n");
	printf("\t.maxstack 8\n");
	printf("\tldarg.0\n");
	printf("\tcall instance void object::'.ctor'()\n");
	printf("\tret\n"); 
    	printf("}\n");
	generate(body);
	printf("}\n");
}
// Working correctly
char* ir_class_decln_list(nodeType* n)
{
	nodeType* class_decln_list = get_operand(n,0);
	nodeType* class_decln = get_operand(n,1);
	generate(class_decln_list);
	if(n->opr.oper == CLASSLIST)
		{
		generate(class_decln);
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s", get_code(class_decln_list), get_code(class_decln));
		}
	else
		{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s", get_code(class_decln_list));
		}
	n->opr.code = strdup(buffer);
	return buffer;
}
// Working correctly
char* ir_fun_def_list(nodeType* n)
{
	nodeType* fun_def_list = get_operand(n,0);
	nodeType* fun_def = get_operand(n,1);
	generate(fun_def_list);
	if(n->opr.oper == FUNC_DEF_LIST)
		{
		generate(fun_def);
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s", get_code(fun_def_list), get_code(fun_def));
		}
	else
		{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s", get_code(fun_def_list));
		}
	n->opr.code = strdup(buffer);
	return buffer;
	
}
void ir_compound_stmt(nodeType* n)
{
	
	if(main_found==1)
	{
		printf(" .entrypoint\n");
		main_found=0;
	}
	printf("{\n");
	generate(get_operand(n,0));
	printf("}\n");
}
void ir_assign(nodeType* n)
{
	nodeType* unary_exp = get_operand(n,0);
	nodeType* assop = get_operand(n,1);
	nodeType* ass_exp = get_operand(n,2);
	printf("ASSOP IS %d\n",ass_exp->opr.oper);
	in_assign=1;
	switch(assop->con_i.value)
	{
		case EQ:
			generate(ass_exp);
			printf("stloc %s\n",unary_exp->id.symrec->sym_name);
			break;
		case PLUS_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->sym_name);
			printf("add\n");
			printf("stloc %s",unary_exp->id.symrec->sym_name);
			break;
		case MINUS_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->sym_name);
			printf("sub\n");
			printf("stloc %s",unary_exp->id.symrec->sym_name);
			break;
		case MULT_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->sym_name);
			printf("mul\n");
			printf("stloc %s",unary_exp->id.symrec->sym_name);
			break;
		case DIV_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->sym_name);
			printf("div\n");
			printf("stloc %s",unary_exp->id.symrec->sym_name);
			break;
		default: printf("ASSOP DEFAULT\n");
	}
	in_assign=0;
}
// Rest working correctly
// NEED TO COMPLETE SHIFT OPERATIONS			
char* ir_arithmetic(nodeType* n)
{
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	generate(E2);
	switch(n->opr.oper)
	{
		case PLUS:
			printf("add\n");
			break;
		case MINUS:
			printf("sub\n");
			break;
		case MULT:
			printf("mul\n");
			break;
		case DIV:
			printf("div\n");
			break;
		case BIT_AND:
			printf("and\n");
			break;
		case BIT_OR:
			printf("or\n");
			break;
		case XOR:
			printf("xor\n");
			break;
		case LSH:
			//printf("xor\n");
			break;
		case RSH:
			//printf("xor\n");
			break;
		default:
			printf("arithmetic default\n");
	}
	n->opr.code = strdup(buffer);
	return(buffer);
}
void print_type(nodeType* n)
{
	switch(n->con_i.value)
	{
		case MY_INT:
			printf("int32 ");
			break;
		case MY_FLOAT:	
			printf("float32 ");
			break;
		case MY_CHAR:
			printf("char ");
			break;
		case MY_VOID:
			printf("void ");
			break;
		default:
			printf("IN DEFAULT OF PRINT RET TYPE\n");
	}
	return;
}
void print_formal_args(nodeType* n)
{
	if(n->opr.oper==EMPTY)
		return;
	nodeType* lc=get_operand(n,0);
	nodeType* rc=get_operand(n,1);
	nodeType* s;
	if(n->opr.oper==FORMAL_ARG)
	{
		print_type(get_operand(n,1));
		s=get_operand(n,0);
		printf(" %s ",s->id.symrec->sym_name); 
		return;
	}
	else
	{
		print_formal_args(lc);
		printf(",");
	}	
	print_formal_args(rc);
	return;
}
char* ir_fun_def(nodeType* n)
{
	
	nodeType* fun_name = get_operand(n,0);	
	nodeType* formal_arguments = get_operand(n,1);
	nodeType* return_type =get_operand(n,2);
	nodeType* compound =get_operand(n,3);
	// only static for time being
	printf(".method static ");
	
	print_type(return_type);
	printf("%s",fun_name->id.symrec->sym_name);
	if(strcmp(fun_name->id.symrec->sym_name,"main")==0)
	{
		main_found=1;
		main_was_found=1;
	}	
	printf("(");
	print_formal_args(formal_arguments);
	printf(") cil managed\n");
	generate(compound);
	return buffer;
}
void print_vardec_code(nodeType* Idlist,nodeType* Type)
{
	if(Idlist->type==typeId)
	{
		print_type(Type);
		printf(" %s ",Idlist->id.symrec->sym_name); 
		return;
	}
	else
	{
		nodeType* lc=get_operand(Idlist,0);
		nodeType* rc=get_operand(Idlist,1);
		print_vardec_code(lc,Type);
		printf(",");
		print_type(Type);
		printf(" %s ",rc->id.symrec->sym_name); 
	}	
	return;
}
void ir_var_dec(nodeType* n)
{
	nodeType* Idlist = get_operand(n,0);
	nodeType* Type = get_operand(n,1);
	printf(".locals init(");
	print_vardec_code(Idlist,Type);
	printf(")\n");
}
// NEED TO PUT FLAG FOR CONTROL FLOW AND EXPRESSION 
void ir_relop(nodeType* n)
{
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	generate(E2);
	switch(n->opr.oper)
	{
		case LT:
			printf("clt\n");
			break;
		case GT:
			printf("cgt\n");
			break;
		case LE:
			printf("cgt\n");
			printf("ldc.i4.0\n");
			printf("ceq\n");
			break;
		case GE:
			printf("clt\n");
			printf("ldc.i4.0\n");
			printf("ceq\n");
			break;
		default:
			printf("Relational default\n");
	}
}
// NEED TO TEST THIS ONCE
void ir_explist(nodeType* n)
{
	nodeType* exp=get_operand(n,0);
	nodeType* assexp=get_operand(n,1);
	generate(exp);
	generate(assexp);
}
////////////////////////////////////////////////////////////////////////
void ir_relop_flow(nodeType* n)
{

}
void ir_bool(nodeType* n)
{
	nodeType* B1 = get_operand(n,0);
	nodeType* B2 = get_operand(n,1);
	printf("HI SID\n");
	fflush(stdout);
	generate(B1);
	generate(B2);
	switch(n->opr.oper)
	{
		case NEQ:
			printf("ceq\n");
			printf("ldc.i4.0\n");
			printf("ceq\n");
			break;
		case BOOL_EQ:
			printf("ceq\n");
			break;
		case BOOL_OR:
			bzero(buffer,BUFFSIZE);
			B1->opr.T = get_T(n);
			B1->opr.F = strdup(newlabel());
			B2->opr.T = get_T(n);
			B2->opr.F = get_F(n);
			sprintf(buffer,"%s\n%s\n%s",get_code(B1),get_F(B1),get_code(B2));
			break;
		case BOOL_AND:
			bzero(buffer,BUFFSIZE);
			B1->opr.T = strdup(newlabel());
			B1->opr.F = get_F(n);
			B2->opr.T = get_T(n);
			B2->opr.F = get_F(n);
			sprintf(buffer,"%s\n%s\n%s",get_code(B1),get_T(B1),get_code(B2));
			break;
		default: printf("Bool DEFAULT\n");
	}
}
char* ir_bool_flow(nodeType* n)
{
	nodeType* B1 = get_operand(n,0);
	nodeType* B2 = get_operand(n,1);
	generate(B1);
	generate(B2);
	switch(n->opr.oper)
	{
	case NEQ:
		sprintf(buffer,"%s\n%s\n%s%s%s",get_code(B1), get_code(B2), get_place(B1), " != ", get_place(B2));
		break;
	case BOOL_EQ:
		sprintf(buffer,"%s\n%s\n%s%s%s",get_code(B1), get_code(B2), get_place(B1), " == ", get_place(B2));
		break;
	case BOOL_OR:
		bzero(buffer,BUFFSIZE);
		B1->opr.T = get_T(n);
		B1->opr.F = strdup(newlabel());
		B2->opr.T = get_T(n);
		B2->opr.F = get_F(n);
		sprintf(buffer,"%s\n%s\n%s",get_code(B1),get_F(B1),get_code(B2));
		break;
	case BOOL_AND:
		bzero(buffer,BUFFSIZE);
		B1->opr.T = strdup(newlabel());
		B1->opr.F = get_F(n);
		B2->opr.T = get_T(n);
		B2->opr.F = get_F(n);
		sprintf(buffer,"%s\n%s\n%s",get_code(B1),get_T(B1),get_code(B2));
		break;
	default: printf("Bool DEFAULT\n");
	}
	n->opr.code = strdup(buffer);
	return buffer;
	
}







char*  ir_idlist(nodeType* n)
{
	nodeType* Idlist = get_operand(n,0);
	nodeType* ident = get_operand(n,1);
	generate(Idlist);
	//~ printf("huhahuahuahauha\n");
	//no need to generate code for ident as it is generated during installation
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"%s\n%s", get_code(Idlist), get_code(ident));
	n->opr.code = strdup(buffer);
	return buffer;
}	

void  ir_stmtlist(nodeType* n)
{
	nodeType* Stmtlist = get_operand(n,0);
	nodeType* Stmt = get_operand(n,1);
	generate(Stmtlist);
	if(Stmtlist->opr.oper == STMT_LIST)
	{
		generate(Stmt);
	}
}
