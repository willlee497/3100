#include <stdio.h>
#include <assert.h>

double leibnizRecurrent(int n)
{
  double z;
  double cheese;
  if (n==0){
    return 1.0;
  }
  else{
    z = leibnizRecurrent(n-1);
    cheese =  (n % 2 == 0 ? 1.0 : -1.0)/(2*n +1);
    return cheese + z;
  }
  /* TODO: Fill in a recurrent version. That is, compute the term for n plus leibnizRecurrent(n - 1) 
           Try to avoid the use of pow.
  */

}

double leibnizIterative(int n)
{
   double sum = 0.0;
    
    for (int i = 0; i <= n; i++) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
        sum += term;
    }
    
  return sum;
  /* TODO: Fill in the iterative version. That is, use a loop to compute the summation. 
           Try to avoid the use of pow.
  */
}

int main(int argc, char* argv[]){
  if(argc != 3){
    printf("Usage: ./pi <mode> <n>, where <mode> is 1 for recurrent version, and 2 is for the iterative version, and n is the upper bound of the summation.\n");
  }else{
    int mode = 0, n = 0;
    double pi = 0;
    assert(sscanf(argv[1], "%d", &mode) == 1);
    assert(sscanf(argv[2], "%d", &n) == 1);
    assert(mode == 1 || mode == 2);
    assert(n >= 0);
    if(mode == 1){
      pi = 4*leibnizRecurrent(n);
    }else{
      pi = 4*leibnizIterative(n);
    }
    printf("PI: %f\n", pi);
  }
  return 0;
}
