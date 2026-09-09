#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 20
#define MAX_SYM  10
#define SYM_LEN  10
#define MAX_FIRST 20

typedef struct {
    char lhs;
    char rhs[MAX_SYM][SYM_LEN];
    int numSym;
} Production;

Production prod[MAX_PROD];
int n;

char firstSet[26][MAX_FIRST][SYM_LEN];
int firstCount[26];
int state[26];  /* 0 = not started, 1 = in progress, 2 = done */

int isNonTerminal(const char *s)
{
    return (strlen(s) == 1 && isupper((unsigned char)s[0]));
}

void addFirst(char nonTerminal, const char *sym)
{
    int idx = nonTerminal - 'A';
    for (int i = 0; i < firstCount[idx]; i++)
        if (strcmp(firstSet[idx][i], sym) == 0)
            return;
    strcpy(firstSet[idx][firstCount[idx]], sym);
    firstCount[idx]++;
}

/* Break "E+T" into tokens ["E","+","T"], "(E)" into ["(","E",")"],
   "id" into ["id"], "#" (epsilon) into ["#"] */
void tokenizeRHS(const char *rhs, Production *p)
{
    int i = 0, len = strlen(rhs), c = 0;
    while (i < len) {
        if (isupper((unsigned char)rhs[i])) {
            p->rhs[c][0] = rhs[i];
            p->rhs[c][1] = '\0';
            c++; i++;
        } else if (islower((unsigned char)rhs[i])) {
            int j = 0;
            while (i < len && islower((unsigned char)rhs[i]))
                p->rhs[c][j++] = rhs[i++];
            p->rhs[c][j] = '\0';
            c++;
        } else {
            /* single-char terminal: +, -, *, /, (, ), #, etc. */
            p->rhs[c][0] = rhs[i];
            p->rhs[c][1] = '\0';
            c++; i++;
        }
    }
    p->numSym = c;
}

void computeFirst(char A);

void processAlternative(char A, Production *p)
{
    int nullablePrefix = 1;

    for (int k = 0; k < p->numSym && nullablePrefix; k++) {
        char *sym = p->rhs[k];

        if (strcmp(sym, "#") == 0) {
            addFirst(A, "#");
            nullablePrefix = 0;
        } else if (isNonTerminal(sym)) {
            char B = sym[0];
            computeFirst(B);
            int bIdx = B - 'A';
            int hasEpsilon = 0;
            for (int m = 0; m < firstCount[bIdx]; m++) {
                if (strcmp(firstSet[bIdx][m], "#") == 0) { hasEpsilon = 1; continue; }
                addFirst(A, firstSet[bIdx][m]);
            }
            if (!hasEpsilon)
                nullablePrefix = 0;
        } else {
            addFirst(A, sym);
            nullablePrefix = 0;
        }
    }

    if (nullablePrefix)
        addFirst(A, "#");
}

/* Left-recursion safe: if A is already being computed (state 1),
   this call returns immediately instead of recursing forever. */
void computeFirst(char A)
{
    int idx = A - 'A';
    if (state[idx] == 2 || state[idx] == 1)
        return;

    state[idx] = 1;
    for (int i = 0; i < n; i++)
        if (prod[i].lhs == A)
            processAlternative(A, &prod[i]);
    state[idx] = 2;
}

int main()
{
    char input[50];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions one per line, e.g.\n");
    printf("  E->E+T\n  E->T\n  T->T*F\n  T->F\n  F->(E)\n  F->id\n");
    printf("(use # for epsilon, e.g. A->#)\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", input);
        char *arrow = strstr(input, "->");
        prod[i].lhs = input[0];
        tokenizeRHS(arrow + 2, &prod[i]);
    }

    for (int i = 0; i < 26; i++) {
        firstCount[i] = 0;
        state[i] = 0;
    }

    /* remember distinct LHS symbols in the order first seen */
    char seen[26];
    int numSeen = 0;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < numSeen; j++)
            if (seen[j] == prod[i].lhs) found = 1;
        if (!found) seen[numSeen++] = prod[i].lhs;
    }

    for (int i = 0; i < numSeen; i++)
        computeFirst(seen[i]);

    printf("\nFIRST Sets:\n");
    for (int i = 0; i < numSeen; i++) {
        char A = seen[i];
        int idx = A - 'A';
        printf("FIRST(%c) = { ", A);
        for (int j = 0; j < firstCount[idx]; j++)
            printf("%s ", firstSet[idx][j]);
        printf("}\n");
    }

    return 0;
}
