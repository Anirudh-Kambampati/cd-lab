%{
#include <stdio.h>
%}

%%
[0-9]+                                      { printf("NUMBER: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                       { printf("IDENTIFIER: %s\n", yytext); }
"+"|"-"|"*"|"/"|"="                         { printf("OPERATOR: %s\n", yytext); }
"("                                          { printf("LPAREN\n"); }
")"                                          { printf("RPAREN\n"); }
[ \t\n]+                                    ;
.                                           { printf("SPECIAL SYMBOL: %s\n", yytext); }
%%

int main()
{
    printf("Enter input:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
