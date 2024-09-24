/* Write a program to compute the binomial. */

#include <stdio.h>

/* This function should recursively compute the binomial (n, k) and return its value. */
int binomial(int n, int k){
  
  if(k==0 || k==n) {
    return 1;
  }
  return (binomial(n-1,k)+binomial(n-1,k-1));
  
}

int main(int argc, char* argv[]){
  int n,k = 0;
  printf("Enter n: ");
  scanf("%d", &n);
  printf("Enter k: ");
  scanf("%d", &k);
  printf("%d, choose %d, = %d", n, k, binomial(n,k));
  return 0;
}
