#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aresta.h"
#include "dijkstra.h"
#include "vector.h"
#include "vertice.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Error: precisa de um arquivo de entrada e um arquivo de saída.\n");
        exit(0);
    }

    FILE *archive = fopen(argv[1], "r");
    if (archive == NULL)
    {
        printf("Error: file not found.\n");
        exit(0);
    }

    int source;
    fscanf(archive, "node_%d\n", &source);

    // Vetor principal contendo vertices para que seja possivel
    // acessar em tempo O(1) as informações de um dado vértice
    Vector *vertices = vector_construct();

    // váriaveis buffer e de contagem
    Vertice *v;
    Aresta *a;

    int origem;
    int destino;
    char peso_str[100];
    float peso;

    char c;

    while (fscanf(archive, "node_%d", &origem) == 1)
    {
        v = vertice_construct(origem);
        if (origem == source)
        {
            vertice_set_id_pai(v, 0);
            vertice_set_distancia_origem(v, 0.0);
        }
        vector_push_back(vertices, v);

        destino = 0;
        while (1)
        {
            if (fscanf(archive, "%c", &c) != 1) break;
            if (c == '\n') break;

            if (destino == origem) destino++;

            fscanf(archive, " %99[^,\n]", peso_str);
            peso = atof(peso_str);
            // printf("%d %d %.2f\n", origem, destino, peso); // debug

            if (peso > 0)
            {
                a = aresta_construct(origem, destino, peso);
                vertice_add_aresta(v, a);
            }

            destino++;
        }
    }

    fclose(archive);

    dijkstra(vertices, source);

    // quicksort vector de vertices
    // cria outro vetor separado
    // para que seja possível indexar o vértice pelo id no vetor de vertices original
    Vector *ordenado = vector_construct();
    for (int i = vector_size(vertices)-1; i >= 0; i--) // itera em ordem reversa para preservar a ordem original
    {
        vector_push_back(ordenado, (Vertice *)vector_get(vertices, i));
    }
    vector_qsort(ordenado, cmp_vertice);

    // for (int i = 0; i < vector_size(vertices); i++) // debug
    // {
    //     v = (Vertice *)vector_get(vertices, i);
    //     printf("id: %d pai: %d dist_source: %.2f\n", vertice_get_id(v), vertice_get_id_pai(v), vertice_get_distancia_origem(v));
    // }

    // imprime os vertices
    int id_pai;
    float distancia;
    for (int i = 0; i < vector_size(vertices); i++) // debug
    {
        v = (Vertice *)vector_get(ordenado, i);
        distancia = vertice_get_distancia_origem(v);
        printf("SHORTEST PATH TO node_%d: node_%d ", vertice_get_id(v), vertice_get_id(v));

        do
        {
            id_pai = vertice_get_id_pai(v);
            printf("<- node_%d ", id_pai);
            v = (Vertice *)vector_get(vertices, id_pai);
        }
        while (id_pai != 0);

        printf("(Distance: %.2f)\n", distancia);
    }

    // destroy
    for (int i = 0; i < vector_size(vertices); i++)
    {
        v = (Vertice *)vector_get(vertices, i);
        vertice_destroy(v);
    }
    vector_destroy(vertices);
    vector_destroy(ordenado);

    return 0;
}