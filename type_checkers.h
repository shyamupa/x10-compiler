#include "my_defines.h"
#include "node_def.h"
#include "helper_functions.h"
#include "y.tab.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef type_checkers_h_included
#define type_checkers_h_included

void type_check_array_invoc(nodeType* parent,nodeType* array_name,nodeType* type_of_arg);
void type_check_assign(nodeType* assOp,nodeType* lhs,nodeType* rhs);
void type_check_addmult(nodeType* parent,nodeType* lhs,nodeType* rhs);
void type_check_cast(nodeType* parent,nodeType* node);
void type_check_char(nodeType* node);
void type_check_division(nodeType* parent,nodeType* lhs,nodeType* rhs);
void type_check_float(nodeType* node);
void type_check_int(nodeType* parent,nodeType* lhs,nodeType* rhs);
void type_check_invoc(nodeType* parent,nodeType* func_name,nodeType* arg_list);
void type_check_modulo(nodeType* parent,nodeType* lhs,nodeType* rhs);
void type_check_obj(nodeType* lhs,nodeType* class_name,nodeType* argexplist);
void type_check_prepostfix(nodeType* parent,nodeType* node);
void type_check_rel(nodeType* parent,nodeType* lhs,nodeType* rhs);
void type_check_shift(nodeType* parent,nodeType* node);
void type_check_typeid(nodeType* node);
void type_check_ternary(nodeType* parent,nodeType* bool_stmt,nodeType* exp1,nodeType* exp2);
#endif
