#include "ir_code.h"

extern char buffer[BUFFSIZE];
extern int tempno;
extern int labelno;
nodeType* root;
extern int generate(nodeType *n);
extern FILE* output;
char mybuf[100];
int main_found=0;
int main_was_found=0;
int in_assign=0;
int in_func=0;
extern int idno;
// Working correctly
void ir_class_decln(nodeType* n)
{
	nodeType* mod=get_operand(n,0);
	nodeType* class_name=get_operand(n,1);
	nodeType* body=get_operand(n,2);
	printf(".class ");
	fprintf(output,".class ");
	switch(mod->con_i.value)
	{
		case modPUBLIC:
				printf("public "); 
				fprintf(output,"public "); 
				break;
		case modPRIVATE:
				printf("private "); 
				fprintf(output,"private "); 
				break;
		case modPROTECTED:
				printf("protected "); 
				fprintf(output,"protected "); 
				break;				
	}
	printf("auto ansi beforefieldinit "); 
	fprintf(output,"auto ansi beforefieldinit "); 
	printf("%s ",class_name->id.symrec->sym_name);
	fprintf(output,"%s ",class_name->id.symrec->sym_name);
	printf("extends [mscorlib]System.Object\n");
	fprintf(output,"extends [mscorlib]System.Object\n");
	printf("{\n");
	fprintf(output,"{\n");
    printf(".method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed \n");
    fprintf(output,".method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed \n");
    printf("{\n");
    fprintf(output,"{\n");
	printf("\t.maxstack 8\n");
	fprintf(output,"\t.maxstack 8\n");
	printf("\tldarg.0\n");
	fprintf(output,"\tldarg.0\n");
	printf("\tcall instance void object::'.ctor'()\n");
	fprintf(output,"\tcall instance void object::'.ctor'()\n");
	printf("\tret\n"); 
	fprintf(output,"\tret\n"); 
    printf("}\n");
    fprintf(output,"}\n");
	generate(body);
	printf("}\n");
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
	//~ free(n);
}
void ir_compound_stmt(nodeType* n)
{
	
	printf("{\n");
	fprintf(output,"{\n");
	
	if(main_found==1)
	{
		printf(" .entrypoint\n");
		fprintf(output," .entrypoint\n");
		main_found=0;
	}
	if(in_func==1)
	{
		printf(".maxstack 50\n");
		fprintf(output,".maxstack 50\n");
		in_func=0;
	}
	nodeType* stmtlist = get_operand(n,0);
	strcat(stmtlist->opr.next,newlabel());
	//~ printf("COMPOUND TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
	//~ traverse(root);
	//~ printf("COMPOUND TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
	generate(stmtlist);
	
	printf("%s:\n",stmtlist->opr.next);
	fprintf(output,"%s:\n",stmtlist->opr.next);

	printf("}\n");
	fprintf(output,"}\n");
	//~ free(n);
}
void ir_assign(nodeType* n)
{
	nodeType* unary_exp = get_operand(n,0);
	nodeType* assop = get_operand(n,1);
	nodeType* ass_exp = get_operand(n,2);
	//~ printf("ASSIGN TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
	//~ traverse(root);
	//~ printf("ASSIGN TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
	
	printf("Unary_exp TYPE IS %d\n",unary_exp->type);
	printf("assop TYPE IS %d\n",assop->type);
	printf("ass_Exp TYPE IS %d\n",ass_exp->type);
	switch(assop->con_i.value)
	{
		case EQ:
			printf("OOOOOOLAALALALALA!!\n");
			//~ printf("ASSEXP VALUE IS %d\n",ass_exp->con_i.value);
			fflush(stdout);
			generate(ass_exp);
			printf("stloc %s\n",unary_exp->id.symrec->uid);
			fprintf(output,"stloc %s\n",unary_exp->id.symrec->uid);
			break;
		case PLUS_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->uid);
			fprintf(output,"ldloc %s\n",unary_exp->id.symrec->uid);
			printf("add\n");
			fprintf(output,"add\n");
			printf("stloc %s",unary_exp->id.symrec->uid);
			fprintf(output,"stloc %s",unary_exp->id.symrec->uid);
			break;
		case MINUS_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->uid);
			fprintf(output,"ldloc %s\n",unary_exp->id.symrec->uid);
			printf("sub\n");
			fprintf(output,"sub\n");
			printf("stloc %s",unary_exp->id.symrec->uid);
			fprintf(output,"stloc %s",unary_exp->id.symrec->uid);
			break;
		case MULT_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->uid);
			fprintf(output,"ldloc %s\n",unary_exp->id.symrec->uid);
			printf("mul\n");
			fprintf(output,"mul\n");
			printf("stloc %s",unary_exp->id.symrec->uid);
			fprintf(output,"stloc %s",unary_exp->id.symrec->uid);
			break;
		case DIV_EQ:
			generate(ass_exp);
			printf("ldloc %s\n",unary_exp->id.symrec->uid);
			fprintf(output,"ldloc %s\n",unary_exp->id.symrec->uid);
			printf("div\n");
			fprintf(output,"div\n");
			printf("stloc %s",unary_exp->id.symrec->uid);
			fprintf(output,"stloc %s",unary_exp->id.symrec->uid);
			break;
		default: printf("ASSOP DEFAULT\n");
	}
}
// Rest working correctly
// NEED TO COMPLETE SHIFT OPERATIONS			
void ir_arithmetic(nodeType* n)
{
	nodeType* E1 = get_operand(n,0);
	nodeType* E2 = get_operand(n,1);
	generate(E1);
	generate(E2);
	switch(n->opr.oper)
	{
		case PLUS:
			printf("add\n");
			fprintf(output,"add\n");
			break;
		case MINUS:
			printf("sub\n");
			fprintf(output,"sub\n");
			break;
		case MULT:
			printf("mul\n");
			fprintf(output,"mul\n");
			break;
		case DIV:
			printf("div\n");
			fprintf(output,"div\n");
			break;
		case BIT_AND:
			printf("and\n");
			fprintf(output,"and\n");
			break;
		case BIT_OR:
			printf("or\n");
			fprintf(output,"or\n");
			break;
		case XOR:
			printf("xor\n");
			fprintf(output,"xor\n");
			break;
		case LSH:
			printf("ldc.i4.s 0x1f\n");
			fprintf(output,"ldc.i4.s 0x1f\n");
			printf("and\n");
			fprintf(output,"and\n");
			printf("shl\n");
			fprintf(output,"shl\n");
			break;
		case RSH:
			printf("ldc.i4.s 0x1f\n");
			fprintf(output,"ldc.i4.s 0x1f\n");
			printf("and\n");
			fprintf(output,"and\n");
			printf("shr\n");
			fprintf(output,"shr\n");
			break;
		default:
			printf("arithmetic default\n");
			fprintf(output,"arithmetic default\n");
	}
}
void print_type(nodeType* n)
{
	switch(n->con_i.value)
	{
		case MY_INT:
			printf("int32 ");
			fprintf(output,"int32 ");
			break;
		case MY_FLOAT:	
			printf("float32 ");
			fprintf(output,"float32 ");
			break;
		case MY_CHAR:
			printf("char ");
			fprintf(output,"char ");
			break;
		case MY_BOOL:
			printf("bool ");
			fprintf(output,"bool ");
			break;
		case MY_VOID:
			printf("void ");
			fprintf(output,"void ");
			break;
		default:
			printf("IN DEFAULT OF PRINT RET TYPE\n");
	}
	return;
}
void print_formal_args(nodeType* n)
{
	if(n->opr.oper==EMPTY)
		return;
	nodeType* lc=get_operand(n,0);
	nodeType* rc=get_operand(n,1);
	nodeType* s;
	if(n->opr.oper==FORMAL_ARG)
	{
		print_type(get_operand(n,1));
		s=get_operand(n,0);
		printf(" %s ",s->id.symrec->uid); 
		fprintf(output," %s ",s->id.symrec->uid); 
		return;
	}
	else
	{
		print_formal_args(lc);
		printf(",");
		fprintf(output,",");
	}	
	print_formal_args(rc);
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
	bzero(fun_name->id.symrec->signature,100);
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
	strcat(fun_name->id.symrec->signature,fun_name->id.symrec->sym_name);
	strcat(fun_name->id.symrec->signature," ( ");
	create_formal_args(formalarg);
	strcat(fun_name->id.symrec->signature,mybuf);
	bzero(mybuf,1000);
	strcat(fun_name->id.symrec->signature," ) ");
	printf("FINAL SIGNATURE:%s\n",fun_name->id.symrec->signature);
}

void ir_fun_def(nodeType* n)
{
	
	nodeType* fun_name = get_operand(n,0);	
	nodeType* formal_arguments = get_operand(n,1);
	nodeType* return_type =get_operand(n,2);
	nodeType* compound =get_operand(n,3);
	// only static for time being
	printf(".method static ");
	fprintf(output,".method static ");
	
	print_type(return_type);
	printf("%s",fun_name->id.symrec->sym_name);
	fprintf(output,"%s",fun_name->id.symrec->sym_name);
	if(strcmp(fun_name->id.symrec->sym_name,"main")==0)
	{
		main_found=1;
		main_was_found=1;
	}	
	printf("(");
	fprintf(output,"(");
	print_formal_args(formal_arguments);
	printf(") cil managed\n");
	fprintf(output,") cil managed\n");
	in_func=1;
	generate(compound);
}

void print_vardec_code(nodeType* Idlist,nodeType* Type)
{
	if(Idlist->type==typeId)
	{
		print_type(Type);
		printf(" %s ",Idlist->id.symrec->uid); 
		fprintf(output," %s ",Idlist->id.symrec->uid); 
		return;
	}
	else
	{
		nodeType* lc=get_operand(Idlist,0);
		nodeType* rc=get_operand(Idlist,1);
		print_vardec_code(lc,Type);
		printf(",");
		fprintf(output,",");
		print_type(Type);
		printf(" %s ",rc->id.symrec->uid); 
		fprintf(output," %s ",rc->id.symrec->uid); 
	}	
	return;
}

void ir_var_dec(nodeType* n)
{
	nodeType* Idlist = get_operand(n,0);
	nodeType* Type = get_operand(n,1);
	printf(".locals init(");
	fprintf(output,".locals init(");
	print_vardec_code(Idlist,Type);
	printf(")\n");
	fprintf(output,")\n");
	//~ free(n);
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
			printf("clt\n");
			fprintf(output,"clt\n");
			break;
		case GT:
			printf("cgt\n");
			fprintf(output,"cgt\n");
			break;
		case LE:
			printf("cgt\n");
			fprintf(output,"cgt\n");
			printf("ldc.i4.0\n");
			fprintf(output,"ldc.i4.0\n");
			printf("ceq\n");
			fprintf(output,"ceq\n");
			break;
		case GE:
			printf("clt\n");
			fprintf(output,"clt\n");
			printf("ldc.i4.0\n");
			fprintf(output,"ldc.i4.0\n");
			printf("ceq\n");
			fprintf(output,"ceq\n");
			break;
		default:
			printf("Relational default\n");
	}
}
void ir_bool(nodeType* n)
{
	nodeType* B1 = get_operand(n,0);
	nodeType* B2 = get_operand(n,1);
	char* label1;
	char* label2;
	switch(n->opr.oper)
	{
		case NEQ:
			generate(B1);
			generate(B2);
			printf("ceq\n");
			fprintf(output,"ceq\n");
			printf("ldc.i4.0\n");
			fprintf(output,"ldc.i4.0\n");
			printf("ceq\n");
			fprintf(output,"ceq\n");
			break;
		case BOOL_EQ:
			generate(B1);
			generate(B2);
			printf("ceq\n");
			fprintf(output,"ceq\n");
			break;
		case BOOL_OR:
			generate(B1);
			label1 = strdup(newlabel());
			printf("brtrue %s\n",label1);
			fprintf(output,"brtrue %s\n",label1);
			generate(B2);
			label2 = strdup(newlabel());
			printf("br.s %s\n",label2);
			fprintf(output,"br.s %s\n",label2);
			printf("%s: ldc.i4.1 \n",label1);
			fprintf(output,"%s: ldc.i4.1 \n",label1);
			printf("%s: ",label2);
			fprintf(output,"%s: ",label2);
			break;
		case BOOL_AND:
			generate(B1);
			label1 = strdup(newlabel());
			printf("brfalse %s\n",label1);
			fprintf(output,"brfalse %s\n",label1);
			generate(B2);
			label2 = strdup(newlabel());
			printf("br.s %s\n",label2);
			fprintf(output,"br.s %s\n",label2);
			printf("%s: ldc.i4.0\n",label1);
			fprintf(output,"%s: ldc.i4.0\n",label1);
			printf("%s: ",label2);
			fprintf(output,"%s: ",label2);
			break;
		default: printf("Bool DEFAULT\n");
	}
}
// NEED TO TEST THIS ONCE
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
	if(strcmp(func_name->id.symrec->sym_name,"println")!=0)
	{
		generate(explist);
		printf("call ");
		fprintf(output,"call ");
		printf("%s ",func_name->id.symrec->signature);
		fprintf(output,"%s \n",func_name->id.symrec->signature);
	}
	else  		// default println function called
	{
		generate(explist);
		fprintf(output,"call void [mscorlib]System.Console::WriteLine");
		fprintf(output,"(");
		fprintf(output,"int32");
		fprintf(output,")\n");
	}	
}

void ir_return(nodeType* n)
{
	if(n->opr.nops == 0)
		{
			printf("pop \n");
			printf("ret \n");
			fprintf(output,"pop \n");
			fprintf(output,"ret \n");
		}
	else
	{
		nodeType* return_exp = get_operand(n,0);
		generate(return_exp);
		printf("ret \n");
		fprintf(output,"ret \n");
	}
}
////////////////////////////////////////////////////////////////////////
				
void ir_relop_flow(nodeType* n)
{

}

void ir_if(nodeType* n)
{
	nodeType* expr = get_operand(n,0);
	nodeType* stmt = get_operand(n,1);
	set_T(expr,newlabel());
	set_F(expr,n->opr.next);
	//~ stmt->opr.next=strdup(n->opr.next);
	//~ bzero(stmt->opr.next,10);
	strcat(stmt->opr.next,n->opr.next);
	printf("expr true label:%s\n",get_T(expr));
	printf("expr false label:%s\n",get_F(expr));
	generate(expr);
	printf("%s:\n",get_T(expr));
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
	strcat(stmt1->opr.next,n->opr.next);
	strcat(stmt2->opr.next,n->opr.next);
	generate(expr);
	printf("%s:\n",get_T(expr));
	fprintf(output,"%s:\n",get_T(expr));
	generate(stmt1);
	printf("br.s %s\n ",n->opr.next);
	fprintf(output,"br.s %s\n",n->opr.next);
	printf("%s:\n",get_F(expr));
	fprintf(output,"%s:\n",get_F(expr));
	generate(stmt2);
	
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
	strcat(stmt->opr.next,begin);
	printf("%s:\n",begin);
	fprintf(output,"%s:\n",begin);
	generate(expr);
	printf("%s:\n",get_T(expr));
	fprintf(output,"%s:\n",get_T(expr));
	generate(stmt);
	printf("br.s %s\n ",begin);
	fprintf(output,"br.s %s\n",begin);
}	
	
void ir_bool_flow(nodeType* n)
{
	nodeType* B1 = get_operand(n,0);
	nodeType* B2 = get_operand(n,1);
	printf("n true label:%s\n",get_T(n));
	printf("n false label:%s\n",get_F(n));
	switch(n->opr.oper)
	{
	case BOOL_OR:
		printf("MATCHED BOOL_OR in ir_bool_flow\n");
		set_T(B1,n->opr.T);
		set_F(B1,newlabel());
		set_T(B2,n->opr.T);
		set_F(B2,n->opr.F);
		generate(B1);
		printf("%s:",get_F(B1)); 
		fprintf(output,"%s:",get_F(B1)); 
		generate(B2);
		break;
	case NEQ:
		 set_T(B1,get_F(n));
		 set_F(B1,get_T(n));
		 generate(B1);
		break;
	case BOOL_AND:
		set_T(B1,newlabel());
		set_F(B1, get_F(n));
		set_T(B2, get_T(n));
		set_F(B2, get_F(n));
		generate(B1);
		printf("%s:",get_T(B1)); 
		fprintf(output,"%s:",get_T(B1)); 
		generate(B2);
		break;
	default: printf("Bool DEFAULT\n");
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
	//~ Stmtlist->opr.next = strdup(newlabel());	//yahi hai gadbad!!!!
	//~ printf("STMT_LIST1 TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
	//~ traverse(root);
	//~ printf("STMT_LIST1 TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
	memset(Stmtlist->opr.next,0,16);
	strcat(Stmtlist->opr.next,newlabel());
	printf("Stmtlist next:%s \n",Stmtlist->opr.next);
	printf("Stmtlist type:%d \n",Stmtlist->type);
	printf("Stmtlist nops:%d \n",Stmtlist->opr.nops);
	//~ if(Stmtlist->opr.nops>2) printf("nops:%d \n",get_operand(Stmtlist,1)->type);
	//~ printf("STMT_LIST2 TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
	//~ traverse(root);
	//~ printf("STMT_LIST2 TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");

	generate(Stmtlist);
	memset(Stmt->opr.next,0,16);
	strcat(Stmt->opr.next,n->opr.next);	
	printf("%s: \n",Stmtlist->opr.next);
	fprintf(output,"%s: \n",Stmtlist->opr.next);
	generate(Stmt);
	//~ free(n);
}

void ir_asynch_list(nodeType* n)
{
	printf("Entered Async\n");
	nodeType* func = get_operand(n,0);
	nodeType* fun_name = get_operand(func,0);
	char* sign,*pch;
	sign = strdup(fun_name->id.symrec->signature);
	
	printf(".locals init (class [mscorlib]System.Threading.Thread V%d)\n",idno);
	fprintf(output,".locals init (class [mscorlib]System.Threading.Thread V%d)\n",idno);
	printf("ldnull\n");
	fprintf(output,"ldnull\n");
	printf("ldftn ");
	fprintf(output,"ldftn ");
	
	
	if(strcmp(sign,"")==0)		return;	
	pch = strtok (sign," ::");
	printf("%s ",pch);
	fprintf(output,"%s ",pch);
	
	printf("class ");
	fprintf(output,"class ");
	printf("%s::",fun_name->id.symrec->my_st->parent->owner_name);
	fprintf(output,"%s::",fun_name->id.symrec->my_st->parent->owner_name);
	printf("%s",fun_name->id.symrec->sym_name);
	fprintf(output,"%s",fun_name->id.symrec->sym_name);
	printf("()\n");
	fprintf(output,"()\n");
	
	printf("newobj instance void class [mscorlib]System.Threading.ThreadStart::'.ctor'(object, native int)\n");
	fprintf(output,"newobj instance void class [mscorlib]System.Threading.ThreadStart::'.ctor'(object, native int)\n");
	printf("newobj instance void class [mscorlib]System.Threading.Thread::'.ctor'(class [mscorlib]System.Threading.ThreadStart)\n");
	fprintf(output,"newobj instance void class [mscorlib]System.Threading.Thread::'.ctor'(class [mscorlib]System.Threading.ThreadStart)\n");
	printf("stloc V%d\n",idno); 
	fprintf(output,"stloc V%d\n",idno); 
	printf("ldloc V%d\n",idno); 
	fprintf(output,"ldloc V%d\n",idno); 
	printf("callvirt instance void class [mscorlib]System.Threading.Thread::Start()\n");
	fprintf(output,"callvirt instance void class [mscorlib]System.Threading.Thread::Start()\n");
	idno++;
}
