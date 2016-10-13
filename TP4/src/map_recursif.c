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

int tree_height(tree);
tree tree_delete_node(tree root, int key, keyfunc f);
tree tree_insert_object(tree root, void *object, keyfunc f);
void tree_destroy(tree root);
tree tree_find(tree, int, keyfunc);


int max(int x, int y){
  if(x<y)
    return y;
  else
    return x;
}

/* create an empty map */
map map_create(keyfunc f){
  map m = malloc(sizeof(*m));
  m->f = f;
  m->root = NULL;
  return m;
}

/* destroy a map */
void map_destroy(map f){
  if(f == NULL)
    return;
  else if(f->root == NULL){
    free(f);
    return;
  }

  tree_destroy(f->root);
  free(f->root);
  free(f);
}

/* return the height of a map */
int map_height(map f){
  if(f == NULL || f->root == NULL)
    return -1;
  return tree_height(f->root);
}

/* find an object in the map and return it or NULL if not found */
void * map_find(map m, int key){
  if(m == NULL || m->root == NULL)
    return NULL;

  return (tree_find(m->root, key, m->f))->object;
}



/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * map_insert(map m, void * object){

  m->root = tree_insert_object(m->root, object, m->f);

  return map_find(m, m->f(object));
}

/* delete an object from a map and return it or NULL in not found */
void * map_delete(map m, int key){
  
  if(m == NULL || m->root == NULL)
    return NULL;

  void * toReturn;
  tree toDelete = m->root;
  while(toDelete != NULL && m->f(toDelete->object) != key){
    if(m->f(toDelete->object) > key)
      toDelete = toDelete->left;
    else if(m->f(toDelete->object) < key)
      toDelete = toDelete->right;
  }
  if(toDelete == NULL)
    return NULL;
  toReturn = toDelete->object;
  m->root = tree_delete_node(m->root, key, m->f);
  return toReturn;

}
   






//------------------AFFICHAGE D'ARBRE BINAIRE--------------


int tree_height(tree node) {
  if(node == NULL) return 0;   /* the height of a void tree is 0. */
  return 1 + max(tree_height(node->left),tree_height(node->right));
}

tree tree_delete_node(tree root, int key, keyfunc f){

  if(f(root->object) == key){
    if(root->left == NULL && root->right == NULL)
      return NULL;
    else if (root->left == NULL)
      return root->right;
    else if (root->right == NULL)
      return root->left;
    else {
      tree left = root->left;
      while(left->right != NULL)
        left = left->right;
      void *swap = root->object;
      root->object = left->object;
      left->object = swap;
      root->left = tree_delete_node(root->left, key, f);
      return root;
    } 
  }

  if(f(root->object) > key)
    root->left = tree_delete_node(root->left, key, f);
  else if(f(root->object) < key)
    root->right = tree_delete_node(root->right, key, f);
  return root;
  
}

tree create_node(void* object){
  tree t = malloc(sizeof(*t));
  t->left = NULL;
  t->right = NULL;
  t->object = object;
  return t;
}

tree tree_insert_object(tree root, void *object, keyfunc f){

  if(root == NULL)
    return create_node(object);
  else if(f(root->object) > f(object))
    root->left = tree_insert_object(root->left, object, f);
  else 
    root->right = tree_insert_object(root->right, object, f);
  return root;
}

tree tree_find(tree root, int key, keyfunc f){
  if(root == NULL)
    return NULL;

  if(f(root->object) == key)
    return root;
  else if(f(root->object) > key)
    return tree_find(root->left, key, f);
  else 
    return tree_find(root->right, key, f);
}

void tree_destroy(tree root){
  assert(root != NULL);
  if(root->left == NULL && root->right == NULL)
    return;
  if(root->left != NULL){
    tree_destroy(root->left);
    free(root->left);
  }
  if(root->right != NULL){
    tree_destroy(root->right);
    free(root->right);
  } 
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
