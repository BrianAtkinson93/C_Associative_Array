# Associative Arrays (Hashmap, Map, Dictionary) in C

---

This repo was created to learn about associative arrays and implement a working "dictionary" in C. 

Some of the key learnings from this exercise was the use of double pointers, dynamic resizing to ensure efficent processing, and double hashing functions.


#### POINTERS

A pointer in C is a variable that stores the memory address of another variable.

Ex:
    If you have `int x = 10;` a pointer to `x` would store the address of `x` in memory,
    allowing you to access and manipulate `x` through the pointer.

#### DOUBLE POINTERS
A Pointer to a Pointer adds another level of indirection. This means the first pointer
points to another pointer that then points to the actual data. This concept is often
used for dynamic multidimensional arrays, among other things.

__APPLICATION:__
Using an array of pointers rather then an array of structures directory has several advantages, especially in a hash table context:

* __Memory efficiency:__ Pointers are usually the same size regardless of the structure size. If `ht_item` structures are large, storing pointers to them can be more memory-efficient than storing the structures directly.

* __Flexibility:__ Its easier to resize an array of pointers (example: when resizing the hash table) compared to resizing an array of structres. You can allocate or free individual elements without reallocating the entire array.

* __Indirection Benefits:__ With pointers, you can have elements scattered in memory, which might be beneficial for certain memory management strategies. It also allows for elements to be shared or moved easily without copying data.

