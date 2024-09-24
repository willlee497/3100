/* Write a C program to implement a min heap. Your program must implement the below functions:
 * makeHeap - creates a heap in memory. Input: max number of values that the heap can hold. Output: pointer to the heap in memory. 
 * insertHeap - insert values in a heap starting at index 1. Make sure the heap property is maintained. Input: pointer to a heap, value to insert.  
 * printHeap -  prints the values as a heap. Input: pointer to a heap. 
 * emptyHeap - check if a heap is empty. Input: pointer to a heap. Output: true if the heap is empty; false otherwise.
 * extractMin - extract and return the min value from a heap. Make sure the remaining elements form a valid heap. Input: pointer to a heap. Output: an int value.
 * freeHeap - deallocates any allocated memory. Input: pointer to a heap.*/
/*heap.c*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int* t; //pointer to an array containing the elements in the heap
    int sz;  //number of elements currently in the heap
    int msz; //max number of elements a heap can store
} Heap;


Heap* makeHeap(int msz) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->t = (int*)malloc(sizeof(int)*msz);
    h->sz = 0;
    h->msz = msz;
    return h;
}

void freeHeap(Heap* h) {
    free(h->t);
    free(h);
    return;
}

int emptyHeap(Heap* h) {
    return h->sz == 0;
}

void printHeapAux(Heap* h, int from) {
    if(from <= h->sz) {
        printf("(");
        printf("%d ", h->t[from]);
    printHeapAux(h, from*2);
    printf(" ");
    printHeapAux(h, from*2+1);
    printf(")");
} else printf(".");
   return;
}

void printHeap(Heap* h) {
    printHeapAux(h, 1);
    printf("\n");
    return;
}

void insertHeap(Heap* h, int val) {
    if(h->sz < h->msz) {
        int at = h->sz + 1;
        h->t[at] = val;
        h->sz++;
        int p = at;
        while(at>1) {
            p = at/2;
            if(h->t[at] > h->t[p])
               return;
                h->t[at] = h->t[p];
                h->t[p] = val;
                at = p;
        } 
    } else printf("Heap is full\n");
    return;
}

void heapify(Heap* h, int from) {
    while(1) {
        int l = from *2;
        int r = from * 2 +1;
        int s = from;
        if(l <= h->sz && h->t[l] < h->t[from])
            s = l;
        if(r <= h->sz && h->t[r] < h->t[s])
            s = r;
        if(s!=from) {
            int temp = h->t[s];
            h->t[s] = h->t[from];
            h->t[from] = temp;
            from = s;
        }else break;
    }
}

int extractMin(Heap* h) {
    int val = h->t[1];
    h->t[1] = h->t[h->sz];
    h->sz--;
    heapify(h,1);
    return val;
}

int main() {
    Heap* h = makeHeap(128);
    for(int i=0; i<5; i++){
        insertHeap(h, 5-i);
    }
    printHeap(h);
    while(!emptyHeap(h)){
        int v = extractMin(h);
        printf("Got: %d\n", v);
    }

    freeHeap(h);
    return 0;
}

/*heapTest.c*/
#ifndef ___HEAPHEADER_H
#define ___HEAPHEADER_H

typedef struct Heap{
    int* t;
    int sz;
    int msz;
} Heap;

Heap* makeHeap(int msz);
void freeHeap(Heap* h);
int emptyHeap(Heap* h);
void printHeap(Heap* h);
void insertHeap(Heap* h, int val);
void heapify(Heap* h, int from);
int extractMin(Heap* h);

#endif ___HEAPHEADER_H
