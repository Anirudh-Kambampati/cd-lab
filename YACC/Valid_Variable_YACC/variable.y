%{
#include <stdio.h>
int yylex(void);
int yyerror(const char *s);
%}

%token ID NUM

%%
input : variable          { printf("Valid Variable\n"); }
      ;

variable : ID
         | ID '_' ID
         ;
%%

int main()
{
    printf("Enter variable: ");
    yyparse();
    return 0;
}

int yyerror(const char *s)
{
    printf("Invalid Variable\n");
    return 0;
}

//yacc -d variable.y
//lex variable.l
//cc y.tab.c lex.yy.c -ll
//./a.out
