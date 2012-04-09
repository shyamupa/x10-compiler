#include "my_defines.h"
#include "node_def.h"
#include "helper_functions.h"
#include "y.tab.h"
#include<stdio.h>
#include<string.h>
#ifndef ir_code_h_included
#define ir_code_h_included
//char* ir_ifelse(nodeType* S,nodeType* E,nodeType* S1,nodeType* S2);
//char* ir_while(nodeType* S,nodeType* E,nodeType* S1);
//char* ir_boolor(nodeType* E,nodeType* E1,nodeType* E2);
//char* ir_booland(nodeType* E,nodeType* E1,nodeType* E2);
//char* ir_boolneg(nodeType* B,nodeType* B1);
//char* ir_ident(nodeType* E,nodeType* id);
//char* ir_negexp(nodeType* E,nodeType* E1);		/*E ->  -(E)*/
//char* ir_truefalse(nodeType* E,int value);
//char* ir_bitandorxor(nodeType* E,nodeType* E1,nodeType* E2, int value);
//char* ir_shift(nodeType* S, nodeType* S1, nodeType* E, int value);
void print_signature(nodeType* fun_name,nodeType* formalarg,nodeType* return_type);
void insert_signature_array(nodeType* array_name,nodeType* type);
void insert_signature(nodeType* fun_name,nodeType* formalarg,nodeType* return_type);
void print_type(nodeType* n);
void print_formal_args(nodeType* n);

void ir_array_declaration(nodeType* n);
void ir_array_rhs(nodeType* n);
void ir_array_lhs(nodeType* n);
void ir_assign(nodeType* n);
void ir_arithmetic(nodeType* n);
void ir_break(nodeType* n);
void ir_bool(nodeType* n);
void ir_bool_flow(nodeType* n);
void ir_cast(nodeType* n);
void ir_case_stmt_list(nodeType* n);
void ir_case_stmt(nodeType* n);
void ir_class_decln(nodeType* n);
void ir_class_decln_list(nodeType* n);
void ir_compound_stmt(nodeType* n);
void ir_default_stmt(nodeType* n);
void ir_explist(nodeType* n);
void ir_fun_def(nodeType* n);
void ir_for(nodeType* n);
void ir_fun_def_list(nodeType* n);
void ir_fun_invoc(nodeType* n);
void ir_idlist(nodeType* n);
void ir_if(nodeType* n);
void ir_if_else(nodeType* n);
void ir_prefix(nodeType* n);
void ir_postfix(nodeType* n);
void ir_relop(nodeType* n);
void ir_relop_flow(nodeType* n);
void ir_return(nodeType* n);
void ir_stmtlist(nodeType* n);
void ir_var_dec(nodeType* n);
void ir_while(nodeType* n);
void ir_switch(nodeType* n);




#endif
