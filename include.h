typedef enum { typeCon, typeId, typeOpr } nodeEnum;
typedef struct 
{
	nodeEnum type;
	int value;
} conNodeType;
typedef struct 
{
	nodeEnum type;
	int i;
} idNodeType;
typedef struct 
{
	nodeEnum type;
	int oper;
	int nops;
	union nodeTypeTag *op[1];
} oprNodeType;
typedef union nodeTypeTag 
{
	nodeEnum type;
	conNodeType con;
	idNodeType id;
	oprNodeType opr;
} nodeType;
