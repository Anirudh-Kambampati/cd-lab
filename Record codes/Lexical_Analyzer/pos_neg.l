%{
#include <stdio.h>
int positive_integers = 0;
int negative_integers = 0;
int positive_fractions = 0;
int negative_fractions = 0;
%}
digit [0-9]
%%
[+]?[0-9]+ { positive_integers++; }
-[0-9]+ { negative_integers++; }
[+]?[0-9]*\.[0-9]+ { positive_fractions++; }
-[0-9]*\.[0-9]+ { negative_fractions++; }
[ \t\n]+ ; /* Ignore whitespace */
. ; /* Ignore other characters */
%%
int main() {
 printf("Enter numbers (Press Ctrl+D to stop):\n");
 yylex();
 printf("Positive Integers : %d\n", positive_integers);
 printf("Negative Integers : %d\n", negative_integers);
 printf("Positive Fractions: %d\n", positive_fractions);
 printf("Negative Fractions: %d\n", negative_fractions);
 return 0;
}
int yywrap(){
return 1;
}