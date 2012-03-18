#include "ll_sym_table.h"
#define MAXSTACK 100
#define EMPTYSTACK -1

int st_top = EMPTYSTACK;

void st_push(struct symbol_table* st);
struct symbol_table* st_pop();
int st_empty();
int st_full();

