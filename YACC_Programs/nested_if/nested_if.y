%{
#include <stdio.h>
%}
%token IF THEN ELSE ID
%%
program:
 stmt { printf("Valid Nested-If Statement\n"); }
 ;
stmt:
 IF expr THEN stmt ELSE stmt
 | IF expr THEN stmt
 | ID
 ;
expr:
 ID
 ;
%%
int main()
{
 printf("Enter statement: ");
 yyparse();
 return 0;
}
int yyerror(char *s)
{
 printf("Invalid Statement\n");
 return 0;
}