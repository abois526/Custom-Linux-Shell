/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   memory.c
/
/  Program Purpose(s):
/    Memory allocation functions for managing a 
/    fixed-size heap.
/---------------------------------------------------------*/

#include "memory.h"

char heap[HEAP_SIZE];
char *p_free_heap = heap;

/*---------- FUNCTION: alloc -------------------------------
/  PURPOSE:
/    Allocates a block of memory from the heap and returns a 
/    pointer to the allocated memory.
/  
/  CALLER INPUT:
/    unsigned int size 
/      - The size of memory to allocate in bytes.
/  
/  CALLER OUTPUT:
/    Returns a pointer to the allocated memory block 
/    or NULL if the allocation fails.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that there is enough memory available in the 
/      heap for allocation.
/---------------------------------------------------------*/
char *alloc(unsigned int size) {
    /*Calculate the new pointer after allocation*/
    char *new_free_heap = p_free_heap + size;
    
    /*Check if the new pointer would exceed the allocated heap size*/
    if (new_free_heap <= (p_free_heap + HEAP_SIZE)) {
        char *p_alloced = p_free_heap;
        p_free_heap = new_free_heap;
        return p_alloced;
    } else {
        return NULL; /* error if memory runs out, but shouldn't reach this */
    }
}

/*---------- FUNCTION: free_all ----------------------------
/  PURPOSE:
/    Resets the free heap pointer to the start of the heap,
/    to free allocated memory.
/  
/  CALLER INPUT:
/    N/A-No input parameters. 
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/---------------------------------------------------------*/
void free_all() {
    p_free_heap = heap;
}