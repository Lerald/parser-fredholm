%{
#include "stdio.h"
#include "gram_yacc.h"
#include <QString>

extern double number;
extern QString *func_name;
void yyerror(char *);
extern char * input_string;
   #define YY_INPUT(buf,result,max_size) {\
      int i;\
      char ch;\
      for( i=0 ; i < max_size ; ++i ) {\
         ch = *input_string++;\
         if( !ch )\
            break;\
         buf[i] = ch;\
    fprintf(stderr, "%c ",ch);\
      }\
      buf[i] = 0;\
      result = i;\
   }
%}

%%
[0-9]+      {
                number = atoi(yytext);
                return NUMBER;
            }
\+			return PLUS;
\-			return MINUS;
\*			return MULTI;
\/			return DIV;
\^			return POWER;
\(			return OBRACE;
\)			return CBRACE;
F			return FUNC;
=			return EQ;
,			return COMMA;
x			return XPARAM;
y			return YPARAM;


%%
int yywrap(void) {
    return 1;
}
