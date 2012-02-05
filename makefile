all: lexer

lexer: lex.yy.c
	gcc lex.yy.c -lfl -o lexer
	
lex.yy.c: lexer.l
	flex lexer.l

clean:
	rm -rf lex.yy.c lexer
