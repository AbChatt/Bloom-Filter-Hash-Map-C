/*
 *                         Dynamic Hash Maps
 *                              ---
 *  Like Dynamic Arrays, we can also have Dynamic HashMaps. Working out the
 *  math would for the complexity for this structure would give you
 *  amortized expected O(1) for Add(), Find() and Delete(). Try to prove
 *  this if just computing expected and amortized costs on their own wasn't
 *  enough for you! :)
 *                              ---
 *
 * This is the file where all of your implementation for the HashMap goes. 
 * You will be submitting this file (along with BloomFilter.c) to MarkUs.
 *
 * TestHashMap.c provides some test cases to test your implementation. 
 * You can compile it using the Makefile and running the executable produced.
 *
 * CSCB63 Winter 2020 - Bonus Coding Assignment 
 * (c) Mustafa Quraish
 */

#include "HashMap.h"

/// @brief Create and initialize a new HashMap with the given values
///
/// @param num_buckets  The number of buckers the HashMap starts off with
/// @param func         The hash function to be used for this HashMap
///
/// @return             A pointer to the HashMap
///
/// @TODO: Implement this function
HashMap *newHashMap(int num_buckets, HashFunc func) {
  HashMap *new_map = malloc(1 * sizeof(HashMap));

  if (new_map == NULL) {
    fprintf(stderr, "Error: could not allocate memory for HashMap\n");
  }
  else
  {
    new_map->func = func;
    new_map->num_buckets = num_buckets;
    new_map->buckets = malloc(num_buckets * sizeof(BucketNode*));
    new_map->num_elems = 0;

    for (int i = 0; i < num_buckets; i++) {
      new_map->buckets[i] = NULL;
    }
  }

  return new_map;
}

/// @brief Construct a new HashMap of the given size, and re-hash all
///        the values from the old one. This needs to be done when expanding
///        or shrinking the Dynamic HashMap during insertion and deletion.
///
/// @param hm         The old HashMap
/// @param new_size   Required size of new HashMap
///
/// @return           New HashMap (old one must be freed).
///
/// @TODO: Implement this function. For the sake of consistency, the automarker
///        will expect you to re-hash all the elements in a specific order. Go
///        through the buckets sequentially from [0 - hm->num_buckets], and for
///        each one insert the nodes in the linked list sequentially. See the
///        test casesfor example behaviour.
HashMap *HashMap_Resize(HashMap *hm, int new_size) {
  HashMap *new_hash_map = malloc(1 * sizeof(HashMap));
  int index = -1;

  if (new_hash_map == NULL) {
    fprintf(stderr, "Unable to allocate memory for new hash map\n");
    return hm;
  }
  else
  {
    new_hash_map->func = hm->func;
    new_hash_map->num_buckets = new_size;
    new_hash_map->buckets = malloc(new_size * sizeof(BucketNode *));
    new_hash_map->num_elems = hm->num_elems;

    for (int i = 0; i < new_hash_map->num_buckets; i++) {
      new_hash_map->buckets[i] = NULL;
    }

    for (int j = 0; j < hm->num_buckets; j++) {
      index = hm->func((hm->buckets[j])->key) % new_hash_map->num_buckets;
      BucketNode *new_bucket = malloc(1 * sizeof(BucketNode));
      strcpy(new_bucket->key, (hm->buckets[j])->key);
      strcpy(new_bucket->value, (hm->buckets[j])->value);
      new_bucket->next = new_hash_map->buckets[index];
      new_hash_map->buckets[index] = new_bucket;
    }

    HashMap_Free(hm);

    return new_hash_map;    
  }
}

/// @brief Add a key-value pair to the HashMap. Dynamically resize
///        the hashmap when at capacity.
///
/// @param hm     HashMap
/// @param key    Key to be inserted
/// @param value  Corresponding Value
///
/// @return     Pointer to resulting HashMap (useful when you expand)
///
/// @TODO: Implement this function. Here are some notes in implementation:
///        (1) If the key exists, replace the value.
///
///         (2) If the key doesn't exist, add the new BucketNode at the
///            *head* of the corresponding linked list
///
///        (3) To get the array into the buckets[] array, use the hash
///            function inside `hm` and then take that value mod the
///            number of buckets:
///                      idx = hash(key) % num_buckets
///
///        (4) AFTER you have inserted the new element, if the number
///            of elements in the HashMap is >= the number of buckets,
///            double the size of the HashMap and re-hash all the elements.
HashMap *HashMap_Add(HashMap *hm, const char *key, const char *value) {
  int index = -1;
  int val_found = 0;
  index = hm->func(key) % hm->num_buckets;

  if (strcmp(hm->buckets[index]->key, key) == 0) {  // case 1
    strcpy(hm->buckets[index]->value, value);
  }
  else if (hm->buckets[index] == NULL && hm->buckets[index]->next == NULL) {  // case 2
    BucketNode *new_bucket = malloc(1 * sizeof(BucketNode));
    strcpy(new_bucket->key, key);
    strcpy(new_bucket->value, value);

    hm->num_elems++;
    new_bucket->next = NULL;
    hm->buckets[index] = new_bucket;
  }
  else  // key value pair could be in linked list somewhere (case 1 extended)
  {
    BucketNode *p = NULL;
    p = hm->buckets[index]->next;

    while (p != NULL) {
      if (strcmp(p->key, key) == 0) {
        strcpy(p->value, value);
        val_found = 1;
        break;
      }

      p = p->next;
    }

    if (val_found == 0) { // case 2 if traversal finds nothing
      BucketNode *new_bucket = malloc(1 * sizeof(BucketNode));
      strcpy(new_bucket->key, key);
      strcpy(new_bucket->value, value);

      hm->num_elems++;
      new_bucket->next = NULL;
      hm->buckets[index] = new_bucket; 
    }
  }
  
  if (hm->num_elems >= hm->num_buckets) {
    hm = HashMap_Resize(hm, hm->num_buckets * 2);
  }

  return hm;
  
}

/// @brief Find the value of the given key in the HashMap
///        Return NULL if key does not exist.
///
/// @param hm   HashMap
/// @param key  Key to be queried in the hashmap
///
/// @return     The corresponding value to the key, or NULL.
///
/// @TODO: Implement this function
char *HashMap_Find(HashMap *hm, const char *key) {
  //int index = -1;
  //index = hm->func(key) % hm->num_buckets;


  return NULL;
}

/// @brief Delete a key-value pair from the HashMap. Dynamically resize
///        the HashMap if necessary.
///
/// @param hm   HashMap
/// @param key  Key for which the pair needs to be deleted.
///
/// @return     Pointer to resulting HashMap (useful when you shrink)
///
/// @TODO: Implement this function. Here are some notes in implementation:
///        (1) If the key doesn't exist, don't do anything.
///
///         (2) Don't reorder the rest of the list when removing the node
///
///         (3) AFTER deleting the element, if num_elems < num_buckets/4, then
///             shrink the HashMap by half. (Similar to Dynamic Arrays). You'll
///             need to re-hash all the elements.
HashMap *HashMap_Delete(HashMap *hm, const char *key) {
  return hm;
}

/// @brief Frees all the memory used by the HashMap
///
/// @param hm   HashMap
///
/// @TODO: Implement this function. You will need to use valgrind to properly 
///        check the functionality.
void HashMap_Free(HashMap *hm) {
  BucketNode *p = NULL;
  
  for (int i = 0; i < hm->num_buckets; i++) {
    p = hm->buckets[i];
    while (p != NULL) {
      hm->buckets[i] = p->next;
      free(p);
      p = hm->buckets[i];
    }
  }
  free(hm->buckets);
  free(hm);
  return;
}
