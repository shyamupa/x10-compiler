#include "ll_sym_table.h"
#ifndef node_def_h_included
#define node_def_h_included
typedef enum { typeConI,typeConF,typeConC,typeId,typeOpr } nodeEnum;

// for constants int
typedef struct 
{
	nodeEnum type;
	int datatype;
	int value;
}con_iNodeType;

typedef struct 
{
	nodeEnum type;
	int datatype;
	float value;
}con_fNodeType;

typedef struct 
{
	nodeEnum type;
	int datatype;
	char value;
}con_cNodeType;

// for identifiers
typedef struct 
{
	nodeEnum type;
	struct sym_record* symrec;
	struct symbol_table* st;
	//char* place = symrec->sym_name;
}idNodeType;

// for operators
typedef struct 
{
	nodeEnum type;
	int oper;
	int nops;
	union nodeTypeTag *op[1];
	char* begin;
	char* next;
	char* true;
	char* false;
	char* place;
	char* code;
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
