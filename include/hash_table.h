#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

// Initial base size for hash_table set to 25
#define HT_INITIAL_BASE_SIZE 25
#define HT_PRIME_1 151
#define HT_PRIME_2 163
#define DEBUG 0

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