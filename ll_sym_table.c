#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"ll_sym_table.h"
/*
This is a linked list implementation of the symbol table
*/
typedef struct sym_record sym_record;
typedef struct symbol_table symbol_table;

symbol_table* new_sym_table()
{
	symbol_table* st;
	st=(symbol_table*)malloc(sizeof(symbol_table));
	return st;
}
symbol_table* free_table (symbol_table* st) 
{
	symbol_table* current;
	current = st->parent;
	sym_record* p=st->Head;
	sym_record* t;
	while(p!=NULL)
	{
		t=p->next;
		free(p);
		p=t;
	}
	free(st);
	return current;
}
sym_record* insert(symbol_table* st,char* sym_name)	// inserts a record and returns a ptr to it
{
	sym_record* rv;
	rv=(sym_record*)malloc(sizeof(sym_record));
	rv->sym_name=strdup(sym_name);
	if(st->Head!=NULL)
	{
		rv->next=st->Head;
		st->Head=rv;
	}
	else
	{
		rv->next=NULL;
	}
	return rv;
}
sym_record* search(symbol_table* st,char* target_name)	//searches for a record and returns a ptr to it
{
	sym_record* p;
	p=st->Head;	// first sym_record
	while(p!=NULL)
	{
		if(strcmp(p->sym_name,target_name)==0)
			return p;
		p=p->next;	
	}
	return NULL;
}
void print_st(symbol_table* st)
{
	printf("PRINTING SYM_T\n");
	struct sym_record* p=st->Head;
	while(p!=NULL)
	{
		printf("%s\n",p->sym_name);
		p=p->next;
	}
}
