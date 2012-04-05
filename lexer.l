%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"		// to be included when yacc file is ready
#include "node_def.h"
#include "ll_sym_table.h"
extern YYSTYPE yylval;
extern struct symbol_table* current_st;
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
{ws}		{/* no action */}
\"(\\.|[^"])*\"	{
			/*need to handle \" containing strings*/
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
"true"		{return TRUE;}
"false"		{return FALSE;}

abstract	{return ABSTRACT;} 
as		{return AS;}
async		{return ASYNC;}
at		{return AT;}
athome		{return ATHOME;}
ateach		{return ATEACH;}
atomic		{return ATOMIC;}
catch		{return CATCH;}
class		{return CLASS;}
clocked		{return CLOCKED;}
extends		{return EXTENDS;}
final		{return FINAL;}
finally		{return FINALLY;}
finish		{return FINISH;}
goto		{return GOTO;}
haszero		{return HASZERO;}
here		{return HERE;}
implements	{return IMPLEMENTS;}
import		{return IMPORT;}
instanceof	{return INSTANCEOF;}
interface	{return INTERFACE;}
native		{return NATIVE;}
null		{return MY_NULL;}
offer		{return OFFER;}
offers		{return OFFERS;}
operator	{return OPERATOR;}
package		{return PACKAGE;}
property	{return PROPERTY;}
self		{return SELF;}
static		{return STATIC;}
struct		{return STRUCT;}
super		{return SUPER;}
this		{return THIS;}
throw		{return THROW;}
transient	{return TRANSIENT;}
try 		{return TRY;}
when		{return WHEN;}
"=="		{return BEQ;}
"!="		{return NEQ;}
">="		{return GE;}
">"		{return GT;}
"<="		{return LE;}
"<"		{return LT;}
"<<"	{return LSH;}
">>"	{return RSH;}
"+="		{return PLUS_EQ;}
"-="		{return MINUS_EQ;}
"*="		{return MULT_EQ;}
"/="		{return DIV_EQ;}
"="		{/*printf("!%s!",yytext)*/;return EQ;}
"?"		{return QM;}
"||"		{return BOOL_OR;}
"|"		{return BIT_OR;}
"&&"		{return BOOL_AND;}
"&"		{return BIT_AND;}
"^"		{return XOR;}
"+"		{return PLUS;}
"-"		{return MINUS;}
"*"		{return MULT;}
"/"		{return DIV;}
"**"		{return POW;}
"++"		{return PP;}
"--"		{return MM;}
;		{return ';';}
","		{/*printf("!%s!",yytext);*/return ',';}
\{		{return '{';}
\}		{return '}';}
\(		{return '(';}
\)		{return ')';}
"["		{return '[';}
"]"		{return ']';}
":"		{return ':';}
val		{return VAL;}

int		{return TYPE_INT;}
float		{return TYPE_FLOAT;}
char 		{return TYPE_CHAR;}
void		{return TYPE_VOID;}
boolean		{return TYPE_BOOL;}

var		{return VAR;}
def		{return DEF;}
public		{return PUBLIC;}
protected	{return PROTECTED;}
private		{return PRIVATE;}
Array		{return ARRAY;}
return		{return RETURN;}
assert		{return ASSERT;}
new		{return NEW;}
{comment}	{/* no action */}
{line_comment}	{/* no action */}
{id}		{
			//printf("!%s!",yytext);
			return IDENT;
		}
'{letter}'	{
			yylval.cVal=yytext[0];
			return CHAR;
		}
{integer}	{
			yylval.iVal=atoi(yytext);
			return INTEGER;
		}
{float}		{
			//printf("%s FLOAT lexer",yytext);
			yylval.fVal=atof(yytext);
			return FLOAT;
		}		
%%
int yywrap()
{
	return 1;
}
