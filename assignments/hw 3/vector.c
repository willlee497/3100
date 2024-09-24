#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void initVector(IntVector* vec, int cap)
{
  /*
  list->len = 0;TODO: The IntVector structure is already allocated in memory. You need to fill in the fields of it. For this, you'll need to allocate an array for cap integers.
   */
  vec->numbers = (int*)malloc(sizeof(int) * cap);
  vec->size = 0;
  vec->capacity = cap;

}

void freeVector(IntVector* vec)
{
  free(vec->numbers);

  /*  ILNode* current = list->head;
  ILNode* next; 
    TODO: Free the integer array that the IntVector contains. 
  */
}

void expandVector(IntVector* vec)
{
  vec->capacity *= 2;
  /*
    TODO: Use the realloc function to double the capacity of the vector. This is only one line. 
  */
  vec->numbers = realloc(vec->numbers, sizeof(int)*vec->capacity);
}

void pushBackVector(IntVector* vec, int number)
{
  /*
    TODO: First, check if the vector size is equal to capacity. If it is, then expand it. Then, make the last element of the vector be number; don't forget to increase the size field.
   */
  if (vec->size == vec->capacity){
    expandVector(vec);
  } 
  vec->size++;
  vec->numbers[vec->size - 1] = number;

}
int popBackVector(IntVector* vec)
{
  assert(vec->size > 0); /* asserts that the vector contains at least 1 element */
  /* 
    TODO: Remove and return the last element. Decrease the vector size by 1. 
   */
  int temp = vec->numbers[vec->size -1];
  vec->size--;
  return temp;
}

void pushFrontVector(IntVector* vec, int number)
{
  if (vec->size == vec->capacity){
    expandVector(vec);
  }

  for (int i = vec->size; i<= 0; i--){
    vec->numbers[i] = vec->numbers[i-1];
  }
  vec->numbers[0] = number;
  /*
    TODO: First, check if the vector size is equal to the capacity. If it is, then expand it. Then, insert an element into the front of the vector. Don't forget to increment the size. 
   */
  vec->size++;
}

int popFrontVector(IntVector* vec)
{
  assert(vec->size > 0);
  /*
    TODO: Remove and return the number at the head of the vector. Be sure to shift remaining elements over to the left (toward the start of the vector) by one place. 
   */
  int tempo = vec->numbers[0];
  for (int j = 1; j<=vec->size ;j++){
    vec->numbers[j-1] = vec->numbers[j];
  }
  vec->size--;
  return tempo;
}

void swap(IntVector* vec, size_t indexOne, size_t indexTwo)
{
  assert(indexOne < vec->size);
  assert(indexTwo < vec->size);
  int temp = vec->numbers[indexOne];
  vec->numbers[indexOne] = vec->numbers[indexTwo];
  vec->numbers[indexTwo] = temp;
}

void sortVector(IntVector* vec)
{
  /*
    TODO: Impement Insertion Sorlt to sort the vector. The swap function will be useful here. 
   */
  for(int k = 1; k <=vec->size; k++){
    int key = vec->numbers[k];
    int y = k - 1;
    while(y>=0 && vec->numbers[y]> key){
      vec->numbers[y+1] = vec->numbers[y];
      y--;

    }
    vec->numbers[y+1] = key;
  }
}

void printVector(IntVector* vec)
{
  printf("(");
  for(size_t i = 0; i < vec->size; i++){
    printf("%d ", vec->numbers[i]);
  }
  printf(")\n");
}

int lengthVector(IntVector* vec)
{
  return vec->size;
}
