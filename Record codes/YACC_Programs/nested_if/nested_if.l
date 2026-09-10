%{
#include "y.tab.h"
%}
%%
"if" return IF;
"then" return THEN;
"else" return ELSE;
[a-zA-Z]+ return ID;
[ \t\n]+ ;
. return yytext[0];
%%
int yywrap()
{
 return 1;
}

//bison -d nested_if.y
//lex nested_if.l
//cc nested_if.tab.c lex.yy.c -ll
//./a.out