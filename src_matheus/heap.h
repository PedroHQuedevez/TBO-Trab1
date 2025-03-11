#ifndef _HEAP_H
#define _HEAP_H

#include "vector.h"
#include "vertice.h"

typedef struct Heap {
    Vector *vertices;
} Heap;

Heap *heap_construct();
void heapfy_down(Heap *h, int i);
void heapfy_up(Heap *h, int i);
void heap_push(Heap *h, Vertice *v);
Vertice *heap_pop(Heap *h);
void heap_destroy(Heap *h);

#endif