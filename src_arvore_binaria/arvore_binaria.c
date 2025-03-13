#include <stdlib.h>
#include <stdio.h>
#include "arvore_binaria.h"

typedef struct No {
    Vertice *vertice;
    No *left;
    No *right;
} No;

typedef struct ArvoreBinaria
{
    No *root;
} ArvoreBinaria;

No *no_construct(Vertice *v)
{
    No *n = (No *)calloc(1, sizeof(No));
    n->vertice = v;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void no_destroy(No *n)
{
    free(n);
}

void no_destroy_recursivo(No *n)
{
    if (n == NULL) return;

    // recursivamente destroi os outros nós da árvore
    no_destroy_recursivo(n->left);
    no_destroy_recursivo(n->right);
    free(n);
}

ArvoreBinaria *arvore_binaria_construct()
{
    ArvoreBinaria *ab = (ArvoreBinaria *)calloc(1, sizeof(ArvoreBinaria));
    ab->root = NULL;
    return ab;
}

int arvore_binaria_vazia(ArvoreBinaria *ab)
{
    return ab->root == NULL;
}

void arvore_binaria_push(ArvoreBinaria *ab, Vertice *v)
{
    No *novo = no_construct(v);
    
    if (ab->root == NULL) ab->root = novo;
    else
    {
        No *atual = ab->root;
        while (1)
        {
            if (vertice_get_distancia_origem(v) <= vertice_get_distancia_origem(atual->vertice))
            {
                if (atual->left != NULL) atual = atual->left;
                else
                {
                    atual->left = novo;
                    break;
                }
            }
            else
            {
                if (atual->right != NULL) atual = atual->right;
                else
                {
                    atual->right = novo;
                    break;
                }
            }
        }
    }
}

void arvore_binaria_remove(ArvoreBinaria *ab, Vertice *v)
{
    // itera até achar o nó correspondente ao vértice
    No *atual = ab->root, *pai = NULL;
    int pai_left = 0;
    while (1)
    {
        if (atual == NULL) return; // o vertice nao foi encontrado na arvore

        if (atual->vertice == v) break; // compara vertices por ponteiro

        pai = atual;
        if (vertice_get_distancia_origem(v) <= vertice_get_distancia_origem(atual->vertice))
        {
            atual = atual->left;
            pai_left = 1;
        }
        else
        {
            atual = atual->right;
            pai_left = 0;
        }
    }

    // corrige a árvore caso o nó tenha filhos
    // caso tenha filhos à esquerda e à direita
    if (atual->left != NULL)
    {
        // coloca o filho à esquerda do nó a ser removido como filho do pai do nó a ser removido
        // ou como root da árvore caso o nó a ser removido já seja o root
        if (pai == NULL) ab->root = atual->left;
        else if (pai_left) pai->left = atual->left;
        else pai->right = atual->left;

        if (atual->right != NULL)
        {
            // encontra nó mais à direita dentre os filhos à esquerda do nó a ser removido
            // itera até achar o nó mínimo
            No *novo_pai = atual->left; // nó que vai ser o novo pai da subárvore à direita do nó a ser removido
            while (novo_pai->right != NULL) novo_pai = novo_pai->right;
            novo_pai->right = atual->right;
        }
    }
    else if (atual->right != NULL)
    {
        // coloca o filho à direita do nó a ser removido como filho do pai do nó a ser removido
        // ou como root da árvore caso o nó a ser removido já seja o root
        if (pai == NULL) ab->root = atual->right;
        else if (pai_left) pai->left = atual->right;
        else pai->right = atual->right;
    }

    // salva o vértice, destroi o nó e retorna o vértice
    Vertice *v = atual->vertice;
    no_destroy(atual);
    return v;
}

Vertice *arvore_binaria_pop_min(ArvoreBinaria *ab)
{
    if (ab->root == NULL)
    {
        printf("Error: arvore_binaria_pop_min: arvore_binaria has size 0.\n");
        exit(0);
    }

    // itera até achar o nó mínimo
    No *atual = ab->root, *pai = NULL;
    while (atual->left != NULL)
    {
        pai = atual;
        atual = atual->left;
    }

    // corrige a árvore caso o nó mais à esquerda tenha um filho à direita
    if (atual->right != NULL)
    {
        if (pai == NULL) ab->root = atual->right;
        else pai->left = atual->right;
    }

    // salva o vértice, destroi o nó e retorna o vértice
    Vertice *v = atual->vertice;
    no_destroy(atual);
    return v;
}

void arvore_binaria_destroy(ArvoreBinaria *ab)
{
    no_destroy_recursivo(ab->root);
    free(ab);
}