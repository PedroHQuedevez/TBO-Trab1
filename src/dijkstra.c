#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "vector.h"
#include <limits.h>

// Função auxiliar para trocar dois elementos no array
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função auxiliar para particionar o array
int partition(int indices[], Vector *distances, int low, int high)
{
    float *pivot = (float *)vector_get(distances, indices[high]);
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        float *dist_j = (float *)vector_get(distances, indices[j]);
        if (*dist_j < *pivot || (*dist_j == *pivot && indices[j] < indices[high]))
        {
            i++;
            swap(&indices[i], &indices[j]);
        }
    }
    swap(&indices[i + 1], &indices[high]);
    return (i + 1);
}

// Função QuickSort
void quickSort(int indices[], Vector *distances, int low, int high)
{
    if (low < high)
    {
        int pi = partition(indices, distances, low, high);

        quickSort(indices, distances, low, pi - 1);
        quickSort(indices, distances, pi + 1, high);
    }
}

Vector *visited_nodes_vector_init(int size, char *source_node_id)
{
    Vector *visited_nodes = vector_construct();
    for (int i = 0; i < size; i++)
    {
        int *init = malloc(sizeof(int));
        *init = 0;
        vector_push_back(visited_nodes, init);
    }

    int source_node_index = atoi(&source_node_id[5]);
    int *init = (int *)vector_get(visited_nodes, source_node_index);
    *init = 1;
    return visited_nodes;
}

Vector *distances_vector_init(int size, char *source_node_id)
{
    Vector *distances = vector_construct();
    float max = 3.4E+38;
    for (int i = 0; i < size; i++)
    {
        float *f = malloc(sizeof(float));
        *f = max;
        vector_push_back(distances, f);
    }

    int source_node_index = atoi(&source_node_id[5]);
    float *f = (float *)vector_get(distances, source_node_index);
    *f = 0;
    return distances;
}

Vector *parents_vector_init(int size, char *source_node_id)
{
    Vector *parents = vector_construct();
    for (int i = 0; i < size; i++)
    {
        int *a = malloc(sizeof(int));
        *a = -1;
        vector_push_back(parents, a);
    }

    int *source = (int *)vector_get(parents, atoi(&source_node_id[5]));
    *source = atoi(&source_node_id[5]);

    return parents;
}

void att_visited_nodes(Vector *visited_nodes, int index)
{
    int *att = (int *)vector_get(visited_nodes, index);
    *att = 1;
}

void att_distances(Vector *distances, int index, float value)
{
    float *att = (float *)vector_get(distances, index);
    *att = value;
}

void att_parents(Vector *parents, int index, int parent_index)
{
    int *att = (int *)vector_get(parents, index);
    *att = parent_index;
}

int all_nodes_was_visited(Vector *visited_nodes)
{
    for (int i = 0; i < vector_size(visited_nodes); i++)
    {
        if (*(int *)vector_get(visited_nodes, i) == 0)
            return 0;
    }
    return 1;
}

void add_conexions_heap_min(Vector *heap_min, vector_node *node)
{

    Vector *conexoes = get_vector_conexoes(node);

    for (int i = 0; i < return_size(conexoes); i++)
    {
        conexao *c = (conexao *)vector_get(conexoes, i);

        if (get_weight(c) == 0)
            continue;

        heap_push(heap_min, c);
    }
}

int next_node_index(Vector *distances, Vector *visited_nodes)
{
    float min = 3.4E+38;
    int index = -1;
    for (int i = 0; i < vector_size(distances); i++)
    {
        float *d = (float *)vector_get(distances, i);
        if (*d < min && *(int *)vector_get(visited_nodes, i) == 0)
        {
            min = *d;
            index = i;
        }
    }

    return index;
}

void print_shortest_paths(Vector *distances, Vector *parents, char *source_node_id, char *path_saida)
{
    int num_nodes = vector_size(distances);

    FILE *file = fopen(path_saida, "w");
    if (!file)
    {
        perror("Erro ao abrir arquivo");
        return;
    }

    // Criar um vetor de índices para ordenar os nós pela distância e, em caso de empate, pelo índice do nó
    int indices[num_nodes];
    for (int i = 0; i < num_nodes; i++)
    {
        indices[i] = i;
    }

    // Ordenar os índices com base nas distâncias e, em caso de empate, pelo índice do nó
    quickSort(indices, distances, 0, num_nodes - 1);

    // Escrever os caminhos mínimos no arquivo
    for (int i = 0; i < num_nodes; i++)
    {
        int node_index = indices[i];
        float *distance = (float *)vector_get(distances, node_index);

        // Construir o caminho reverso
        char path[1024];
        int path_length = 0;
        int current = node_index;

        // Garantir que o nó de origem apareça como 'node_X <- node_X'
        if (current == atoi(&source_node_id[5]))
        {
            path_length += sprintf(path + path_length, "node_%d <- node_%d ", current, current);
        }
        else
        {
            while (current != atoi(&source_node_id[5]))
            {
                path_length += sprintf(path + path_length, "node_%d <- ", current);
                int *parent = (int *)vector_get(parents, current);
                if (*parent == -1)
                    break;
                current = *parent;
            }

            // Adicionar o nó de origem ao caminho
            path_length += sprintf(path + path_length, "node_%s", &source_node_id[5]);
        }

        // Escrever no formato correto com distância na mesma linha
        // retirar todos os /n de path, estava recebendo um /n no final de path.
        for (int i = 0; i < strlen(path); i++)
        {
            if (path[i] == '\n')
            {
                path[i] = ' ';
            }
        }
        fprintf(file, "SHORTEST PATH TO node_%d: %s(Distance: %.2f)\n", node_index, path, *distance);
    }

    fclose(file);
}

void dijkstra(Vector *nodes, char *source_node_id, char *path_saida)
{
    // colocar todas as conexões do nó inicial no heap min
    int source_node_index = atoi(&source_node_id[5]);
    vector_node *source_node = (vector_node *)vector_get(nodes, source_node_index);

    int number_of_nodes = vector_size(nodes);

    Vector *visited_nodes = visited_nodes_vector_init(number_of_nodes, source_node_id);
    Vector *distances = distances_vector_init(number_of_nodes, source_node_id);
    Vector *parents = parents_vector_init(number_of_nodes, source_node_id);
    Vector *heap_min = vector_construct();

    add_conexions_heap_min(heap_min, source_node);

    while (all_nodes_was_visited(visited_nodes) == 0)
    {

        for (int i = 0; i < return_size(heap_min); i++)
        {
            conexao *c = heap_pop(heap_min);

            char *origin = get_conexao_origen(c);
            int origin_index = atoi(&origin[5]);

            char *dest = get_conexao_dest(c);
            int dest_index = atoi(&dest[5]);

            float weight = get_weight(c);

            float distance_origin = *(float *)vector_get(distances, origin_index);
            float distance_dest = *(float *)vector_get(distances, dest_index);
            float new_distance = distance_origin + weight;

            if (new_distance < distance_dest)
            {
                att_distances(distances, dest_index, new_distance);
                att_parents(parents, dest_index, origin_index);
            }

            if (vector_size(heap_min) == 0)
            {
                int next_node = next_node_index(distances, visited_nodes);
                add_conexions_heap_min(heap_min, (vector_node *)vector_get(nodes, next_node));
                att_visited_nodes(visited_nodes, next_node);
            }
        }
    }

    print_shortest_paths(distances, parents, source_node_id, path_saida);

    // free

    for (int i = 0; i < vector_size(visited_nodes); i++)
    {
        int *a = (int *)vector_get(visited_nodes, i);
        free(a);
    }

    for (int i = 0; i < vector_size(distances); i++)
    {
        float *a = (float *)vector_get(distances, i);
        free(a);
    }

    for (int i = 0; i < vector_size(parents); i++)
    {
        int *a = (int *)vector_get(parents, i);
        free(a);
    }

    vector_destroy(visited_nodes);
    vector_destroy(distances);
    vector_destroy(parents);
    vector_destroy(heap_min);
}