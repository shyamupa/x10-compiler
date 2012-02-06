#include<stdio.h>
#include<map>
using namespace std;
struct sym_record
{
	char* type;
	char* token;
	//add more fields if needed
};
typedef struct sym_record sym_record;
map<char*,sym_record> sym_table;

sym_record* insert_sym(char* str,sym_record rec)
{	
	// do some checking for errors such as already in sym_table etc
	sym_table[str]=rec;
}
int main()
{
	return 0;
}
