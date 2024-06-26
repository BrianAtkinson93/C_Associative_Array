#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../include/hash_table.h"

static ht_item *ht_new_item(const char *k, const char *v)
{
    ht_item *i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);

    return i;
}

struct ht_hash_table *ht_new_size(const int base_size)
{
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item *));
    return ht;
}

ht_hash_table *ht_new()
{
    return ht_new_size(HT_INITIAL_BASE_SIZE);
}

static void ht_del_item(ht_item *i)
{
    if (i == &HT_DELETED_ITEM)
        return;     // Check if {NULL, NULL} so we don't try to free unallocated pointer
    free(i->key);   // free key
    free(i->value); // free value
    free(i);        // free structure
}

void ht_del_hash_table(ht_hash_table *ht)
{
    if (DEBUG == 1)
    {
        printf("ht->size = %d\n", ht->size);
    }
    for (int i = 0; i < ht->size; i++) // For each item in table, free item
    {
        ht_item *item = ht->items[i];
        if (item != NULL)
        {
            ht_del_item(item);
        }
    }
    free(ht->items); // free pointer array
    free(ht);        // free structure
}

static int ht_hash(const char *s, const int a, const int m)
{
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++)
    {
        hash += (long)pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

static int ht_get_hash(const char *s, const int num_buckets, const int attempt)
{
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

ht_item HT_DELETED_ITEM = {NULL, NULL};

void ht_insert(ht_hash_table *ht, const char *key, const char *value)
{
    const int load = ht->count * 100 / ht->size;
    if (load > 70)
    {
        ht_resize_up(ht);
    }
    ht_item *item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item *cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL)
    {
        if (cur_item != &HT_DELETED_ITEM)
        {
            if (strcmp(cur_item->key, key) == 0)
            {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

char *ht_search(ht_hash_table *ht, const char *key)
{
    const int load = ht->count * 100 / ht->size;
    if (load < 10)
    {
        ht_resize_down(ht);
    }
    int index = ht_get_hash(key, ht->size, 0);
    ht_item *item = ht->items[index];
    int i = 1;
    while (item != NULL)
    {
        if (item != &HT_DELETED_ITEM)
        {

            if (strcmp(item->key, key) == 0)
            {
                return item->value;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

void ht_delete(ht_hash_table *ht, const char *key)
{
    int index = ht_get_hash(key, ht->size, 0);
    ht_item *item = ht->items[index];
    int i = 1;
    while (item != NULL)
    {
        if (item != &HT_DELETED_ITEM)
        {
            if (strcmp(item->key, key) == 0)
            {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

/// @brief The subsequent functions called from ht_resize_up & ht_resize_down functions. Creates new hash_table according to the
///         size provided, and then re-inserts all the items into the new hash_table.
/// @param ht Pointer to hash_table instance to be resized.
/// @param base_size The new size to resize the hash_table to.
static void ht_resize(ht_hash_table *ht, const int base_size)
{
    // This check prevents resizing the hash_table to a smaller size then the default // smallest allowable size.
    if (base_size < HT_INITIAL_BASE_SIZE)
    {
        return;
    }

    // Creates a new hash_table, given the provided size, and inserts the existing items into the new table.
    ht_hash_table *new_ht = ht_new_size(base_size);
    for (int i = 0; i < ht->size; i++)
    {
        ht_item *item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM)
        {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    // Swaps the values from the old_talbe to the new_table, effectively resizing the table.
    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // Swaps the pointers of the new_table and old_table, completing the re_suze_* of the table. 
    // By swapping pointers, the original table can be considered done, and the new_table, which holds the old pointers
    // is finalized and prepared for delete.
    const int temp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = temp_size;

    ht_item **temp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = temp_items;

    // Deletes the new_table and the pointers assigned to it which are the old_tables values.
    ht_del_hash_table(new_ht);
}

/// @brief Increases the size of the hash_table by doubling. Intended on being called when the load factor
///         increases above a threshold, in this case, it has been set to 70% - which was set in `ht_insert()`.
/// @param ht Pointer to the hash_table instance, which will be reduced in size.
void ht_resize_up(ht_hash_table *ht)
{
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

/// @brief Reduces the size of the hash_table by half. Intended on being called when the load factor
///         drops below a threshold, in this case, it has been set to 20% - which was set in `ht_search()`.
///         Reducing the size can improve space efficiency.
/// @param ht Pointer to the hash_table instance, which will be reduced in size.
void ht_resize_down(ht_hash_table *ht)
{
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
