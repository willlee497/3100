/* Print the following pattern of * for n rows, where n is an integer taken as input from the user. In the below example, n = 5.

    * * * * * * * * *
      * * * * * * *
        * * * * *
          * * *
            * 
                
*/
#include <stdio.h>

int main(int argc, char* argv[]) {
    int n;
    printf("Enter a value for n: \n");
    scanf("%d", &n);
    int i, j, k;
    for(int i=0;i < n;i++){
      for(int j=0;j < i ; j++){
        printf("  ");
      }
      for(int k=0 ; k<2*(n-i)-1 ; k++){
        printf("* ");
      }
      printf("\n");
    }

    return 0;
}