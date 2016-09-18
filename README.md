Division Of Work

We split up coding responsibilities mostly as the specification suggested. Jacky handled getmem, as well as checkheap and print_heap, and Hunter handled freemem, as well as the benchmarking program and get_mem_stats. We independently developed pseudocode and algorithms for each of the programs we were responsible for, and coded initial versions of the programs independently. Then we spent the rest of the time running our code, debugging and cleaning up together while looking at the code at the same time.


Organization And Algorithms Used In The Free List

Our free list data structure is in the form of linked-list of free memory blocks. When the user requests for memory, our program searches through the list of available memory blocks. If a block with suitable size is found, the block will be used to satisfy the user's request instead of calling malloc. If the chosen block is substantially larger than the memory requested, the block will be divided and the large enough block will be returned to the user while keeping the remaining memory on the list. Otherwise, the whole memory block will be returned to the user leaving one less memory block on the free list. When the user wants to free the memory previously used, the memory block that is being freed will be reattached to the free list. If the block is adjacent to any existing blocks on the list, they will be combined into one bigger block.


Summary Of Benchmarking

We started our analysis with ten thousand trials and with an increment of factor of ten up to one millon trials. In our test runs, in average, we found out that it roughly took tens of milliseconds to run 10 thousand trials, hundreds of milliseconds to run 100 thousand trials and 10 seconds to run a million trials.

In terms of memory usage efficiency, our program will always allocate 16 kB of memory if the memory requested is smaller than 16 kB. If the memory requested is larger than the default 16 kB, our program will allocate just enough to satisfy the request. As a result, during the test runs, the amount of memory malloc'd at each stage reduces as more memory requests are made. During the first 10% of a bench-test, a relatively large amount of memory is malloc'd from the underlying system. As the test continues, less and less bytes must be malloc'd per length of runtime. Eventually, for some cases, no malloc calls are needed since future requests can be satisfied by simply using the left over memory chunks from previous malloc calls.
