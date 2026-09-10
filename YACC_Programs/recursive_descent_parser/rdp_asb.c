#include <stdio.h>
char input[100];
int i = 0;
// S -> aSb | eps
void S()
{
 if(input[i] == 'a')
 {
 i++; // match 'a'
 S();
 if(input[i] == 'b')
 i++; // match 'b'
 else
 {
 printf("String Rejected\n");
 i = -1;
 }
 }
 // epsilon production
}

int main()
{
 printf("Enter string: ");
 scanf("%s", input);
 S();
 if(i != -1 && input[i] == '\0')
 printf("String Accepted\n");
 else
 printf("String Rejected\n");
 return 0;
}

//gcc rdp_asb.c -o rdp_asb
//./rdp_asb