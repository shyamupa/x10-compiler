#include "ll_sym_table.h"
#ifndef node_def_h_included
#define node_def_h_included
typedef enum { typeCon, typeId, typeOpr } nodeEnum;
// for constants
typedef struct 
{
	nodeEnum type;	
	int value;
}conNodeType;

// for identifiers
typedef struct 
{
	nodeEnum type;
	struct sym_record* i;	// index in ident array
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
	conNodeType con;
	idNodeType id;
	oprNodeType opr;
};
#endif
