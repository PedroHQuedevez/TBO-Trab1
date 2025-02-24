#ifndef _HEAP_H
#define _HEAP_H

#include "vector.h"

typedef struct vector_node vector_node;
typedef struct conexao conexao;

vector_node *vector_node_construct(char *node_id, Vector *heap_min);
conexao *conexao_construct(char *Origen, char *Dest, char *weight);

int return_size_conexoes(vector_node *v);
Vector *get_vector_conexoes(vector_node *v);
conexao *get_conexao(vector_node *v, int i);
char *get_conexao_origen(conexao *c);
char *get_conexao_dest(conexao *c);
float get_weight(conexao *c);
char *return_node_id(vector_node *v);

void heapfy_down(Vector *heap_min, int i);
void heapfy_up(Vector *heap_min, int i);
void heap_push(Vector *heap_min, conexao *c);
conexao *heap_pop(Vector *heap_min);

void print_node(vector_node *node);

void heap_destroy(Vector *heap_min);
void vector_node_destroy(vector_node *vn);

#endif