
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SYMS 8

// Symbols supported by the parser
char symbols[SYMS] = {
    'i', '+', '-', '*', '/', '(', ')', '$'
};

// Operator precedence table
// '<' = Shift
// '>' = Reduce
// '=' = Equal precedence
// ' ' = Error
char table[SYMS][SYMS] = {

    /*       i    +    -    *    /    (    )    $  */

    /* i */ { ' ', '>', '>', '>', '>', ' ', '>', '>' },

    /* + */ { '<', '>', '>', '<', '<', '<', '>', '>' },

    /* - */ { '<', '>', '>', '<', '<', '<', '>', '>' },

    /* * */ { '<', '>', '>', '>', '>', '<', '>', '>' },

    /* / */ { '<', '>', '>', '>', '>', '<', '>', '>' },

    /* ( */ { '<', '<', '<', '<', '<', '<', '=', ' ' },

    /* ) */ { ' ', '>', '>', '>', '>', ' ', '>', '>' },

    /* $ */ { '<', '<', '<', '<', '<', '<', ' ', ' ' }
};

// Find the index of a symbol
int symIndex(char c) {

    for (int i = 0; i < SYMS; i++) {
        if (symbols[i] == c)
            return i;
    }

    return -1;
}

// Stack declaration
char stack[100];
int top = -1;

// Push an element onto the stack
void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

// Pop an element from the stack
char pop(void) {

    char c = stack[top--];

    stack[top + 1] = '\0';

    return c;
}

// Get the topmost stack symbol
char peekTerm(void) {
    return stack[top];
}

int main() {

    char input[100], buffer[100];

    int ip = 0;
    int len, i, j = 0;

    stack[0] = '\0';

    printf("Enter input string (use 'i' for id, e.g. i+i*i): ");
    scanf("%99s", buffer);

    // Append end marker '$'
    len = strlen(buffer);

    for (i = 0; i < len; i++)
        input[j++] = buffer[i];

    input[j++] = '$';
    input[j] = '\0';

    // Initialize stack with '$'
    push('$');

    printf("\n%-15s %-15s %-10s\n",
           "STACK", "INPUT", "ACTION");

    while (1) {

        char a = peekTerm();
        char b = input[ip];

        printf("%-15s %-15s ", stack, input + ip);

        // Check acceptance condition
        if (a == '$' && b == '$') {

            printf("Accept\n");

            printf("\nInput string is VALID as per operator precedence parsing.\n");

            break;
        }

        int ai = symIndex(a);
        int bi = symIndex(b);

        // Check for invalid symbols
        if (ai == -1 || bi == -1) {

            printf("Error\n");
            printf("\nInvalid symbol encountered.\n");

            break;
        }

        // Get precedence relation
        char rel = table[ai][bi];

        // SHIFT operation
        if (rel == '<' || rel == '=') {

            printf("Shift %c\n", b);

            push(b);
            ip++;
        }

        // REDUCE operation
        else if (rel == '>') {

            char popped;

            do {
                popped = pop();

            } while (
                top >= 0 &&
                table[symIndex(peekTerm())][symIndex(popped)] != '<'
                && peekTerm() != '$'
            );

            printf("Reduce\n");
        }

        // No precedence relation
        else {

            printf("Error\n");

            printf("\nInput string is INVALID - no precedence relation between '%c' and '%c'.\n",
                   a, b);

            break;
        }
    }

    return 0;
}
// gcc op_precedence.c
// ./a.out