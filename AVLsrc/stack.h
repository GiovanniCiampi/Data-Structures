

struct stack_t;
typedef struct stack_t * stack;

stack stack_create();

int stack_empty(stack s);

void *stack_pop(stack s);

void stack_push(stack s, void *object);

void stack_destroy(stack s);