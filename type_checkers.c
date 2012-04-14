#include "type_checkers.h"

/*
	TYPE_CHECK_ASSIGN
	checks type for assign opr
	type should STRICTLY MATCH
*/
extern struct symbol_table* current_st;
void type_check_assign(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	if(get_type(lhs)!=get_type(rhs))
	{
		yyerror("type mismatch in assign");
		exit(0);
	}
	parent->opr.datatype=get_type(rhs);
	return;
}

// TYPE_CHECK_BOOLEQ
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
	TYPE_CHECK_ADDMULT
	checks type for add and mult 
	allows all 4 combos of int and float
*/
void type_check_addmult(nodeType* parent,nodeType* lhs,nodeType* rhs)
{	
	
	if(get_type(lhs)==MY_INT && get_type(rhs)==MY_INT)
	{
		parent->opr.datatype=get_type(rhs);			// both int so parent int
		return;
	}
	else if(get_type(lhs)==MY_FLOAT && get_type(rhs)==MY_FLOAT)
	{
		parent->opr.datatype=get_type(rhs);			// both float so parent float
		return;
	}
	else if(get_type(lhs)==MY_FLOAT || get_type(rhs)==MY_FLOAT)
	{	
		parent->opr.datatype=MY_FLOAT;				// either is float then parent float
		return;
	}
	yyerror("type mismatch in addmult");
	exit(0);
}

// TYPE_CHECK_REL
// allows all 4 combos of float and int
void type_check_rel(nodeType* parent,nodeType* lhs,nodeType* rhs)		// was wrong eariler GIGLAMESH
{	
	if(get_type(lhs)==MY_INT && get_type(rhs)==MY_INT)		//  both int
	{
			parent->opr.datatype=MY_BOOL;		// operator node type is bool
			return;
		
	}
	else if(get_type(lhs)==MY_FLOAT && get_type(rhs)==MY_FLOAT)		// both float 
	{
			parent->opr.datatype=MY_BOOL;		// operator node type is bool
			return;
	}
	else if(get_type(lhs)==MY_INT && get_type(rhs)==MY_FLOAT || get_type(lhs)==MY_FLOAT && get_type(rhs)==MY_INT)	// float int combos
	{
			parent->opr.datatype=MY_BOOL;		// operator node type is bool
			return;
	}
	yyerror("type mismatch in relational\n");
	exit(0);
}

// both operands should be int and the operator node will be int
void type_check_int(nodeType* parent,nodeType* lhs,nodeType* rhs)
{
	if(get_type(lhs)!=MY_INT || get_type(rhs)!=MY_INT)
	{
		yyerror("type mismatch in int\n");
		exit(0);
	}
	parent->opr.datatype=MY_INT;		// assign type to parent
	return;
}

// both operands should be BOOL and the operator node will be BOOL
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

// only int allowed and answer will also be int
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
	// first check div by 0 if present then should handle error GIGLAMESH
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

// modulo only allows int operands,also need to check for div by 0
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

// prepost operations only allowed in float and int right now
void type_check_prepostfix(nodeType* parent,nodeType* node)
{
	if(get_type(node)!=MY_INT && get_type(node)!=MY_FLOAT)
	{
		yyerror("type mismatch in ppprefix\n");
		exit(0);
	}
	else if(node->type != typeId)
	{
		yyerror("No identifier in the increment operation\n");
		exit(0);
	}
	parent->opr.datatype=get_type(node);
	return;
}

// used to check if node is of identifer type
void type_check_typeid(nodeType* node)
{
	if(node->type!=typeId)
	{
		yyerror("type undefined\n");
		exit(0);
	}
	return;
}

// GIGLAMESH
void type_check_invoc(nodeType* parent,nodeType* func_name,nodeType* arg_list)
{
	if(func_name->opr.oper==FIELD)
	{
		debugger("TYPE CHECK IN FIELD\n");
		// incomplete
		nodeType* objref=get_operand(func_name,0);
		nodeType* func_name=get_operand(func_name,1);
		enum modifier accmod=func_name->id.symrec->access_mode;
		if(accmod==modPRIVATE)
		{
			yyerror("calling private function");
			return;
		}
	}
	else
	{
		//Making node as int node for taking int input
		//Currently we can take only int inputs
		if(strcmp(func_name->id.symrec->sym_name,"scanf")==0)
		{
			parent->opr.datatype = MY_INT;
			return;
		}
	
		char * pch;
		char* sign;
		sign = strdup(func_name->id.symrec->signature);
		if(strcmp(sign,"")==0)
		{
			debugger("SIGN IS NULL\n");
			return;
		}	
		debugger ("Splitting string \"%s\" into tokens:\n",func_name->id.symrec->signature);
		pch = strtok (sign," ::");
		int count = 0;
		
		// first enter return type value into parent node
		if(strcmp(pch,"int32")==0)	
		{
			debugger("PCH IS %s\n",pch);
			parent->opr.datatype = MY_INT;
		}
		else if(strcmp(pch,"float32")==0)	
		{
			debugger("PCH IS %s\n",pch);
			parent->opr.datatype = MY_FLOAT;
		}
		else if(strcmp(pch,"void")==0)	
		{
			debugger("PCH IS %s\n",pch);
			parent->opr.datatype = MY_VOID;
		}
		
		if(arg_list->opr.oper==EMPTY)
			return;
		
		while (pch != NULL)
		{
			if(count>3)
			{
				
				debugger("%s\n",pch);
				pch = strtok (NULL, " )(,::");
			}
			else
			{
					count = count+1;
					pch = strtok (NULL, " )(,::");
			}

		}
	}	
}	

// GIGLAMESH
void type_check_array_invoc(nodeType* parent,nodeType* array_name,nodeType* type_of_arg)
{
	if(get_type(type_of_arg) != MY_INT)
	{
		yyerror("Array arguement should be a int");
		exit(0);
	}
	struct sym_record*p = search(current_st,array_name->id.symrec->sym_name);	// find array in sym_tab
	if(p==NULL)
	{
		yyerror("  Array not declared\n");
		exit(0);
	}
	parent->opr.datatype = p->type;			// assign array's data type to parent node
}	

void type_check_array(nodeType* type)
{
	if(get_type(type)!=MY_INT)
	{
		yyerror("Array arguement should be a int");
		exit(0);
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

void type_check_obj(nodeType* lhs,nodeType* class_name,nodeType* argexplist)
{
	if(strcmp(lhs->id.symrec->sym_name,lhs->id.symrec->sym_name)!=0)
	{
		yyerror("wrong class creation\n");
		exit(0);
	}
	// incomplete
}

void type_check_ternary(nodeType* parent,nodeType* bool_stmt,nodeType* exp1,nodeType* exp2)
{	
	if(get_type(bool_stmt)!= MY_BOOL)
	{
		yyerror("No boolean condition in conditional operator");
		exit(0);
	}
	else if(get_type(exp1) != get_type(exp2))
	{
		yyerror("type mismatch in ternary operator, types of operand 2 & 3 should be same");
		exit(0);
	}
	parent->opr.datatype=get_type(exp1);
}	
