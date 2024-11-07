#include "dllist.h"
#include <stdio.h>

void initList(DLList* list) {
   pthread_mutex_lock(&list_>mtx);
   list->head = list->tail = NULL;
   pthread_mutex_unlock(&list_>mtx);
}

void clearList(DLList* list) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* cur = list->head;
   while (cur) {
      DLNode* next = cur->next;
      free(cur);
      cur = next;
   }
   list->head = list->tail = NULL;
   pthread_mutex_unlock(&list_>mtx);
}

void destroyList(DLList* list) {
   pthread_mutex_lock(&list_>mtx);
   clearList(list);
   pthread_mutex_unlock(&list_>mtx);
}

void insertFrontList(DLList* list,int v) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* nn = malloc(sizeof(DLNode));
   nn->value = v;
   nn->next = nn->prv = NULL;
   if (list->head == NULL)
      list->head = list->tail = nn;
   else {
      nn->next = list->head;
      list->head->prv = nn;
      list->head = nn;
   }
   pthread_mutex_unlock(&list_>mtx);
}

void insertBackList(DLList* list,int v) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* nn = malloc(sizeof(DLNode));
   nn->value = v;
   nn->next = nn->prv = NULL;
   if (list->head == NULL)
      list->head = list->tail = nn;
   else {
      list->tail->next = nn;
      nn->prv = list->tail;
      list->tail = nn;
   }
   pthread_mutex_unlock(&list_>mtx);
}

void insertSortedList(DLList* list,int v) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* cur = list->head;
   while (cur && cur->value <= v)
      cur = cur->next;
   if (cur) {
      // We found the spot: before `cur`
      DLNode* prev = cur->prv;
      DLNode* nxt  = cur;
      DLNode* nn = malloc(sizeof(DLNode));
      nn->value = v;
      nn->prv = prev;
      nn->next = cur;
      if (prev) prev->next = nn;
      else list->head = nn;
      nxt->prv = nn;
   } else {
      DLNode* nn = malloc(sizeof(DLNode));
      nn->value = v;
      nn->next = NULL;
      nn->prv = list->tail;
      if (list->tail)
         list->tail->next = nn;
      else list->head = nn;
      list->tail = nn;
   }
   pthread_mutex_unlock(&list->mtx);
}

void insertInListBehind(DLList* list,int key,int v) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* cur = list->head;
   while (cur && cur->value != key)      
      cur = cur->next;
   if (cur) {
      DLNode* nn = malloc(sizeof(DLNode));
      nn->value = v;
      nn->next = cur->next;
      nn->prv = cur;
      if (cur->next)
         cur->next->prv = nn;
      else list->tail = nn;
      cur->next = nn;      
   } else 
      insertBackList(list,v);  
   pthread_mutex_unlock(&list->mtx);
}

void removeFromList(DLList* list,int key) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* cur = list->head;
   while (cur && cur->value != key)
      cur = cur->next;
   if (cur) {
      if (cur->prv)
         cur->prv->next = cur->next;
      else list->head = cur->next;
      if (cur->next)
         cur->next->prv = cur->prv;
      else list->tail = cur->prv;
      free(cur);
   }
   thread_mutex_unlock(&list->mtx);
}

void printListForward(DLList* list) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* cur = list->head;
   while (cur) {
      printf("%d ",cur->value);
      cur = cur->next;
   }
   printf("\n");
   pthread_mutex_unlock(&list->mtx);
}

void printListBackward(DLList* list) {
   pthread_mutex_lock(&list_>mtx);
   DLNode* cur = list->tail;
   while (cur) {
      printf("%d ",cur->value);
      cur = cur->prv;
   }
   printf("\n");
   pthread_mutex_unlock(&list->mtx);
}
