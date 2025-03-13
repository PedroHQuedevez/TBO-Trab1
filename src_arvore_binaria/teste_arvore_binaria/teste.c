#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aresta.h"
#include "vertice.h"

int main(int argc, char *argv[])
{
    ArvoreBinaria *ab = arvore_binaria_construct();

    // 1
    // 0 2
    Vertice *um = vertice_construct(1);
    vertice_set_distancia_origem(1.0);
    arvore_binaria_push(um);

    Vertice *zero = vertice_construct(0);
    vertice_set_distancia_origem(0.0);
    arvore_binaria_push(zero);

    Vertice *dois = vertice_construct(2);
    vertice_set_distancia_origem(2.0);
    arvore_binaria_push(dois);

    //
    printf("min: %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 0.00
    printf("min: %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 1.00
    printf("min: %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 2.00

    // free
    vertice_destroy(um);
    vertice_destroy(zero);
    vertice_destroy(dois);
    arvore_binaria_destroy(ab);

    return 0;
}