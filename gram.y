%{
#include <stdio.h>
yyerror(s)
char *s;
{
  fprintf(stderr, "%s\n",s);
}

yywrap()
{
  return(1);
}

main()
{
        yyparse();
} 

%}

%token NUMBER PLUS MINUS MULTI DIV POWER OBRACE CBRACE FUNC EQ COMMA XPARAM YPARAM
%left PLUS MINUS   
%left MULTI DIV   
%left UNARYMINUS 

%%
core: 	/* empty */
	| 
	leftPart EQ rightPart { $1 = $3;}
	;

leftPart:
	FUNC OBRACE paramList CBRACE 
	;

paramList:
	XPARAM COMMA YPARAM
	;

rightPart: /* empty */
	   | expression { $$ = $1;}
	;

expression: 	expression PLUS expression { $$ = $1 +$3;}
		| expression MINUS expression { $$ = $1 - $3;}
		| expression MULTI expression { $$ = $1 * $3;}
		| expression DIV expression { $$ = $1 / $2;}
	    	| MINUS expression %prec UNARYMINUS { $$ = -$2;}
	   	| OBRACE expression CBRACE { $$ = $2; }
	    	| param { $$ = $1;}
	    ;

param:	NUMBER { $$ = $1;}
	| XPARAM { }
	| YPARAM { }
	;

%%







