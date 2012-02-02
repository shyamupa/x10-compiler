%{
#include<stdio.h>
%}

delim 		[ \t]
ws		{delim}+
letter 		[A-Za-z_]
digit 		[0-9]
id		{letter}({letter}|{digit})*	
comment 	"/*"(.|\n)*"*/"
line_comment 	\/\/.*\n$
%%
^\n$		{}
{ws}		{printf(" ");}
if		{printf("IF");}
then		{printf("THEN");}
else		{printf("ELSE");}
"=="		{printf("==");}
">="		{printf(">=");}
">"		{printf(">");}
var		{printf("VAR");}
def		{printf("DEF");}
public		{printf("PUBLIC");}
private		{printf("PRIVATE");}
Array		{printf("ARRAY");}
{comment}	{/* no action */}
{line_comment}	{/* no action */}
{id}		{printf("ID");}
%%
