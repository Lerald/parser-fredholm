%{
#include "stdio.h"
#include "y.tab.h"
%}

%%
[0-9]+                  return NUMBER;
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
