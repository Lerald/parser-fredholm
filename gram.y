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

%token NUMBER PLUS MINUS MULTI DIV POWER OBRACE CBRACE EQ COMMA XPARAM YPARAM FUNC FUNC_D FUNC_DD FUNC_DI
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

expression: 	expression PLUS subexpression { $$ = new Sum($1, $3);}
                | expression MINUS subexpression { $$ = new Diff($1, $3);}
                | subexpression { $$ = $1;}
	;

subexpression:  subexpression MULTI subsub { $$ = new Multi($1, $3);}
                | subexpression DIV subsub { $$ = new Fraction($1, $3);}
                | subsub { $$ = $1;}

        ;
subsub:         subsub POWER subsubsub { $$ = new Power($1, $3);}
                | subsubsub { $$ = $1;}
        ;

subsubsub:      MINUS subsubsub %prec UNARYMINUS { $2->negative = !$2->negative; $$ = $2;}
                | OBRACE expression CBRACE { $$ = $2; }
                | operand { $$ = $1;}
        ;

operand:        NUMBER { $$ = new Number(number);}
                | XPARAM { $$ = new Variable("x"); $$->head = calc_result;}
                | YPARAM { $$ = new Variable("y"); $$->head = calc_result;}
                | functionCall { $$ = $1;}
        ;

functionCall: 	FUNC_D OBRACE expression CBRACE { $$ = new Func_OneParam(func_name, $3);}
                | FUNC_DD OBRACE expression COMMA expression CBRACE { $$ = new Func_TwoParam(func_name, $3, $5);}
                | FUNC_DI OBRACE expression COMMA expression CBRACE { $$ = new Func_TwoParam(func_name, $3, $5);}
	;


%%







