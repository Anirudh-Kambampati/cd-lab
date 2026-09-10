%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(const char *s);
%}
%token NUM
%left '+' '-'
%left '*' '/'
%%
input:
 expr { printf("Valid Expression\n"); };
expr:
 expr '+' expr
 | expr '-' expr
 | expr '*' expr
 | expr '/' expr
 | '(' expr ')'
 | NUM
 ;
%%
int main(){
 printf("Enter Expression: ");
 yyparse();
 return 0;
}
int yyerror(const char *s){
 printf("Invalid Expression\n");
 return 0;
}

//yacc -d calc.y
//lex calc.l
//cc y.tab.c lex.yy.c -ll
//./a.out