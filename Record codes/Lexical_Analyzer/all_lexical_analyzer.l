%{
#include <stdio.h>
%}

%%
"//".*                                      { printf("Comment: %s\n", yytext); }
"/*"([^*]|\*+[^*/])*\*+"/"                 { printf("Comment: %s\n", yytext); }
"if"|"else"|"for"|"while"|"int"|"float"|"char" { printf("Keyword: %s\n", yytext); }
[0-9]+(\.[0-9]+)?                           { printf("Constant: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                       { printf("Identifier: %s\n", yytext); }
"+"|"-"|"*"|"/"|"="|"=="|"!="|"<="|">="|"<"|">" { printf("Operator: %s\n", yytext); }
[ \t\n]+                                    ;
.                                           { printf("Symbol: %s\n", yytext); }
%%

int main()
{
    printf("Enter the input:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
