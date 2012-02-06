#include<stdio.h>
#include<string.h>
char error_msg[]="";
int add_error(const char* str)
{
	strcat(error_msg,str);
	strcat(error_msg,"\n");
	return 0;
}
// main for testing
int main()
{
	add_error("This is error 1");
	add_error("This is error 2");
	printf("%s",error_msg);
}
