#include "dllist.h"
#include <stdio.h>

void initList(DLList* list) {
   pthread_mutex_lock(&list->mtx);
   list->head = list->tail = NULL;
   pthread_mutex_unlock(&list->mtx);
}

void clearList(DLList* list) {
   pthread_mutex_lock(&list->mtx);
   DLNode* cur = list->head;
   while (cur) {
      DLNode* next = cur->next;
      free(cur);
      cur = next;
   }
   list->head = list->tail = NULL;
   pthread_mutex_unlock(&list->mtx);
}

void destroyList(DLList* list) {
   pthread_mutex_lock(&list->mtx);
   clearList(list);
   pthread_mutex_unlock(&list->mtx);
}

void insertFrontList(DLList* list,int v) {
   pthread_mutex_lock(&list->mtx);
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
   pthread_mutex_unlock(&list->mtx);
}

void insertBackList(DLList* list,int v) {
   pthread_mutex_lock(&list->mtx);
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
   pthread_mutex_unlock(&list->mtx);
}

void insertSortedList(DLList* list,int v) {
   pthread_mutex_lock(&list->mtx);
   DLNode* cur = list->head, *prv = NULL;
   while (cur && cur->value <= v)
      cur = cur->next;
   if (cur == NULL) {
      DLNode* nn = malloc(sizeof(DLNode));
      pthread_mutex_init(&nn->mtx,NULL);
      // We found the spot: before `cur`
      nn->value = v;
      nn->next = nn->prv = NULL;
      list->head = list->tail = nn;
      pthread_mutex_unlock(&list->mtx);
   } else{
      pthread_mutex_t* lastLock = &list->mtx;
      while(cur){
         pthread_mutex_lock(&cur->mtx);
         if (cur->value > v) break;
         pthread_mutex_unlock(lastLock);
         lastLock = &cur-> mtx;
         prv = cur;
         cur = cur->next;
      }
      if(cur){
         DLNode* prev = cur->prv;
         DLNode* nxt = cur;
         DLNode* nn = malloc(sizeof(DLNode));
         pthread_mutex_init(&nn->mtx, NULL); //initalize mutex
         nn->value = v;
         nn->prev = prev;
         nn->next = cur;
         if (prev) prev->next = nn;
         else list->head = nn;
                  nxt->prv = nn;                          // nxt is the same as cur. So it's locked. Safe to write.
         pthread_mutex_unlock(&cur->mtx);        // we are done. unlock current
         pthread_mutex_unlock(lastLock);         // we are done. unlock the previous (node or list).
      } else {
         // Note that CUR == NULL. Therefore only the last node (prv) is locked. (lastLock)
         DLNode* nn = malloc(sizeof(DLNode));    // safe
         pthread_mutex_init(&nn->mtx,NULL);      // safe
         nn->value = v;                          // safe since we are the only one with access to nn
         nn->next = NULL;                        // see above
         nn->prv  = prv;                         // point back to former last
         prv->next = nn;                         // make last point here
         pthread_mutex_unlock(lastLock);         // done modifying prv
         pthread_mutex_lock(&list->mtx);
         list->tail = nn;
         pthread_mutex_unlock(&list->mtx);

      }
   }
}
  
      

void insertInListBehind(DLList* list,int key,int v) {
   pthread_mutex_lock(&list->mtx); //lock and use iterations
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
   pthread_mutex_lock(&list->mtx);
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
   pthread_mutex_lock(&list->mtx);
   DLNode* cur = list->head;
   while (cur) {
      printf("%d ",cur->value);
      cur = cur->next;
   }
   printf("\n");
   pthread_mutex_unlock(&list->mtx);
}

void printListBackward(DLList* list) {
   pthread_mutex_lock(&list->mtx);
   DLNode* cur = list->tail;
   while (cur) {
      printf("%d ",cur->value);
      cur = cur->prv;
   }
   printf("\n");
   pthread_mutex_unlock(&list->mtx);
}
