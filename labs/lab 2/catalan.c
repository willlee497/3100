/* Write a program to compute the nth Catalan number. */

#include <stdio.h>

long catalan_number(int n)
{
    if(n==0){
        return 1;
    }
    else {
        // return (((4*n -2)/(n+1))* catalan_number(n-1));
        return catalan_number(n-1) * (4 * n - 2) / (n + 1);
    }
    /* TODO: Calculate the nth catalan number using the given recursi4on.
	     You do not need to use floating point operations */
}

/* Do not change the main function */
int main(void)
{
    int n;

    while (scanf("%d", &n) == 1) {
        if (n < 0) 
            printf("C(%2d) is not defined.\n", n);
        else 
            printf("C(%2d)=%18ld\n", n, catalan_number(n));
    }
    return 0;
}