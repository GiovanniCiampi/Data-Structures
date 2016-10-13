CFLAGS=-g -Wall -std=c99

# Makefile

all: test_sequence_array test_sequence_list test_sequence_gap

test_sequence_gap: test_sequence.c sequence.h sequence_gap.c
	gcc $(CFLAGS) test_sequence.c sequence_gap.c -o test_sequence_gap

test_sequence_array: test_sequence.c sequence.h sequence_array.c
	gcc $(CFLAGS) test_sequence.c sequence_array.c -o test_sequence_array


test_sequence_list: test_sequence.c sequence.h sequence_list.c
	gcc $(CFLAGS) test_sequence.c sequence_list.c -o test_sequence_list

clean:
	rm -f *.o *~ 
	rm test_sequence_*