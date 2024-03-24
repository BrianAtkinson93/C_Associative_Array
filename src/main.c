#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

/* Test the associative array by populating the array 
then clearing the array*/
int main()
{
    ht_hash_table *ht = ht_new();
    ht_insert(ht, "key1", "value1");
    char *value_one = ht_search(ht, "key1");

    if (value_one != NULL && strcmp(value_one, "value1") == 0)
    {
        printf("Test insert and search passed\n");
    }
    else
    {
        printf("Test insert and search failed\n");
    }

    ht_delete(ht, "key1");
    char *value_two = ht_search(ht, "key1");
    if (value_two == NULL)
    {
        printf("Test delete passed\n");
    }
    else
    {
        printf("Test delete failed\n");
    }

    ht_del_hash_table(ht);
    return 0;
}
