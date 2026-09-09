%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(const char *s);
%}

%token NUM

%%
input : expr '\n'       { printf("Result = %d\n", $1); }
      ;

expr  : expr '+' term   { $$ = $1 + $3; }
      | expr '-' term   { $$ = $1 - $3; }
      | term            { $$ = $1; }
      ;

term  : term '*' factor { $$ = $1 * $3; }
      | term '/' factor { $$ = $1 / $3; }
      | factor          { $$ = $1; }
      ;

factor: '(' expr ')'    { $$ = $2; }
      | NUM             { $$ = $1; }
      ;
%%

int main()
{
    printf("Enter expression: ");
    yyparse();
    return 0;
}

int yyerror(const char *s)
{
    printf("Invalid Expression\n");
    return 0;
}
