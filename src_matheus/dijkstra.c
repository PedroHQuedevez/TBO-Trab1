#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

void dijkstra(Vector *vertices, int source)
{
    // constroi o heap de não-visitados e insere o vértice inicial
    Heap *nao_visitados = heap_construct();
    heap_push(nao_visitados, (Vertice *)vector_get(vertices, source));

    // variáveis buffer
    Vertice *origem, *destino;
    float peso;
    Vector *arestas;
    Aresta *a;
    int idx;

    int count_debug = 0; // debug
    Vector *visitados = vector_construct(); // debug
    while (heap_size(nao_visitados) > 0)
    {
        origem = heap_pop(nao_visitados);
        arestas = vertice_get_arestas(origem);

        if (vector_find(visitados, origem) == -1) vector_push_back(visitados, origem); // debug
        else printf("%p já foi visitado\n", origem);
        count_debug += 1; // debug
        printf("%d %d %d\n", count_debug, heap_size(nao_visitados), vector_size(visitados)); // debug

        for (int i = 0; i < vector_size(arestas); i++) {
            a = (Aresta *)vector_get(arestas, i);
            // printf("%d %d\n", vector_size(vertices), aresta_get_destino(a)); // debug
            destino = (Vertice *)vector_get(vertices, aresta_get_destino(a));
            peso = aresta_get_peso(a);

            int find = vector_find(visitados, destino) != -1; // debug
            // if (find) printf("%.2f + %.2f = %.2f || %.2f\n", vertice_get_distancia_origem(origem), peso, vertice_get_distancia_origem(origem) + peso, vertice_get_distancia_origem(destino)); // debug

            if (vertice_get_distancia_origem(origem) + peso < vertice_get_distancia_origem(destino))
            {
                if (find) printf("^^^^^^^^^\n"); // debug

                vertice_set_id_pai(destino, vertice_get_id(origem));
                vertice_set_distancia_origem(destino, vertice_get_distancia_origem(origem) + peso);

                // caso o vertice esteja no heap, atualiza-o com heapify up. senão, adiciona-o ao heap
                // printf("heap: %d %d || vector: %d %d\n", heap_find(nao_visitados, destino), heap_size(nao_visitados), vector_find(nao_visitados->vertices, destino), vector_size(nao_visitados->vertices));

                idx = heap_find(nao_visitados, destino);
                if (idx >= 0) heapify_up(nao_visitados, idx);
                else heap_push(nao_visitados, destino);
            }
        }
    }

    heap_destroy(nao_visitados);
}