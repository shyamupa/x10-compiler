%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"		// to be included when yacc file is ready
#include "node_def.h"
#include "ll_sym_table.h"
extern YYSTYPE yylval;
%}

delim 		[ \t\n]
ws		{delim}+
letter 		[A-Za-z_]
digit 		[0-9]
line_comment 	"//".*\n
id		{letter}({letter}|{digit})*	
integer		{digit}+
float		[-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?
comment 	"/*"(.|\n)*"*/"
%%
^\n$		{}
{ws}		{printf("");}
\"(\\.|[^"])*\"	{
			printf("STRING %s",yytext);	/*need to handle \" containing strings*/
			return *yytext;
		}

if		{return IF;}
then		{return THEN;}
else		{return ELSE;}

for		{return FOR;}
in		{return IN;}
".."		{return ELLIPSIS;}		
while		{return WHILE;}
continue	{return CONTINUE;}
break		{return BREAK;}
do		{return DO;}

switch		{return SWITCH;}
case		{return CASE;}
default		{return DEFAULT;}

"=="		{return BEQ;}
">="		{return GE;}
">"		{return GT;}
"<="		{return LE;}
"<"		{return LT;}

"+="		{return PLUS_EQ;}
"-="		{return MINUS_EQ;}
"*="		{return MULT_EQ;}
"/="		{return DIV_EQ;}
"="		{return EQ;}

"+"		{
			return PLUS;
		}
"-"		{
			return MINUS;
		}
"*"		{
			return MULT;
		}
"/"		{
			return DIV;
		}
"**"		{
			return POW;
		}
"++"		{
			return PP;
		}
"--"		{
			return MM;
		}
;		{
			return ';';
		}
","		{
			return ',';
		}

\{		{
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
			return ')';
		}
"["		{
			return '[';
		}
"]"		{
			return ']';
		}
":"		{
			return ':';
		}
val		{
			return VAL;
		}
int		{return TYPE_INT;}
float		{return TYPE_FLOAT;}
char 		{return TYPE_CHAR;}
var		{return VAR;}
def		{return DEF;}
public		{return PUBLIC;}
protected	{return PROTECTED;}
private		{return PRIVATE;}
Array		{return ARRAY;}
return		{return RETURN;}
assert		{return ASSERT;}

{comment}	{/* no action */}
{line_comment}	{printf("\n");}
{id}		{
				printf("!%s!",yytext); 
				yylval.sPtr->sym_name=strdup(yytext); 
				return IDENT;
			}
'{letter}'			{
				yylval.cVal=yytext[0];
				return CHAR;
			}
{integer}	{
			yylval.iVal=atoi(yytext);
			return INTEGER;
		}
{float}	{
			yylval.fVal=atoi(yytext);
			return INTEGER;
		}		
%%
int yywrap()
{
	return 1;
}
