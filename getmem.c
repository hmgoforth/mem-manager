// Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
// Project: Homework 5: Memory Management

#include "mem.h"
#include "mem_impl.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define chunk 16000  // minimum memory in byte allocated when using malloc
#define min_size 32  // minimum free memory size for any block on the free list

// getmem returns a pointer to a new block of storage with at least size bytes
// of memory. size must be greater than 0. NULL is returned if size is
// not positive or if getmem cannot satisfy the request.
void* getmem(uintptr_t size) {
    check_heap();
    if (size <= 0) {
        return NULL;

    } else {  // valid input size
        // computes the nearest multiple of 16 + header size
        uintptr_t round = size - size % 16 + 16 + 16 * (size % 16 > 0);

        if (list == NULL) {  // if free list is empty
            if (size <= chunk) {
                list = malloc(chunk + 16);

                if (list == NULL) {  // check if malloc is successful
                    return NULL;
                }

                total_size_g += (chunk + 16);
                total_free_g += (chunk + 16);
                list->size = chunk;
                list->next = NULL;
            } else {
                list = malloc(round);
                // printf("list: %p\n", list);
                if (list == NULL) {
                    return NULL;
                }

                total_size_g += round;
                total_free_g += round;
                list->size = round - 16;
                list->next = NULL;
            }

            n_free_blocks_g += 1;
        }

        // make a temp pointer for list
        FreeListNode *temp = list;

        int first = 1;

        // edge case: if first block is not big enough
        if (temp->size < round - 16) {
            first = 0;

            // scan through the free list for a suitable block
            while (temp->next != NULL) {
                if (temp->next->size < round) {
                    temp = temp->next;
                } else {  // found the block, not first block
                    break;
                }
            }

            // malloc the case when no block is found
            if (temp->next == NULL) {
                if (size <= chunk) {
                    temp->next = malloc(chunk + 16);

                    if (temp->next == NULL) {
                        return NULL;
                    }

                    total_size_g += (chunk + 16);
                    total_free_g += (chunk + 16);
                    temp->next->size = chunk;
                    temp->next->next = NULL;
                } else {
                    temp->next = malloc(round);

                    if (temp->next == NULL) {
                        return NULL;
                    }

                    total_size_g += round;
                    total_free_g += round;
                    temp->next->size = round - 16;
                    temp->next->next = NULL;
                }

                n_free_blocks_g += 1;
            }
        }

        // helper pointer to return result
        FreeListNode *result;

        // case 1: first block: block with slightly larger size (no dividing)
        if (first == 1 && temp->size - (round - 16) < min_size) {
            // temp = list->next;
            result = list;
            total_free_g -= temp->size + 16;
            n_free_blocks_g -= 1;
            list = list->next;

        // case 2: not first block: block with slightly larger size
        } else if (first == 0 && temp->next->size - (round - 16) < min_size) {
            result = temp->next;
            total_free_g -= (temp->next->size + 16);
            temp->next = temp->next->next;
            result->next = NULL;
            n_free_blocks_g -= 1;

        // case 3: dividing
        } else {
            if (first != 1) {  // edge case: not first block
                temp = temp->next;
            }

            result = (FreeListNode*)((uintptr_t)temp + 16 + temp->size - round);
            result->size = round - 16;
            result->next = NULL;
            temp->size -= round;
            total_free_g -= round;
        }

        // total_free_g -= size;
        result = (void*)((uintptr_t)result + 16);
        check_heap();
        return result;
    }
}
