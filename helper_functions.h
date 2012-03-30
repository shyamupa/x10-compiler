#include "my_defines.h"
#include "node_def.h"
#include<stdio.h>
#include<string.h>
#ifndef helper_functions_h_included
#define helper_functions_h_included

char* concat(char* c1,char* c2);
char* newlabel();
char* newtmp();
nodeType* get_operand(nodeType* opnode,int index);
void dist_type(nodeType* nptr);
int get_type(nodeType* data_type_ptr);

#endif
