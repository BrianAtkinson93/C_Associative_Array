#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

#define HT_INITIAL_BASE_SIZE 25
#define HT_PRIME_1 151
#define HT_PRIME_2 163

// Hash table item
typedef struct ht_item
{
    char *key;
    char *value;

} ht_item;

extern ht_item HT_DELETED_ITEM;

// Hash table itself
typedef struct ht_hash_table
{
    int size;
    int count;
    ht_item **items; // Array of pointers
    int base_size;
} ht_hash_table;

/*
POINTERS

A pointer in C is a variable that stores the memory address of another variable.

Ex:
    If you have `int x = 10;` a pointer to `x` would store the address of `x` in memory,
    allowing you to access and manipulate `x` through the pointer.

A Pointer to a Pointer adds another level of indirection. This means the first pointer
points to another pointer that then points to the actual data. This concept is often
used for dynamic multidimensional arrays, among other things.

APPLICATION:
    Using an array of pointers rather then an array of structures directory has several
    advantages, especially in a hash table context:

        * Memory efficiency: Pointers are usually the same size regardless of the structure
        size. If `ht_item` structures are large, storing pointers to them can be more memory-efficient
        than storing the structures directly.

        * Flexibility: Its easier to resize an array of pointers ( for example: when resizing
        the hash table ) compared to resizing an array of structres. You can allocate or free
        individual elements without reallocating the entire array.

        *Indirection Benefits: With pointers, you can have elements scattered in memory, which
        might be beneficial for certain memory management strategies. It also allows for elements
        to be shared or moved easily without copying data.

*/

// Function declarations
ht_hash_table *ht_new(void);
int next_prime(int);

void ht_insert(ht_hash_table *ht, const char *key, const char *value);
char *ht_search(ht_hash_table *ht, const char *key);
void ht_delete(ht_hash_table *ht, const char *key);

void ht_resize_up(ht_hash_table *ht);
void ht_resize_down(ht_hash_table *ht);

void ht_del_hash_table(ht_hash_table *ht);

#endif