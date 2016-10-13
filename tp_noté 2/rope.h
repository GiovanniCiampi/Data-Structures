union rope;
enum kind {string, concatenation, factor};

typedef union rope * rope;

typedef enum kind kind;

//Basic functions

//returns the length of rope
int length(rope ch);

//construct the sub-rope of r starting a position 'start' and of length 'length'
rope sub_rope(rope r, int start, int length);

//construct the concatenation of the ropes ch1 and ch2
rope concat(rope ch1, rope ch2);

//construct the rope from the string str
rope of_string(char * str);

//when the rope r is a leaf with the string str, it returns str
char * get_string(rope r);

//when the rope r is a sub-rope of some rope r', it returns the position a which r starts in r'
int get_offset(rope r);

//when the rope r is a concatenation of two ropes r1 and r2, it returns r1
//when the rope r is a sub-rope of some rope r', it returns r'
//it returns r otherwise
rope get_left_child(rope r);

//when the rope r is a concatenation of two ropes r1 and r2, it returns r2
//when the rope r is a sub-rope of some rope r', it returns r'
//it returns r otherwise
rope get_right_child(rope r);

//returns the number of parent nodes the rope r has
int get_nbparents(rope r);

//increments the number of parents of the rope r
void inc_nbparents(rope r);

//decrements the number of parents of the rope r
void dec_nbparents(rope r);

//Functions to write in exercice 1

//returns the character at position 'pos' in the rope 'r'
char char_at(rope r, int pos);

//returns the rope constructed from the rope r where the sub-rope starting at position 'pos' and of length 'length' has beed deleted
rope delete(rope r, int pos, int length);

//returns the rope obtained from r1 where r2 has been inserted at position 'pos'
rope insert(rope r1, rope r2, int pos);

//returns the string represented by the rope r
char * to_string(rope r);

//returns 1 when the strings represented by the ropes r1 and r2 are the same and 0 otherwise
int equal(rope r1, rope r2);

//Functions to write in exercice 2

// when the rope r is of the form sub_{i,j}(sub_{k,l}(r)), it transforms it in a rope of the form sub_{n,p}(r) representing the same string
void sub_sub_case(rope r);

// pushes one level down the sub on top of a rope of the form sub_{i,j}(@(r1,r2))
void sub_append_case(rope r);

// pushes the sub nodes as low as possible in the rope r
void push_sub_nodes(rope r);

// produce a balanced rope that is the concatenation of the balanced ropes left and right
rope balanced_concat(rope left, rope right);

// erases the rope r from the memory
void destroy(rope r);

kind get_kind(rope r);
