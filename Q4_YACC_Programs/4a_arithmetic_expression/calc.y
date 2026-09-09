%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(const char *s);
%}

%token NUM

%%
input : expr                 { printf("Valid Arithmetic Expression\n"); }
      ;

expr  : expr '+' term
      | expr '-' term
      | term
      ;

term  : term '*' factor
      | term '/' factor
      | factor
      ;

factor: '(' expr ')'
      | NUM
      ;
%%

int main()
{
    printf("Enter arithmetic expression: ");
    yyparse();
    return 0;
}

int yyerror(const char *s)
{
    printf("Invalid Arithmetic Expression\n");
    return 0;
}
