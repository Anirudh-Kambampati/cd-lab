#include <stdio.h>
#include <string.h>
/* Stack storage allocation - menu driven (push / pop) */
char name[10][10];     /* function names */
int size[10];          /* memory size of each function */
int top = -1;          /* top of stack */
int sp = 0;            /* total memory used */
void push() {
    char f[10];
    int s;
    if (top == 9) {
        printf("Stack is full\n");
        return;
    }
    printf("Enter function name and size: ");
    scanf("%9s %d", f, &s);
    top++;
    strcpy(name[top], f);
    size[top] = s;
    sp = sp + s;
    printf("Pushed %s, stack pointer = %d\n", f, sp);
}
void pop() {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    sp = sp - size[top];
    printf("Popped %s, stack pointer = %d\n", name[top], sp);
    top--;
}
int main() {
    int choice;
    while (1) {
        printf("\n1.Push  2.Pop  3.Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1)   /* stop on bad input / end of input */
            return 0;
        switch (choice) {
            case 1: push(); break;
            case 2: pop();  break;
            case 3: return 0;
            default: printf("Invalid choice\n");
        }
    }
}

//how to run
// gcc stack.c 
// ./a.out

/* example output
1.Push  2.Pop  3.Exit
Enter choice: 1
Enter function name and size: main 100
Pushed main, stack pointer = 100

1.Push  2.Pop  3.Exit
Enter choice: 1
Enter function name and size: display 50
Pushed display, stack pointer = 150

1.Push  2.Pop  3.Exit
Enter choice: 2
Popped display, stack pointer = 100

1.Push  2.Pop  3.Exit
Enter choice: 3*/