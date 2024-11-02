#include "hashMap.h"
#include "dllist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Computes the hash value corresponding the key */
unsigned long long hash(char* key) {
  const int p = 31;
  const int m = 1e9 + 9;
  unsigned long long hash_value = 0;
  long long p_pow = 1;
  for (int i = 0; i < strlen(key); i++) {
    char c = key[i];
    hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
    p_pow = (p_pow * p) % m;
  }
  return hash_value;
}

void initHashMap(HashMap* hm, unsigned int nb) {
  /* Set the numBuckets and numItems fields of hm. Initially the hash map has 0 items.
   * Allocate memory for nb buckets, allocate memory for a DLList for each bucket, initialize the list, and initialize the bucket's lock.
   * Initialize the tableLock.
   */
  hm->numBuckets = nb;
  hm->numItems = 0;
  hm->buckets = malloc(nb * sizeof(Bucket));
  if (!hm->buckets) {
    perror("Failed to allocate buckets");
    exit(EXIT_FAILURE);
  }

  for (unsigned int i = 0; i < nb; ++i) {
    // Allocate and initialize the DLList
    hm->buckets[i].list = malloc(sizeof(DLList));
    if (!hm->buckets[i].list) {
      perror("Failed to allocate DLList");
      exit(EXIT_FAILURE);
    }
    initList(hm->buckets[i].list);

    // Initialize the bucket's mutex lock
    pthread_mutex_init(&(hm->buckets[i].lock), NULL);
  }

  // Initialize the tableLock
  pthread_mutex_init(&(hm->tableLock), NULL);
}

void destroyHashMap(HashMap* hm) {
  /* Free up each bucket and the hash map. Destroy all the mutexes.
   * Set the numBuckets and numItems fields to zero.
   */
  for (unsigned int i = 0; i < hm->numBuckets; ++i) {
    // Destroy the bucket's mutex lock
    pthread_mutex_destroy(&(hm->buckets[i].lock));
    // Destroy the DLList
    destroyList(hm->buckets[i].list);
    // Free the DLList
    free(hm->buckets[i].list);
  }

  // Destroy the tableLock
  pthread_mutex_destroy(&(hm->tableLock));

  // Free the buckets array
  free(hm->buckets);
  hm->buckets = NULL;

  // Set numBuckets and numItems to zero
  hm->numBuckets = 0;
  hm->numItems = 0;
}

void insertHashMap(HashMap* hm, char* key, char* value) {
  unsigned int h = hash(key) % hm->numBuckets;
  /* Go to bucket h, and insert the (key, value) pair, unless the key is already in the hash map. Note that only one thread may access bucket h at any point in time.
   * If you inserted the pair, increment the hash map's numItems field (under mutex protection, of course!)
   */
  // Lock the bucket's mutex
  pthread_mutex_lock(&(hm->buckets[h].lock));

  // Try to insert the (key, value) pair into the DLList
  int inserted = insertSortedList(hm->buckets[h].list, key, value);

  // Unlock the bucket's mutex
  pthread_mutex_unlock(&(hm->buckets[h].lock));

  // If inserted, increment numItems under protection of tableLock
  if (inserted) {
    pthread_mutex_lock(&(hm->tableLock));
    hm->numItems++;
    pthread_mutex_unlock(&(hm->tableLock));
  }
}

char* retrieveValue(HashMap* hm, char* key) {
  unsigned int h = hash(key) % hm->numBuckets;
  /* Find the key in bucket h, under mutex protection. Since the bucket's key-value pairs are stored in a DLList, look at the DLList.h file for an appropriate function to get the value corresponding to the key.
   */
  // Lock the bucket's mutex
  pthread_mutex_lock(&(hm->buckets[h].lock));

  // Use getValue to retrieve the value
  char* value = getValue(hm->buckets[h].list, key);

  // Unlock the bucket's mutex
  pthread_mutex_unlock(&(hm->buckets[h].lock));

  return value;
}

void deleteEntry(HashMap* hm, char* key) {
  unsigned int h = hash(key) % hm->numBuckets;
  /* Delete the key from bucket h, under mutex protection. If the key isn't in the bucket, don't do anything.
   * If the key was successfully removed from the bucket, decrement the hashmap's numItems field.
   */
  // Lock the bucket's mutex
  pthread_mutex_lock(&(hm->buckets[h].lock));

  // Try to remove the key from the DLList
  int removed = removeFromList(hm->buckets[h].list, key);

  // Unlock the bucket's mutex
  pthread_mutex_unlock(&(hm->buckets[h].lock));

  // If key was removed, decrement numItems under mutex protection
  if (removed) {
    pthread_mutex_lock(&(hm->tableLock));
    hm->numItems--;
    pthread_mutex_unlock(&(hm->tableLock));
  }
}
