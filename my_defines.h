#ifndef my_defines_h
#define my_defines_h

#define INVOC 1337
#define FOR_STMT 1338
#define ASSIGN 1339
#define ARGS 1340
#define CLOSURE 1341
#define IDLIST 1342
#define FUNC 1343
#define COMMA 1344
#define VAR_DEC 1345
#define FORMAL_ARG 1346
#define FUNC_DEF_LIST 1347
#define STMT_LIST 1348
#define FORMAL_ARG_LIST 1349
#define ID_LIST 1350
#define EMPTY 1351
#define EXP_LIST 1352
#define TERNARY 1353
#define CAST 1354
#define POSTFIX 1355
#define PREFIX 1356
#define ARGEXPLIST 1357
#define COMPOUND 1358
#define CLASSLIST 1359
#define IF_ELSE 1360

#define YYDEBUG 1	//enable debugging

#define MY_INT 133
#define MY_FLOAT 134
#define MY_CHAR 135
#define MY_VOID 136
#define MY_BOOL 137

#define BUFFSIZE 100
#include "y.tab.h"

typedef union nodeTypeTag nodeType;	

#endif
