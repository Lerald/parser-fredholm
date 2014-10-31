all: gram

gram: lex.yy.c y.tab.c
	cc lex.yy.c y.tab.c -o gram

lex.yy.c: gram.l
	lex gram.l

y.tab.c: gram.y
	yacc -d gram.y
