all: lexer

lexer: lex.yy.c
	gcc lex.yy.c -lfl -o lexer
	
lex.yy.c: lexer.l y.tab.h
	flex lexer.l
y.tab.h:
	yacc -d parser.y
clean:
	rm -rf lex.yy.c lexer y.tab.*
