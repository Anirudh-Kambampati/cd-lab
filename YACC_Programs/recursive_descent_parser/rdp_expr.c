#include <stdio.h>
#include <ctype.h>
char input[100];
int i = 0;
// Function declarations
void E(), EP(), T(), TP(), F();
// Match current character
void match(char ch) {
 if (input[i] == ch)
 i++;
 else { printf("String Rejected\n");
 return;
 } }
// E -> T E'
void E() {
 T();
 EP();
}
// E' -> + T E' | eps
void EP() {
 if (input[i] == '+') {
 match('+');
 T();
 EP();
 } }
// T -> F T'

void T() {
 F();
 TP();
}
// T' -> * F T' | eps
void TP() {
 if (input[i] == '*') {
 match('*');
 F();
 TP();
 } }
// F -> (E) | id
void F() {
 if (isalnum(input[i])) { // id represented by single letter or digit
 i++;
 }
 else if (input[i] == '(') {
 match('(');
 E();
 if (input[i] == ')')
 match(')');
 else {
 printf("String Rejected\n");
 i = -1;
 } }
 else {
 printf("String Rejected\n");
 i = -1;
 } }
int main() {
 printf("Enter expression: ");
 scanf("%s", input);
 E();
 if (i != -1 && input[i] == '\0')
 printf("String Accepted\n");
 else
 printf("String Rejected\n");
 return 0;
}

//gcc rdp_expr.c -o rdp_expr
//./rdp_expr