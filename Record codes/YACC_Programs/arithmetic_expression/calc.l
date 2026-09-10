%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+              { yylval = atoi(yytext); return NUM; }
[ \t\n]+            ;
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"("                 { return '('; }
")"                 { return ')'; }
.                   { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}

//yacc -d calc.y
//lex calc.l
//cc y.tab.c lex.yy.c -ll
//./a.out