# Makefile
CFLAGS=-g -Wall

all: test_map_recursif perf_map_recursif test_map_iteratif perf_map_iteratif test_map_recursif_terminal perf_map_recursif_terminal

test_map_recursif: test_map.c map.h map_recursif.c
	gcc $(CFLAGS) test_map.c map_recursif.c -o test_map_recursif

perf_map_recursif: perf_map.c map.h map_recursif.c
	gcc $(CFLAGS) perf_map.c map_recursif.c -o perf_map_recursif

test_map_iteratif: test_map.c map.h map_iteratif.c
	gcc $(CFLAGS) test_map.c map_iteratif.c -o test_map_iteratif

perf_map_iteratif: perf_map.c map.h map_iteratif.c
	gcc $(CFLAGS) perf_map.c map_iteratif.c -o perf_map_iteratif

test_map_recursif_terminal: test_map.c map.h map_recursif_terminal.c
	gcc $(CFLAGS) test_map.c map_recursif_terminal.c -o test_map_recursif_terminal

perf_map_recursif_terminal: perf_map.c map.h map_recursif_terminal.c
	gcc $(CFLAGS) perf_map.c map_recursif_terminal.c -o perf_map_recursif_terminal

clean:
	rm -f *.o *~ test_map_recursif perf_map_recursif test_map_iteratif perf_map_iteratif test_map_recursif_terminal perf_map_recursif_terminal
