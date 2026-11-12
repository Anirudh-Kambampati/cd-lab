%{
#include <stdio.h>
%}
%%
[a-z] { printf("Lowercase: %s\n", yytext); }
[A-Z] { printf("Uppercase: %s\n", yytext); }
[ \t\n]+ ; /* Ignore whitespace */
. ; /* Ignore digits and special characters */
%%
int main()
{
 printf("Enter characters: ");
 yylex();
 return 0;
}
int yywrap()
{
 return 1;
}

//flex upper_lower.l
// gcc lex.yy.c -o upper_lower -lfl
// ./upper_lower