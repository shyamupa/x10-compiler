#include "helper_functions.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern struct symbol_table* current_st;
extern FILE* output;
extern char* out_file;

// global variables
nodeType* expr_queue[MAXQUEUE];
char label_queue[MAXQUEUE][16];
int queue_length = 0;


// concats strings with /n in between
char* concat(char* c1,char* c2)
{
	strcat(c1,"\n");
	strcat(c1,c2);
	return c1;
}

// Generates new temp and returns the string
// NEEDS global variables buffer and tempno
char* newtmp()
{
	memset(buffer,0,BUFFSIZE);
	sprintf(buffer,"t%d",tempno++);
	return(buffer);
}

// Generates a newlabel and returns the string 
// NEEDS global variables buffer and labelno
char* newlabel()
{
	memset(buffer,0,BUFFSIZE);
	sprintf(buffer,"l%d",labelno++);
	return(buffer);
}

// get_operand takes a nodeType ptr of opr node type
// and returns the operand at position index
nodeType* get_operand(nodeType* opnode,int index)
{
	if(index < opnode->opr.nops)
		return opnode->opr.op[index];
	else
		{
			printf("get operand main fasa\n");
			exit(0);
		}	
}

// NEEDS ASSERT statements GIGLAMESH
// takes a VarDec node and spread the type info 
void dist_type(nodeType* nptr)
{
	printf("%d\n",nptr->type); // should be typeOp
	printf("%d is the type to be assigned\n",get_operand(nptr,1)->con_i.value);
	int TypeToAssign=get_operand(nptr,1)->con_i.value;
	nodeType* idlist=get_operand(nptr,0);
	if(idlist->type==typeId)
		idlist->id.symrec->type=TypeToAssign;		
	else
	{
		while(idlist->type!=typeId)
		{
			nodeType* leftnode=get_operand(idlist,0);
			nodeType* rightnode=get_operand(idlist,1);
			rightnode->id.symrec->type=TypeToAssign;
			idlist=leftnode;
		}
		idlist->id.symrec->type=TypeToAssign;
	}	
}

// get_type takes a data_type node ptr and returns the data type embedded in it	
// return values like MY_INT MY_BOOL etc
int get_type(nodeType* data_type_ptr)
{
	if(data_type_ptr->type==typeConI)		// integer
	{
		return data_type_ptr->con_i.datatype;	
	}
	else if(data_type_ptr->type==typeConF)	// float
	{
		return data_type_ptr->con_f.datatype;	
	}
	else if(data_type_ptr->type==typeConC)		// char
	{
		return data_type_ptr->con_c.datatype;	
	}
	else if(data_type_ptr->type==typeConB)		// boolean
	{
		return data_type_ptr->con_b.datatype;	
	}
	else if(data_type_ptr->type==typeId)		// id
	{
		return data_type_ptr->id.symrec->type;
	}
	else if(data_type_ptr->type==typeOpr)
	{
		return data_type_ptr->opr.datatype;
	}
}

// USELESS FUNC
// gets the code field from a given node 
// returns values like ?? GIGLAMESH
char* get_code(nodeType* n)
{
	 switch(n->type)
	 {
		case typeConI:
			return n->con_i.code;
			break;
		case typeConC:
			return n->con_c.code;
			break;
		case typeConF:
			return n->con_f.code;
			break;
		case typeOpr:
			return n->opr.code;
			break;
		case typeId:
			return n->id.code;
			break;

		default:
			printf("Can't get code for unknown node type\n");
	}
}

// gets the place field from a given node
char* get_place(nodeType* n)
{
	 switch(n->type)
		{
		  case typeConI:
				return n->con_i.place;
				break;
		  case typeConC:
				return n->con_c.place;
				break;
		  case typeConF:
				return n->con_f.place;
				break;
		  case typeOpr:
				return n->opr.place;
				break;
		  case typeId:
				return n->id.place;
				break;
		  default:
					printf("Can't get place for unknown node type\n");
		}
}

// sets the true label to a label passed as argument
// memsets are used before strcat
void set_F(nodeType* n,char* label)
{
	switch(n->type)
	{
		case typeConI:
			memset(n->con_i.F,0,16);
			strcat(n->con_i.F,label);
			break;
		case typeConC:
			memset(n->con_c.F,0,16);
			strcat(n->con_c.F,label);
			break;
		case typeConB:
			memset(n->con_b.F,0,16);
			strcat(n->con_b.F,label);
			break;		
		case typeConF:
			memset(n->con_f.F,0,16);
			strcat(n->con_f.F,label);
			break;
		case typeOpr:
			memset(n->opr.F,0,16);
			strcat(n->opr.F,label);
			break;
		case typeId:
			memset(n->id.F,0,16);
			strcat(n->id.F,label);
			break;
		default:
			printf("Can't set F for unknown node type\n");
	}
}

// sets the true label to a label passed as argument
// memsets are used before strcat
void set_T(nodeType* n,char* label)
{
	switch(n->type)
	{
		case typeConI:
			memset(n->con_i.T,0,16);
			strcat(n->con_i.T,label);
			break;
		case typeConC:
			memset(n->con_c.T,0,16);
			strcat(n->con_c.T,label);
			break;
		case typeConB:
			memset(n->con_b.T,0,16);
			strcat(n->con_b.T,label);
			break;		
		case typeConF:
			memset(n->con_f.T,0,16);
			strcat(n->con_f.T,label);
			break;
		case typeOpr:
			memset(n->opr.T,0,16);
			strcat(n->opr.T,label);
			break;
		case typeId:
			memset(n->id.T,0,16);
			strcat(n->id.T,label);
			break;
		default:
			printf("Can't set T for unknown node type\n");
	}
}

// gets the false label string from a given node
// to be used in bool flow ir code
char* get_F(nodeType* n)
{
	 switch(n->type)
	 {
	  case typeConI:
			return n->con_i.F;
			break;
	  case typeConC:
			return n->con_c.F;
			break;
	  case typeConF:
			return n->con_f.F;
			break;
	  case typeOpr:
			return n->opr.F;
			break;
	  case typeId:
			return n->id.F;
			break;
	  case typeConB:
			return n->con_b.F;
			break;			
			
	  default:
				printf("Can't get F for unknown node type\n");
	}
}

// gets the true label string from a given node
// to be used in bool flow ir code
char* get_T(nodeType* n)
{
	 switch(n->type)
		{
	  case typeConI:
			return n->con_i.T;
			break;
	  case typeConC:
			return n->con_c.T;
			break;
	  case typeConF:
			return n->con_f.T;
			break;
	  case typeOpr:
			return n->opr.T;
			break;
	  case typeId:
			return n->id.T;
			break;
	  case typeConB:
			return n->con_b.T;
			break;			
	  default:
				printf("Can't get T for unknown node type\n");
		}
}

nodeType* con_i(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_iNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type = typeConI;
	p->con_i.value = value;
	p->con_i.datatype = MY_INT;
	memset(buffer,0,BUFFSIZE);
	sprintf(buffer,"%d",value);
	p->con_i.place = strdup(buffer);
	p->con_i.code = strdup(buffer);
	
	return p;
}
nodeType* con_b(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_bNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConB;
	p->con_b.value=value;
	p->con_b.datatype=MY_BOOL;
	memset(buffer,0,BUFFSIZE);
	sprintf(buffer,"%d",value);
	p->con_b.place = strdup(buffer);
	p->con_b.code = strdup(buffer);
	return p;
}
nodeType* con_f(float value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_fNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConF;
	p->con_f.value=value;
	p->con_f.datatype=MY_FLOAT;
	memset(buffer,0,BUFFSIZE);
	sprintf(buffer,"%f",value);
	p->con_f.place = strdup(buffer);
	p->con_f.code = strdup(buffer);
	return p;
}

nodeType* con_c(char value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_cNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConC;
	p->con_c.value=value;
	p->con_c.datatype=MY_CHAR;
	memset(buffer,0,BUFFSIZE);
	sprintf(buffer,"%d",value);
	p->con_c.place = strdup(buffer);
	p->con_c.code = strdup(buffer);
	return p;
}

// Having installed a ident in the symbol table we call id() with its sym_record pointer
// this creates a node for the ident which will be used in the Syntax Tree
nodeType *id(struct sym_record* symrec)	 
{
	nodeType *p;
	if ((p = malloc(sizeof(idNodeType))) == NULL)
		yyerror("out of memory");
	p->type = typeId;
	p->id.symrec = symrec;
	printf("SSSSSSSSS%dSSSSSSSSSSS  %s\n",p->type,p->id.symrec->sym_name);
	p->id.code = strdup(symrec->sym_name);
	p->id.place = strdup(symrec->sym_name);
	return p;
}

nodeType* empty(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(oprNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type = typeOpr;
	p->opr.oper = value;
	return p;
}

//
// 
nodeType *opr(int oper, int nops, ...) 
{
	va_list ap;
	nodeType *p;
	size_t size;
	int i;
	size = sizeof(oprNodeType) + (nops-1) * sizeof(nodeType*);
	if ((p = malloc(size)) == NULL)
		yyerror("out of memory");
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
		p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
	return p;
}

// GIGLAMESH
struct sym_record* install(char* sym_name)
{
	printf("installing %s\n",sym_name);
	struct sym_record* r;
	int rv=search_keywords(sym_name);
	if(rv==1)
		printf("using reserved keyword\n");
	else
	{
		r=search(current_st,sym_name);
		if(r==NULL)	// sym_name not already in table add it
		{
			//printf("I AM HERE\n");
			r=insert(current_st,sym_name);
			printf("install complete\n");
			return r;
		}
		else	// oops the name already exists
		{
			if(r->is_class==1)
			{
				r=insert(current_st,sym_name);
				printf("install complete\n");
				return r;
			}	
			else
				printf("BIG PROBLEM\n");
		// what to do here?? do we check scope or not
		}
	}
	printf("outside install\n");
}

// prints header info for the output il file
void print_header()
{
	printf(".assembly extern mscorlib {} \n");
	fprintf(output,".assembly extern mscorlib {} \n");
	printf(".assembly output\n");
	fprintf(output,".assembly output\n");
	printf("{\n");
	fprintf(output,"{\n");
	printf(".ver  0:0:0:0\n");
	fprintf(output,".ver  0:0:0:0\n");
	printf("}\n");
	fprintf(output,"}\n");
	printf(".module output.exe\n");
	fprintf(output,".module %s.exe\n",out_file);
}

// debugging utility function
// no general use
void traverse(nodeType* n)
{
 if(n->type == typeOpr)
	{
		 printf("found opr node\n");
		 int number = n->opr.nops;
		 int count = 0;
		 while(count < number)
		 {
			 traverse(get_operand(n,count));
			 count++;
		 }
		 printf("Parent Node Type:%d \n",n->type);
	}
 else
	 printf("Node Type:%d \n",n->type);
}	

// inserts a label into the queue 
// for use in switch case scenarios
void insert_queue(nodeType* n, char* label)
{
	expr_queue[queue_length] = n;
	strcpy(label_queue[queue_length],label);		// strcpy used GIGLAMESH
	queue_length++;
}

// chooses correct instruction to store a variable which might be any of stloc starg etc
// NEED TO ADD FOR OBJECTS GIGLAMESH
void print_store_var(nodeType* n)
{
	if(n->type != typeId)
		{
			printf("Trying to store into non variable \n");
			exit(0);
		}	
	if(n->id.symrec->formal !=1 && n->id.symrec->is_field !=1)
		{
			printf("stloc %s\n",n->id.symrec->uid);
			fprintf(output,"stloc %s\n",n->id.symrec->uid);
		}
	else if(n->id.symrec->is_field==1)
		{
			printf("stfld ");
			fprintf(output,"stfld ");
			print_type(n);
			printf("%s::",n->id.symrec->in_st_of);
			fprintf(output,"%s::",n->id.symrec->in_st_of);
			printf("%s\n",n->id.symrec->sym_name);
			fprintf(output,"%s\n",n->id.symrec->sym_name);
		}		
	else
		{
			printf("starg %s \n",n->id.symrec->uid);
			fprintf(output,"starg %s \n",n->id.symrec->uid);
		}
}

// chooses correct instruction to load a variable which might be any of ldloc ldarg etc
// NEED TO ADD FOR OBJECTS GIGLAMESH
void print_load_var(nodeType* n)
{
	if(n->type != typeId)
		{
			printf("Trying to load a non variable \n");		// for safety against ldc.i4 needs
			exit(0);
		}
	if(n->id.symrec->formal !=1 && n->id.symrec->is_field !=1)		// formal flag off so must be local
		{
			printf("ldloc %s\n",n->id.symrec->uid);
			fprintf(output,"ldloc %s\n",n->id.symrec->uid);
		}
	else if(n->id.symrec->is_field==1)
		{
			printf("ldfld ");
			fprintf(output,"ldfld ");
			print_type(n);
			printf("%s::",n->id.symrec->in_st_of);
			fprintf(output,"%s::",n->id.symrec->in_st_of);
			printf("%s\n",n->id.symrec->sym_name);
			fprintf(output,"%s\n",n->id.symrec->sym_name);
		}	
	else 			// must be a local variable
		{
			printf("ldarg %s \n",n->id.symrec->uid);
			fprintf(output,"ldarg %s \n",n->id.symrec->uid);
		}
}	

