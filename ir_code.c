#include "ir_code.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern int generate(nodeType *n);

int main_found=0;
int main_was_found=0;
/* make a global flag for assgn bool 
 * make a function get_operator which retireives operator if node of oper type else returns false
 * in ir_assign chcek oper of assexp(which is right_child)using the above func 
 * if operator is BOOL_AND||BOOL_OR||BOOLEQ etc then send the unaryexp.place to new func boolarithm
 * in boolarithm put SIR's grammar
 * 
*/
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
char* ir_explist(nodeType* N)
{
	nodeType* exp=get_operand(N,0);
	nodeType* assexp=get_operand(N,1);
	generate(exp);
	generate(assexp);
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"%s\n%s", get_code(exp), get_code(assexp));
	return(buffer);
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
char* ir_assign(nodeType* N)
{
	nodeType* unary_exp = get_operand(N,0);
	nodeType* assop = get_operand(N,1);
	printf("PPPWWW : %d",assop->con_i.value);
	nodeType* ass_exp = get_operand(N,2);
	generate(unary_exp);
	//generate(assop);
	printf("ASSIGN FLAG 2\n:");
	generate(ass_exp);
	printf("OOOOOOOOOOOOLAAAA!!\n") ;  //segmentation fault here
	printf("ASSIGNMENT EXP CODE:\n**%s**",get_code(ass_exp));
	switch(assop->con_i.value)
	{
	case EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s", get_code(unary_exp), get_code(ass_exp),get_place(unary_exp),get_place(ass_exp));
		printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("UUUU%s\n",get_code(unary_exp));
		printf("AAAA%s\n",get_code(ass_exp));
		printf("UUUU%s\n",get_place(unary_exp));
		printf("AAAA%s\n",get_place(ass_exp));
		break;
	case PLUS_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s+%s", get_code(unary_exp), get_code(ass_exp),get_place(unary_exp),get_place(unary_exp),get_place(ass_exp));
		break;
	case MINUS_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s-%s", get_code(unary_exp), get_code(ass_exp),get_place(unary_exp),get_place(unary_exp),get_place(ass_exp));
		break;
	case MULT_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s*%s", get_code(unary_exp),get_code(ass_exp),get_place(unary_exp),get_place(unary_exp),get_place(ass_exp));
		break;
	case DIV_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s+%s", get_code(unary_exp), get_code(ass_exp),get_place(unary_exp),get_place(unary_exp),get_place(ass_exp));
		break;
	default: printf("ASSOP DEFAULT\n");
	}
	N->opr.code = strdup(buffer);
	return buffer;
}

char* ir_arithmetic(nodeType* n)
{
	printf("Entered arithmetic\n");
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	printf("E1 code:%s\n",get_code(E1));
	generate(E2);
	printf("E2 code:%s\n",get_code(E2));
	switch(n->opr.oper)
	{
	case PLUS:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ777:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s+%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		printf("QQQQQQQQQQQ:%s",buffer);
		break;
	case MINUS:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ778:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s-%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	case MULT:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ779:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s*%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	case DIV:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ790:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s/%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	case BIT_AND:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ790:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s&%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	case BIT_OR:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ790:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s|%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	case XOR:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ790:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s$%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	case LSH:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ790:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s<<%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	case RSH:
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		printf("QQQQQQQQ790:%s",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s>>%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		break;
	default:
		printf("arithmetic default\n");
	}
	n->opr.code = strdup(buffer);
	printf("Exiting arithmetic\n");
	return(buffer);
}


char* ir_relop(nodeType* n)
{
	//printf("Entered Relational\n");
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	//printf("E1 code:%s\n",get_code(E1));
	generate(E2);
	//printf("E2 code:%s\n",get_code(E2));
	switch(n->opr.oper)
	{
	case LT:
		printf("Relational LT\n");
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		//printf("Rel:%s\n",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s<%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		//printf("%s\n",buffer);
		//printf("End Relational LT\n");
		break;

	case GT:
		printf("Relational GT\n");
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		//printf("Rel:%s\n",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s>%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		//printf("End Relational GT\n");
		break;
		
	case LE:
		printf("Relational LE\n");
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		//printf("Rel:%s\n",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s<=%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		//printf("End Relational LE\n");
		break;

	case GE:
		printf("Relational GE\n");
		bzero(buffer,BUFFSIZE);
		n->opr.place = strdup(newtmp());
		//printf("Rel:%s\n",get_place(n));
		sprintf(buffer, "%s\n%s\n%s=%s>=%s", get_code(E1), get_code(E2), get_place(n), get_place(E1),  get_place(E2));
		//printf("End Relational GE\n");
		break;

	default:
		printf("Relational default\n");
	}
	n->opr.code = strdup(buffer);
	return(buffer);
}


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
	if(n->opr.oper==FORMAL_ARG)
	{
		print_type(get_operand(n,1));// 
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
	nodeType* stmt_list =get_operand(n,3);
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
	generate(stmt_list);
	/*
	if(formal_arguments->opr.oper != EMPTY)
	{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s",get_code(fun_name) , get_code(formal_arguments) , get_code(stmt_list));
	}
	else
	{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s",get_code(fun_name) , get_code(stmt_list));
	}
	n->opr.code = strdup(buffer);
	*/
	return buffer;

}

char* ir_var_dec(nodeType* n)
{
	nodeType* Idlist = n->opr.op[0];
	nodeType* Type = n->opr.op[1];
	generate(Idlist);
	printf("1ughuguguguygug\n");
	generate(Type);
	printf("2ughuguguguygug\n");
	n->opr.code = strdup(get_code(Idlist));
	printf("POPOPOP\n");
	return n->opr.code;
} 

char*  ir_idlist(nodeType* n)
{
	nodeType* Idlist = n->opr.op[0];
	nodeType* ident = n->opr.op[1];
	generate(Idlist);
	printf("huhahuahuahauha\n");
	//no need to generate code for ident as it is generated during installation
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"%s\n%s", get_code(Idlist), get_code(ident));
	n->opr.code = strdup(buffer);
	return buffer;
}	

char*  ir_stmtlist(nodeType* n)
{
	nodeType* Stmtlist = get_operand(n,0);
	nodeType* Stmt = get_operand(n,1);
	generate(Stmtlist);
	//printf("wjbsadoulaJSBHDONJSA\n");
	if(Stmtlist->opr.oper == STMT_LIST)
	{
		//printf("WWWjbsadoulaJSBHDONJSA\n");
		generate(Stmt);
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s", get_code(Stmtlist), get_code(Stmt));
	}
	else
	{
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s", get_code(Stmtlist));
	}
	n->opr.code = strdup(buffer);
	//printf("wjbsadoulaJSBHDONJSA\n");
	return buffer;
}
