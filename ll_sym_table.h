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
	/*some other attributes as required*/
	struct sym_record* proc_st;		//ptr to symbol table of the procedure in case the sym_name is a proc name
	enum modifier access_mode;
	struct sym_record * next;
};


struct sym_record* insert(struct sym_record* st,char* sym_name);	// inserts a record and returns a ptr to it
struct sym_record* search(struct sym_record* st,char* target_name);	//searches for a record and returns a ptr to it

#endif
