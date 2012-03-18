#include<stdio.h>
#include<stdlib.h>
#include "st_stack.h"

typedef struct symbol_table symbol_table;

symbol_table* st_stack[MAXSTACK];

void st_push(symbol_table* st)
{
	if(!st_full())
		stack[++st_top]= st;
	else
		stderr("Stack overflow\n");
			
}
symbol_table* st_pop()
{
	if(!st_empty())
		return st_stack[st_top--];
	else
		stderr("Stack Underflow\n");
}
int st_empty()	// returns 0 if not empty and 1 if empty
{
	return st_top==EMPTYSTACK;
}
int st_full()
{
	return (st_top+1)==MAXSTACK;	
}



