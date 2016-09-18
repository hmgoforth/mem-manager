// Authors: Ting-Yu (Jacky) Wang, Hunter Goforth
// Project: Homework 5: Memory Management

/* 
bench allows the user to execute a large number of
calls to the functions getmem and freemem from mem.h
to allocate and free blocks of random sizes and 
in random order. The program allows the following
command-line parameter:

ntrials - total number of getmem plus freemem calls to
randomly perform during the test. Default 10,000

pctget: percent of the total getmem/freemem calls that 
should be getmem. Default 50.

pctlarge: percent of the getmem calls that should request
"large" blocks with a size greater than small_limit. 
Default 10.

small_limit: largest size in bytes of a "small" block. 
Default 200.

large_limit: largest size in bytes of a "large" block. 
Default 20000.

random_seed: initial seed value for the random number generator. 
Default: the system time-of-day clock
*/

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv) {
    int ntrials = argc > 1 ? atoi(argv[1]) : 10000;
    int pctGet = argc > 2 ? atoi(argv[2]) : 50;
    int pctLarge = argc > 3 ? atoi(argv[3]) : 10;
    int small_limit = argc > 4 ? atoi(argv[4]) : 200;
    int large_limit = argc > 5 ? atoi(argv[5]) : 20000;
    int random_seed = argc > 6 ? atoi(argv[5]) : clock();

    srand(random_seed);

    void *mem_arr[ntrials];
    int arr_end = 0;

    int i;
    int request_size;
    int rand_index;
    uintptr_t total_size = 0;
    uintptr_t total_free = 0;
    uintptr_t n_free_blocks = 0;
    FILE* f = fopen("test.txt", "w");
    for (i = 1; i <= ntrials; i++) {
        if (rand() % 100 < pctGet) {
            if (rand() % 100 < pctLarge) {
                request_size = rand() % (large_limit - small_limit) +
                               small_limit;
            } else {
                request_size = rand() % small_limit + 1;
            }
            mem_arr[arr_end] = getmem(request_size);
            arr_end++;
        } else {
            if (arr_end != 0) {
                rand_index = rand() % arr_end;
                freemem(mem_arr[rand_index]);
                mem_arr[rand_index] = mem_arr[arr_end - 1];
                arr_end--;
            }
        }

        if (i % (ntrials / 10) == 0) {
            get_mem_stats(&total_size, &total_free, &n_free_blocks);
            printf("(%.0f%%) ", i / (double) ntrials * 100);
            printf("seconds run: %.2f, ", (float) clock() / CLOCKS_PER_SEC);
            printf("bytes malloc'd: %lu, ", total_size);
            printf("length of free list: %lu, ", n_free_blocks);
            printf("mean size: %.2f\n", total_free / (double) n_free_blocks);
        }
    }
    print_heap(f);
}





















