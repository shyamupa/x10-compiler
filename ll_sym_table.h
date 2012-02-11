#ifndef ll_sym_table_h_included
#define ll_sym_table_h_included
struct sym_record
{
	char sym_name[20];		// name of symbol like 'counter'
	char* type;		// type of symbol like 'int'
	struct sym_record * next;
};
typedef struct sym_record sym_record;



sym_record* insert(char* sym_name);	// inserts a record and returns a ptr to it
sym_record* search(char* target_name);	//searches for a record and returns a ptr to it
#endif
