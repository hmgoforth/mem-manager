// Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
// Project: Homework 5: Memory Management

#include "mem.h"
#include "mem_impl.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

// total_size: stores the total amount of storage in bytes used by the memory
// management program so far in satisfying the memory allocation requests.
// total_free: stores the total amount of storage in bytes that is currently
// stored on the free list.
// n_free_blocks: stores the total number of individual blocks of memory
// currently stored on the free list.
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks) {
    *total_size = total_size_g;
    *total_free = total_free_g;
    *n_free_blocks = n_free_blocks_g;
}
