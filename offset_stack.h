#ifndef offset_stack_h_included
#define offset_stack_h_included

#include "ll_sym_table.h"
#define MAXSTACK 200
#define EMPTYSTACK -1



void off_push(int offset);
int off_pop();
int off_empty();
int off_full();

#endif
