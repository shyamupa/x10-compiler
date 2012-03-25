all: lexer

lexer: lex.yy.o y.tab.o ll_sym_table.o
	gcc y.tab.o lex.yy.o ll_sym_table.o -lm -o lexer
	
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: lexer.l y.tab.h
	flex lexer.l
	
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c:
	yacc -d parser.y
	
y.tab.h:
	yacc -d --verbose parser.y
clean:
	rm -rf lex.yy.* lexer y.tab.* lexer a.out y.output


