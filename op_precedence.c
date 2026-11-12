#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SYMS 8 /* id + - * / ( ) $ */
char symbols[SYMS] = {'i', '+', '-', '*', '/', '(', ')', '$'};
/* Operator precedence table
 Rows/Cols order: id + - * / ( ) $
 '<' = yields precedence, '>' = takes precedence,
 '=' = equal precedence, ' ' = error / no relation */
char table[SYMS][SYMS] = {
 /* id */ { ' ', '>', '>', '>', '>', ' ', '>', '>' },
 /* + */ { '<', '>', '>', '<', '<', '<', '>', '>' },
 /* - */ { '<', '>', '>', '<', '<', '<', '>', '>' },
 /* * */ { '<', '>', '>', '>', '>', '<', '>', '>' },
 /* / */ { '<', '>', '>', '>', '>', '<', '>', '>' },
 /* ( */ { '<', '<', '<', '<', '<', '<', '=', ' ' },
 /* ) */ { ' ', '>', '>', '>', '>', ' ', '>', '>' },
 /* $ */ { '<', '<', '<', '<', '<', '<', ' ', ' ' }
};

int symIndex(char c) {
 int i;
 for (i = 0; i < SYMS; i++)
 if (symbols[i] == c) return i;
 return -1;
}
char stack[100];
int top = -1;
void push(char c) { stack[++top] = c; stack[top + 1] = '\0'; }
char pop(void) { char c = stack[top--]; stack[top + 1] = '\0'; return c; }
char peekTerm(void){ return stack[top]; }
int main() {
 char input[100], buffer[100];
 int ip = 0, len, i, j = 0;
 stack[0] = '\0';
 printf("Enter input string (use 'i' for id, e.g. i+i*i): ");
 scanf("%s", buffer);
 /* append end marker $ */
 len = strlen(buffer);
 for (i = 0; i < len; i++) input[j++] = buffer[i];
 input[j++] = '$';
 input[j] = '\0';
 push('$');
 printf("\n%-15s %-15s %-10s\n", "STACK", "INPUT", "ACTION");
 while (1) {
 char a = peekTerm();
 char b = input[ip];
 printf("%-15s %-15s ", stack, input + ip);
 if (a == '$' && b == '$') {
 printf("Accept\n");
 printf("\nInput string is VALID as per operator precedence parsing.\n");
 break;
 }

 int ai = symIndex(a); int bi = symIndex(b);
 if (ai == -1 || bi == -1) {
 printf("Error\n");
 printf("\nInvalid symbol encountered.\n");
 break;
 }
 char rel = table[ai][bi];
 if (rel == '<' || rel == '=') {
 printf("Shift %c\n", b);
 push(b);
 ip++;
 } else if (rel == '>') {
 char popped;
 do {
 popped = pop();
 } while (top >= 0 && table[symIndex(peekTerm())][symIndex(popped)] != '<'
 && peekTerm() != '$');
 printf("Reduce\n");
 } else {
 printf("Error\n");
 printf("\nInput string is INVALID - no precedence relation between '%c' and '%c'.\n", a, b);
 break;
 }
 }
 return 0;
}

//gcc op_precedence.c -o op_precedence
//./op_precedence