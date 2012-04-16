%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"		// to be included when yacc file is ready
#include "node_def.h"
#include "ll_sym_table.h"
extern YYSTYPE yylval;
extern struct symbol_table* current_st;
int yyline_no = 1;
int yycolumn=1;
void yyerror (char *);

%}
delim 			[ \t]
ws				{delim}+
letter 			[A-Za-z_]
digit 			[0-9]
line_comment 	"//".*\n
id				{letter}({letter}|{digit})*	
integer			{digit}+
hexval			0[xX][0-9a-fA-F]+
float			[-+]?{digit}*\.{digit}+([eE][-+]?{digit}+)?[Ff]
comment 		"/*"(.|\n)*"*/"

%%
^\n$		{}
\n			{yycolumn=1; yyline_no++;}
{ws}		{/* no action */}
\"(\\.|[^"])*\"	{	yycolumn=yycolumn+yyleng;
					/*need to handle \" containing strings*/
					return *yytext;
				}
if			{yycolumn=yycolumn+yyleng;return IF;}
then		{yycolumn=yycolumn+yyleng;return THEN;}
else		{yycolumn=yycolumn+yyleng;return ELSE;}

for			{yycolumn=yycolumn+yyleng;return FOR;}
in			{yycolumn=yycolumn+yyleng;return IN;}
".."		{yycolumn=yycolumn+yyleng;return ELLIPSIS;}		
while		{yycolumn=yycolumn+yyleng;return WHILE;}
continue	{yycolumn=yycolumn+yyleng;return CONTINUE;}
break		{yycolumn=yycolumn+yyleng;return BREAK;}
do			{yycolumn=yycolumn+yyleng;return DO;}

switch		{yycolumn=yycolumn+yyleng;return SWITCH;}
case		{yycolumn=yycolumn+yyleng;return CASE;}
default		{yycolumn=yycolumn+yyleng;return DEFAULT;}
"true"		{yycolumn=yycolumn+yyleng;return TRUE;}
"false"		{yycolumn=yycolumn+yyleng;return FALSE;}

abstract	{yycolumn=yycolumn+yyleng;return ABSTRACT;} 
as			{yycolumn=yycolumn+yyleng;return AS;}
async		{yycolumn=yycolumn+yyleng;return ASYNC;}
at			{yycolumn=yycolumn+yyleng;return AT;}
athome		{yycolumn=yycolumn+yyleng;return ATHOME;}
ateach		{yycolumn=yycolumn+yyleng;return ATEACH;}
atomic		{yycolumn=yycolumn+yyleng;return ATOMIC;}
catch		{yycolumn=yycolumn+yyleng;return CATCH;}
class		{yycolumn=yycolumn+yyleng;return CLASS;}
clocked		{yycolumn=yycolumn+yyleng;return CLOCKED;}
extends		{yycolumn=yycolumn+yyleng;return EXTENDS;}
final		{yycolumn=yycolumn+yyleng;return FINAL;}
finally		{yycolumn=yycolumn+yyleng;return FINALLY;}
finish		{yycolumn=yycolumn+yyleng;return FINISH;}
goto		{yycolumn=yycolumn+yyleng;return GOTO;}
haszero		{yycolumn=yycolumn+yyleng;return HASZERO;}
here		{yycolumn=yycolumn+yyleng;return HERE;}
implements	{yycolumn=yycolumn+yyleng;return IMPLEMENTS;}
import		{yycolumn=yycolumn+yyleng;return IMPORT;}
instanceof	{yycolumn=yycolumn+yyleng;return INSTANCEOF;}
interface	{yycolumn=yycolumn+yyleng;return INTERFACE;}
native		{yycolumn=yycolumn+yyleng;return NATIVE;}
null		{yycolumn=yycolumn+yyleng;return MY_NULL;}
offer		{yycolumn=yycolumn+yyleng;return OFFER;}
offers		{yycolumn=yycolumn+yyleng;return OFFERS;}
operator	{yycolumn=yycolumn+yyleng;return OPERATOR;}
package		{yycolumn=yycolumn+yyleng;return PACKAGE;}
property	{yycolumn=yycolumn+yyleng;return PROPERTY;}
self		{yycolumn=yycolumn+yyleng;return SELF;}
static		{yycolumn=yycolumn+yyleng;return STATIC;}
struct		{yycolumn=yycolumn+yyleng;return STRUCT;}
super		{yycolumn=yycolumn+yyleng;return SUPER;}
this		{yycolumn=yycolumn+yyleng;return THIS;}
throw		{yycolumn=yycolumn+yyleng;return THROW;}
transient	{yycolumn=yycolumn+yyleng;return TRANSIENT;}
try 		{yycolumn=yycolumn+yyleng;return TRY;}
when		{yycolumn=yycolumn+yyleng;return WHEN;}
"=="		{yycolumn=yycolumn+yyleng;return BOOL_EQ;}
"!="		{yycolumn=yycolumn+yyleng;return NEQ;}
">="		{yycolumn=yycolumn+yyleng;return GE;}
">"			{yycolumn=yycolumn+yyleng;return GT;}
"<="		{yycolumn=yycolumn+yyleng;return LE;}
"<"			{yycolumn=yycolumn+yyleng;return LT;}
"<<"		{yycolumn=yycolumn+yyleng;return LSH;}
">>"		{yycolumn=yycolumn+yyleng;return RSH;}
"+="		{yycolumn=yycolumn+yyleng;return PLUS_EQ;}
"-="		{yycolumn=yycolumn+yyleng;return MINUS_EQ;}
"*="		{yycolumn=yycolumn+yyleng;return MULT_EQ;}
"/="		{yycolumn=yycolumn+yyleng;return DIV_EQ;}
"="			{yycolumn=yycolumn+yyleng;return EQ;}
"?"			{yycolumn=yycolumn+yyleng;return QM;}
"||"		{yycolumn=yycolumn+yyleng;return BOOL_OR;}
"|"			{yycolumn=yycolumn+yyleng;return BIT_OR;}
"&&"		{yycolumn=yycolumn+yyleng;return BOOL_AND;}
"&"			{yycolumn=yycolumn+yyleng;return BIT_AND;}
"^"			{yycolumn=yycolumn+yyleng;return XOR;}
"+"			{yycolumn=yycolumn+yyleng;return PLUS;}
"-"			{yycolumn=yycolumn+yyleng;return MINUS;}
"*"			{yycolumn=yycolumn+yyleng;return MULT;}
"/"			{yycolumn=yycolumn+yyleng;return DIV;}
"%"			{yycolumn=yycolumn+yyleng;return MODULO;}
"**"		{yycolumn=yycolumn+yyleng;return POW;}
"++"		{yycolumn=yycolumn+yyleng;return PP;}
"--"		{yycolumn=yycolumn+yyleng;return MM;}
;			{yycolumn=yycolumn+yyleng;return ';';}
","			{yycolumn=yycolumn+yyleng;/*printf("!%s!",yytext);*/return ',';}
\{			{yycolumn=yycolumn+yyleng;return '{';}
\}			{yycolumn=yycolumn+yyleng;return '}';}
\(			{yycolumn=yycolumn+yyleng;return '(';}
\)			{yycolumn=yycolumn+yyleng;return ')';}
"["			{yycolumn=yycolumn+yyleng;return '[';}
"]"			{yycolumn=yycolumn+yyleng;return ']';}
":"			{yycolumn=yycolumn+yyleng;return ':';}
"."			{yycolumn=yycolumn+yyleng;return '.';}
val			{yycolumn=yycolumn+yyleng;return VAL;}

int			{yycolumn=yycolumn+yyleng;return TYPE_INT;}
float		{yycolumn=yycolumn+yyleng;return TYPE_FLOAT;}
char 		{yycolumn=yycolumn+yyleng;return TYPE_CHAR;}
void		{yycolumn=yycolumn+yyleng;return TYPE_VOID;}
boolean		{yycolumn=yycolumn+yyleng;return TYPE_BOOL;}

var			{yycolumn=yycolumn+yyleng;return VAR;}
def			{yycolumn=yycolumn+yyleng;return DEF;}
public		{yycolumn=yycolumn+yyleng;return PUBLIC;}
protected	{yycolumn=yycolumn+yyleng;return PROTECTED;}
private		{yycolumn=yycolumn+yyleng;return PRIVATE;}
Array		{yycolumn=yycolumn+yyleng;return ARRAY;}
return		{yycolumn=yycolumn+yyleng;return RETURN;}
assert		{yycolumn=yycolumn+yyleng;return ASSERT;}
new			{yycolumn=yycolumn+yyleng;return NEW;}
{comment}	{/*yycolumn=1; yyline_no++; no action */}
{line_comment}	{yycolumn=1; yyline_no++;/* no action */}
{id}		{	yycolumn=yycolumn+yyleng;
				//printf("!%s!",yytext);
				return IDENT;
			}
'{letter}'	{	yycolumn=yycolumn+yyleng;
				yylval.cVal=yytext[0];
				return CHAR;
			}
{hexval}	{	yycolumn=yycolumn+yyleng;
				yylval.iVal=strtol(yytext,NULL,16);
				//printf("HEX %s\n",yytext);
				return INTEGER;
			}
{integer}	{	yycolumn=yycolumn+yyleng;
				yylval.iVal=atoi(yytext);
				//printf("INT %s\n",yytext);
				return INTEGER;
			}
				
{float}		{	yycolumn=yycolumn+yyleng;
				//printf("%s FLOAT lexer",yytext);
				yylval.fVal=atof(yytext);
				return FLOAT;
			}		
%%
int yywrap()
{
	return 1;
}
