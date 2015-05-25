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
([0-9]+)|([0-9]+.[0-9]+)?     {
                QString tmp(yytext);
                number = tmp.toDouble();
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

cos|sin|tan|acos|asin|atan|cosh|sinh|tanh|acosh|asinh|atanh|exp|log|log10|exp2|expm1|log2|sqrt|cbrt|fabs    {
    func_name = new QString(yytext);
    return FUNC_D;
}

fmax|fmin|modf		{
                func_name = new QString(yytext);
                return FUNC_DD;
            }
frexp|ldexp		{
                func_name = new QString(yytext);
                return FUNC_DI;
            }

%%
int yywrap(void) {
    return 1;
}
