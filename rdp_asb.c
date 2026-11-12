#include <stdio.h>

char input[100];
int i = 0;

// Grammar: S -> aSb | epsilon

void S() {
    if (input[i] == 'a') {

        i++;          // Match 'a'

        S();          // Recursively parse S

        if (input[i] == 'b') {
            i++;      // Match 'b'
        }
        else {
            printf("String Rejected\n");
            i = -1;
        }
    }
    // If current character is not 'a',
    // apply epsilon (empty production).
}

int main() {
    printf("Enter string: ");
    scanf("%99s", input);

    S();

    if (i != -1 && input[i] == '\0') {
        printf("String Accepted\n");
    }
    else {
        printf("String Rejected\n");
    }

    return 0;
}
//gcc rdp_asb.c -o rdp_asb
// ./rdp_asb