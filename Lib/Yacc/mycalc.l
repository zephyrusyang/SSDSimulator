%{
#include <stdio.h>
#include "y.tab.h"

int
yywrap(void)
{
  return 1;
}
%}
%%
"if"     return keyword_if;
"else"   return keyword_else;
"for"    return keyword_for;
"switch" return keyword_switch;
"end"    rerurn keyword_end;;
"="      return keyword_eq;
"=="     return keyword_eq;
"!="
"<"
">"
">="
"<="
"|"
"&"
"||"
"&&"
"+"      return oADD;
"-"      return oSUB;
"*"      return oMUL;
"/"      return oDIV;
"\n"     return CR;
[1-9][0-9]* {
  double temp;
  sscanf(yytext,"%lf",&temp);
  yylval.double_value = temp;
  return DOUBLE_LITERAL;
}
[0-9]*\.[0-9]* {
  double temp;
  sscanf(yytext,"%lf",&temp);
  yylval.double_value = temp;
  return DOUBLE_LITERAL;
}
%%


