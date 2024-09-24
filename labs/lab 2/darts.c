/* This program approximates the value of pi. 
 * TODO: Fix this code by replacing DISTSQUARED and SAMPLE with the corresponding functions. 
 */

#include <stdio.h>
#include <stdlib.h>

#define N 10000
#define MAX 2147483647
#define RANDPOINT (1.0*(rand() % MAX)/MAX)
/*
#define DISTSQUARED(x, y) (x*x + y*y)
#define SAMPLE (DISTSQUARED(RANDPOINT, RANDPOINT) <= 1)
*/
double distsquared(double x, double y){
  double result = (x*x) + (y*y);
  return result;

}

int sample(){
  double result1 = distsquared(RANDPOINT, RANDPOINT);
  return result1 <= 1;

}

int main(int argc, char* argv[]){
  srand(10);
  unsigned int j = 0;
  for(unsigned int i = 0; i < N; i++){
    if(sample()){
      j++;
    }
  }
  double pi = 4.0*j/N;
  printf("pi: %f\n", pi);
    
  return 0;
}

