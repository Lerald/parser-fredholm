%{
#include <stdio.h>
#include "corefunc.h"
#include "base.h"
#include <QString>

#define YYSTYPE Base*
#define YYERROR_VERBOSE 1

coreFunc *calc_result;
char * input_string;
QString *func_name;
double number;

extern int gramlex(void);
extern int gramparse(void);
void yyerror(const char *s)
{
  fprintf(stderr, "%s\n",s);
}



int calculate(char * str, coreFunc * result) {
   int res;
   input_string = str;
   calc_result = result;
   res = yyparse();
   if( res == 0 ) {
      //*result = calc_result;
   }
   return res;
}

%}

%token NUMBER PLUS MINUS MULTI DIV POWER OBRACE CBRACE FUNC EQ COMMA XPARAM YPARAM
%left PLUS MINUS   
%left MULTI DIV   
%left UNARYMINUS 
%start core
%%
core: 	/* empty */
	| 
        leftPart EQ rightPart
        {
            if(calc_result)
            {
                calc_result->expression = $3;
            }
        }
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

expression: 	expression PLUS expression { $$ = new Sum($1, $3);}
                | expression MINUS expression { $$ = new Diff($1, $3);}
                | expression MULTI expression { $$ = new Multi($1, $3);}
                | expression DIV expression { $$ = new Fraction($1, $3);}
                | MINUS expression %prec UNARYMINUS { $2->negative = !$2->negative; $$ = $2;}
	   	| OBRACE expression CBRACE { $$ = $2; }
                | NUMBER { $$ = new Number(number);}
                | XPARAM { $$ = new Variable("x"); $$->head = calc_result;}
                | YPARAM { $$ = new Variable("y"); $$->head = calc_result;}
	    ;


%%







