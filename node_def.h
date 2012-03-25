#include "ll_sym_table.h"
#ifndef node_def_h_included
#define node_def_h_included
typedef enum { typeConI,typeConF,typeConC,typeId,typeOpr } nodeEnum;

// for constants int
typedef struct 
{
	nodeEnum type;
	int value;
	int datatype;
}con_iNodeType;

typedef struct 
{
	nodeEnum type;
	float value;
	int datatype;
}con_fNodeType;

typedef struct 
{
	nodeEnum type;
	char value;
	int datatype;
}con_cNodeType;

// for identifiers
typedef struct 
{
	nodeEnum type;
	struct sym_record* symrec;
	struct symbol_table* st;
}idNodeType;

// for operators
typedef struct 
{
	nodeEnum type;
	int oper;
	int nops;
	union nodeTypeTag *op[1];
}oprNodeType;

union nodeTypeTag 
{
	nodeEnum type;		// type of node
	con_iNodeType con_i;
	con_fNodeType con_f;
	con_cNodeType con_c;
	idNodeType id;
	oprNodeType opr;
};
#endif
