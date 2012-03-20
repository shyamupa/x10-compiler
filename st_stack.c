#include<stdio.h>
#include<stdlib.h>
#include "st_stack.h"

int st_top = EMPTYSTACK;
struct symbol_table* st_stack[MAXSTACK];

void st_push(struct symbol_table* st)
{
	if(!st_full())
		st_stack[++st_top]= st;
	else
		fprintf(stderr,"Stack overflow\n");
			
}
struct symbol_table* st_examine_top()
{
	if(!st_empty())
		return st_stack[st_top];
	else
		return NULL;
}
struct symbol_table* st_pop()
{
	if(!st_empty())
		return st_stack[st_top--];
	else
		fprintf(stderr,"Stack Underflow\n");
}
int st_empty()	// returns 0 if not empty and 1 if empty
{
	return st_top==EMPTYSTACK;
}
int st_full()
{
	return (st_top+1)==MAXSTACK;	
}



