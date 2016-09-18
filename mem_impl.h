/* Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
 * Date: 2/15/2016
 * Program: mem_impl.h
 *
 * This header file stores primary struct for the memory
 * management program.
 */
 
#ifndef MEM_IMPL_H
#define MEM_IMPL_H
#include <stdint.h>

// Creating the struct for a memory block of the free list
// Each memory block contains this struct as header
typedef struct node {
    uintptr_t size;  // stores the size of the memory block
    struct node *next;  // stores the pointer to the next memory block
} FreeListNode;

// Checks for problems with the free list data structure and verifies that,
// blocks are ordered with increasing memory addresses,
// block sizes are positive and not smaller than the chosen minimum block size,
// blocks do not overlap and not touching.
// Function returns silently if no errors are detected.
void check_heap();

FreeListNode* list;
uintptr_t total_size_g;
uintptr_t total_free_g;
uintptr_t n_free_blocks_g;

#endif
