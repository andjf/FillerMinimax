#include "queue.h"

struct Queue *create_queue()
{
    struct Queue *q = calloc(1, sizeof(struct Queue));
    q->head = 0;
    q->tail = 0;
    return q;
}

void enqueue(struct Queue *q, point p)
{
    q->data[q->tail++] = p;
}

point dequeue(struct Queue *q)
{
    return q->data[q->head++];
}

uint8_t size(struct Queue *q)
{
    return q->head > q->tail ? (QUEUE_CAPACITY - q->head + q->tail) : (q->tail - q->head);
}

void free_queue(struct Queue *q)
{
    free(q);
}

void print_queue(struct Queue *q)
{
    printf("head [%d] => ", q->head);
    if (size(q))
    {
        for (uint8_t i = q->head; i != q->tail; i++)
        {
            point current_point = q->data[i];
            printf("(%d %d) ", get_x(current_point), get_y(current_point));
        }
    }
    else
    {
        printf("empty ");
    }
    printf("=> tail [%d]\n", q->tail);
}