#include <stdlib.h>
#include <float.h>
#include "vertice.h"

// Construtor de vértice
Vertice *vertice_construct(int id) {
    Vertice *v = (Vertice *)malloc(sizeof(Vertice));
    v->id = id;
    v->id_pai = -1;
    v->distancia_origem = FLT_MAX;
    v->arestas = vector_construct();
    return v;
}

// Destruir vértice
void vertice_destroy(Vertice *v) {
    vector_destroy(v->arestas);
    free(v);
}

// Adicionar aresta ao vértice
void vertice_add_aresta(Vertice *v, Aresta *a) {
    vector_push_back(v->arestas, a);
}

// Getters e setters
float vertice_get_distancia_origem(Vertice *v) {
    return v->distancia_origem;
}

void vertice_set_distancia_origem(Vertice *v, float distancia) {
    v->distancia_origem = distancia;
}

int vertice_get_id_pai(Vertice *v) {
    return v->id_pai;
}

void vertice_set_id_pai(Vertice *v, int id_pai) {
    v->id_pai = id_pai;
}

int vertice_get_id(Vertice *v) {
    return v->id;
}
