%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"		// to be included when yacc file is ready
//#include "include.h"
//#include "header.h"
extern YYSTYPE yylval;
%}
delim 		[ \t\n]
ws		{delim}+
letter 		[A-Za-z_]
digit 		[0-9]
line_comment 	"//".*\n
id		{letter}({letter}|{digit})*	
number		{digit}+(\.{digit}+)?(E[-+]?{digit}+)?	
comment 	"/*"(.|\n)*"*/"
%%
^\n$		{}
{ws}		{printf("");}
\"(\\.|[^"])*\"	{
			printf("STRING %s",yytext);	/*need to handle \" containing strings*/
			return *yytext;
		}

if		{printf("IF");return IF;}
then		{printf("THEN");}
else		{printf("ELSE");}

for		{printf("FOR");}
in		{printf("IN");}
".."		{printf("..");}		
while		{printf("WHILE");}
continue	{printf("CONTINUE");}
break		{printf("BREAK");}
do		{printf("DO");}

switch		{printf("SWITCH");}
case		{printf("CASE");}
default		{printf("DEFAULT");}

"=="		{printf("==");}
">="		{printf(">=");}
">"		{printf(">");}
"<="		{printf("<=");}
"<"		{printf("<");}

"+="		{printf("+=");}
"-="		{printf("-=");}
"*="		{printf("*=");}
"/="		{printf("/=");}
"="		{printf("=");}

"+"		{
			//printf("+");
			return '+';
		}
"-"		{
			//printf("-");
			return '-';
		}
"*"		{
			//printf("*");
			return '*';
		}
"/"		{
			//printf("/");
			return '/';
		}
"**"		{
			return POW;
		}
;		{
			//printf(";");
			return ';';
		}
","		{
			//printf(";");
			return ',';
		}

\{		{
			//printf("{");
			return '{';
		}
\}		{
			//printf("}");
			return '}';
		}
\(		{
			//printf("(");
			return '(';
		}
\)		{
			//printf(")");
			return ')';
		}
"["		{
			//printf("[");
			return '[';
		}
"]"		{
			//printf("]");
			return ']';
		}
":"		{
			//printf(":");
			return ':';
		}
val		{
			//printf("VAL");
			return VAL;
		}
var		{printf("VAR");}
def		{printf("DEF");}
public		{printf("PUBLIC");}
private		{printf("PRIVATE");}
Array		{printf("ARRAY");}
return		{printf("RETURN");}
assert		{printf("ASSERT");}

{comment}	{/* no action */}
{line_comment}	{printf("\n");}
{id}		{printf("!%s!",yytext); yylval.charPtr=yytext; return IDENT;}
{number}	{
			yylval.iVal=atoi(yytext);
			//printf("NUMBER{%d}",yylval);
			return NUMBER;
		}
%%
int yywrap()
{
	return 1;
}
