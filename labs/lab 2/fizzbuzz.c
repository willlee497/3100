
#include <stdio.h>
int main(int argc, char* argv[])
{
    int n;
    printf("Enter a value for n:");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        if ((i % 5 == 0) && (i % 3 == 0)) {
            printf("fizzbuzz\n");
        }
        else if (i % 5 == 0) {
            printf("buzz\n");
        }
        else if (i % 3 == 0) {
            printf("fizz\n");
        }
        else {
            printf("%d\n", i);
        }
     
    }    
    return 0;    
}  


    