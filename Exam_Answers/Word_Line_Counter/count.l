%{
#include <stdio.h>
int lines = 0, words = 0;
%}

%%
\n                  { lines++; }
[a-zA-Z0-9]+        { words++; }
[ \t]+              ;
.                   ;
%%

int main()
{
    printf("Enter text (Ctrl+D to finish):\n");
    yylex();

    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);

    return 0;
}

int yywrap()
{
    return 1;
}

//lex count.l
//cc lex.yy.c -ll
//./a.out
