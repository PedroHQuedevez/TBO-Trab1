#ifndef _CONEXAO_H
#define _CONEXAO_H

typedef struct conexao
{
    char origem[50];
    char dest[50];
    float weight;
} conexao;

char *get_conexao_origem(conexao *c);
char *get_conexao_dest(conexao *c);
float get_weight(conexao *c);
void conexao_destroy(conexao *c);
conexao *conexao_construct(char *Origen, char *Dest, char *weight);

#endif