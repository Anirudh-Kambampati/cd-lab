%{
#include <stdio.h>
%}
simple [a-zA-Z]+
compound [a-zA-Z]+[ \t]+[a-zA-Z]+
%%
{compound} { printf("Compound Word\n"); }
{simple} { printf("Simple Word\n"); }
[ \t\n]+ ; /* Ignore whitespace */
. ; /* Ignore other characters */
%%
int main()
{
 printf("Enter a word: ");
 yylex();
 return 0;
}
int yywrap()
{
 return 1;
}

//lex simple_compound.l
//cc lex.yy.c -ll -o simple_compound -lfl
//./simple_compound