#include <stdio.h>
#include <string.h>
/* Type checking for statements like:  a = b + c
   Step 1: read variable declarations (type and name).
   Step 2: read statements and check the types.
   Rule 1: if any operand is float, the expression is float.
   Rule 2: a float value cannot be stored in an int variable. */
char type[10][10];     /* type of each variable */
char name[10][10];     /* name of each variable */
int n;                 /* number of variables   */
/* returns the type of a variable (or "none" if not declared) */
char *gettype(char *v) {
    for (int i = 0; i < n; i++)
        if (strcmp(name[i], v) == 0)
            return type[i];
    return "none";
}
int main() {
    int m;
    char a[10], eq[3], b[10], op[3], c[10];
    char *ta, *tb, *tc;
    scanf("%d", &n);                      /* number of declarations */
    for (int i = 0; i < n; i++)
        scanf("%s %s", type[i], name[i]);
    scanf("%d", &m);                      /* number of statements */
    while (m--) {
        scanf("%s %s %s %s %s", a, eq, b, op, c);
        printf("%s = %s %s %s  ->  ", a, b, op, c);
        ta = gettype(a);
        tb = gettype(b);
        tc = gettype(c);
        if (strcmp(ta, "none") == 0 || strcmp(tb, "none") == 0 || strcmp(tc, "none") == 0)
            printf("Undeclared variable\n");
        else if (strcmp(ta, "int") == 0 && (strcmp(tb, "float") == 0 || strcmp(tc, "float") == 0))
            printf("Type Error (float assigned to int)\n");
        else
            printf("Type OK\n");
    }
    return 0;
}
//how to run
// gcc typecheck.c
// ./a.out

/* example input/output
3
int a
int b
float c
2
a = b + c
c = b + c

a = b + c  ->  Type Error (float assigned to int)
c = b + c  ->  Type OK*/