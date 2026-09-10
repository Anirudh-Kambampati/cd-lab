%{
#include<stdio.h>
%}
int vowels = 0;
int consonants=0;
%%
vowel [aeiouAEIOU]
letter [a-zA-Z]
{vowel} {vowels++;}
{letter} {consonants++;}
int main(){
    printf("Enter input strings");
    yylex();
    printf("Vowels:n", vowels);
 printf("Consonants: %d\n", consonants);

    return 0
}
int yywrap(){
    return 1;
}