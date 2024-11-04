/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   memory.h
/
/  Program Purpose(s):
/    User-defined header file for memory.c. 
/---------------------------------------------------------*/

#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

#define HEAP_SIZE 4096 /* 4kb of memory */

/* globals */
extern char heap[HEAP_SIZE];
extern char *p_free_heap;


char *alloc(unsigned int size);
void free_all();

#endif