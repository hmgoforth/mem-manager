// Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
// Project: Homework 5: Memory Management

#include "mem.h"
#include "mem_impl.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <assert.h>

#define min_size 16  // minimum free memory size for any block on the free list

// Checks for problems with the free list data structure and verifies that,
// blocks are ordered with increasing memory addresses,
// block sizes are positive and not smaller than the chosen minimum block size,
// blocks do not overlap and not touching.
// Function returns silently if no errors are detected.
void check_heap() {
    // check for increasing addresses
    FreeListNode *temp = list;
    FreeListNode *prev = list;

    while (temp != NULL) {
        // block sizes are positive and not smaller than the
        // chosen minimum block size
        // printf("temp->size: %lu\n", temp->size);
        assert(temp->size >= min_size);

        // blocks are ordered with increasing memory addresses
        if (temp != list) {  // if not the first block
            assert(temp > prev);
            // blocks do not overlap and not touching (start of block)
            assert((uintptr_t)prev + 16 + prev->size < (uintptr_t)temp);
        }

        if (temp->next != NULL) {
            // blocks do not overlap and not touching (end of block)
            assert((uintptr_t)temp + 16 + temp->size < (uintptr_t)temp->next);
        }

        prev = temp;
        temp = temp->next;
    }
}
