/* map.c */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct tree_t * tree;
struct tree_t{
  tree left;
  tree right;
  void * object;
};

struct map_t{
  keyfunc f;
  tree root;
};

int max(int x, int y){
  if(x<y)
    return y;
  else
    return x;
}

/* create an empty map */
map map_create(keyfunc f){
  map m = malloc(sizeof(*m));
  m->root = malloc(sizeof(tree_t));
  m->root = NULL;
  m->f = f;
  return m;
}

/* destroy a map */
void map_destroy(map f){
/////////
}

/* return the height of a map */
int map_height(map f){
  if(f == NULL)
    return 0;
  return tree_height(f->root);
}

/* find an object in the map and return it or NULL if not found */
void * map_find(map m, int key){
  if(m == NULL)
    return NULL;
  return(node_find(m->root, key, m->f))->object;
}

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * map_insert(map m, void * object){
  if(m == NULL || m->f == NULL)
    return NULL;
  
  m->root = tree_insert(m->root, object, m->f);

  return map_find(m->f(object));
}

/* delete an object from a map and return it or NULL in not found */
void * map_delete(map m, int key){
  return NULL;
}



//------------------AFFICHAGE D'ARBRE BINAIRE--------------

tree tree_delete(tree root, int key, keyfunc f){

  if(root == NULL)
    return NULL;

  tree prev = NULL, now = root;
  char type = ' ';

  while(1){
    if(f(now->object) == key){

      if(now->left == NULL && now->right == NULL){
        if(now != root && prev){
          if(type == 'r')
            prev->right = NULL;
          if(type == 'l')
            prev->left = NULL;
        } else {
          root = NULL;
        }

      } else if(now->left != NULL && now->right != NULL){
          tree left = now->left;
          while(left->right != NULL)
            left = left->right;
          now->object = left->object;
          key = f(left->object);

          prev = now;
          now = now->left;
          type = 'l';
      } else {

        if(now == root){
          root = root->left ? root->left : root->right;
        } else {

          if(type == 'l')
            prev->left = now->left ? now->left : now->right;
          else 
            prev->right = now->left ? now->left : now->right;
        }
      }
      prev = now;
      if(key < f(now->object)){
        now = now->left;
        type = 'l';
      } else {
        now = now->right;
        type = 'r';
      }
    }
  }
    return root;
}

tree create_leaf(void *object){
  tree leaf = malloc(sizeof(*leaf));
  leaf->left = NULL;
  leaf->right = NULL;
  leaf->object = object;
  return leaf;
}

tree tree_insert(tree root, void *object, keyfunc f){

  if(root == NULL)
    return create_leaf(object);

  int currentKey = f(root->object);
  int objectKey = f(object);

 
  while(1){
    if(currentKey == objectKey)
      return;

    if(currentKey > objectKey){
      if(root->left == NULL)
        root->left = create_leaf(object);
      root = root->left;

    } else if (currentKey < objectKey){
      if(root->right == NULL)
        root->right = create_leaf(object);
      root = root->right;
    }
    currentKey = f(root->object);
  }
}

tree node_find(tree root, int key, keyfunc f){

  while(root != null && f(root->object) != key){
    if(f(root->object) > key)
      root = root->left;
    else 
      root = root->right;
  }
  return root;
}

int tree_height(tree node)
{
  if(node == NULL) return 0;   /* the height of a void tree is 0. */
  return 1 + max(tree_height(node->left),tree_height(node->right));
}

void tree_traverse_and_mark(map m,
			    tree node,   /* current node */
			    int height,  /* tree height */
			    int * array, /* 2d array of marks */
			    int h,       /* node depth */
			    int w)       /* node lateral position */
{
  // traverse...
  if(node->left != NULL) 
    tree_traverse_and_mark(m,node->left,height,array,h+1,2*w);    
  if (node->right != NULL) 
    tree_traverse_and_mark(m,node->right,height,array,h+1,w*2+1);
  
  // mark...
  int width = (2 << (height-1)) - 1; /* width = 2^height - 1*/
  int j = h;
  int delta = (2 << (height-h-1)); /* delta =  2^(height-h) */
  int offset = delta/2-1;          /* offset = 2^(height-h-1) - 1*/
  int i = w*delta+offset; 
  int key = (*m->f)(node->object);   
  assert(key > 0); /* we assume it is > 0 */
  array[j*width+i] = key;
  // printf("mark: h=%d, w=%d, delta=%d, offset=%d\n", h, w, delta, offset); 
}

void map_dump(map m) 
{
  int height = tree_height(m->root);
  int width = (2 << (height-1)) - 1; /* width = 2^height - 1*/
  // printf("tree height: %d\n", height);
  // printf("tree width: %d\n", width);
  
  int array[height][width];
  int i, j;
  
  // reset array
  for(j = 0 ; j < height ; j++)
    for(i = 0 ; i < width ; i++) 
      array[j][i] = -1;
  
  // traverse tree and mark nodes
  if(m->root != NULL) 
    tree_traverse_and_mark(m,m->root,height,(int*)array,0,0);
  
  // dump array
  for(j = 0 ; j < height ; j++) {    
    printf("|");
    for(i = 0 ; i < width ; i++) {
      if(array[j][i] < 0) printf("  ");
      else printf("%.2d",array[j][i]);
    }
    printf("|\n");
  }
  
}
