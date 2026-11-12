%{
#include <stdio.h>
#include <string.h>
%}
digit [0-9]
letter [a-zA-Z]
keyword int|float|if|else|for|while
%%
{keyword} { printf("Keyword: %s\n", yytext); }
{digit}+ { printf("Number: %s\n", yytext); }
{letter}+ { printf("Word: %s\n", yytext); }
[ \t\n]+ ; /* Ignore whitespace */
. { printf("Symbol: %s\n", yytext); }
%%
int main()
{
 printf("Enter the string: ");
 yylex(); // Start the lexer
 return 0;
}
int yywrap()
{
 return 1;
}

/*
//lex keywords.l
//cc lex.yy.c -ll -o keywords
//./keywords
*/