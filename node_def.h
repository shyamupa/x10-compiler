#include "ll_sym_table.h"
#ifndef node_def_h_included
#define node_def_h_included
typedef enum { typeConI,typeConB,typeConF,typeConC,typeId,typeOpr } nodeEnum;

// for constants int
typedef struct 
{
	nodeEnum type;
	int datatype;
	int value;
	char* code;
	char* place;
	char* T;		// true label
	char* F;		// false label

}con_iNodeType;

typedef struct 
{
	nodeEnum type;
	int datatype;
	int value;
	char* code;
	char* place;
	char T[16];
	char F[16];

}con_bNodeType;

typedef struct 
{
	nodeEnum type;
	int datatype;
	float value;
	char* place;
	char *code;
	char T[16];
	char F[16];


}con_fNodeType;

typedef struct 
{
	nodeEnum type;
	int datatype;
	char value;
	char* place;
	char *code;
	char T[16];
	char F[16];
	

}con_cNodeType;

// for identifiers
typedef struct 
{
	nodeEnum type;
	struct sym_record* symrec;
	struct symbol_table* st;
	char *code;
	char* place;
	char T[16];
	char F[16];
	
}idNodeType;

// for operators
typedef struct 
{
	nodeEnum type;
	int oper;
	int nops;
	int datatype;
	union Gen_Node *op[1];
	char* begin;
	char* place;
	char* code;
	char T[16];
	char F[16];
	char next[16];
	

}oprNodeType;

union Gen_Node 
{
	nodeEnum type;		// type of node
	con_iNodeType con_i;
	con_fNodeType con_f;
	con_cNodeType con_c;
	con_cNodeType con_b;
	idNodeType id;
	oprNodeType opr;
};
#endif
