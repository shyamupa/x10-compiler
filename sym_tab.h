#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
extern int main();
struct sym_record
{
	char sym_name[20];		// name of symbol like 'counter'
	char* type;		// type of symbol like 'int'
	struct sym_record * next;
};
typedef struct sym_record sym_record;
sym_record* sym_table=NULL;	// global sym table
sym_record* insert(char* sym_name)	// inserts a record and returns a ptr to it
{
	sym_record* rv;
	rv=(sym_record*)malloc(sizeof(sym_record));
	strcpy(rv->sym_name,sym_name);
	rv->next=sym_table;
	sym_table=rv;
	return rv;
}
sym_record* search(char* target_name)	//searches for a record and returns a ptr to it
{
	sym_record* p;
	p=sym_table;
	while(p!=NULL)
	{
		if(strcmp(p->sym_name,target_name)==0)
			return p;
		p=p->next;	
	}
	return NULL;
}
//~ int main()
//~ {
	//~ sym_record* p=insert("counter");
	//~ p->type="int";
	//~ sym_record* q=search("counter");
	//~ printf("%s\n",q->type);
	//~ return 0;
//~ }

