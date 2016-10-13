#include "rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------//
//---------------------- Data structures definitions --------------------//
//-----------------------------------------------------------------------//



union rope{
  struct {
    enum kind k;
    char * str;
    int length;
    int nbparents;
  } str;
  
  struct {
    enum kind k;
    union rope * left;
    union rope * right;
    int length;
    int nbparents;
  } conc;
  
  struct {
    enum kind k;
    union rope * rope;
    int start;
    int length;
    int nbparents;
  } fac;
};

struct cursor{
  union rope * current;
  struct cursor * up;
  int modified_below;
  int pos;
};

//-----------------------------------------------------------------------//
//---------------------------- Basic functions --------------------------//
//-----------------------------------------------------------------------//

int ln2(int k){
  assert(k>0);
  int i;
  for(i=-1;k!=0;i++){
    k=k>>1;
  }
  return i;
}


char * new_string(int lg){
  char * res_string = malloc(sizeof(char) * (lg+1));
  res_string[lg]='\0';
  return res_string;
}

char * str_copy(char * str){
  int l = strlen(str);
  char * res = new_string(l);
  int i;
  for(i=0;i<l;i++){res[i]=str[i];}
  return res;
}

kind get_kind(rope r){return r->str.k;}

int length(rope r){
  if(r==NULL){return 0;}
  else{
    kind k = get_kind(r);
    if(k==string){return r->str.length;}
    else if(k==concatenation){return r->conc.length;}
    else{return r->fac.length;}
  }
}

int get_nbparents(rope r){
  //printf("get_nbparents\n");
  if(r==NULL){return -1;}
  else{
    kind k = get_kind(r);
    if(k==string){return r->str.nbparents;}
    else if(k==concatenation){return r->conc.nbparents;}
    else{return r->fac.nbparents;}
  }
}

void add_nbparents(rope r, int n){
  assert(r);
  kind k = get_kind(r);
  if(k==string){r->str.nbparents+=n;return;}
  else if(k==concatenation){r->conc.nbparents+=n;return;}
  else{r->fac.nbparents+=n;return;}
}

void inc_nbparents(rope r){add_nbparents(r,1);return;}

void dec_nbparents(rope r){add_nbparents(r,-1);return;}

rope get_left_child(rope r){
  kind k = get_kind(r);
  if(k==concatenation){return r->conc.left;}
  else if (k==factor){return r->fac.rope;}
  else{return r;}
}

rope get_right_child(rope r){
  kind k = get_kind(r);
  if(k==concatenation){return r->conc.right;}
  else if (k==factor){return r->fac.rope;}
  else{return r;}
}

void set_left_child(rope r1, rope r2){
  kind k = get_kind(r1);
  if(k==concatenation){
    dec_nbparents(r1->conc.left);
    r1->conc.left=r2;
    inc_nbparents(r2);
    return;
  }
  else if (k==factor){
    dec_nbparents(r1->fac.rope);
    r1->fac.rope=r2;
    inc_nbparents(r2);
    return;
  }
  else{return;}
}

void set_right_child(rope r1, rope r2){
  kind k = get_kind(r1);
  if(k==concatenation){
    dec_nbparents(r1->conc.right);
    r1->conc.right=r2;
    inc_nbparents(r2);
    return;
  }
  else if (k==factor){
    dec_nbparents(r1->fac.rope);
    r1->fac.rope=r2;
    inc_nbparents(r2);
    return;
  }
  else{return;}
}

rope sub_rope(rope r, int start, int lg){
  assert(start<length(r));
  assert(start+lg<=length(r));
  if(lg==0){
    printf("made an empty rope\n");
    return NULL;}
  else{
    rope new_rope = malloc(sizeof(union rope));
    new_rope->fac.k=factor;
    new_rope->fac.rope=r;
    inc_nbparents(r);
    new_rope->fac.start=start;
    new_rope->fac.length=lg;
    new_rope->fac.nbparents=0;
    return new_rope;
  }
}

int get_offset(rope r){
  kind k = get_kind(r);
  assert(k==factor);
  return r->fac.start;
}

void add_to_offset(rope r, int n){
  kind k = get_kind(r);
  assert(k==factor);
  r->fac.start += n;
}

rope concat(rope r1, rope r2){
  if(r1==NULL){return r2;}
  else if(r2==NULL){return r1;}
  else{
    rope new_rope = malloc(sizeof(union rope));
    new_rope->conc.k = concatenation;
    new_rope->conc.left = r1;
    new_rope->conc.right = r2;
    inc_nbparents(r1);
    inc_nbparents(r2);
    new_rope->conc.length = length(r1)+length(r2);
    new_rope->conc.nbparents = 0;
    return new_rope;
  }
}

rope of_string(char * str){
  assert(str!=NULL);
  union rope * new_rope = malloc(sizeof(union rope));
  new_rope->str.k = string;
  new_rope->str.str=str_copy(str);
  new_rope->str.length=strlen(str);
  new_rope->str.nbparents=0;
  return new_rope;
}

char * get_string(rope r){
  kind k = get_kind(r);
  assert(k==string);
  return r->str.str;
}

void set_sub_rope(rope r, rope r_sub){
  assert(get_kind(r)==factor);
  dec_nbparents(r->fac.rope);
  inc_nbparents(r_sub);
  r->fac.rope = r_sub;
}


void turn_into_append(rope r, rope left, rope right){
  assert(get_kind(r)==factor);
  int nb_parents = r->fac.nbparents;
  rope r_aux = get_left_child(r);
  r->conc.left = left;
  r->conc.right = right;
  r->conc.k = concatenation;
  r->conc.length = length(left)+length(right);
  r->conc.nbparents = nb_parents;
  inc_nbparents(left);
  inc_nbparents(right);
  dec_nbparents(r_aux);
}

//-----------------------------------------------------------------------//
//---------------- Functions to implement in exercice 1 -----------------//
//-----------------------------------------------------------------------//


char char_at(rope ch, int pos){

  if(get_kind(ch) == string){
    char value = (ch->str.str)[pos];
    return value;

  } else if(get_kind(ch) == concatenation){
    int len = length(ch->conc.left);
    if(len > pos)
      return char_at(ch->conc.left, pos) ;
    return char_at(ch->conc.right,pos - len);
  } else if(get_kind(ch) == factor){
    return char_at(ch->fac.rope, ch->fac.start + pos );
  }
  return '\0';
}

rope delete(rope ch, int start, int lg){

  if(ch == NULL)
    return NULL;

  int len = length(ch);

  if(start < 0 || start + lg > len)
    return NULL;


  if(start == 0)
    return sub_rope(ch, lg + 1, len - (lg + 1));

  return concat(sub_rope(ch, 0, start ), sub_rope(ch, start + lg , len - (start + lg + 1)));
}

rope insert(rope ch1, rope ch2, int pos){
  if(ch1 == NULL && ch2 == NULL)
    return NULL;
  else if(ch1 == NULL)
    return ch2;
  else if (ch2 == NULL)
    return ch1;

  int len = length(ch1);

  if(pos < 0 || pos > len)
    return ch1;

  return concat(concat(sub_rope(ch1, 0, pos), ch2), sub_rope(ch1, pos , len - pos ));
}

char *  to_string(rope ch){
  if (ch == NULL)
    return NULL;

  if(get_kind(ch) == string){
    char * copy = malloc(length(ch) * sizeof(char));
    strcpy(copy, ch->str.str);
    return copy;
  }
  else if(get_kind(ch) == concatenation){
    char *result = malloc(sizeof(char) * length(ch));
    strcpy(result, to_string(ch->conc.left));
    strcat(result, to_string(ch->conc.right));
    return result;
  }
  else {
    char *all = malloc(sizeof(char) * length(ch->fac.rope));
    all = to_string(ch->fac.rope);
    char *result = malloc(sizeof(char) * length(ch));
    strncpy(result, &all[ch->fac.start], ch->fac.length);
    return result;
  }
}

int equal(rope r1, rope r2){
  char *string1 = to_string(r1);
  char *string2 = to_string(r2);
  if(!strcmp(string1, string2))
    return 1;
  return 0;
}

//-----------------------------------------------------------------------//
//---------------- Functions to implement in exercice 2 -----------------//
//-----------------------------------------------------------------------//


void sub_sub_case(rope ch){
  assert(ch->fac.k == factor);

  rope aux = ch->fac.rope;
  assert (aux->fac.k == factor);

  ch->fac.rope = aux->fac.rope;
  add_to_offset(ch, aux->fac.start);

  dec_nbparents(aux);
}

void sub_append_case(rope ch){
  assert(ch->fac.k == factor);
  rope internal = ch->fac.rope;
  assert(internal->conc.k == concatenation);
  if(ch->fac.start <= length(internal->conc.left) && (ch->fac.start + ch->fac.length) <= length(internal->conc.left)){
    ch->fac.rope = internal->conc.left;
    dec_nbparents(internal);
  } else if(ch->fac.start > length(internal->conc.left) && (ch->fac.start + ch->fac.length) <= length(internal->conc.right)){
    ch->fac.rope = internal->conc.right;
    dec_nbparents(internal);
  }
}

void push_sub_nodes(rope ch){
  kind k = get_kind(ch);
  if(k == factor){
    if(get_kind(ch->fac.rope) == concatenation)
      sub_append_case(ch);
    push_sub_nodes(ch->fac.rope);
  } else if (k == concatenation){
    push_sub_nodes(ch->conc.left);
    push_sub_nodes(ch->conc.right);
  } 
}

void destroy(rope ch){
  assert(ch);
  if(get_nbparents(ch) > 0)
    return;

  kind k = get_kind(ch);

  if(k == string)
    free(ch->str.str);
  else if (k == concatenation){
    destroy(ch->conc.left);
    destroy(ch->conc.right);
  } else {
    destroy(ch->fac.rope);
  }
  free(ch);
}

rope balanced_concat(rope left, rope right){
  return left; //a effacer
}
