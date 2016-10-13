
struct queue_t;

void queue_create();

int queue_empty(queue q);

void queue_enqueue(queue q, void *object);

void *queue_dequeue(queue q);

void queue_destroy(queue q);