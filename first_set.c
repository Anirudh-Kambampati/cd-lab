
#include <stdio.h>
#include <string.h>

char production[10][10];
char firstSet[26][10];

int numProductions;

// Check whether a character is a terminal
int isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

// Function to calculate FIRST set
void computeFirst(char symbol) {

    int idx = symbol - 'A';

    // If FIRST is already calculated, return
    if (firstSet[idx][0] != '\0')
        return;

    // Check all productions
    for (int i = 0; i < numProductions; i++) {

        if (production[i][0] == symbol) {

            char rhs = production[i][3];

            // Skip direct left recursion
            if (rhs == symbol)
                continue;

            // If RHS starts with a terminal
            if (isTerminal(rhs)) {

                int len = strlen(firstSet[idx]);

                if (strchr(firstSet[idx], rhs) == NULL) {
                    firstSet[idx][len] = rhs;
                    firstSet[idx][len + 1] = '\0';
                }
            }

            // If RHS starts with a non-terminal
            else {

                computeFirst(rhs);

                int rIdx = rhs - 'A';

                // Copy FIRST of RHS non-terminal
                for (int j = 0; firstSet[rIdx][j] != '\0'; j++) {

                    int len = strlen(firstSet[idx]);

                    if (strchr(firstSet[idx], firstSet[rIdx][j]) == NULL) {
                        firstSet[idx][len] = firstSet[rIdx][j];
                        firstSet[idx][len + 1] = '\0';
                    }
                }
            }
        }
    }
}

int main() {

    printf("Enter number of productions: ");
    scanf("%d", &numProductions);

    printf("Enter productions:\n");

    for (int i = 0; i < numProductions; i++) {
        scanf("%9s", production[i]);
    }

    memset(firstSet, 0, sizeof(firstSet));

    // Calculate FIRST for each non-terminal
    for (int i = 0; i < numProductions; i++) {
        char symbol = production[i][0];
        computeFirst(symbol);
    }

   
// Display FIRST sets without duplicates
printf("\nFIRST Sets:\n");

int printed[26] = {0};

for (int i = 0; i < numProductions; i++) {

    char symbol = production[i][0];
    int idx = symbol - 'A';

    // Print only if this non-terminal hasn't been printed
    if (!printed[idx]) {

        printed[idx] = 1;

        printf("FIRST(%c) = { ", symbol);

        for (int j = 0; firstSet[idx][j] != '\0'; j++) {
            printf("%c ", firstSet[idx][j]);
        }

        printf("}\n");
    }
}

    return 0;
}
// gcc first_set.c
// ./a.out