CFLAGS=-g -Wall

all: test_queue_list test_queue_list_v2 test_queue_array test_queue_list_array

test_queue_list: test_queue.c queue.h queue_list.c
	gcc $(CFLAGS) test_queue.c queue_list.c -o test_queue_list

test_queue_list_v2: test_queue.c queue.h queue_list_v2.c
	gcc $(CFLAGS) test_queue.c queue_list_v2.c -o test_queue_list_v2

test_queue_array: test_queue.c queue.h queue_array.c
	gcc $(CFLAGS) test_queue.c queue_array.c -o test_queue_array

test_queue_list_array: test_queue.c queue.h queue_list_array.c
	gcc $(CFLAGS) test_queue.c queue_list_array.c -o test_queue_list_array

clean:
	-rm -f *.o *~ 
	-rm test_queue_list test_queue_list_v2 test_queue_array test_queue_list_array