#ifndef VERTICE_H
#define VERTICE_H

#include "vector.h"
#include "aresta.h"

typedef struct {
    int id;
    int id_pai;
    float distancia_origem;
    Vector *arestas; // ✅ Lista de arestas dentro do vértice
} Vertice;

Vertice *vertice_construct(int id);
void vertice_destroy(Vertice *v);
void vertice_add_aresta(Vertice *v, Aresta *a);
float vertice_get_distancia_origem(Vertice *v);
void vertice_set_distancia_origem(Vertice *v, float distancia);
int vertice_get_id_pai(Vertice *v);
void vertice_set_id_pai(Vertice *v, int id_pai);
int vertice_get_id(Vertice *v);

#endif
