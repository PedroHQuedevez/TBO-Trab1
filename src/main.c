#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "vector.h"
#include "heap.h"
#include "dijkstra.h"

int main(int argc, char *argv[])
{

    FILE *archive = fopen(argv[1], "r");
    if (archive == NULL)
    {
        printf("Error: file not found.\n");
        exit(0);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, archive);

    char source_node[20];
    strcpy(source_node, line);

    // Vetor principal contendo vector nodes;
    Vector *nodes = vector_construct();

    while ((read = getline(&line, &len, archive)) != -1)
    {

        char *token = strtok(line, ",");
        char *node_id = token;

        token = strtok(NULL, ",");

        // vetor heap_min de conexões para cada node;
        Vector *heap_min = vector_construct();

        int count = 0;
        while (token != NULL)
        {
            // printf("%s ", token);

            char *origin = node_id;

            // no caso de exemplo node 3, a terceira coluna da entrada representaria a conexão com o node 4
            // aqui nós colocamos uma conexão extra de 3 com 3 de valor 0, para manter as entradas consistentes com os vetores
            // que serão criados depois;
            int origin_idx = atoi(&node_id[5]);
            if (origin_idx == count)
            {

                char *weight_aux = "0";
                char dest_aux[50];
                sprintf(dest_aux, "node_%i", count);
                conexao *c = conexao_construct(origin, dest_aux, weight_aux);
                vector_push_back(heap_min, c);
                count++;
            }

            char dest[50];
            sprintf(dest, "node_%i", count);

            char *weight = token;
            token = strtok(NULL, ",");

            conexao *c = conexao_construct(origin, dest, weight);
            vector_push_back(heap_min, c);
            count++;
        }
        vector_node *vn = vector_node_construct(node_id, heap_min);
        vector_push_back(nodes, vn);
    }

    fclose(archive);

    dijkstra(nodes, source_node, argv[2]);

    for (int i = 0; i < vector_size(nodes); i++)
    {
        vector_node *vn = (vector_node *)vector_get(nodes, i);
        vector_node_destroy(vn);
    }

    vector_destroy(nodes);
    free(line);

    return 0;
}