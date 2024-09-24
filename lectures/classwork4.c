#include <stdio.h>
#include <stdlib.h>

typedef struct heap{
    int* t;
    int size;
    int maxsize;
} Heap;

Heap* makeHeap(int maxsize){
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->t = (int*)malloc(sizeof(int)*maxsize)
    h->size = 0;
    h->maxsize = maxsize;
    return h;
}

void freeHeap(Heap* h){
    free(h->t);
    free(h);
    return;
}

int emptyHeap(Heap* h){
    return h->size==0;
}

void printHeapAux(Heap* h, int from){
    if (from <= h->size){
        printf("(");
        printf("%d", h->t[from]);
        printHeapAux(h, from*2);
        printf(" ");
        printHeapAux(h, from*2 +1);
        printf(")");
    }else printf(".");
}
/* p = parent, at = at curent spot ur adding at */
void insertHeap(Heap* h, int val){
    if (h->size < h-> maxsize){
        int at = h-> size +1;
        h-> t[at] = val;
        h-> size++;
        int p = at;   
        while(at>1){
            p = at/2 ;
            if (h->t[at] > h->t[p])
                return;
            h->t[at] = h->t[p];
            h-> t[p] = val;
            at = p;

        }

    }else printf("Heap is full.\n");
    return;
}

void printHeap(Heap* h){
    printHeapAux(h,1);
    printf("\n");
    return;

}

void heapify(Heap* h, int from){
    /*multiple if statements compare vals*/
    return;
}
int extractMin(Heap* h){
    int val = h->t[1];
    h-> t[1] = h->t[h->size];
    h-> size--;
    heapify(h,1);
    return val;
}
int main(){
    Heap* h = makeHeap(128);
    for(int i=0; i< 10; i++){
        insertHeap(h, 10-i);
        printHeap(h);
    while(!emptyHeap(h)) {
        int v = extractMin(h);
        printf("Got: %d\n", v);
    }
    freeHeap(h);
    return 0;
    }   
}









