// Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
// Project: Homework 5: Memory Management

#include "mem.h"
#include "mem_impl.h"
#include <stdio.h>
#include <assert.h>

// freemem frees the block of memory at location . If p is NULL, freemem will
// not take effect. If p has values other than the one returned by getmem
// or if it has previously been released by freemem, then freemem, in this
// case is undefined.

void freemem(void* p) {
    check_heap();

    if (p == NULL) {  // nothing passed to the function
        return;
    }

    FreeListNode* pN = (FreeListNode*) ((uintptr_t) p - 16);

    FreeListNode* temp = list;
    total_free_g += pN->size + 16;
    if (temp == NULL) {  // list is empty
        list = pN;
        n_free_blocks_g++;
    } else {
        if (temp > pN) {  // p should be inserted at the front of the list
            pN->next = temp;
            temp = pN;
            list = pN;
            n_free_blocks_g++;
        } else {
            while (temp->next != NULL &&
                  (uintptr_t) temp->next < (uintptr_t) pN) {
                temp = temp->next;
            }

            // need to append top of p
            if ((uintptr_t) temp + temp->size + 16 == (uintptr_t) pN) {
                temp->size += 16 + pN->size;

            } else {  // insert p into free list
                pN->next = temp->next;
                temp->next = pN;
                temp = pN;

                n_free_blocks_g++;
            }
        }

        // append to bottom of p after it is added to free list
        if (temp->next != NULL &&
           ((uintptr_t) temp + temp->size + 16 == (uintptr_t) temp->next)) {
            temp->size += 16 + temp->next->size;
            temp->next = temp->next->next;
            n_free_blocks_g--;
        }
    }

    check_heap();
}
