struct stack_t;
typedef struct stack_t *stack;

stack stack_create(void);

void stack_push(stack s, void *object);

int stack_empty(stack s);

void *stack_top(stack s);

void stack_pop(stack s);