#include <stdio.h>
#include <string.h>
char production[10][10];
char firstSet[26][10];
int numProductions;
int isTerminal(char c) {
 return !(c >= 'A' && c <= 'Z');
}
void computeFirst(char symbol) {
 int idx = symbol - 'A';
 if (firstSet[idx][0] != '\0')
 return; /* already computed */
 for (int i = 0; i < numProductions; i++) {
 if (production[i][0] == symbol) {
 char rhs = production[i][3]; /* first symbol after "X->" */
 if (isTerminal(rhs)) {
 int len = strlen(firstSet[idx]);
 if (strchr(firstSet[idx], rhs) == NULL) {
 firstSet[idx][len] = rhs;
 firstSet[idx][len + 1] = '\0';
 }
 } else {
 computeFirst(rhs);
 int rIdx = rhs - 'A';
 for (int j = 0; firstSet[rIdx][j] != '\0'; j++) {
 int len = strlen(firstSet[idx]);
 if (strchr(firstSet[idx], firstSet[rIdx][j]) == NULL) {
 firstSet[idx][len] = firstSet[rIdx][j];

 firstSet[idx][len + 1] = '\0';
 }}}}}}}
int main() {
 printf("Enter number of productions: ");
 scanf("%d", &numProductions);
 printf("Enter productions:\n");
 for (int i = 0; i < numProductions; i++) {
 scanf("%s", production[i]);
 }
 memset(firstSet, 0, sizeof(firstSet));
 for (int i = 0; i < numProductions; i++) {
 char symbol = production[i][0];
 computeFirst(symbol);
 }
 printf("\nFIRST Sets:\n");
 for (int i = 0; i < numProductions; i++) {
 char symbol = production[i][0];
 if (firstSet[symbol - 'A'][0] != '\0') {
 printf("FIRST(%c) = { ", symbol);
 for (int j = 0; firstSet[symbol - 'A'][j] != '\0'; j++) {
 printf("%c ", firstSet[symbol - 'A'][j]);
 }
 printf("}\n");
 }
 }
 return 0;
}

//gcc first_set.c -o first_set
//./first_set