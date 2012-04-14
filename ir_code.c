#include "ir_code.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
extern int generate(nodeType *n);
extern FILE* output;
extern int queue_length;	//the number of case statements minus one
extern int idno;


// global variables
char mybuf[100];
int main_found=0;			// flags for main
int main_was_found=0;

int seen_bool_flow=0;		// flag for bool codegen
int in_assign=0;
int seen_bool_and_or=0;
int relop_flow = 0;

int in_func=0;
int prepost_put = 0;
nodeType* root;
nodeType* expr_queue[MAXQUEUE];
char label_queue[MAXQUEUE][16];
char switch_label[16];
char break_label[16];
char curr_class_name[64];
int loop_flag = 0;
int switch_flag = 0;
char continue_label[16];
char thread_id[16];

void ir_continue(nodeType* n)
{
	if(loop_flag > 0)		// check if any loop or switch is active (must be active for valid break)
	{
		debugger("br %s\n",continue_label);			
		fprintf(output,"br %s\n",continue_label);
	}
	else
		debugger("STRAY BREAK\n");
}	

// recursive function to print .fields public etc for all fields of a class
void ir_fieldlist(nodeType* n)
{
	if(n->opr.oper==EMPTY)		// base case 1
		return;
	nodeType* lc=get_operand(n,0);		
	nodeType* rc=get_operand(n,1);
	nodeType* s;
	if(n->opr.oper==FIELD_ARG)		// base case when list degenerates to single arg
	{
		s=get_operand(n,0);
		debugger(" .field public ");				// all fields are public !!!
		fprintf(output," .field public ");
		print_type(get_operand(n,1));
		debugger(" %s ",s->id.symrec->sym_name); 	// get the uid and print it
		fprintf(output," %s ",s->id.symrec->sym_name); 	// get the uid and print it
		return;
	}
	else 						// else recurse on the formal arg list of lc 
	{
		ir_fieldlist(lc);
		debugger("\n");
		fprintf(output,"\n");
	}	
	ir_fieldlist(rc);		// finally print the right child (actually just a formal arg)
	return;
}

// Working correctly
// generates code for class decln
void ir_class_decln(nodeType* n)
{
	nodeType* mod=get_operand(n,0);
	nodeType* class_name=get_operand(n,1);
	nodeType* field_list=get_operand(n,2);
	nodeType* body=get_operand(n,3);
	nodeType* first_func;		// for first fun in body
	strcpy(curr_class_name,class_name->id.symrec->sym_name);	//
	
	debugger("%s IS CURR CLASS\n",curr_class_name);
	debugger(".class ");
	
	fprintf(output,".class ");
	switch(mod->con_i.value)		// print modifer info
	{
		case modPUBLIC:
			debugger("public "); 
			fprintf(output,"public "); 
			break;
		case modPRIVATE:
			debugger("private "); 
			fprintf(output,"private "); 
			break;
		case modPROTECTED:
			debugger("protected "); 
			fprintf(output,"protected "); 
			break;				
	}
	// rest is basically the default class constructor which inherits the object class
	debugger("auto ansi beforefieldinit "); 
	fprintf(output,"auto ansi beforefieldinit "); 
	debugger("%s ",class_name->id.symrec->sym_name);
	fprintf(output,"%s ",class_name->id.symrec->sym_name);
	debugger("extends [mscorlib]System.Object\n");
	fprintf(output,"extends [mscorlib]System.Object\n");
	debugger("{\n");
	fprintf(output,"{\n");
	// to print field info now 
	ir_fieldlist(field_list);		// .field public type fieldname 
	debugger("\n");
	fprintf(output,"\n");
	// to search for constructor method
	nodeType* p=body;		// in general p is a fundeflist node
	nodeType* lc;
	while(p->opr.oper!=FUNC)	// iterate till you get left most function
	{
		lc=get_operand(p,0);	// look at left child	
		debugger("%d is p's oper\n",p->opr.oper);
		p=lc;
	}
	first_func=get_operand(p,2);
	debugger("%d is p's oper\n",p->opr.oper);		
	debugger("%s is name\n",first_func->id.symrec->sym_name);	// get name of first child
	
	if(strcmp(curr_class_name,first_func->id.symrec->sym_name)==0)	// constructor found
	{
		
		debugger("NON DEFAULT CONSTR FOUND\n");
		
		// copy constr sign into class symrec so that class also has signature
		strcpy(class_name->id.symrec->signature,first_func->id.symrec->signature);
		
		debugger("ASSIGNED CLASS SIGNATURE %s \n",class_name->id.symrec->signature);
		
		ir_constructor(p);
	}
	else
	{
		default_constructor();
	}
	
	generate(body);
	
	debugger("}\n");
	fprintf(output,"}\n");
}

// expects a fundef node 
// constructor cant be static 
// so static node will have no relevance here
void ir_constructor(nodeType* n)
{
	nodeType* modifier = get_operand(n,0);		// modifier node
	nodeType* static_or_not = get_operand(n,1);		// static node
	nodeType* fun_name = get_operand(n,2);	
	nodeType* formal_arguments = get_operand(n,3);
	nodeType* return_type =get_operand(n,4);
	nodeType* compound =get_operand(n,5);
	
	debugger("SIGNATURE OF CONSTR %s\n",fun_name->id.symrec->signature);
	
	debugger(".method public hidebysig specialname rtspecialname instance default void '.ctor' (");
	fprintf(output,".method public hidebysig specialname rtspecialname instance default void '.ctor' (");
	print_formal_args(formal_arguments);
	fprintf(output,")  cil managed \n");
   
    debugger("{\n");
    fprintf(output,"{\n");
	
	debugger("\t.maxstack %d\n",MAXSTACK_SIZE);
	fprintf(output,"\t.maxstack %d\n",MAXSTACK_SIZE);
	debugger("\tldarg.0\n");
	fprintf(output,"\tldarg.0\n");
	debugger("\tcall instance void object::'.ctor'()\n");
	fprintf(output,"\tcall instance void object::'.ctor'()\n");
		
	generate(compound);			// this needs some special changes
	
	debugger("\tret\n"); 
	fprintf(output,"\tret\n"); 
    debugger("}\n");
    fprintf(output,"}\n");
}

// prints default constructor which is public 
void default_constructor()
{
	debugger(".method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed \n");
    fprintf(output,".method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed \n");
    debugger("{\n");
    fprintf(output,"{\n");
	debugger("\t.maxstack 8\n");
	fprintf(output,"\t.maxstack 8\n");
	debugger("\tldarg.0\n");
	fprintf(output,"\tldarg.0\n");
	debugger("\tcall instance void object::'.ctor'()\n");
	fprintf(output,"\tcall instance void object::'.ctor'()\n");
	debugger("\tret\n"); 
	fprintf(output,"\tret\n"); 
    debugger("}\n");
    fprintf(output,"}\n");
}

// Working correctly
void ir_class_decln_list(nodeType* n)
{
	nodeType* class_decln_list = get_operand(n,0);
	nodeType* class_decln = get_operand(n,1);
	generate(class_decln_list);
	generate(class_decln);
}

// Working correctly
void ir_fun_def_list(nodeType* n)
{
	nodeType* fun_def_list = get_operand(n,0);
	nodeType* fun_def = get_operand(n,1);
	generate(fun_def_list);
	generate(fun_def);
}

void ir_compound_stmt(nodeType* n)
{
	
	debugger("{\n");
	fprintf(output,"{\n");
	
	if(main_found==1)		// main flag set so this is entrypoint
	{
		debugger(" .entrypoint\n");
		fprintf(output," .entrypoint\n");
		main_found=0;
	}
	if(in_func==1)		// in every function need to set max stack 
	{
		debugger(".maxstack %d\n",MAXSTACK_SIZE);		// GIGLAMESH use a define here
		fprintf(output,".maxstack %d\n",MAXSTACK_SIZE);
		in_func=0;
	}
	nodeType* stmtlist = get_operand(n,0);
	memset(stmtlist->opr.next,0,16);
	strcat(stmtlist->opr.next,newlabel());		// attach a new label to stmt next
	generate(stmtlist);
	
	debugger("%s:\n",stmtlist->opr.next);
	fprintf(output,"%s:\n",stmtlist->opr.next);

	debugger("}\n");
	fprintf(output,"}\n");
}

// generates code for assign expression
// is responsible to perform operations like stloc 
void ir_assign(nodeType* n)
{
	nodeType* unary_exp = get_operand(n,0);
	nodeType* assop = get_operand(n,1);
	nodeType* ass_exp = get_operand(n,2);
	
	debugger("Unary_exp TYPE IS %d\n",unary_exp->type);
	debugger("assop TYPE IS %d\n",assop->type);
	debugger("ass_Exp TYPE IS %d\n",ass_exp->type);
	
	switch(assop->con_i.value)
	{
		case EQ:
			debugger("IN EQ OF ASSIGN\n");
			if(unary_exp->opr.oper==ARRAY_INVOC)		// array invoc use arr stelem
			{	
				ir_array_lhs(unary_exp);
				generate(ass_exp);
				debugger("stelem.i4\n");
				fprintf(output,"stelem.i4\n");
			}
			else if(unary_exp->opr.oper==FIELD)			// assign to field  THIS PART NEEDS TO BE INCLUDED IN LATER CASES
			{
				
				ir_load_ref(unary_exp);			// first load the obj ref
				generate(ass_exp);				// generate whatever is to be assigned
				print_store_var(get_operand(unary_exp,1));		// store in field using stfld
				
			}
			else
			{	
				// this will only be used inside constr for field vars
				if(unary_exp->id.symrec->is_field==1)	// inside constructor to print 
				{
					debugger("ldarg.0\n");			// load obj ref which is always 0 in constr
					fprintf(output,"ldarg.0\n");		
				}
				prepost_put = 1;	
				generate(ass_exp);
				prepost_put = 0;
				print_store_var(unary_exp);		// use store_var function to decide instruction
			}	
			break;
		case PLUS_EQ:
			debugger("IN PLUS EQ OF ASSIGN\n");
			if(unary_exp->opr.oper==ARRAY_INVOC)
			{	
				ir_array_lhs(unary_exp);
				ir_array_rhs(unary_exp);
				generate(ass_exp);
				debugger("add\n");
				fprintf(output,"add\n");
				debugger("stelem.i4\n");
				fprintf(output,"stelem.i4\n");
			}
			else
			{			
				print_load_var(unary_exp);		// first load to perform add
				
				prepost_put = 1;
				generate(ass_exp);
				prepost_put = 0;
				
				debugger("add\n");
				fprintf(output,"add\n");
				print_store_var(unary_exp);		// then store value back
			}	
			break;
		case MINUS_EQ:
			debugger("IN MINUS EQ OF ASSIGN\n");
			if(unary_exp->opr.oper==ARRAY_INVOC)
			{	
				ir_array_lhs(unary_exp);
				ir_array_rhs(unary_exp);
				
				generate(ass_exp);
				
				debugger("sub\n");
				fprintf(output,"sub\n");
				debugger("stelem.i4\n");
				fprintf(output,"stelem.i4\n");
			}
			else
			{			
				print_load_var(unary_exp);
				
				prepost_put = 1;
				generate(ass_exp);
				prepost_put = 0;
				
				debugger("sub\n");
				fprintf(output,"sub\n");
				print_store_var(unary_exp);
			}	
			break;
		case MULT_EQ:
			debugger("IN MULT EQ OF ASSIGN\n");
			if(unary_exp->opr.oper==ARRAY_INVOC)
			{	
				ir_array_lhs(unary_exp);
				ir_array_rhs(unary_exp);
				
				generate(ass_exp);
				
				debugger("mul\n");
				fprintf(output,"mul\n");
				debugger("stelem.i4\n");
				fprintf(output,"stelem.i4\n");
			}
			else
			{			
				print_load_var(unary_exp);
				
				prepost_put = 1;
				generate(ass_exp);
				prepost_put = 0;
				
				debugger("mul\n");
				fprintf(output,"mul\n");
				print_store_var(unary_exp);
			}	
			break;

		case DIV_EQ:
			debugger("IN DIV EQ OF ASSIGN\n");
			if(unary_exp->opr.oper==ARRAY_INVOC)
			{	
				ir_array_lhs(unary_exp);
				ir_array_rhs(unary_exp);
				
				generate(ass_exp);
				
				debugger("div\n");
				fprintf(output,"div\n");
				debugger("stelem.i4\n");
				fprintf(output,"stelem.i4\n");
			}
			else
			{			
				print_load_var(unary_exp);
				
				prepost_put = 1;
				generate(ass_exp);
				prepost_put = 0;
				
				debugger("div\n");
				fprintf(output,"div\n");
				print_store_var(unary_exp);
			}	
			break;
		default: debugger("ASSOP DEFAULT\n");
	}
}

// generates code for arithmetic operators like
// plus minus etc and lsh rsh bitwise operations like xor bit and etc
void ir_arithmetic(nodeType* n)
{
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	generate(E2);
	switch(n->opr.oper)
	{
		case PLUS:
			debugger("add\n");
			fprintf(output,"add\n");
			break;
		case MINUS:
			debugger("sub\n");
			fprintf(output,"sub\n");
			break;
		case MULT:
			debugger("mul\n");
			fprintf(output,"mul\n");
			break;
		case DIV:
			debugger("div\n");
			fprintf(output,"div\n");
			break;
		case MODULO:
			debugger("rem\n");
			fprintf(output,"rem\n");
			break;
	
		case BIT_AND:
			debugger("and\n");
			fprintf(output,"and\n");
			break;
		case BIT_OR:
			debugger("or\n");
			fprintf(output,"or\n");
			break;
		case XOR:
			debugger("xor\n");
			fprintf(output,"xor\n");
			break;
		case LSH:
			debugger("ldc.i4.s 0x1f\n");
			fprintf(output,"ldc.i4.s 0x1f\n");
			debugger("and\n");
			fprintf(output,"and\n");
			debugger("shl\n");
			fprintf(output,"shl\n");
			break;
		case RSH:
			debugger("ldc.i4.s 0x1f\n");
			fprintf(output,"ldc.i4.s 0x1f\n");
			debugger("and\n");
			fprintf(output,"and\n");
			debugger("shr\n");
			fprintf(output,"shr\n");
			break;
		default:
			debugger("arithmetic default\n");
			fprintf(output,"arithmetic default\n");
	}
}

// takes a node as argument and prints appropriate machine instruction to identify it
// eg will print int32 for integer node send as argument
void print_type(nodeType* n)
{
	if(n->type==typeId)
	{
		switch(n->id.symrec->type)
		{
			case MY_INT:
				debugger("int32 ");
				fprintf(output,"int32 ");
				break;
			case MY_FLOAT:	
				debugger("float32 ");
				fprintf(output,"float32 ");
				break;
			case MY_CHAR:
				debugger("char ");
				fprintf(output,"char ");
				break;
			case MY_BOOL:
				debugger("bool ");
				fprintf(output,"bool ");
				break;
			case MY_VOID:
				debugger("void ");
				fprintf(output,"void ");
				break;
			default:
				debugger("IN DEFAULT OF PRINT TYPE\n");		// GIGLAMESH
		}

	}
	else
	{
		switch(n->con_i.value)
		{
			case MY_INT:
				debugger("int32 ");
				fprintf(output,"int32 ");
				break;
			case MY_FLOAT:	
				debugger("float32 ");
				fprintf(output,"float32 ");
				break;
			case MY_CHAR:
				debugger("char ");
				fprintf(output,"char ");
				break;
			case MY_BOOL:
				debugger("bool ");
				fprintf(output,"bool ");
				break;
			case MY_VOID:
				debugger("void ");
				fprintf(output,"void ");
				break;
			default:
				debugger("IN DEFAULT OF PRINT TYPE\n");		// GIGLAMESH
		}
	}
	return;
}

// recursive function which prints the formal args given a node of formal arg list
void print_formal_args(nodeType* n)
{
	if(n->opr.oper==EMPTY)		// base case 1
		return;
	nodeType* lc=get_operand(n,0);
	nodeType* rc=get_operand(n,1);
	nodeType* s;
	if(n->opr.oper==FORMAL_ARG)		// base case when list degenerates to single arg
	{
		print_type(get_operand(n,1));
		s=get_operand(n,0);
		debugger(" %s ",s->id.symrec->uid); 	// get the uid and print it
		fprintf(output," %s ",s->id.symrec->uid); 
		return;
	}
	else 						// else recurse on the formal arg list of lc 
	{
		print_formal_args(lc);
		debugger(",");
		fprintf(output,",");
	}	
	print_formal_args(rc);		// finally print the right child (actually just a formal arg)
	return;
}

void create_formal_args(nodeType* n)
{
	if(n->opr.oper==EMPTY)
		return;
	nodeType* lc=get_operand(n,0);
	nodeType* rc=get_operand(n,1);
	nodeType* s;
	if(n->opr.oper==FORMAL_ARG)
	{
		s=get_operand(n,1);
		switch(s->con_i.value)
		{
				case MY_INT: 
							strcat(mybuf," int32 ");
							break;
				case MY_FLOAT: 
							strcat(mybuf," float32 "); 
							break;
				case MY_BOOL:
							strcat(mybuf," bool ");
							break;
				default:	
							strcat(mybuf," unhandled type ");
							break;					
		}
		return;
	}
	else
	{
		create_formal_args(lc);
		strcat(mybuf,",");
	}	
	create_formal_args(rc);
	return;
}
void insert_signature(nodeType* fun_name,nodeType* formalarg,nodeType* return_type)
{
	debugger("DOING SIGNATURE\n");
	if(fun_name==NULL || return_type==NULL)
			yyerror("function name or return type not in symbol table");
	else
	{	
		memset(fun_name->id.symrec->signature,0,100);
		switch(return_type->con_i.value)
		{
			case MY_INT:
						strcat(fun_name->id.symrec->signature,"int32 ");
						break;
			case MY_FLOAT:
						strcat(fun_name->id.symrec->signature,"float32 ");
						break;			
			case MY_VOID:
						strcat(fun_name->id.symrec->signature,"void ");
						break;			
		}
		strcat(fun_name->id.symrec->signature,"class ");
		strcat(fun_name->id.symrec->signature,fun_name->id.symrec->my_st->parent->owner_name);
		strcat(fun_name->id.symrec->signature,"::");
		if(strcmp(fun_name->id.symrec->my_st->parent->owner_name,fun_name->id.symrec->sym_name)==0)
		{
			strcat(fun_name->id.symrec->signature,"'.ctor'");
		}
		else
		{
			strcat(fun_name->id.symrec->signature,fun_name->id.symrec->sym_name);
		}	
		strcat(fun_name->id.symrec->signature," ( ");
		
		memset(mybuf,0,100);
		create_formal_args(formalarg);
		
		strcat(fun_name->id.symrec->signature,mybuf);
		memset(mybuf,0,100);
		strcat(fun_name->id.symrec->signature," ) ");
		
		debugger("FINAL SIGNATURE:%s\n",fun_name->id.symrec->signature);
	}	
}

void ir_fun_def(nodeType* n)
{
	nodeType* mods = get_operand(n,0);	
	nodeType* static_or_not = get_operand(n,1);	
	nodeType* fun_name = get_operand(n,2);	
	nodeType* formal_arguments = get_operand(n,3);
	nodeType* return_type =get_operand(n,4);
	nodeType* compound =get_operand(n,5);

	if(strcmp(curr_class_name,fun_name->id.symrec->sym_name)==0)		// this function is some class's constructor method
	{
		return;		// must have dealt with eariler so skip
	}

	// all are public or private right now
	debugger(".method ");
	fprintf(output,".method ");
	if(mods->con_i.value!=EMPTY)		// if static node is not empty the method is private 
	{
		debugger("private ");
		fprintf(output,"private ");
	}
	
	else
	{
		debugger("public ");
		fprintf(output,"public ");
	}
	
	if(static_or_not->opr.oper!=EMPTY)		// if static node is not empty the method is static 
	{
		debugger("static ");
		fprintf(output,"static ");
		fun_name->id.symrec->is_static=1;		// method is static
	}
	if(strcmp(fun_name->id.symrec->sym_name,"main")==0)		// func name is main so main found
	{
		main_found=1;
		main_was_found=1;
	}
	
	print_type(return_type);		// print return type info
	debugger("%s",fun_name->id.symrec->sym_name);	// print func name
	fprintf(output,"%s",fun_name->id.symrec->sym_name);
		
	debugger("(");
	fprintf(output,"(");
	print_formal_args(formal_arguments);		// print formal args
	debugger(") cil managed\n");
	fprintf(output,") cil managed\n");
	in_func=1;
	generate(compound);				// generate the body
}

void print_vardec_code(nodeType* Idlist,nodeType* Type)
{
	if(Idlist->type==typeId)
	{
		print_type(Type);
		debugger(" %s ",Idlist->id.symrec->uid); 
		fprintf(output," %s ",Idlist->id.symrec->uid); 
		return;
	}
	else
	{
		nodeType* lc=get_operand(Idlist,0);
		nodeType* rc=get_operand(Idlist,1);
		print_vardec_code(lc,Type);
		debugger(",");
		fprintf(output,",");
		print_type(Type);
		debugger(" %s ",rc->id.symrec->uid); 
		fprintf(output," %s ",rc->id.symrec->uid); 
	}	
	return;
}

void ir_var_dec(nodeType* n)
{
	nodeType* Idlist = get_operand(n,0);
	nodeType* Type = get_operand(n,1);
	debugger(".locals init(");
	fprintf(output,".locals init(");
	print_vardec_code(Idlist,Type);
	debugger(")\n");
	fprintf(output,")\n");
}

// NEED TO PUT FLAG FOR CONTROL FLOW AND EXPRESSION 
void ir_relop(nodeType* n)
{
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	generate(E2);
	switch(n->opr.oper)
	{
		case LT:
			debugger("clt\n");
			fprintf(output,"clt\n");
			break;
		case GT:
			debugger("cgt\n");
			fprintf(output,"cgt\n");
			break;
		case LE:
			debugger("cgt\n");
			fprintf(output,"cgt\n");
			debugger("ldc.i4.0\n");
			fprintf(output,"ldc.i4.0\n");
			debugger("ceq\n");
			fprintf(output,"ceq\n");
			break;
		case GE:
			debugger("clt\n");
			fprintf(output,"clt\n");
			debugger("ldc.i4.0\n");
			fprintf(output,"ldc.i4.0\n");
			debugger("ceq\n");
			fprintf(output,"ceq\n");
			break;
		default:
			debugger("Relational default\n");
	}
}

void ir_bool(nodeType* n)
{
	debugger("in ir_bool\n");
	nodeType* B1 = get_operand(n,0);
	nodeType* B2 = get_operand(n,1);
	char* label1;
	char* label2;
	switch(n->opr.oper)
	{
		case NEQ:
			generate(B1);
			generate(B2);
			debugger("ceq\n");
			fprintf(output,"ceq\n");
			debugger("ldc.i4.0\n");
			fprintf(output,"ldc.i4.0\n");
			debugger("ceq\n");
			fprintf(output,"ceq\n");
			break;
		case BOOL_EQ:
			generate(B1);
			generate(B2);
			debugger("ceq\n");
			fprintf(output,"ceq\n");
			break;
		case BOOL_OR:
			generate(B1);
			label1 = strdup(newlabel());
			debugger("brtrue %s\n",label1);
			fprintf(output,"brtrue %s\n",label1);
			generate(B2);
			label2 = strdup(newlabel());
			debugger("br.s %s\n",label2);
			fprintf(output,"br.s %s\n",label2);
			debugger("%s: ldc.i4.1 \n",label1);
			fprintf(output,"%s: ldc.i4.1 \n",label1);
			debugger("%s: ",label2);
			fprintf(output,"%s: ",label2);
			break;
		case BOOL_AND:
			generate(B1);
			label1 = strdup(newlabel());
			debugger("brfalse %s\n",label1);
			fprintf(output,"brfalse %s\n",label1);
			generate(B2);
			label2 = strdup(newlabel());
			debugger("br.s %s\n",label2);
			fprintf(output,"br.s %s\n",label2);
			debugger("%s: ldc.i4.0\n",label1);
			fprintf(output,"%s: ldc.i4.0\n",label1);
			debugger("%s: ",label2);
			fprintf(output,"%s: ",label2);
			break;
		default: debugger("Bool DEFAULT\n");
	}
}

void ir_explist(nodeType* n)
{
	nodeType* exp=get_operand(n,0);
	nodeType* assexp=get_operand(n,1);
	generate(exp);
	generate(assexp);
}

void ir_fun_invoc(nodeType* n)
{
	nodeType* func_name = get_operand(n,0);
	nodeType* explist = get_operand(n,1);
	if(func_name->opr.oper==FIELD)			// is of type objref.method and method is definitely not static
	{
			nodeType* objref=get_operand(func_name,0);
			nodeType* method=get_operand(func_name,1);
			
			print_load_var(objref);		// load the obj ref first
			
			generate(explist);		// generate arguments
			
			debugger("callvirt instance %s\n",method->id.symrec->signature);		// as method is not static so callvirt used
			fprintf(output,"callvirt instance %s\n",method->id.symrec->signature);
			
	}
	else if(strcmp(func_name->id.symrec->sym_name,"println")==0)  		// println function for ints
	{
		generate(explist);
		debugger("call void [mscorlib]System.Console::WriteLine");
		debugger("(");
		debugger("int32");
		debugger(")\n");

		fprintf(output,"call void [mscorlib]System.Console::WriteLine");
		fprintf(output,"(");
		fprintf(output,"int32");
		fprintf(output,")\n");
	}
	else if(strcmp(func_name->id.symrec->sym_name,"print")==0) 		// print function for ints
	{
		generate(explist);
		debugger("call void [mscorlib]System.Console::Write");
		debugger("(");
		debugger("int32");
		debugger(")\n");

		fprintf(output,"call void [mscorlib]System.Console::Write");
		fprintf(output,"(");
		fprintf(output,"int32");
		fprintf(output,")\n");
	}
	else if(strcmp(func_name->id.symrec->sym_name,"scanf")==0)		//scanf function for ints
	{
		debugger("call string class [mscorlib]System.Console::ReadLine()\n");
		debugger("call int32 int32::Parse(string)\n");

		fprintf(output,"call string class [mscorlib]System.Console::ReadLine()\n");
		fprintf(output,"call int32 int32::Parse(string)\n");
	}
	else    				// 
	{
		debugger("Method Called in same class it belongs %s\n",func_name->id.symrec->in_st_of);
		if(strcmp(curr_class_name,func_name->id.symrec->in_st_of)==0 && func_name->id.symrec->is_static!=1)
		{	
			debugger("Method invoc in same class it method:%s class:%s\n",func_name->id.symrec->in_st_of,curr_class_name);
			debugger("ldarg.0\n");
			fprintf(output,"ldarg.0\n");
		}
		generate(explist);		//generate arguments
		debugger("call ");
		fprintf(output,"call ");
		debugger("%s ",func_name->id.symrec->signature);		// call using signature
		fprintf(output,"%s \n",func_name->id.symrec->signature);
	}	
}

void ir_return(nodeType* n)
{
	if(n->opr.nops != 0)
	{
		nodeType* return_exp = get_operand(n,0);
		generate(return_exp);
	}
	debugger("ret \n");
	fprintf(output,"ret \n");
}
				
void ir_relop_flow(nodeType* n)
{
	int temp_bool_flow = seen_bool_flow;
	seen_bool_flow = 0;
	nodeType* B1 = get_operand(n,0);
	nodeType* B2 = get_operand(n,1);
	generate(B1);
	generate(B2);
	switch(n->opr.oper)
	{
		case LT:
			debugger("MATCHED LT in ir_relop_flow\n");
			debugger("blt %s\n",get_T(n));
			fprintf(output,"blt %s\n",get_T(n));
			debugger("br %s\n",get_F(n));
			fprintf(output,"br %s\n",get_F(n));
			break;
		case GT:
			debugger("MATCHED GT in ir_relop_flow\n");
			debugger("bgt %s\n",get_T(n));
			fprintf(output,"bgt %s\n",get_T(n));
			debugger("br %s\n",get_F(n));
			fprintf(output,"br %s\n",get_F(n));
			break;
		case LE:
			debugger("MATCHED LE in ir_relop_flow\n");
			debugger("ble %s\n",get_T(n));
			fprintf(output,"ble %s\n",get_T(n));
			debugger("br %s\n",get_F(n));
			fprintf(output,"br %s\n",get_F(n));
			break;
		case GE:
			debugger("MATCHED GE in ir_relop_flow\n");
			debugger("bge %s\n",get_T(n));
			fprintf(output,"bge %s\n",get_T(n));
			debugger("br %s\n",get_F(n));
			fprintf(output,"br %s\n",get_F(n));
			break;
		default:
			debugger("Relational Flow default\n");
	}
	seen_bool_flow = temp_bool_flow;
}
void ir_if(nodeType* n)
{
	nodeType* expr = get_operand(n,0);
	nodeType* stmt = get_operand(n,1);
	set_T(expr,newlabel());
	set_F(expr,n->opr.next);
	
	memset(stmt->opr.next,0,16);
	strcat(stmt->opr.next,n->opr.next);
	
	debugger("expr true label:%s\n",get_T(expr));
	debugger("expr false label:%s\n",get_F(expr));
	
	seen_bool_flow = 1;prepost_put = 1;
	
	generate(expr);
	
	seen_bool_flow = 0;prepost_put = 0;
	
	debugger("%s:\n",get_T(expr));
	fprintf(output,"%s:\n",get_T(expr));
	
	generate(stmt);
	
	return;
}	
void ir_if_else(nodeType* n)
{
	nodeType* expr = get_operand(n,0);
	nodeType* stmt1 = get_operand(n,1);
	nodeType* stmt2 = get_operand(n,2);
	set_T(expr,newlabel());
	set_F(expr,newlabel());
	
	memset(stmt1->opr.next,0,16);
	memset(stmt2->opr.next,0,16);
	strcpy(stmt1->opr.next,n->opr.next);
	strcpy(stmt2->opr.next,n->opr.next);
	
	seen_bool_flow = 1;prepost_put = 1;
	generate(expr);
	seen_bool_flow = 0;prepost_put = 0;
	
	debugger("%s:\n",get_T(expr));
	fprintf(output,"%s:\n",get_T(expr));
	generate(stmt1);
	debugger("br.s %s\n ",n->opr.next);
	fprintf(output,"br.s %s\n",n->opr.next);
	debugger("%s:\n",get_F(expr));
	fprintf(output,"%s:\n",get_F(expr));
	generate(stmt2);
}	
void ir_ternary(nodeType* n)
{
	nodeType* expr = get_operand(n,0);
	nodeType* stmt1 = get_operand(n,1);
	nodeType* stmt2 = get_operand(n,2);
	set_T(expr,newlabel());
	set_F(expr,newlabel());
	memset(stmt1->opr.next,0,16);
	memset(stmt2->opr.next,0,16);
	memset(n->opr.next,0,16);
	strcpy(stmt1->opr.next,n->opr.next);
	strcpy(stmt2->opr.next,n->opr.next);
	strcpy(n->opr.next,newlabel());
	
	seen_bool_flow = 1;
	generate(expr);
	seen_bool_flow = 0;
	
	debugger("%s:\n",get_T(expr));
	fprintf(output,"%s:\n",get_T(expr));
	prepost_put = 1;
	generate(stmt1);
	prepost_put = 0;
	debugger("br.s %s\n ",n->opr.next);
	fprintf(output,"br.s %s\n",n->opr.next);
	debugger("%s:\n",get_F(expr));
	fprintf(output,"%s:\n",get_F(expr));
	prepost_put = 1;
	generate(stmt2);
	prepost_put = 0;
	debugger("%s:\n",n->opr.next);
	fprintf(output,"%s:\n",n->opr.next);
}	
void ir_while(nodeType* n)
{
	nodeType* expr = get_operand(n,0);
	nodeType* stmt = get_operand(n,1);
	char begin[16];
	memset(begin,0,16);
	strcat(begin,newlabel());
	set_T(expr,newlabel());
	set_F(expr,n->opr.next);
	memset(stmt->opr.next,0,16);
	strcpy(stmt->opr.next,begin);
	debugger("%s:\n",begin);
	fprintf(output,"%s:\n",begin);
	
	seen_bool_flow = 1;prepost_put = 1;
	generate(expr);
	seen_bool_flow = 0;prepost_put = 0;
	
	debugger("%s:\n",get_T(expr));
	fprintf(output,"%s:\n",get_T(expr));

	//##for break statement##
	char initial_break_label[16];
	memset(initial_break_label,0,16);
	strcat(initial_break_label,break_label);
	memset(break_label,0,16);
	loop_flag = loop_flag + 1;
	strcat(break_label,n->opr.next);
	//#####for continue statement############
	char initial_continue_label[16];
	memset(initial_continue_label,0,16);
	strcpy(initial_continue_label,continue_label);
	memset(continue_label,0,16);
	strcpy(continue_label,begin);
	debugger("CONTINUE LABEL: %s\n",continue_label);
	//#######################################

	
	generate(stmt);
	
	debugger("br.s %s\n ",begin);
	fprintf(output,"br.s %s\n",begin);

	//for break statement
	loop_flag = loop_flag - 1;
	memset(break_label,0,16);
	strcat(break_label,initial_break_label);
	memset(continue_label,0,16);
	strcpy(continue_label,initial_continue_label);	
}	
	
void ir_bool_flow(nodeType* n)
{
	nodeType* B1 = get_operand(n,0);
	nodeType* B2 = get_operand(n,1);
	debugger("n true label:%s\n",get_T(n));
	debugger("n false label:%s\n",get_F(n));
	switch(n->opr.oper)
	{
	case BOOL_OR:
		debugger("MATCHED BOOL_OR in ir_bool_flow\n");
		set_T(B1,n->opr.T);
		set_F(B1,newlabel());
		set_T(B2,n->opr.T);
		set_F(B2,n->opr.F);
		generate(B1);
		debugger("%s:",get_F(B1)); 
		fprintf(output,"%s:",get_F(B1)); 
		debugger("seen_bool_flow : %d\n",seen_bool_flow);
		generate(B2);
		break;
	case BOOL_EQ:
		//the rule is to load value of B1 and B2 on stack then use beq to jump accordingly so we have to switch of seen_bool_flow flag and restart later.
		seen_bool_flow = 0;
		generate(B1);
		generate(B2);
		seen_bool_flow = 1;
		debugger("MATCHED BOOL_EQ in ir_relop_flow\n");
		debugger("beq %s\n",get_T(n));
		fprintf(output,"beq %s\n",get_T(n));
		debugger("br %s\n",get_F(n));
		fprintf(output,"br %s\n",get_F(n));
		break;
	case NEQ:
		debugger("NOT EQUAL TO\n");
		//the rule is to load value of B1 and B2 on stack then use bne.un to jump accordingly so we have to switch of seen_bool_flow flag and restart later.
		seen_bool_flow = 0;
		generate(B1);
		generate(B2);
		seen_bool_flow = 1;
		debugger("MATCHED NEQ in ir_relop_flow\n");
		debugger("bne.un %s\n",get_T(n));
		fprintf(output,"bne.un %s\n",get_T(n));
		debugger("br %s\n",get_F(n));
		fprintf(output,"br %s\n",get_F(n));
		break;
	case BOOL_AND:
		set_T(B1,newlabel());
		set_F(B1, get_F(n));
		set_T(B2, get_T(n));
		set_F(B2, get_F(n));
		generate(B1);
		debugger("%s:",get_T(B1)); 
		fprintf(output,"%s:",get_T(B1)); 
		generate(B2);
		break;
	default: debugger("Bool DEFAULT\n");
	}
	
}

void ir_idlist(nodeType* n)
{
	nodeType* Idlist = get_operand(n,0);
	nodeType* ident = get_operand(n,1);
	generate(Idlist);
}	

void ir_stmtlist(nodeType* n)
{
	nodeType* Stmtlist = get_operand(n,0);
	nodeType* Stmt = get_operand(n,1);
	memset(Stmtlist->opr.next,0,16);
	strcat(Stmtlist->opr.next,newlabel());
	debugger("Stmtlist next:%s \n",Stmtlist->opr.next);
	debugger("Stmtlist type:%d \n",Stmtlist->type);
	debugger("Stmtlist nops:%d \n",Stmtlist->opr.nops);
	generate(Stmtlist);
	memset(Stmt->opr.next,0,16);
	strcat(Stmt->opr.next,n->opr.next);	
	debugger("%s: \n",Stmtlist->opr.next);
	fprintf(output,"%s: \n",Stmtlist->opr.next);
	generate(Stmt);
}

char* ir_async(nodeType* n)
{
	debugger("Entered Async\n");
	nodeType* func = get_operand(n,0);
	nodeType* fun_name = get_operand(func,0);
	char* sign,*pch;
	sign = strdup(fun_name->id.symrec->signature);
	memset(thread_id,0,16);
	strcpy(thread_id,newuid());
	debugger(".locals init (class [mscorlib]System.Threading.Thread %s)\n",thread_id);
	fprintf(output,".locals init (class [mscorlib]System.Threading.Thread %s)\n",thread_id);
	debugger("ldnull\n");
	fprintf(output,"ldnull\n");
	debugger("ldftn ");
	fprintf(output,"ldftn ");
	
	if(strcmp(sign,"")==0)	
		return;	
	pch = strtok (sign," ::");
	debugger("%s ",pch);
	fprintf(output,"%s ",pch);
	
	debugger("class ");
	fprintf(output,"class ");
	debugger("%s::",fun_name->id.symrec->my_st->parent->owner_name);
	fprintf(output,"%s::",fun_name->id.symrec->my_st->parent->owner_name);
	debugger("%s",fun_name->id.symrec->sym_name);
	fprintf(output,"%s",fun_name->id.symrec->sym_name);
	debugger("()\n");
	fprintf(output,"()\n");
	debugger("newobj instance void class [mscorlib]System.Threading.ThreadStart::'.ctor'(object, native int)\n");
	fprintf(output,"newobj instance void class [mscorlib]System.Threading.ThreadStart::'.ctor'(object, native int)\n");
	debugger("newobj instance void class [mscorlib]System.Threading.Thread::'.ctor'(class [mscorlib]System.Threading.ThreadStart)\n");
	fprintf(output,"newobj instance void class [mscorlib]System.Threading.Thread::'.ctor'(class [mscorlib]System.Threading.ThreadStart)\n");
	debugger("stloc %s\n",thread_id); 
	fprintf(output,"stloc %s\n",thread_id); 
	debugger("ldloc %s\n",thread_id); 
	fprintf(output,"ldloc %s\n",thread_id); 
	debugger("callvirt instance void class [mscorlib]System.Threading.Thread::Start()\n");
	fprintf(output,"callvirt instance void class [mscorlib]System.Threading.Thread::Start()\n");
	return thread_id;
}

void ir_finish(nodeType* n)
{
	//the first child node of n would be a ASYNC_LIST node or ASYNC node...
	debugger("In finish\n");
	nodeType* async_stmt_list = get_operand(n,0);
	char thread_id[16];
	memset(thread_id,0,16);
	if(async_stmt_list->opr.oper == ASYNC)
		{
			debugger("single async in finish\n");
			strcpy(thread_id,ir_async(async_stmt_list));
			debugger("ldloc %s\n",thread_id); 
			fprintf(output,"ldloc %s\n",thread_id); 
			//the below lines perform thread.join operation of the thread just started
			debugger("callvirt instance void class [mscorlib]System.Threading.Thread::Join()\n");
			fprintf(output,"callvirt instance void class [mscorlib]System.Threading.Thread::Join()\n");
		}
	else generate(async_stmt_list);
}	

void ir_async_stmt_list(nodeType* n)
{
	debugger("In ir_async_stmt_list\n");
	nodeType* async_stmt = get_operand(n,0);
	nodeType* async_stmt_list = get_operand(n,1);
	//char thread_id[16];  		// GIGLAMESH !!!
	//since X10 does not associate explicit thread id with a thread during async we generate one explicitly for code gen and store it in thread_id..
	nodeType* temp_node;
	temp_node = n;
	while(n->opr.oper == ASYNC_LIST)
	{
		async_stmt = get_operand(n,0);
		async_stmt_list = get_operand(n,1);
		memset(thread_id,0,16);
		strcpy(thread_id,ir_async(async_stmt));
		debugger("ldloc %s\n",thread_id); 
		fprintf(output,"ldloc %s\n",thread_id); 
		//the below lines perform thread.join operation of the thread just started
		debugger("callvirt instance void class [mscorlib]System.Threading.Thread::Join()\n");
		fprintf(output,"callvirt instance void class [mscorlib]System.Threading.Thread::Join()\n");
		n = async_stmt_list;
	}
	//the loop would break when n->oper.opr is ASYNC so perform its codegen below...
	memset(thread_id,0,16);
	strcpy(thread_id , ir_async(async_stmt_list));
	debugger("ldloc %s\n",thread_id); 
	fprintf(output,"ldloc %s\n",thread_id); 
	debugger("callvirt instance void class [mscorlib]System.Threading.Thread::Join()\n");
	fprintf(output,"callvirt instance void class [mscorlib]System.Threading.Thread::Join()\n");
	memset(thread_id,0,16);
	
}
void ir_for(nodeType* n)
{
	nodeType* initialize = get_operand(n,0);
	nodeType* expr = get_operand(n,1);
	nodeType* increament = get_operand(n,2);
	nodeType* stmt = get_operand(n,3);
	char initializenext[16], begin[16];
	memset(initializenext,0,16);
	memset(begin,0,16);
	strcat(initializenext,newlabel());
	strcat(begin,newlabel());
	set_T(expr,begin);
	set_F(expr,n->opr.next);
	generate(initialize);				//generate code for initialization expression
	
	//##for break statement##
	char initial_break_label[16];
	memset(initial_break_label,0,16);
	strcpy(initial_break_label,break_label);
	memset(break_label,0,16);
	strcpy(break_label,newlabel());
	//#####for continue statement############
	char initial_continue_label[16];
	memset(initial_continue_label,0,16);
	strcpy(initial_continue_label,continue_label);
	memset(continue_label,0,16);
	strcpy(continue_label,newlabel());
	//#######################################
	loop_flag = loop_flag + 1;

	debugger("br %s\n",initializenext);
	fprintf(output,"br %s\n",initializenext);
	debugger("%s: \n",begin);
	fprintf(output,"%s: ",begin);
	
	generate(stmt);
	
	prepost_put = 0;
	debugger("%s:\n",continue_label);
	fprintf(output,"%s:\n",continue_label);
	
	generate(increament);
	
	debugger("%s: ",initializenext);
	fprintf(output,"%s: ",initializenext);
	seen_bool_flow = 1;
	
	generate(expr);
	
	seen_bool_flow = 0;
	debugger("%s: \n",break_label);
	fprintf(output,"%s: \n",break_label);

	//for break statement
	loop_flag = loop_flag - 1;
	memset(break_label,0,16);
	strcpy(break_label,initial_break_label);
	memset(continue_label,0,16);
	strcpy(continue_label,initial_continue_label);
}

void ir_array_declaration(nodeType* n)
{
	nodeType* array_name = get_operand(n,0);
	nodeType* array_type = get_operand(n,1);
	nodeType* array_size = get_operand(n,2);
	
	debugger(".locals init (");
	fprintf(output,".locals init (");
	print_type(array_type);
	debugger("[] ");
	fprintf(output,"[] ");
	debugger(" %s )\n",array_name->id.symrec->uid); 	
	fprintf(output," %s )\n",array_name->id.symrec->uid); 	
	
	generate(array_size);
	
	debugger("newarr [mscorlib]System.Int32\n"); 		// create a new array
	fprintf(output,"newarr [mscorlib]System.Int32\n"); 
	debugger("stloc %s\n",array_name->id.symrec->uid );
	fprintf(output,"stloc %s\n",array_name->id.symrec->uid );
}

void ir_array_lhs(nodeType* n)
{
	nodeType* array_name = get_operand(n,0);
	nodeType* array_index = get_operand(n,1);
	debugger("ldloc %s\n",array_name->id.symrec->uid ); //number[i] = i
	fprintf(output,"ldloc %s\n",array_name->id.symrec->uid ); //number[i] = i
	generate(array_index);
}	

void ir_array_rhs(nodeType* n)
{
	nodeType* array_name = get_operand(n,0);
	nodeType* array_index = get_operand(n,1);
	debugger("ldloc %s\n",array_name->id.symrec->uid ); 
	fprintf(output,"ldloc %s\n",array_name->id.symrec->uid ); 
	generate(array_index);
	debugger("ldelem.i4\n");
	fprintf(output,"ldelem.i4\n");
}


void ir_cast(nodeType* n)
{
	debugger("IN IRCAST\n");
	nodeType* unary_op = get_operand(n,0);
	nodeType* cast_exp = get_operand(n,1);
	if(unary_op->con_i.value == MY_MINUS)
		{
			generate(cast_exp);
			debugger("neg\n");
			fprintf(output,"neg\n");
		}
	else
			generate(cast_exp);
}	


void ir_switch(nodeType* n)
{
	nodeType* expr = get_operand(n,0);
	nodeType* case_stmt_list = get_operand(n,1);
	generate(expr);//after this the value of expr will be on stack
	
	int default_present=0;
	
	char test_label[16];
	char old_break_label[16];	
	char end_label[16];	
	
	memset(test_label,0,16);
	strcat(test_label,newlabel());
	
	//at the starting jump to test the cases. 
	debugger("br %s\n",test_label);
	fprintf(output,"br %s\n",test_label);
	
	switch_flag++;
	
	//label that will appear at the end of switch
	memset(end_label,0,16);
	strcat(end_label,newlabel());

	//maybe someone is already using the break label so save it so as to restore it later
	memset(old_break_label,0,16);
	strcat(old_break_label,break_label);

	//set the label to be used for break statements in switch	
	memset(break_label,0,16);
	strcat(break_label,end_label);
	
	generate(case_stmt_list);
	
	//after default jump to end of switch statement
	debugger("br %s\n",end_label);				
	fprintf(output,"br %s\n",end_label);
	
	//jump here to test the conditions
	debugger("%s:\n",test_label);
	fprintf(output,"%s:\n",test_label);
	
	int count = 0;
	nodeType* const_exp;
	char* label;
	queue_length = queue_length -1;			
	debugger("QUEUE LENGTH:%d\n",queue_length);
	while(count <= queue_length)		//since at the end queue_length is one more than the actual queue length
	{
		const_exp = expr_queue[count];
		
		if(const_exp->type == typeOpr )
		{
			//the below if else handles default statement
			if(const_exp->opr.oper == EMPTY)
			{
				default_present = 1;
				debugger("br %s\n",label_queue[count]);
				fprintf(output,"br %s\n",label_queue[count]);
			}
			else
			{
				generate(const_exp);
				debugger("beq %s\n",label_queue[count]);
				fprintf(output,"beq %s\n",label_queue[count]);
			}
		}
		else
		{
			generate(const_exp);
			debugger("beq %s\n",label_queue[count]);
			fprintf(output,"beq %s\n",label_queue[count]);
		}
		
		
		if(count <= queue_length-1- default_present)		//do not do it after the last statement //recheck this condition
			{
			//debugger("KJKJOK\n");
			generate(expr);				//basically this will load the value of x in switch(x) on the stack 
			}
		count++;
	}

	queue_length = 0;

	debugger("%s:\n",end_label);
	fprintf(output,"%s:\n",end_label);

	switch_flag--;
	memset(break_label,0,16);
	strcat(break_label,old_break_label);
}	


void ir_case_stmt_list(nodeType* n)
{
	nodeType* casestmtlist = get_operand(n,0);
	nodeType* casestmt = get_operand(n,1);
	nodeType* default_stmt = get_operand(n,2);
	generate(casestmtlist);	
	generate(casestmt);	
	generate(default_stmt);	
}	
void ir_case_stmt(nodeType* n)
{
	nodeType* const_exp = get_operand(n,0);
	nodeType* stmt = get_operand(n,1);
	char mylabel[16];
	memset(mylabel,0,16);
	strcat(mylabel,newlabel());
	debugger("%s: ",mylabel);
	fprintf(output,"%s: ",mylabel);
	generate(stmt);
	insert_queue(const_exp,mylabel);
}	

void ir_default_stmt(nodeType* n)
{
	nodeType* stmt = get_operand(n,0);
	char mylabel[16];
	memset(mylabel,0,16);
	strcat(mylabel,newlabel());
	debugger("%s: ",mylabel);
	fprintf(output,"%s: ",mylabel);
	generate(stmt);
	nodeType* const_exp = empty(EMPTY);
	insert_queue(const_exp,mylabel);
}	

void ir_break(nodeType* n)
{
	if(loop_flag > 0 || switch_flag > 0)		// check if any loop or switch is active (must be active for valid break)
	{
		debugger("FOR FLAG\n");
		debugger("br %s\n",break_label);			
		fprintf(output,"br %s\n",break_label);
	}
	else
		debugger("STRAY BREAK\n");
}

void ir_prefix(nodeType* n)
{	
	nodeType* operator = get_operand(n,0);
	nodeType* unary_exp = get_operand(n,1);
	debugger("IN IR PREFIX %d, PP = %d, Prepost flag = %d\n",operator->con_i.value,MY_PP, prepost_put);
	
	print_load_var(unary_exp);
	debugger("ldc.i4 1\n");			// load 1 to add or sub
	fprintf(output,"ldc.i4 1\n");
	
	if(operator->con_i.value==MY_PP)		// if ++ then add instr
	{
		fprintf(output,"add\n");
		debugger("add\n");
	}
	else if(operator->con_i.value==MY_MM)	// if -- then sub instr
	{
		fprintf(output,"sub\n");
		debugger("sub\n");
	}
	print_store_var(unary_exp);				// store the val according to type
	if(prepost_put == 1)
		print_load_var(unary_exp);
}

void ir_postfix(nodeType* n)
{	
	nodeType* operator = get_operand(n,1);
	nodeType* postfix_exp = get_operand(n,0);
	debugger("IN IR POSTFIX %d, PP = %d\n",operator->con_i.value,MY_PP);

	if(prepost_put == 1)
		print_load_var(postfix_exp);
	print_load_var(postfix_exp);
	debugger("ldc.i4 1\n");
	fprintf(output,"ldc.i4 1\n");		
	if(operator->con_i.value==MY_PP)
	{
		debugger("add\n");
		fprintf(output,"add\n");
	}
	else if(operator->con_i.value==MY_MM)
	{
		debugger("sub\n");
		fprintf(output,"sub\n");
	}
	print_store_var(postfix_exp);
}

void ir_obj(nodeType* n)
{
	nodeType* ident = get_operand(n,0);	// ident	
	nodeType* class_name = get_operand(n,1);	// class name
	nodeType* initexplist = get_operand(n,2);	// class name
	
	debugger(".locals init( class\n");
	fprintf(output,".locals init( class");
	
	debugger(" %s ",class_name->id.symrec->sym_name);		// .locals init(class ClassName V12)
	fprintf(output," %s ",class_name->id.symrec->sym_name);
	
	debugger(" %s) \n",ident->id.symrec->uid); 
	fprintf(output," %s) \n",ident->id.symrec->uid);
	
	// generate arguments
	generate(initexplist);
	
	if(strlen(class_name->id.symrec->signature)!=0)		
	{
		// signature found means non default constr specified
		debugger("NULL NAHI MILA\n");
		debugger("newobj instance %s\n",class_name->id.symrec->signature); 
		fprintf(output,"newobj instance %s\n",class_name->id.symrec->signature);	
	}
	else
	{
		// use default constr
		debugger("newobj instance void class %s::'.ctor'()\n",class_name->id.symrec->sym_name); 
		fprintf(output,"newobj instance void class %s::'.ctor'()\n",class_name->id.symrec->sym_name);	
	}
	
	debugger("stloc %s \n",ident->id.symrec->uid); 
	fprintf(output,"stloc %s \n",ident->id.symrec->uid);

}

// expects a unary exp node which has FIELD as oper and loads the reference to object
void ir_load_ref(nodeType* n)
{
	debugger("IN IR_LOAD_REF\n");
	nodeType* ident = get_operand(n,0);	// ident from ident.field	
	debugger("ldloc %s\n",ident->id.symrec->uid ); //	load the object reference
	fprintf(output,"ldloc %s\n",ident->id.symrec->uid ); 
}

// to handle situations 
void ir_method_invoc(nodeType* n)
{
	nodeType* ident = get_operand(n,0);	// ident	
	nodeType* method = get_operand(n,1);	// method
	nodeType* arglist = get_operand(n,2);	// arglist
	ir_load_ref(n);
	generate(arglist);
	
}
