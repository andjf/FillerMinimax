#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_CAPACITY 256

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#include "point.h"

// Circular Queue that can store up to 256 elements
struct Queue
{
    point data[QUEUE_CAPACITY];
    uint8_t head;
    uint8_t tail;
};

struct Queue *create_queue();

void enqueue(struct Queue *q, point p);

point dequeue(struct Queue *q);

uint8_t size(struct Queue *q);

void print_queue(struct Queue *q);

void free_queue(struct Queue *q);

#endif