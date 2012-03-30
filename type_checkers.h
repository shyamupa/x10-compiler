#include "my_defines.h"
#include "node_def.h"
#include "helper_functions.h"
#include "y.tab.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef type_checkers_h_included
#define type_checkers_h_included
void type_check_assign(nodeType* lhs,nodeType* rhs);
void type_check_addmult(nodeType* lhs,nodeType* rhs);
void type_check_rel(nodeType* lhs,nodeType* rhs);
void type_check_int(nodeType* node);
void type_check_float(nodeType* node);
void type_check_char(nodeType* node);
void type_check_division(nodeType* lhs,nodeType* rhs);
void type_check_prepostfix(nodeType* node);
void type_check_typeid(nodeType* node);

#endif
