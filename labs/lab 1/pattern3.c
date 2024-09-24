/* Print the following diamond of * for n rows, where n is an integer taken as input from the user. In the below example, n = 5.

            *
          * * *
        * * * * *
      * * * * * * *
    * * * * * * * * *
      * * * * * * *
        * * * * *
          * * *
            * 
            
*/

/* Do not edit the code that is given to you. */

#include <stdio.h>

int main(int argc, char* argv[]) {
    int n;
    printf("Enter a value for n: \n");
    scanf("%d", &n);
    int i, j, k;

    for (i = 1; i <= n; i++) {
        for (j = i; j < n; j++) {
            printf("  ");
        }
        for (k = 1; k <= 2*i-1; k++) {
            printf("* ");
        }
        printf("\n");
    }

    for (i = n-1; i > 0; i--) {
        for (j = n; j > i; j--) {
            printf("  ");
        }
        for (k = 1; k <= 2*i-1; k++) {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}


