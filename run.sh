yacc -d --verbose parser.y
flex lexer.l
gcc -c y.tab.c lex.yy.c ll_sym_table.c 
gcc y.tab.o lex.yy.o ll_sym_table.o -lm -o lexer

