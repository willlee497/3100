#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void initList(IntList* list)
{
  /*
    TODO: The IntList structure is already allocated in memory. You need to fill the fields in. In the initList function, you are passed a pointer to an IntList. You just need to set the head and tail fields
to NULL, and the len field to 0. For the freeList, you need to iterate through the list, and call free on each
node( head and tail to null and lenfield 0)
   */
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}

void freeList(IntList* list)
{
  /* (call free on each node)
    TODO: You need to free each node in the list. However, the actual list itself doesn't need to be freed here.
   */
  ILNode* current = list->head;
  ILNode* next; 

  while(current!= NULL){
    next = current->next;
    free(current);
    current = next;
  }
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}

void pushBackList(IntList* list, int number)
{
  /*
    TODO: Add a node containing the number to the end of the list
   */
  
  ILNode* new = (ILNode*)malloc(sizeof(ILNode));
  new->number = number;
  new->next = NULL;
  if (list->tail == NULL){
    list->head = new;
    list->tail = new;

  }else{
    list->tail->next = new;
    list->tail = new;
  }
  list->len++;
}

int popBackList(IntList* list)
{
  assert(list->head && list->tail && list->len > 0);
    ILNode* tempo = list->tail;
    int val = tempo->number;
  if (list->len == 1){
    free(tempo);
    list->head = list->tail = NULL;
  }else{
    ILNode* current = list->head;
    while(current->next != list->tail){
      current = current->next;
      
    }
    current->next = NULL;
    list->tail = current;
    free(tempo);
    

  }
  list->len--;
  return val;

    /*
    TODO: Remove the tail node of the list, and return the integer contained in it.
  */

}

void pushFrontList(IntList* list, int number)
{
  /*
    TODO: Add a node containing the number to the start of the list 
  */
  ILNode* new = (ILNode*)malloc(sizeof(ILNode));
  new->number = number;
  if (list->len == 0){
    list->head = new;
    list->tail = new;
    new->next = NULL;
  }else{
    new->next = list->head;
    list->head = new;
  }
  list->len++;
}

int popFrontList(IntList* list)
{
  assert(list->head && list->tail && list->len > 0);
  ILNode* temp = list->head;
  int val = temp->number;
  list->head = list->head->next;
  if (list->len = 0){
    list->tail == NULL;
  }
  free(temp);
  list->len--;
  return val;
  
  
  /*
    TODO: Remove the head node of the list, and return the integer contained in it. 
  */
}

void sortedInsert(IntList* sortedList, ILNode* nodeToInsert){
  /*
    TODO: You're given a linked list where the nodes are sorted (the smallest number is at the head, the largest at the tail). Iterate through the list until you find where to insert nodeToInsert, so as to keep the list sorted, and insert it. 
   */
  if (sortedList->len == 0 || nodeToInsert->number <= sortedList->head->number){
    nodeToInsert->next = sortedList->head;
    sortedList->head = nodeToInsert; 
    if (sortedList->len == 0){
      sortedList->tail = nodeToInsert;
    }

  }else{
    ILNode* current = sortedList->head;
    while(current->next != NULL && current->next->number < nodeToInsert->number){
      current = current->next;
    }
    nodeToInsert->next = current->next;
    current->next = nodeToInsert;
    if(nodeToInsert->next == NULL){
      sortedList->tail = nodeToInsert;
  }

  }
  sortedList->len++;

}

void sortList(IntList* list)
{
  IntList newList = {NULL,NULL};
  ILNode* next = NULL;
  ILNode* cur = list->head;
  while(cur){
    next = cur->next;
    sortedInsert(&newList, cur);
    cur = next;
  }
  *list = newList;
}

int lengthList(IntList* list)
{
  return list->len;
}

void printList(IntList* list)
{
   printf("(");
   ILNode* node = list->head;
   while (node) {
      printf("%d ", node->number);
      node = node->next;
   }
   printf(")\n");
}
