/* map.c */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int u = 0;

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

void tree_destroy(tree);
tree left_rotation(tree);
tree right_rotation(tree);
tree tree_delete(tree, int, keyfunc);
tree tree_insert(tree, void*, keyfunc);
int tree_height(tree);
void *tree_find(tree, int, keyfunc);
tree create_leaf(void*);

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
  if(f == NULL)
    return;
  tree_destroy(f->root);
  return;
}

/* return the height of a map */
int map_height(map f){
  return tree_height(f->root);
}

/* find an object in the map and return it or NULL if not found */
void * map_find(map m, int key){
  return tree_find(m->root, key, m->f);
}

/* insert an object in a map and return it or NULL in case of
   failure (NULL object or object already inside the map) */
void * map_insert(map m, void * object){
  /*if(!m || !(m->f))
    return NULL;
  */
  //printf("test %d | \n", u++);
  m->root = tree_insert(m->root, object, m->f);
  return map_find(m, m->f(object));
}

/* delete an object from a map and return it or NULL in not found */
void * map_delete(map m, int key){
  if(!m || !(m->f))
    return NULL;

  void *obj = map_find(m, key);
  m->root = tree_delete(m->root, key, m->f);
  return obj;
}



//------------------AFFICHAGE D'ARBRE BINAIRE--------------

tree create_leaf(void *object){
  tree leaf = malloc(sizeof(*leaf));
  leaf->left = NULL;
  leaf->right = NULL;
  leaf->object = object;
  return leaf;
}

void *find_min(tree root){
  if(root->left == NULL)
    return root->object;
  root = root->left;
  while(root->right != NULL)
    root = root->right;
  return root->object;
}

void tree_destroy(tree root){
  if(root == NULL)
    return;
  stack s = stack_create();
  tree pop;
  stack_push(s, root);
  while(!stack_empty(s)){
    pop = stack_pop(s);
    if(pop->left != NULL)
      stack_push(s, pop->left);
    if(pop->right != NULL)
      stack_push(s, pop->right);
    free(pop);
  }
}

tree tree_delete(tree root, int key, keyfunc f){

  if(root == NULL)
    return NULL;

  stack s = stack_create();
  tree now = root;

  while(now && f(now->object) != key){
    stack_push(s, now);

    if(f(now->object) > key)
      now = now->left;
    else 
      now = now->right;
  }

  if(now == NULL)
    return root;


  if(now->left != NULL && now->right != NULL){
    now->object = find_min(now);
    key = f(now->object);
    stack_push(s, now);
    now = now->left;
    while(f(now->object) != key){
      stack_push(s, now);
      now = now->right;
    }
  }

  tree new_child;

  if(now->left == NULL && now->right == NULL)
    new_child = NULL;
  else if(now->left == NULL)
    new_child = now->right;
  else if(now->right == NULL)
    new_child = now->left;


  if(stack_empty(s))
    return new_child;


  tree pop, new_root = stack_pop(s);

  if(new_root->left == now)
    new_root->left = new_child;
  else
    new_root->right = new_child;


  while(!stack_empty(s)){

    if(tree_height(new_root->right) > (tree_height(new_root->left) + 1))
      new_root = left_rotation(new_root);
    else if (tree_height(new_root->left) > (tree_height(new_root->right) + 1))
      new_root = right_rotation(new_root);

    pop = stack_pop(s);

    if(f(pop->object) > f(new_root->object))
      pop->left = new_root;
    else 
      pop->right = new_root;

    new_root = pop;

  }
  if(tree_height(new_root->right) > (tree_height(new_root->left) + 1))
    new_root = left_rotation(new_root);
  else if (tree_height(new_root->left) > (tree_height(new_root->right) + 1))
    new_root = right_rotation(new_root);


  return new_root;
}

tree tree_insert(tree root, void *object, keyfunc f){

  if(root == NULL)
    return create_leaf(object);

  int currentKey;
  int objectKey = f(object);

  stack s = stack_create();

  tree copy = root;
 
  while(copy){
    stack_push(s, copy);
    currentKey = f(copy->object);

    if(currentKey == objectKey)
      break;

    if(currentKey > objectKey){
      if(copy->left == NULL)
        copy->left = create_leaf(object);

      copy = copy->left;

    } else if (currentKey < objectKey){
      if(copy->right == NULL)
        copy->right = create_leaf(object);

      copy = copy->right;
    }
  }
  printf("test");

  tree new_root = stack_pop(s);
  tree pop;

  while(!stack_empty(s)){

    if(tree_height(new_root->right) > (tree_height(new_root->left) + 1))
      new_root = left_rotation(new_root);
    else if (tree_height(new_root->left) > (tree_height(new_root->right) + 1))
      new_root = right_rotation(new_root);

    pop = stack_pop(s);

    if(f(pop->object) > f(new_root->object))
      pop->left = new_root;
    else 
      pop->right = new_root;

    new_root = pop;

  }

  if(tree_height(new_root->right) > (tree_height(new_root->left) + 1))
    new_root = left_rotation(new_root);
  else if (tree_height(new_root->left) > (tree_height(new_root->right) + 1))
    new_root = right_rotation(new_root);


  return new_root;
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


void *tree_find(tree root, int key, keyfunc f){
  int current;
  while(root){
    current = f(root->object);

    if(current == key)
      return root->object;
    if(current > key)
      root = root->left;
    else 
      root = root->right;
  }
  return root->object;
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
