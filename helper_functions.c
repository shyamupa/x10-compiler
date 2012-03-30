#include "helper_functions.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;

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
	sprintf(buffer,"t%d:",tempno++);
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
}
