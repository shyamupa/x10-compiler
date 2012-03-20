#ifndef st_stack_h_included
#define st_stack_h_included


#include "ll_sym_table.h"
#define MAXSTACK 100
#define EMPTYSTACK -1


void st_push(struct symbol_table* st);
int st_empty();
struct symbol_table* st_pop();
struct symbol_table* st_examine_top();
int st_full();

#endif
