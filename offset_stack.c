#include<stdio.h>
#include<stdlib.h>
#include "offset_stack.h"

int off_stack[MAXSTACK];

void off_push(int offset)
{
	if(!off_full())
		off_stack[++off_top]= offset;
	else
		stderr("Stack overflow\n");
			
}
symbol_table* off_pop()
{
	if(!off_empty())
		return off_stack[off_top--];
	else
		stderr("Stack Underflow\n");
}
int off_empty()	// returns 0 if not empty and 1 if empty
{
	return off_top==EMPTYSTACK;
}
int off_full()
{
	return (off_top+1)==MAXSTACK;	
}



