#ifndef MAP_H
#define MAP_H
/* Header file for the map abstract data type (map.h) */

struct map_t;

typedef struct map_t *map;

/* map an integer key to an object pointer */
typedef int (*keyfunc)(void *);

/* create an empty map */
map map_create(keyfunc f);

/* create an empty map */
void map_destroy(map f);

/* create an empty map */
int map_height(map f);

/* find an object in the map and return it or NULL if not found */
void * map_find(map m, int key);

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * map_insert(map m, void * object);

/* delete an object from a map and return it or NULL in not found */
void * map_delete(map m, int key);

/* dump the underlying binary research tree */
void map_dump(map m);

#endif
