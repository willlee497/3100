#include "selectionSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void* sortThread(void* args) {
   TArg* targ = args;
   Segment* me = targ->seg;
   Share*  shr = targ->shr;
   me->won  = 1;
   int best = MAXINT,myGen=0;
   while(me->from < me->to) {
     /*
       TODO: Implement this function as follows.
        * Set the generation for the thread as the barrier gen and find the min element of the segment array.
        * Compare the min value to the value stored in the "best" field of the shared data structure shr. If the min found is smaller, update the best and winner fields of the shared structure. Do not forget to grab the lock before checking and updating values.
        * Incremement the number of threads reported and wait till all threads have entered the barrier.
        * If this thread is the last to enter, add the best value to the output array and swap the min element with the first elements of the winning segment. Reset the other fields of the shared structure and update the generation. Broadcast to wake up all threads. Note that if the winning segment has no more values left, the thread should exist and the number of threads expected in the barrier would be one less than before.
        * Finally, unlock the mutex for the shared object.
      */
      //selection sort using threads. shared data and barriers to sync. sorting process.
      // each thread needs its generation to share global gen for sync. purposes
      myGen = shr->gen;
      //reset thread won field to 0 to indicate that we have not finished sorting 
      me->won = 0;
      // segments of the array will be divided for each thread, they gotta cooperate with the others
      //selection sort n^2 time 
      //every thread grabs best min val at segment. if we need to compare all threads for best val we need to wait on threads to finish computing. 
      //if thread finishes work and others didnt, all threads got to wait (barriers) 
      //this program is reliant on every thread to do the work to get the right answer
      //each thread iterates over its assigned segment (from to to) then finds min val and index
      for(int i = me->from; i < me->to; i++){
        if (me->array[i] <best){
          best = me->array[i];
          me->minAt = i;
        }
      }
      //shr->best tracks curr min val
      //we lock so each thread can compare with global and if its smaller then we update the global with the threads smalelst val
      pthread_mutex_lock(&shr->mtx);
      if (shr->winner == NULL || best < shr->best){
        shr->winner = me;
        shr->best = best;
      }
      shr->reporting++; // indicate thread reaching barrier
      //reporting tracks how many threads have reached the sync. barrier
      //shr->needed = # of threads needed that need to be sorting their section
      //shr->gen (all threads wait for each thread to get min val so we need to get smallest val then 2nd smallest in these iterations)
      if (shr->reporting == shr->needed){
        //if all threads reached the thread barrier
        shr->winner->won = 1;
        //res array gets best value added and increments index then we perform swap with first unsorted element
        shr->res[shr->nbIn++] = shr->best;
        //we mark index and swaps with earliest index (from being earliest index) e.x. if we go from 2-4 from would be 2, then in this case we swap index of min val 
        //with the val we're at currently smallest index
        shr->winner->array[shr->winner->minAt] = shr->winner->array[shr->winner->from];
        shr->winner->array[shr->winner->from] = shr->best;
        shr->winner->from++; // now we move to next unsorted element
        if (shr->winner->from == shr->winner->to){ //basically done (from to to are equal now)
          shr->needed--;
        } //if we got no more elements we decrement thread participating
        shr->gen++; //signal a new round of sorting
        //reset vals
        shr->best = MAXINT;
        shr->winner = NULL;
        shr->reporting = 0;
        pthread_cond_broadcast(&shr->done);//then we wake up all threas w/ broadcast
      }
      else{ //threads that are not the last will have to wait on cond variable
        pthread_cond_wait(&shr->done, &shr->mtx);
      }
      //release mutex and reset thread local best for next iteration
      pthread_mutex_unlock(&shr->mtx);
      best = MAXINT;
   }
   return NULL;
}

MTArray* initArray(int* numbers, int n)  {   /* To initialize the array */
  MTArray* array = malloc(sizeof(MTArray));
  array->numbers = numbers;
  array->size = n;
  return array;
}

void printArray(MTArray* array) {           /* To print the array */
  for(int i = 0; i < array->size; i++)
    printf("%d ", array->numbers[i]);    
  printf("\n");
}

void checkArray(MTArray* a) {            /* To check if the array contains n elements and all elements are sorted */ 
   int ok =  1;
   for(int i=0; ok && i < a->size - 1;i++)
      ok = ok && a->numbers[i] <= a->numbers[i+1];
   if (!ok) {
      printf("Not sorted....\n");
      exit(1);
   }
}


