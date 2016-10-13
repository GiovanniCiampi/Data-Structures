#ifndef HEAP_H
#define HEAP_H
/* Header file for the map abstract data type (map.h) */

struct heap_t;

typedef struct heap_t *heap;

/* map an integer key to an object pointer */
typedef int (*keyfunc)(void *);

/* create an empty map */
heap heap_create(keyfunc f);

/* create an empty map */
void heap_destroy(heap h);

/**/
void heap_enqueue(heap h, void* object);

/* find an object in the map and return it or NULL if not found */
void* heap_dequeue(heap h);

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * heap_get_max(heap h);

/* dump the underlying binary research tree */
void heap_dump(heap h);

#endif
