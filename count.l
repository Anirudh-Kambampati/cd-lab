%{
#include <stdio.h>
int lines = 0, words = 0, spaces = 0, characters = 0;
%}
space [ \t]
word [a-zA-Z]+
%%
\n { lines++; }
{space} { spaces++; }
{word} { words++; characters += yyleng; }
. { characters++; }
%%
int main() {
 printf("Enter text (Press Ctrl+D to finish):\n");
 yylex();
 printf("Lines : %d\n", lines);
 printf("Words : %d\n", words);
 printf("Spaces : %d\n", spaces);
 printf("Characters : %d\n", characters);
 return 0;
}
int yywrap() {
 return 1;
}

//flex count.l
//gcc lex.yy.c -o wordcount -lfl
// ./wordcount