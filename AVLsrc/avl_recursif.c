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
int tree_height(tree root);
tree left_rotation(tree root);
tree right_rotation(tree root);
tree tree_delete(tree root, int key, keyfunc f);
tree tree_insert(tree root, void *object, keyfunc f);
tree create_new_node(void *object);
void *tree_find(tree root, int key, keyfunc f);

int max(int x, int y){
  if(x<y)
    return y;
  else
    return x;
}

/* create an empty map */
map map_create(keyfunc f){
  map m = malloc(sizeof(*m));
  m->root = NULL;
  m->f = f;
  return m;
}

/* destroy a map */
void map_destroy(map f){
  return;
}

/* return the height of a map */
int map_height(map f){
   /* the height of a void tree is 0. */
   return tree_height(f->root);
}

/* find an object in the map and return it or NULL if not found */
void * map_find(map m, int key){
  if(m == NULL)
    return NULL;
  return tree_find(m->root, key, m->f);
}

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * map_insert(map m, void * object){
  m->root = tree_insert(m->root, object, m->f);
  return map_find(m, m->f(object));
}

/* delete an object from a map and return it or NULL in not found */
void * map_delete(map m, int key){
  void *object = map_find(m, key);
  if(object == NULL)
    return NULL;
  m->root = tree_delete(m->root, key, m->f);
  return object;
}



//------------------AFFICHAGE D'ARBRE BINAIRE--------------

tree tree_delete(tree root, int key, keyfunc f){
  if(root == NULL)
    return NULL;
  if(f(root->object) == key){
    if(root->left == NULL && root->right == NULL)
      return NULL;
    else if(root->left == NULL)
      return root->right;
    else if(root->right == NULL)
      return root->left;
    else{
      tree left = root->left;
      while(left->right != NULL)
        left = left->right;
      void *swap = left->object;
      left->object = root->object;
      root->object = swap;
      root->left = tree_delete(root->left, key, f);
    }
  } else if(f(root->object) > key){
      root->left = tree_delete(root->left, key, f);
  } else {
      root->right = tree_delete(root->right, key, f);
  } 

  if(tree_height(root->right) > (tree_height(root->left) + 1))
    return left_rotation(root);
  else if (tree_height(root->left) > (tree_height(root->right) + 1))
    return right_rotation(root);

  return root;
}

tree tree_insert(tree root, void *object, keyfunc f){
  if(root == NULL)
    return create_new_node(object);

  if(f(root->object) == f(object))
    return root;

  if(f(root->object) > f(object))
    root->left = tree_insert(root->left, object, f);
  else 
    root->right = tree_insert(root->right, object, f);
  if(tree_height(root->right) > (tree_height(root->left) + 1))
    return left_rotation(root);
  else if (tree_height(root->left) > (tree_height(root->right) + 1))
    return right_rotation(root);
  return root;
}

tree left_rotation(tree root){
  if(root == NULL)
    return NULL;
  tree A, B;
  A = root;
  B = A->right;
  if(tree_height(B->right) < tree_height(B->left))
    B = right_rotation(B);
  A->right = B->left;
  B->left = A;
  return B;
}

tree right_rotation(tree root){
  if(root == NULL)
    return NULL;
  tree A, B;
  A = root;
  B = A->left;
  if(tree_height(B->right) > tree_height(B->left))
    B = left_rotation(B);
  A->left = B->right;
  B->right = A;
  return B;

}

tree create_new_node(void *object){
  tree node = malloc(sizeof(*node));
  node->left = NULL;
  node->right = NULL;
  node->object = object;
  return node;
}

void *tree_find(tree root, int key, keyfunc f){
  if(root == NULL)
    return NULL;

  if(f(root->object) == key)
    return root->object;
  else if(f(root->object) > key)
    return tree_find(root->left, key, f);
  else 
    return tree_find(root->right, key, f);
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
