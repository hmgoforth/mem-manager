// Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
// Project: Homework 5: Memory Management

#include "mem.h"
#include "mem_impl.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

// Prints a formatted listing to file f showing the blocks on the free list.
// Shows the address and length of each free blocks on the free list
void print_heap(FILE* f) {
    FreeListNode *temp = list;
    int i = 1;
    while (temp != NULL) {
        fprintf(f, "%p %lu\n", temp, temp->size + 16);
        i++;
        temp = temp->next;
    }
}
