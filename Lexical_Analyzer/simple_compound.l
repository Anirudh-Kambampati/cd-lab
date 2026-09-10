%{
#include<stdio.h>
#include<string.h>
%}
simple [a-zA-Z]+
compound [a-zA-Z]+[ \t]+[a-zA-Z]+
%%
{simple} { printf("Simple\n"); }
{compound} { printf("Compound\n"); }
int main(){
    printf("Enter the input:\n");
    yylex();
    return 0;
}
int yywrap() { return 1; }

//lex keywords.l
//gcc lex.yy.c -o -lfl
//./a.out
