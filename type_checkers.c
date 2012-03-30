#include "type_checkers.h"
/*
	checks type for assign opr
	type should strictly match
*/
void type_check_assign(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)!=get_type(rhs))
	{
		printf("type mismatch in assign\n");
		exit(0);
	}
	return;
}
/*
	checks type for add and mult 
	allows all 4 combos of int and float
*/
void type_check_addmult(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)==133 || get_type(lhs)==134)
	{
		if(get_type(rhs)==133 || get_type(rhs)==134)
		{
			return;
		}
	}
	printf("type mismatch in addmult\n");
	exit(0);
}

void type_check_rel(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)==133 || get_type(lhs)==134)
	{
		if(get_type(rhs)==133 || get_type(rhs)==134)
		{
			return;
		}
	}
	printf("type mismatch in relational\n");
	exit(0);
}

void type_check_int(nodeType* node)
{
	if(get_type(node)!=133)
	{
		printf("type mismatch in int\n");
		exit(0);
	}
	return;
}

void type_check_float(nodeType* node)
{
	if(get_type(node)!=134)
	{
		printf("type mismatch in float\n");
		exit(0);
	}
	return;
}
void type_check_char(nodeType* node)
{
	if(get_type(node)!=135)
	{
		printf("type mismatch in char\n");
		exit(0);
	}
	return;
}

void type_check_division(nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)==133 || get_type(lhs)==134)
	{
		if(get_type(rhs)==133 || get_type(rhs)==134)
		{
			if(rhs->type==typeConI)
			{
				if(rhs->con_i.value!=0)		return;
			}
			else if(rhs->type==typeConF)
			{
				if(rhs->con_f.value!=0)		return;
			}
			printf("Division by zero\n");
			exit(0);
		}
	}
	printf("type mismatch in division\n");
	exit(0);
}

void type_check_prepostfix(nodeType* node)
{
	printf("HELLO %d",get_type(node));
	if(get_type(node)!=133 && get_type(node)!=134)
	{
		printf("type mismatch in ppprefix\n");
		exit(0);
	}
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

