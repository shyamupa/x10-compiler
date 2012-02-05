%{
#include<stdio.h>
//#include<y.tab.h>		// to be included when yacc file is ready
%}

delim 		[ \t]
ws		{delim}+
letter 		[A-Za-z_]
digit 		[0-9]
line_comment 	"//".*\n
id		{letter}({letter}|{digit})*	
comment 	"/*"(.|\n)*"*/"
%%
^\n$		{}
{ws}		{printf(" ");}
\"(\\.|[^"])*\"	{printf("STRING %s",yytext);}

if		{printf("IF");}
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
"<"		{printf("<");}
"<="		{printf("<=");}

"+="		{printf("+=");}
"-="		{printf("-=");}
"*="		{printf("*=");}
"/="		{printf("/=");}
"="		{printf("=");}

"+"		{printf("+");}
"-"		{printf("-");}
"*"		{printf("*");}
"/"		{printf("/");}
;		{printf(";");}

\{		{printf("{");}
\}		{printf("}");}
\(		{printf("(");}
\)		{printf(")");}
"["		{printf("[");}
"]"		{printf("]");}
":"		{printf(":");}
var		{printf("VAR");}
def		{printf("DEF");}
public		{printf("PUBLIC");}
private		{printf("PRIVATE");}
Array		{printf("ARRAY");}
return		{printf("RETURN");}
assert		{printf("ASSERT");}

{comment}	{/* no action */}
{line_comment}	{printf("\n");}
{id}		{printf("ID");}
%%
