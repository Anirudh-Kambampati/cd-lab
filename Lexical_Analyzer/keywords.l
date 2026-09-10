%{
#include<stdio.h>
#include<string.h>
%}
digit [0-9]
letter [a-zA-Z]
keyword if|else|for|while|int|float|char
%%
{keyword} { printf("Keyword: %s\n", yytext); }
{digit}+ { printf("Number: %s\n", yytext); }
{a-zA-Z}+ { printf("Letter: %s\n", yytext); }
[ \t\n]+;
. { printf("Symbol: %s\n", yytext); }
int main(){
    printf("Enter the input:\n");
    yylex();
    return 0;
}
int yywrap() { return 1; }

//lex keywords.l
//gcc lex.yy.c -o -lfl
//./a.out
