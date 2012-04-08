#include "type_checkers.h"
/*
	checks type for assign opr
	type should STRICTLY MATCH
*/
void type_check_assign(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	if((lhs->type==typeOpr) && (lhs->opr.oper==ARRAY_INVOC))	lhs = get_operand(lhs,0);
	if((rhs->type==typeOpr) && (rhs->opr.oper==ARRAY_INVOC))	rhs = get_operand(rhs,0);
	printf("%d %d HIHI\n",get_type(lhs),get_type(rhs));
	if(get_type(lhs)!=get_type(rhs))
	{
		//printf("type mismatch in assign or bool eq / neq \n");
		yyerror("type mismatch in assign or bool eq/neq");
		exit(0);
	}
	parent->opr.datatype=get_type(rhs);
	return;
}
/*
	checks type for add and mult 
	allows all 4 combos of int and float
*/
void type_check_addmult(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	
	if(get_type(lhs)==MY_INT && get_type(rhs)==MY_INT)
	{
		parent->opr.datatype=get_type(rhs);
		//printf("case 1\n");
		return;
	}
	else if(get_type(lhs)==MY_FLOAT && get_type(rhs)==MY_FLOAT)
	{
		parent->opr.datatype=get_type(rhs);
		//printf("case 2\n");
		return;
	}
	else if(get_type(lhs)==MY_FLOAT || get_type(rhs)==MY_FLOAT)
	{
		parent->opr.datatype=MY_FLOAT;
		//printf("case 3\n");
		return;
	}
	yyerror("type mismatch in addmult");
	exit(0);
}

void type_check_rel(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)==MY_INT || get_type(rhs)==MY_FLOAT)
	{
		if(get_type(lhs)==MY_INT || get_type(rhs)==MY_FLOAT)
		{
			parent->opr.datatype=MY_BOOL;
			return;
		}
	}
	yyerror("type mismatch in relational\n");
	exit(0);
}

void type_check_int(nodeType* parent,nodeType* lhs,nodeType* rhs)
{
	if(get_type(lhs)!=MY_INT || get_type(rhs)!=MY_INT)
	{
		yyerror("type mismatch in int\n");
		exit(0);
	}
	parent->opr.datatype=MY_INT;
	return;
}

void type_check_bool(nodeType* parent,nodeType* lhs,nodeType* rhs)
{
	//printf("SIDD %d %d\n",get_type(lhs),get_type(rhs));
	if(get_type(lhs)!=MY_BOOL || get_type(rhs)!=MY_BOOL)
	{
		yyerror("type mismatch in bool\n");
		exit(0);
	}
	parent->opr.datatype=MY_BOOL;
	return;
}

void type_check_shift(nodeType* parent,nodeType* node)
{
	if(get_type(node)!=MY_INT)
	{
		yyerror("type mismatch in shift\n");
		exit(0);
	}
	parent->opr.datatype=MY_INT;
	return;
}

void type_check_division(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	// first check div by 0
	if(rhs->type==typeConI)
	{
		if(rhs->con_i.value!=0)		return;
	}
	else if(rhs->type==typeConF)
	{
		if(rhs->con_f.value!=0.0)		return;
	}
	yyerror("Division by zero\n");
	exit(0);
	// assign type to parent
	if(get_type(lhs)==MY_INT && get_type(rhs)==MY_INT)
	{
		parent->opr.datatype=get_type(rhs);
		return;
	}
	else if(get_type(lhs)==MY_FLOAT && get_type(rhs)==MY_FLOAT)
	{
		parent->opr.datatype=get_type(rhs);
		return;
	}
	else if(get_type(lhs)==MY_FLOAT || get_type(rhs)==MY_FLOAT)
	{
		parent->opr.datatype=MY_FLOAT;
		return;
	}
	yyerror("type mismatch in division\n");
	exit(0);
}

void type_check_prepostfix(nodeType* parent,nodeType* node)
{
	if(get_type(node)!=MY_INT && get_type(node)!=MY_FLOAT)
	{
		yyerror("type mismatch in ppprefix\n");
		exit(0);
	}
	parent->opr.datatype=get_type(node);
	return;
}

void type_check_typeid(nodeType* node)
{
	if(node->type!=typeId)
	{
		yyerror("type undefined\n");
		exit(0);
	}
	return;
}
void type_check_invoc(nodeType* parent,nodeType* func_name,nodeType* arg_list)
{
	char * pch;
	char* sign;
	sign = strdup(func_name->id.symrec->signature);
	if(strcmp(sign,"")==0)
	{
		//printf("SIGN IS NULL\n");
		return;
	}	
	//printf ("Splitting string \"%s\" into tokens:\n",func_name->id.symrec->signature);
	pch = strtok (sign," ::");
	int count = 0;
	if(strcmp(pch,"int32")==0)	
	{
		//printf("PCH IS %s\n",pch);
		parent->opr.datatype = MY_INT;
	}
	else if(strcmp(pch,"float32")==0)	
	{
		//printf("PCH IS %s\n",pch);
		parent->opr.datatype = MY_FLOAT;
	}
	
	while (pch != NULL)
	{
		if(count>3)
		{
			
			printf("%s\n",pch);
			pch = strtok (NULL, " )(,::");
		}
		else
		{
				count = count+1;
				pch = strtok (NULL, " )(,::");
		}

	}
}	

void type_check_array_invoc(nodeType* parent,nodeType* array_name)
{
	if(strcmp(array_name->id.symrec->signature,"int32")==0)	
	{
		parent->opr.datatype = MY_INT;
	}
	else if(strcmp(array_name->id.symrec->signature,"float32")==0)	
	{
		parent->opr.datatype = MY_FLOAT;
	}
	else if(strcmp(array_name->id.symrec->signature,"char")==0)	
	{
		parent->opr.datatype = MY_CHAR;
	}
}	


void type_check_cast(nodeType* parent,nodeType* node)
{	
	
	if(get_type(node)==MY_INT || get_type(node)==MY_FLOAT)
	{
		parent->opr.datatype=get_type(node);
		return;
	}
	else
	{
		yyerror("type mismatch in addmult");
		exit(0);
	}
}	
