# Associative Arrays (Hashmap, Map, Dictionary) in C

---

This repo was created to learn about associative arrays and implement a working "dictionary" in C. 

Some of the key learnings from this exercise was the use of double pointers, dynamic resizing to ensure efficent processing, and double hashing functions.


#### Pointers

A pointer in C is a variable that stores the memory address of another variable.

Ex:
    If you have `int x = 10;` a pointer to `x` would store the address of `x` in memory,
    allowing you to access and manipulate `x` through the pointer.

#### Double Pointers
A Pointer to a Pointer adds another level of indirection. This means the first pointer
points to another pointer that then points to the actual data. This concept is often
used for dynamic multidimensional arrays, among other things.

__APPLICATION:__
Using an array of pointers rather then an array of structures directory has several advantages, especially in a hash table context:

* __Memory efficiency:__ Pointers are usually the same size regardless of the structure size. If `ht_item` structures are large, storing pointers to them can be more memory-efficient than storing the structures directly.

* __Flexibility:__ Its easier to resize an array of pointers (example: when resizing the hash table) compared to resizing an array of structres. You can allocate or free individual elements without reallocating the entire array.

* __Indirection Benefits:__ With pointers, you can have elements scattered in memory, which might be beneficial for certain memory management strategies. It also allows for elements to be shared or moved easily without copying data.

---

## Double Hashing

Double hashing is a technique used to resolve collisions in hash tables, particularly within the context of open addressing schemes.

#### How double hashing works:
1. Initial Hash: when an element is inserted, a hash function (`hash1`) computes an initial index based on the element's key.

2. Collision: If the calculated index is already occupied by a different element (a collision occurs), a second hash function (`hash2`) is used to calculate the step size for probing.

3. Probing: The hash table is then probed at intervals determined by the second hash function (`hash2`). Specifically, the i-th probe position is calculated as `(hash1(key) + i * hash2(key)) % table_size`, where `i` ranges from 1 onwards until an empty slot is found or the table is deemed full.
