/* Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
 * Date: 2/15/2016
 * Program: mem.h
 *
 * This header file stores the function prototypes for the functions
 * that will be used for the memory management program.
 */

#ifndef MEM_H
#define MEM_H
#include <stdint.h>
#include <stdio.h>

// function prototypes

// Returns a pointer to a new block of storage with at least size bytes
// of memory. size must be greater than 0. NULL is returned if size is
// not positive or if getmem cannot satisfy the request.
void* getmem(uintptr_t size);

// Returns the block of memory at location p. If p is NULL, freemem will
// not take effect. If p has values other than the one returned by getmem
// or if it has previously been released by freemem, then freemem, in this
// case is undefined.
void freemem(void* p);

// total_size: stores the total amount of storage in bytes used by the memory
// management program so far in satisfying the memory allocation requests.
// total_free: stores the total amount of storage in bytes that is currently
// stored on the free list.
// n_free_blocks: stores the total number of individual blocks of memory
// currently stored on the free list.
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks);

// Prints a formatted listing to file f showing the blocks on the free list.
// Shows the address and length of each free blocks on the free list
void print_heap(FILE* f);

#endif
