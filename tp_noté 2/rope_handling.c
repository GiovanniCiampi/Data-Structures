#include "rope.h"
#include "rope_handling.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

struct historic{
  rope content;
  struct historic * next;
};

struct rope_names{
  rope content;
  char * name;
  int root;
  struct rope_names * next;
};

struct links{
  char * n1;
  char * n2;
  struct links * next;
};

struct sym_tab{
  struct rope_names * tab;
  struct links * rel;
  int fresh;
};

typedef struct rope_names * rope_names;
typedef struct links * links;
typedef struct sym_tab * sym_tab;

char * conc(char * s1, char * s2){
  assert(s1);
  assert(s2);
  int l1  =strlen(s1);
  int l2 = strlen(s2);
  int l = l1+l2;
  char * res = malloc(sizeof(char)*(l+1));
  res[l]='\0';
  int i;
  for(i=0;i<l1;i++){res[i] = s1[i];}
  for(i=0;i<l2;i++){res[i+l1] = s2[i];}
  return res;
}

char * conc_ff(char * s1, char * s2){
  char * res = conc(s1,s2);
  free(s1);
  free(s2);
  s1=NULL;
  s2=NULL;
  return res;
}

char * conc_kf(char * s1, char * s2){
  char * res = conc(s1,s2);
  free(s2);
  s2=NULL;
  return res;
}
char * conc_fk(char * s1, char * s2){
  char * res = conc(s1,s2);
  free(s1);
  s1=NULL;
  return res;
}



historic create_historic(rope r, historic h){
  historic new_historic= malloc(sizeof(struct historic));
  new_historic->next = h;
  inc_nbparents(r);
  new_historic->content = r;
  return new_historic;
}

rope get_rope(historic h){return h->content;}

historic insert_rope(historic h, rope r,int pos){
  assert(h);
  r = insert(h->content,r,pos);
  return create_historic(r,h);
}

historic delete_rope(historic h, int start, int l){
  assert(h);
  rope r = delete(h->content,start,l);
  return create_historic(r,h);
}

historic sub_rope_historic(historic h,int start, int length){
  if(h && h->content){
    rope r =sub_rope(h->content,start,length);
    return create_historic(r,h);
  }
  else{
    return h;
  }
}

void sub_append_case_historic(historic h){
  sub_append_case(h->content);
}

void sub_sub_case_historic(historic h){
  sub_sub_case(h->content);
}

void push_sub_nodes_historic(historic h){push_sub_nodes(h->content);}

historic sub_rope_push_historic(historic h,int start, int length){
  if(h && h->content){
    rope r =sub_rope(h->content,start,length);
    push_sub_nodes(r);
    return create_historic(r,h);
  }
  else{
    return h;
  }
}

historic concat_historic(historic h){
  if(h && h->content && h->next->content){
    return create_historic(concat(h->content,h->next->content),h);
  }
  else{return h;}
}

historic balanced_concat_historic(historic h,rope r){
  if(h && h->content){
    return create_historic(balanced_concat(h->content,r),h);
  }
  else{return h;}
}

historic square_historic(historic h){
  if(h && h->content){
    return create_historic(balanced_concat(h->content,h->content),h);
  }
  else{return h;}
}

historic undo(historic h){
  assert(h);
  rope r = h->content;
  dec_nbparents(r);
  destroy(r);
  historic old = h->next;
  free(h);
  //printf("destruction complete\n");
  return old;
}

char * node_def(rope r,int mode,int root, char * name){
  
}

char * get_node_def(rope_names rn, int mode){
  assert(rn);
  rope r = rn->content;
  kind k = get_kind(r);
  char * name = rn->name;
  int root = rn->root;
  char * end;
  if(root==0||mode < 4){end="\"]";}
  else{end="\", color=lightgray, style=filled]";}
  char * start = "[shape=Mrecord, label=\"";
  char* label;
  char * l;
  if(mode==1 || mode==3 || mode == 5 || mode == 7){
     l = malloc(sizeof(char)*8);
     sprintf(l,"|%d",get_nbparents(r));
  }
  else{
    l=malloc(sizeof(char));
    l[0]='\0';
  }
  if(k==string){label=conc_kf(get_string(r),l);}
  else if(k==concatenation){label = conc_kf("@",l);}
  else if(k==factor){
    char * offset = malloc(sizeof(char)*8);
    assert(k==factor);
    sprintf(offset,"%d",get_offset(r));
    char * lg = malloc(sizeof(char)*8);
    sprintf(lg,"%d",length(r));
    label = conc_ff(conc_kf("sub(",conc_ff(offset,conc_kf(",",conc_fk(lg,")")))),l);
  }
  else{label=conc_kf("_",l);}
  if(mode==2 || mode == 3 || mode == 6 || mode == 7){
    label=conc_kf("{",conc_fk(label,conc_kf("|{",conc_fk(to_string(r),"}}"))));
  }
  return conc_kf(name,conc_kf(start,conc_fk(label,end)));
}

rope_names create_rope_names(rope r, int l, int root){
  rope_names rn = malloc(sizeof(struct rope_names));
  rn->content=r;
  char * name = malloc(sizeof(char)*8);
  sprintf(name,"s%d",l);
  rn->name = name;
  rn->root = root;
  rn->next=NULL;
  //printf("%s\n",get_node_def(rn,0));
  return rn;
}

links create_links(char * n1, char * n2,links l){
  links nl = malloc(sizeof(struct links));
  nl->n1 = n1;
  nl->n2 = n2;
  //printf("link %s -> %s added\n",n1,n2);
  nl->next = l;
  return nl;
}

void destroy_rope_names(rope_names rn){
  if(rn){
    destroy_rope_names(rn->next);
    free(rn->name);
    rn->name=NULL;
    free(rn);
  }
}

void destroy_links(links l){
  if(l){
    destroy_links(l->next);
    free(l);
  }
}

sym_tab create_sym_tab(){
  sym_tab t = malloc(sizeof(struct sym_tab));
  t->tab=NULL;
  t->rel=NULL;
  t->fresh=0;
}

void destroy_sym_tab(sym_tab t){
  destroy_rope_names(t->tab);
  destroy_links(t->rel);
  free(t);
}

int find_link(links t, char * s1, char * s2){
  if(t){
    if(t->n1==s1 && t->n2==s2){return 1;}
    else{return find_link(t->next,s1,s2);}
  }
  else{return 0;}
}

void add_links(sym_tab t, char * s1, char * s2){
  int k = find_link(t->rel,s1,s2);
  if(k==0){
    links l = create_links(s1,s2,t->rel);
    t->rel=l;
  }
}

void add_double_links(sym_tab t, char * s1, char * s2){
  int k = find_link(t->rel,s1,s2);
  if(k==0){
    links l = create_links(s1,s2,t->rel);
    l = create_links(s1,s2,l);
    t->rel=l;
  }
}

char * find_aux(rope_names rn, rope r,sym_tab t,int root){
  if(rn){
    if(rn->content==r){
      if(root!=0){
        rn->root=root;
      }
      return rn->name;
    }
    else{
      if(rn->next){
        return find_aux(rn->next,r,t,root);
      }
      else{
        rn->next = create_rope_names(r,t->fresh,root);
        t->fresh++;
        return rn->next->name;
      }
    }
  }
  else{return NULL;}
}
  
char * find(sym_tab t, rope r,int root){
  if(t->tab){
    return find_aux(t->tab,r,t,root);
  }
  else{
    t->tab=create_rope_names(r,t->fresh,root);
    t->fresh++;
    return t->tab->name;
  }
}
  
char * draw_rope_aux(rope r, sym_tab t,int root){
  
  char * nr = find(t,r,root);
 
  kind k = get_kind(r);
  
  if(k==concatenation){
    rope left = get_left_child(r);
    rope right = get_right_child(r);
    char * nleft = draw_rope_aux(left,t,0);
    char * nright = draw_rope_aux(right,t,0);
    if(nleft==nright){
      add_double_links(t,nr,nleft);
    }
    else{
      add_links(t,nr,nleft);
      add_links(t,nr,nright);
    }
  }
  else if(k==factor){
    rope p = get_left_child(r);
    char * np =draw_rope_aux(p,t,0);
    add_links(t,nr,np);
  }
  return nr;
}

void print_node_def(rope_names r, int mode, FILE * fp){
  if(r){
    fprintf(fp,"\t%s;\n",get_node_def(r,mode));
    print_node_def(r->next,mode,fp);
  }
}

void print_links(links l, FILE * fp){
  if(l){
    fprintf(fp,"\t%s -> %s;\n",l->n1,l->n2);
    print_links(l->next,fp);
  }
}

void print_sym_tab(sym_tab t, int mode, FILE * fp){
  fprintf(fp,"digraph G{\n");
  print_node_def(t->tab,mode,fp);
  print_links(t->rel,fp);
  fprintf(fp,"}\n");
}

void historic_draw_aux(historic to_draw, sym_tab t, int nb, int mode, FILE * fp){
  if(to_draw){
    rope r = to_draw->content;
    nb++;
    draw_rope_aux(r,t,nb);
    historic_draw_aux(to_draw->next,t,nb,mode,fp);
  }
  else{print_sym_tab(t,mode,fp);}
}

void rope_draw(rope r, char * file_name, int mode){
  FILE *fp;
  if (fp = fopen(file_name, "w+"))
    {
      sym_tab t= create_sym_tab();
      draw_rope_aux(r,t,0);
      print_sym_tab(t,mode,fp);
      destroy_sym_tab(t);
      fclose(fp);
    }
  else
    printf("Error opening the file %s\n",file_name);
}

void historic_draw(historic h, char * file_name, int mode){
  FILE *fp;
  if (fp = fopen(file_name, "w+"))
    {
      sym_tab t= create_sym_tab();
      historic_draw_aux(h,t,0,mode,fp);
      destroy_sym_tab(t);
      fclose(fp);
    }
  else
    printf("Error opening the file %s\n",file_name);
}
  

void print_historic(historic h){
  if(h!=NULL){
    rope r = h->content;
    char * str = to_string(r);
    printf("rope: %s\n",str);
    free(str);
    str=NULL;
    return print_historic(h->next);
  }
  else{return;}
}
