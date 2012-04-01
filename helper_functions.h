#include "my_defines.h"
#include "node_def.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h> // for variable arguments
#include<string.h>
#ifndef helper_functions_h_included
#define helper_functions_h_included

char* concat(char* c1,char* c2);
char* newlabel();
char* newtmp();
nodeType* get_operand(nodeType* opnode,int index);
void dist_type(nodeType* nptr);
int get_type(nodeType* data_type_ptr);
char* get_place(nodeType* n);
char* get_code(nodeType* n);
char* get_T(nodeType* n);
char* get_F(nodeType* n);
nodeType* con_f(float value);
nodeType* con_i(int value);
nodeType* con_c(char value);
nodeType* empty(int value);
nodeType *id(struct sym_record* symrec);
nodeType *opr(int oper, int nops, ...); 
struct sym_record* install(char* sym_name);


#endif
