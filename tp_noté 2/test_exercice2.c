#include "rope.h"
#include "rope_handling.h"
#include "stdlib.h"
#include "stdio.h"



int main(int argc, char* argv[]){
  rope a = of_string("aaaaaaaaa");
  printf("ici");
  rope b = of_string("bbbbbbebbbbbb");
  historic h = create_historic(a,NULL);
  h = create_historic(b,h);
  h = concat_historic(h);
  h = sub_rope_historic(h,5,10);
  h = sub_rope_historic(h,2,7);

  //question 2.1

  //rope_draw(rss,"test_sub_sub_init.dot",0);//for viewing the rope structure only. 
  rope_draw(get_rope(h),"test_sub_sub_init.dot",2);//for visualisation of intermediate values in ropes, requires 'to_string' to be implemented
 
  sub_sub_case_historic(h);
  //rope_draw(rss,"test_sub_sub.dot",0);//for viewing the rope structure only. 
  
  rope_draw(get_rope(h),"test_sub_sub.dot",2);//for visualisation of intermediate values in ropes, requires 'to_string' to be implemented
  

  //question 2.2
  
  h = create_historic(a,h);
  h = create_historic(b,h);
  h = concat_historic(h);
  h = sub_rope_historic(h,6,12);
  //rope_draw(rss,"test_sub_append_init.dot",0);//for viewing the rope structure only. 
  rope_draw(get_rope(h),"test_sub_append_init.dot",2);//for visualisation of intermediate values in ropes, requires that 'to_string' is implemented
  sub_append_case_historic(h);
  //rope_draw(rss,"test_sub_append.dot",0);//for viewing the rope structure only. 
  rope_draw(get_rope(h),"test_sub_append.dot",2);//for visualisation of intermediate values in ropes, requires 'to_string' to be implemented
  
  //question 2.3
 
  push_sub_nodes_historic(h);
  //rope_draw(rss,"test_push_sub_nodes.dot",0);//for viewing the rope structure only. 
  rope_draw(get_rope(h),"test_push_sub_nodes.dot",2);//for visualisation of intermediate values in ropes, requires 'to_string' to be implemented
  
  //question 2.4
  
  h=square_historic(h);
  h=sub_rope_push_historic(h,4,12);
  historic_draw(h,"test_destroy_init.dot",2);
  h=undo(h);
  //historic_draw(h,"test_destroy.dot",0);//for viewing the rope structure only. 
  historic_draw(h,"test_destroy.dot",2);//for visualisation of intermediate values in ropes, requires 'to_string' to be implemented
  printf("balanced_concat\n");
  rope d = of_string("d");
  rope r = d;
  int i;
  for(i=0;i<8;i++){
    r=balanced_concat(r,d);
  }
  //rope_draw(r,"test_balanced_concat.dot",0);//for viewing the rope structure only. 
  rope_draw(r,"test_balanced_concat.dot",2);//for visualisation of intermediate values in ropes, requires 'to_string' to be implemented
  return 0;
}
