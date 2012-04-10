#include "type_checkers.h"
/*
	checks type for assign opr
	type should STRICTLY MATCH
*/
extern struct symbol_table* current_st;
void type_check_assign(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	printf("%d %d HIHI\n",get_type(lhs),get_type(rhs));
	if(get_type(lhs)!=get_type(rhs))
	{
		yyerror("type mismatch in assign");
		exit(0);
	}
	parent->opr.datatype=get_type(rhs);
	return;
}

// in bool eq or neq check for strict matching of data types
// int==int float==float is allowed etc etc
// final result will have data type of bool
void type_check_booleq(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)!=get_type(rhs))
	{
		yyerror("type mismatch in bool eq/neq");
		exit(0);
	}
	parent->opr.datatype=MY_BOOL;
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
		if(rhs->con_i.value==0)
		{
			yyerror("Division by zero\n");
			exit(0);
		}	
	}
	else if(rhs->type==typeConF)
	{
		if(rhs->con_f.value!=0.0)
		{
			yyerror("Division by zero\n");
			exit(0);
		}		
	}
	
	// assign type to parent
	if(get_type(lhs)==MY_INT && get_type(rhs)==MY_INT)			// both are int parent is int
	{
		parent->opr.datatype=get_type(rhs);
		return;
	}
	else if(get_type(lhs)==MY_FLOAT && get_type(rhs)==MY_FLOAT)	// both are int parent is float
	{
		parent->opr.datatype=get_type(rhs);
		return;
	}
	else if(get_type(lhs)==MY_FLOAT || get_type(rhs)==MY_FLOAT)	// either is float,parent is float
	{
		parent->opr.datatype=MY_FLOAT;
		return;
	}
	yyerror("type mismatch in division\n");
	exit(0);
}
void type_check_modulo(nodeType* parent,nodeType* lhs,nodeType* rhs)
{
	// first check div by 0
	if(rhs->type==typeConI)
	{
		if(rhs->con_i.value==0)
		{
			yyerror("Modulo by zero\n");
			exit(0);
		}	
	}
	if(get_type(lhs)==MY_INT && get_type(rhs)==MY_INT)		//both are only allowed to be int right now
	{	
		parent->opr.datatype=get_type(lhs);			// parent is also int
		return;
	}
	else
	{
		yyerror("type mismatch in modulo\n");
		exit(0);
	}
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
	printf("izbdidsadbdis\n");
	char * pch;
	char* sign;
	sign = strdup(func_name->id.symrec->signature);
	if(strcmp(sign,"")==0)
	{
		printf("SIGN IS NULL\n");
		return;
	}	
	printf ("Splitting string \"%s\" into tokens:\n",func_name->id.symrec->signature);
	pch = strtok (sign," ::");
	int count = 0;
	if(strcmp(pch,"int32")==0)	
	{
		printf("PCH IS %s\n",pch);
		parent->opr.datatype = MY_INT;
	}
	else if(strcmp(pch,"float32")==0)	
	{
		printf("PCH IS %s\n",pch);
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
	struct sym_record*p = search(current_st,array_name->id.symrec->sym_name);
	if(p==NULL)
	{
		yyerror("  Array not declared\n");
		exit(0);
	}
	parent->opr.datatype = p->type;
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
