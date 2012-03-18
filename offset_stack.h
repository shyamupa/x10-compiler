#include "ll_sym_table.h"
#define MAXSTACK 200
#define EMPTYSTACK -1

int off_top = EMPTYSTACK;

void off_push(int offset);
int off_pop();
int off_empty();
int off_full();

