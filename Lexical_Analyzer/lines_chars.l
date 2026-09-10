%{
#include<stdio.h>
%}
int lines = 0,words = 0,spaces = 0,characters = 0;
%%
\n {lines++;}
{space} {spaces++;} [aeiouAEIOU]
{words} {words++;characters+=yyleng;}
. {characters++;}
int main(){
    printf("Enter input strings");
    yylex();
     printf("Lines : %d\n", lines);
 printf("Words : %d\n", words);
 printf("Spaces : %d\n", spaces);
 printf("Characters : %d\n", characters);
    return 0
}
int yywrap(){
    return 1;
}