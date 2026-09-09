#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char word[])
{
    char keywords[][10] = {
        "int", "float", "char", "if", "else",
        "for", "while", "return"
    };

    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;

    return 0;
}

int main()
{
    char input[200];
    int i = 0;

    printf("Enter a C statement:\n");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0')
    {
        if (isspace(input[i]))
        {
            i++;
        }
        else if (isalpha(input[i]) || input[i] == '_')
        {
            char word[50];
            int j = 0;

            while (isalnum(input[i]) || input[i] == '_')
                word[j++] = input[i++];

            word[j] = '\0';

            if (isKeyword(word))
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
        }
        else if (isdigit(input[i]))
        {
            char number[50];
            int j = 0;

            while (isdigit(input[i]) || input[i] == '.')
                number[j++] = input[i++];

            number[j] = '\0';
            printf("Constant: %s\n", number);
        }
        else if (strchr("+-*/%=<>!", input[i]))
        {
            char op[3];
            op[0] = input[i];
            op[1] = '\0';
            i++;

            /* merge two-character operators: ==, !=, <=, >= */
            if ((op[0] == '=' || op[0] == '!' || op[0] == '<' || op[0] == '>') &&
                input[i] == '=')
            {
                op[1] = '=';
                op[2] = '\0';
                i++;
            }

            printf("Operator: %s\n", op);
        }
        else
        {
            printf("Special Symbol: %c\n", input[i]);
            i++;
        }
    }

    return 0;
}
