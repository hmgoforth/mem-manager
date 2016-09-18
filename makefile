# Authors: Ting-Yu Wang (Jacky), Hunter Goforth
# Date: 2/16/2016
# Program: makefile

# This makefile allows compilation of the programs
# This makefile will only compile necessary part(s) of the programs
# after changes are made

bench : bench.o freemem.o check_heap.o get_mem_stats.o getmem.o print_heap.o
	gcc -Wall -std=c11 -o bench bench.o freemem.o check_heap.o get_mem_stats.o getmem.o print_heap.o
	
freemem.o : freemem.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c freemem.c mem.h mem_impl.h
    
check_heap.o : check_heap.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c check_heap.c mem.h mem_impl.h
    
get_mem_stats.o : get_mem_stats.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c get_mem_stats.c mem.h mem_impl.h
    
getmem.o : getmem.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c getmem.c mem.h mem_impl.h
    
print_heap.o : print_heap.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c print_heap.c mem.h mem_impl.h

bench.o : bench.c mem.h
	gcc -Wall -std=c11 -g -c bench.c mem.h

test : bench
	./bench

dist :
	tar -cvf hw5.tar mem.h mem_impl.h getmem.c freemem.c get_mem_stats.c check_heap.c print_heap.c bench.c makefile git.log README

clean :
	rm -f bench *.o *.gch
