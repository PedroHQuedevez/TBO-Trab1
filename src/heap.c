#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

typedef struct vector_node
{
    char node_id[50];
    Vector *conexoes;
} vector_node;

typedef struct conexao
{
    char Origen[50];
    char Dest[50];
    float weight;
} conexao;

int return_size_conexoes(vector_node *v)
{
    return return_size(v->conexoes);
}

char *return_node_id(vector_node *v)
{
    return v->node_id;
}

Vector *get_vector_conexoes(vector_node *v)
{
    return (v->conexoes);
}

conexao *get_conexao(vector_node *v, int i)
{
    return (conexao *)vector_get(v->conexoes, i);
}

char *get_conexao_origen(conexao *c)
{
    return c->Origen;
}

char *get_conexao_dest(conexao *c)
{
    return c->Dest;
}

float get_weight(conexao *c)
{
    return c->weight;
}

void conexao_destroy(conexao *c)
{
    free(c);
}

void vector_node_destroy(vector_node *vn)
{
    for (int i = 0; i < return_size(vn->conexoes); i++)
    {
        conexao *c = (conexao *)vector_get(vn->conexoes, i);
        conexao_destroy(c);
    }
    vector_destroy(vn->conexoes);
    free(vn);
}

void set_vector_conexoes(vector_node *v, Vector *conexoes)
{
    v->conexoes = conexoes;
}

vector_node *vector_node_construct(char *node_id, Vector *conexoes)
{
    vector_node *vn = (vector_node *)calloc(1, sizeof(vector_node));
    strcpy(vn->node_id, node_id);
    vn->conexoes = conexoes;
    return vn;
}

conexao *conexao_construct(char *Origen, char *Dest, char *weight)
{
    conexao *c = (conexao *)calloc(1, sizeof(conexao));
    strcpy(c->Origen, Origen);
    strcpy(c->Dest, Dest);
    float weight_f = atof(weight);
    c->weight = weight_f;
    return c;
}

void heapfy_down(Vector *heap_min, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int idx = i;
    // comparação utilizando >= para manter a estabilidade entre chaves iguais;
    if (left < return_size(heap_min) && ((conexao *)vector_get(heap_min, left))->weight >= ((conexao *)vector_get(heap_min, idx))->weight)
        idx = left;

    if (right < return_size(heap_min) && ((conexao *)vector_get(heap_min, right))->weight >= ((conexao *)vector_get(heap_min, idx))->weight)
        idx = right;

    if (idx != i)
    {
        vector_swap(heap_min, i, idx);
        heapfy_down(heap_min, idx);
    }
}

void heapfy_up(Vector *heap_min, int idx)
{
    int parent_idx = (idx - 1) / 2;
    if (parent_idx >= 0)
    {
        conexao *current = (conexao *)vector_get(heap_min, idx);
        conexao *parent = (conexao *)vector_get(heap_min, parent_idx);

        if (current->weight < parent->weight)
        {
            vector_swap(heap_min, idx, parent_idx);
            heapfy_up(heap_min, parent_idx);
        }
    }
}

void heap_push(Vector *heap_min, conexao *c)
{
    vector_push_back(heap_min, c);
    heapfy_up(heap_min, return_size(heap_min) - 1);
}

conexao *heap_pop(Vector *heap_min)
{
    conexao *c = (conexao *)vector_get(heap_min, 0);
    if (return_size(heap_min) == 1)
    {
        vector_pop_back(heap_min);
        return c;
    }
    vector_set(heap_min, 0, vector_pop_back(heap_min));
    heapfy_down(heap_min, 0);
    return c;
}

void print_node(vector_node *node)
{
    printf("%s:\n", node->node_id);
    for (int i = 0; i < return_size(node->conexoes); i++)
    {
        conexao *c = (conexao *)vector_get(node->conexoes, i);
        printf("%s -> %s - %.2f \n", c->Origen, c->Dest, c->weight);
    }
    printf("\n");
}