#ifndef ll_sym_table_h_included
#define ll_sym_table_h_included

enum modifier 
{
	modPUBLIC=1, modPRIVATE=2, modPROTECTED=3
};
struct sym_record
{
	char* sym_name;		// name of symbol like 'counter'
	int type;			// type of symbol like 'int'
	int offset;			// offset of symbol
	int is_proc_name;		// 1 if ident is proc
	int is_field;		// 1 if ident is field
	int is_class;		// 1 if ident is class
	int is_static;		// 1 if ident is static method
	int formal; 
	enum modifier access_mode;
	char signature[100];		
	struct symbol_table* my_st;	//ptr to symbol table of the procedure in case of proc and class in case of class
	struct sym_record * next;
	char* in_st_of;		// name of owner of st in which this symrec belongs
	char* uid;
};

struct symbol_table{
	struct symbol_table* parent;	//pointer to parent symbol table
	char * owner_name;
	struct sym_record* Head;	//first entry in list of local variables
	struct sym_record* Tail;	//last entry in list of local variable
	int numparam;			//header
	int proc_sym;		// 1 if st of proc else 0
};

struct symbol_table* free_table (struct symbol_table* st); 
struct symbol_table* new_sym_table(struct symbol_table* parent);
struct sym_record* insert(struct symbol_table* st,char* sym_name);	// inserts a record and returns a ptr to it
struct sym_record* search(struct symbol_table* st,char* target_name);	//searches for a record and returns a ptr to it
struct sym_record* search_shallow(struct symbol_table* st,char* target_name);	//searches for a record and returns a ptr to it
void print_st(struct symbol_table* st);
int search_keywords(char* sym_name);
char* newuid();


#endif
