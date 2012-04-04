#include "helper_functions.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern struct symbol_table* current_st;
char* concat(char* c1,char* c2)
{
	strcat(c1,"\n");
	printf("jbdsah\n");
	strcat(c1,c2);
	printf("jbdsah\n");
	return c1;
}
// Generates new temp and returns the string
// NEEDS global variables buffer and tempno
char* newtmp()
{
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"t%d",tempno++);
	return(buffer);
}
// Generates a newlabel and returns the string 
// NEEDS global variables buffer and labelno
char* newlabel()
{
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"l%d:",labelno++);
	return(buffer);
}
// get_operand takes a nodeType ptr of opr node type
// and returns the operand at position index
nodeType* get_operand(nodeType* opnode,int index)
{
	return opnode->opr.op[index];
}
// NEEDS ASSERT statements
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
int get_type(nodeType* data_type_ptr)
{
	if(data_type_ptr->type==typeConI)
	{
		return data_type_ptr->con_i.datatype;	
	}
	else if(data_type_ptr->type==typeConF)
	{
		return data_type_ptr->con_f.datatype;	
	}
	else if(data_type_ptr->type==typeConC)
	{
		return data_type_ptr->con_c.datatype;	
	}
	else if(data_type_ptr->type==typeId)
	{
		return data_type_ptr->id.symrec->type;
	}
	else if(data_type_ptr->type==typeOpr)
	{
		return data_type_ptr->opr.datatype;
	}
}

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
  default:
			printf("Can't get T for unknown node type\n");
}
}

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
  default:
			printf("Can't get F for unknown node type\n");
}
}

nodeType* con_i(int value)
{
	nodeType *p;
	if((p=malloc(sizeof(con_iNodeType)))==NULL)
	{
		yyerror("out of memory");
	}
	p->type=typeConI;
	p->con_i.value=value;
	p->con_i.datatype=MY_INT;
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"%d",value);
	p->con_i.place = strdup(buffer);
	p->con_i.code = strdup(buffer);
	
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
	bzero(buffer,BUFFSIZE);
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
	bzero(buffer,BUFFSIZE);
	sprintf(buffer,"%d",value);
	p->con_c.place = strdup(buffer);
	p->con_c.code = strdup(buffer);
	return p;
}

// Having installed a ident in the symbol table we call id() with its sym_record pointer
// this creates a node for the ident which will be used in the Syntax Tree
nodeType *id(struct sym_record* symrec)	 
{
	//printf("name is %s\n",i->sym_name);
	nodeType *p;
	if ((p = malloc(sizeof(idNodeType))) == NULL)
		yyerror("out of memory");
	p->type = typeId;
	p->id.symrec = symrec;
	p->id.code = strdup(symrec->sym_name);
	p->id.place = strdup(symrec->sym_name);
	printf("ffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
	printf("%s\n",p->id.symrec->sym_name);
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
	size = sizeof(oprNodeType) + (nops - 1) * sizeof(nodeType*);
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
			r=insert(current_st,sym_name);
			return r;
		}
		else	// oops the name already exists
		{
		// what to do here?? do we check scope or not
		}
	}
}
void print_header()
{
	printf(".assembly extern mscorlib {} \n");
	printf(".assembly output\n");
	printf("{\n");
	printf(".ver  0:0:0:0\n");
	printf("}\n");
	printf(".module output.exe\n");
}


