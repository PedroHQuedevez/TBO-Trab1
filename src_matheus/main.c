#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "vector.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error: needs exactly one argument.\n");
        exit(0);
    }

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

    // Vetor principal contendo vertices para que seja possivel
    // acessar em tempo O(1) as informações de um dado vértice
    Vector *vertices = vector_construct();

    // Heap principal contendo os nós não visitados
    Heap *nao_visitados = heap_construct();

    Vertice *v;
    Aresta *a;

    while ((read = getline(&line, &len, archive)) != -1)
    {
        char *token = strtok(line, ",");
        char *node_id = token;

        token = strtok(NULL, ",");

        int count = 0;
        while (token != NULL)
        {
            // printf("%s ", token);

            char *origem = node_id;

            // no caso de exemplo node 3, a terceira coluna da entrada representaria a conexão com o node 4
            // aqui nós colocamos uma conexão extra de 3 com 3 de valor 0, para manter as entradas consistentes com os vetores
            // que serão criados depois;
            int origem_idx = atoi(&node_id[5]);
            v = vertice_construct(origem_idx);

            if (origem_idx == count)
            {
                char *peso_aux = "0";
                char destino_aux[50];
                sprintf(destino_aux, "node_%i", count);

                a = aresta_construct(atoi(origem), atoi(destino_aux), atoi(peso_aux));

                vertice_add_aresta(v, a);
                count++;
            }

            char destino[50];
            sprintf(destino, "node_%i", count);

            char *peso = token;
            token = strtok(NULL, ",");

            conexao *c = conexao_construct(origem, destino, peso);
            vector_push_back(heap_min, c);
            count++;
        }
        vector_node *vn = vector_node_construct(node_id, heap_min);
        vector_push_back(nodes, vn);
    }

    fclose(archive);

    return 0;
}