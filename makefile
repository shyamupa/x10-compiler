all: lexer

lexer: lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -o lexer
	
lex.yy.c: lexer.l y.tab.h
	flex lexer.l
y.tab.c:
	yacc -d parser.y
y.tab.h:
	yacc -d parser.y
clean:
	rm -rf lex.yy.c lexer y.tab.*
