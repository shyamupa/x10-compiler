#include "ir_code.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern int generate(nodeType *n);

char* ir_if(nodeType* S,nodeType* E,nodeType* S1)
{
	E->opr.T = newlabel();
	E->opr.F = S->opr.next;
	S1->opr.next = S->opr.next;
	bzero(buffer,BUFFSIZE);

	sprintf(buffer,"%s\n%s\n%s", E->opr.code, E->opr.T, S1->opr.code);
	return(buffer);
}

char* ir_arithmetic(nodeType* n)
{
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	generate(E2);
	switch(n->opr.oper)
	{
	case PLUS:
		
		bzero(buffer,BUFFSIZE);
		n->opr.place = newtmp();
		sprintf(buffer, "%s\n%s\n%s=%s+%s", E1->opr.code, E2->opr.code, n->opr.place, E1->opr.place,  E2->opr.place);
		
	case MINUS:
		
		bzero(buffer,BUFFSIZE);
		n->opr.place = newtmp();
		sprintf(buffer, "%s\n%s\n%s=%s-%s", E1->opr.code, E2->opr.code, n->opr.place, E1->opr.place,  E2->opr.place);
	case MULT:
		
		bzero(buffer,BUFFSIZE);
		n->opr.place = newtmp();
		sprintf(buffer, "%s\n%s\n%s=%s*%s", E1->opr.code, E2->opr.code, n->opr.place, E1->opr.place,  E2->opr.place);
	case DIV:
		
		bzero(buffer,BUFFSIZE);
		n->opr.place = newtmp();
		sprintf(buffer, "%s\n%s\n%s=%s/%s", E1->opr.code, E2->opr.code, n->opr.place, E1->opr.place,  E2->opr.place);
	
	default:
		printf("arithmetic default\n");
	}
	return(buffer);
}

char* ir_explist(nodeType* N)
{
	nodeType* exp=get_operand(N,0);
	nodeType* assexp=get_operand(N,1);
	generate(exp);
	generate(assexp);
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"%s\n%s", exp->opr.code, assexp->opr.T);
	return(buffer);
}

char* ir_assign(nodeType* N)
{
	nodeType* unary_exp = get_operand(N,0);
	nodeType* assop = get_operand(N,1);
	nodeType* ass_exp = get_operand(N,2);
	generate(unary_exp);
	//generate(assop);
	generate(ass_exp);
	printf("WWWWWW : %d",assop->con_i.value);
	switch(assop->con_i.value)
	{
	case EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s", unary_exp->opr.code, ass_exp->opr.code,unary_exp->opr.place,ass_exp->opr.place);
		break;
	case PLUS_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s+%s", unary_exp->opr.code, ass_exp->opr.code,unary_exp->opr.place,unary_exp->opr.place,ass_exp->opr.place);
		break;
	case MINUS_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s-%s", unary_exp->opr.code, ass_exp->opr.code,unary_exp->opr.place,unary_exp->opr.place,ass_exp->opr.place);
		break;
	case MULT_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s*%s", unary_exp->opr.code, ass_exp->opr.code,unary_exp->opr.place,unary_exp->opr.place,ass_exp->opr.place);
		break;
	case DIV_EQ:
		bzero(buffer,BUFFSIZE);
		sprintf(buffer,"%s\n%s\n%s=%s/%s", unary_exp->opr.code, ass_exp->opr.code,unary_exp->opr.place,unary_exp->opr.place,ass_exp->opr.place);
		break;
	default: printf("ASSOP DEFAULT\n");
	}
	return buffer;
}

char* ir_ternary(nodeType* N)
{
	nodeType* log_or_exp=get_operand(N,0);
	nodeType* exp=get_operand(N,1);
	nodeType* cond_exp=get_operand(N,2);
	generate(log_or_exp);
	generate(exp);
	generate(cond_exp);
	//Incomplete
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
