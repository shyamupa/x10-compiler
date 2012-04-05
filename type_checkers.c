#include "type_checkers.h"
/*
	checks type for assign opr
	type should STRICTLY MATCH
*/
void type_check_assign(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	printf("%d %d HIHI\n",get_type(lhs),get_type(rhs));
	if(get_type(lhs)!=get_type(rhs))
	{
		printf("type mismatch in assign or bool eq / neq \n");
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
	printf("type mismatch in addmult\n");
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
	printf("type mismatch in relational\n");
	exit(0);
}

void type_check_int(nodeType* parent,nodeType* lhs,nodeType* rhs)
{
	if(get_type(lhs)!=MY_INT || get_type(rhs)!=MY_INT)
	{
		printf("type mismatch in int\n");
		exit(0);
	}
	parent->opr.datatype=MY_INT;
	return;
}

void type_check_bool(nodeType* parent,nodeType* lhs,nodeType* rhs)
{
	printf("SIDD %d %d\n",get_type(lhs),get_type(rhs));
	if(get_type(lhs)!=MY_BOOL || get_type(rhs)!=MY_BOOL)
	{
		printf("type mismatch in bool\n");
		exit(0);
	}
	parent->opr.datatype=MY_BOOL;
	return;
}

void type_check_shift(nodeType* parent,nodeType* node)
{
	if(get_type(node)!=MY_INT)
	{
		printf("type mismatch in shift\n");
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
	printf("Division by zero\n");
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
	printf("type mismatch in division\n");
	exit(0);
}

void type_check_prepostfix(nodeType* parent,nodeType* node)
{
	if(get_type(node)!=MY_INT && get_type(node)!=MY_FLOAT)
	{
		printf("type mismatch in ppprefix\n");
		exit(0);
	}
	parent->opr.datatype=get_type(node);
	return;
}

void type_check_typeid(nodeType* node)
{
	if(node->type!=typeId)
	{
		printf("type undefined\n");
		exit(0);
	}
	return;
}

