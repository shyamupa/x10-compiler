#ifndef ll_sym_table_h_included
#define ll_sym_table_h_included

enum modifier 
{
	modPUBLIC, modPRIVATE, modPROTECTED
};
struct sym_record
{
	char*sym_name;		// name of symbol like 'counter'
	int type;			// type of symbol like 'int'
	int offset;			// offset of symbol
	/*some other attributes as required*/
	struct sym_record* proc_st;		//ptr to symbol table of the procedure in case the sym_name is a proc name
	enum modifier access_mode;
	struct sym_record * next;
};

struct symbol_table{
	struct symbol_table* parent;	//pointer to parent symbol table
	struct sym_record* Head;	//first entry in list of local variables
	struct sym_record* Tail;	//last entry in list of local variable
	int numparam;			//header
	int depth;		// 
};

struct symbol_table* free_table (struct symbol_table* st); 
struct symbol_table* new_sym_table();
struct sym_record* insert(struct symbol_table* st,char* sym_name);	// inserts a record and returns a ptr to it
struct sym_record* search(struct symbol_table* st,char* target_name);	//searches for a record and returns a ptr to it


#endif
