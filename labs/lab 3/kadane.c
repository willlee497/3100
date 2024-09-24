#include <stdio.h>
#include <stdlib.h>

struct SubArray{
  /* code i changed*/
  int start;
  int end;
  int sum;

};

/* Given the array of numbers, this function computes the max sub array and returns the struct SubArray. numbers is a pointer to the array of numbers. length represents the number of values in the array */
struct SubArray kadane(int* numbers, int length){
  /* We begin by initializing a struct that contains the best sub array we've found so far (bestSubArray), and the best subarray ending at the previous position. */
  struct SubArray bestSubArray = {0, 0, numbers[0]};
  struct SubArray prevSubArray = {0, 0, numbers[0]};
/*if(numbers[j-1] + prevSubArray{0,j-1,numbers[j-1]}> numbers[j]){
      bestSubArray = prevSubArray{0,j-1,numbers[j-1]};
    }else{
      bestSubArray =  prevSubArray{0,j,numbers[j]};
    }*/
  for(int j = 1; j < length; j++){
    prevSubArray.end = j;
    if (prevSubArray.sum <= 0) {
      prevSubArray.start = j;
      prevSubArray.sum = numbers[j];
    } else {
      prevSubArray.sum += numbers[j];
    }
    if (prevSubArray.sum > bestSubArray.sum) {
      bestSubArray = prevSubArray;
    }
  }
  return bestSubArray;
} 
    /* TODO: When we are at index j, we need to make a decision about what the best sub-array ending at index j is. As described in the assignment, there are two options:
	1) The best sub-array ending at index j also starts at index j
	2) The best sub-array ending at index j starts at an index before j
	Suppose case 2 is true. Then, the best sub-array ending at index j is just an extension of the best array ending at index j - 1.
	To evaluate which case is better, we need to keep track of the best sub-array ending at index j - 1.
      
	Decide if case 1 or 2 is correct, and then do what is necessary for each case. */

  



int main(int argc, char* argv[]){
  printf("Enter numbers (then press 0 and enter): ");
  int numbersLength = 1;
  int* numbers = (int*)malloc(sizeof(int)*numbersLength); /*code i changed*/
  int x = 0;
  int i = 0;
  while(scanf("%d", &x) == 1 && x != 0){
    if(i == numbersLength){
      numbers = realloc(numbers, (numbersLength+1)*sizeof(int));
                              /* TODO: Call realloc to add space for another integer to the numbers array. */
      numbersLength++;
    }
    numbers[i] = x;
    i++;
  }
  struct SubArray result = kadane(numbers, i);
  printf("Max Sub Array: ");
  for(i = result.start; i <= result.end; i++){
    printf("%d ", numbers[i]);
  }
  printf("\n");
  free(numbers);
  return 0;
}
