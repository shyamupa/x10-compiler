yacc -d --verbose parser.y
flex lexer.l
gcc -g y.tab.c lex.yy.c ll_sym_table.c st_stack.c helper_functions.c ir_code.c type_checkers.c

