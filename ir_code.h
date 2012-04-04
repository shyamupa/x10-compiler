#include "my_defines.h"
#include "node_def.h"
#include "helper_functions.h"
#include "y.tab.h"
#include<stdio.h>
#include<string.h>
#ifndef ir_code_h_included
#define ir_code_h_included
//char* ir_if(nodeType* S,nodeType* E,nodeType* S1);
char* func_invoc(nodeType* n);
char* ir_explist(nodeType* N);
char* ir_arithmetic(nodeType* n);
char* ir_class_decln_list(nodeType* n);
void ir_compound_stmt(nodeType* n);
char* ir_class_decln(nodeType* n);
//char* ir_ifelse(nodeType* S,nodeType* E,nodeType* S1,nodeType* S2);
//char* ir_while(nodeType* S,nodeType* E,nodeType* S1);
//char* ir_boolor(nodeType* E,nodeType* E1,nodeType* E2);
//char* ir_booland(nodeType* E,nodeType* E1,nodeType* E2);
//char* ir_boolneg(nodeType* B,nodeType* B1);
//char* ir_ident(nodeType* E,nodeType* id);
//char* ir_negexp(nodeType* E,nodeType* E1);		/*E ->  -(E)*/
char* ir_relop(nodeType* n);
//char* ir_truefalse(nodeType* E,int value);
//char* ir_bitandorxor(nodeType* E,nodeType* E1,nodeType* E2, int value);
//char* ir_shift(nodeType* S, nodeType* S1, nodeType* E, int value);
char* ir_fun_def(nodeType* n);
char* ir_fun_def_list(nodeType* n);
char* ir_var_dec(nodeType* n);
char* ir_idlist(nodeType* n);
char* ir_assign(nodeType* n);
//char* ir_ternary(nodeType* n);
char* ir_stmtlist(nodeType* n);
char* ir_bool_flow(nodeType* n);
void print_type(nodeType* n);
void print_formal_args(nodeType* n);
#endif
