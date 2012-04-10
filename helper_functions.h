#include "my_defines.h"
#include "node_def.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h> // for variable arguments
#include<string.h>
#ifndef helper_functions_h_included
#define helper_functions_h_included
#define MAXQUEUE 100

char* concat(char* c1,char* c2);
char* newlabel();
char* newtmp();
nodeType* get_operand(nodeType* opnode,int index);
void dist_type(nodeType* nptr);
void print_header();
int get_type(nodeType* data_type_ptr);
char* get_place(nodeType* n);
char* get_code(nodeType* n);
void set_T(nodeType* n,char* label);
void set_F(nodeType* n,char* label);
char* get_T(nodeType* n);
char* get_F(nodeType* n);
nodeType* con_f(float value);
nodeType* con_i(int value);
nodeType* con_b(int value);
nodeType* con_c(char value);
nodeType* empty(int value);
nodeType *id(struct sym_record* symrec);
nodeType *opr(int oper, int nops, ...); 
struct sym_record* install(char* sym_name);
void traverse(nodeType* n);
void insert_queue(nodeType* n, char* label);
void print_store_var(nodeType* n);
void print_load_var(nodeType* n);




#endif
