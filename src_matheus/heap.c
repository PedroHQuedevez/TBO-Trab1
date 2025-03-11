#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

Heap *heap_construct()
{
    Heap *h = (Heap *)calloc(1, sizeof(Heap));
    h->vertices = vector_construct();
    return h;
}

void heapfy_down(Heap *h, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int idx = i;
    // comparação utilizando >= para manter a estabilidade entre chaves iguais;
    if (left < return_size(h->vertices) && ((Vertice *)vector_get(h->vertices, left))->distancia_origem >= ((Vertice *)vector_get(h->vertices, idx))->distancia_origem)
        idx = left;

    if (right < return_size(h->vertices) && ((Vertice *)vector_get(h->vertices, right))->distancia_origem >= ((Vertice *)vector_get(h->vertices, idx))->distancia_origem)
        idx = right;

    if (idx != i)
    {
        vector_swap(h->vertices, i, idx);
        heapfy_down(h, idx);
    }
}

void heapfy_up(Heap *h, int idx)
{
    int parent_idx = (idx - 1) / 2;
    if (parent_idx >= 0 && ((Vertice *)vector_get(h->vertices, idx))->distancia_origem < ((Vertice *)vector_get(h->vertices, parent_idx))->distancia_origem)
    {
        vector_swap(h->vertices, idx, parent_idx);
        heapfy_up(h, parent_idx);
    }
}

void heap_push(Heap *h, Vertice *v)
{
    vector_push_back(h->vertices, v);
    heapfy_up(h, return_size(h->vertices) - 1);
}

Vertice *heap_pop(Heap *h)
{
    Vertice *v = (Vertice *)vector_get(h->vertices, 0);
    if (return_size(h->vertices) == 1)
    {
        vector_pop_back(h->vertices);
        return v;
    }
    vector_set(h->vertices, 0, vector_pop_back(h->vertices));
    heapfy_down(h, 0);
    return v;
}

void heap_destroy(Heap *h) {
    vector_destroy(h->vertices);
}