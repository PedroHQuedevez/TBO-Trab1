#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conexao.h"

char *get_conexao_origem(conexao *c)
{
    return c->origem;
}

char *get_conexao_dest(conexao *c)
{
    return c->dest;
}

float get_weight(conexao *c)
{
    return c->weight;
}

void conexao_destroy(conexao *c)
{
    free(c);
}

conexao *conexao_construct(char *origem, char *dest, char *weight)
{
    conexao *c = (conexao *)calloc(1, sizeof(conexao));
    strcpy(c->origem, origem);
    strcpy(c->dest, dest);
    float weight_f = atof(weight);
    c->weight = weight_f;
    return c;
}