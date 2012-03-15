#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"ll_sym_table.h"
/*
This is a linked list implementation of the symbol table
*/
typedef struct sym_record sym_record;
sym_record* new_sym_table()
{
	sym_record* st=NULL;
	return st;
}
sym_record* insert(sym_record* st,char* sym_name)	// inserts a record and returns a ptr to it
{
	sym_record* rv;
	rv=(sym_record*)malloc(sizeof(sym_record));
	rv->sym_name=strdup(sym_name);
	rv->next=st;
	st=rv;
	return rv;
}
sym_record* search(sym_record* st,char* target_name)	//searches for a record and returns a ptr to it
{
	sym_record* p;
	p=st;
	while(p!=NULL)
	{
		if(strcmp(p->sym_name,target_name)==0)
			return p;
		p=p->next;	
	}
	return NULL;
}
