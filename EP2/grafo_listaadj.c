/*
    grafo_listaadj.c
    Nome: Guilherme Oliveira Goularte
    n°USP: 10387748
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grafo_listaadj.h"

#define VN -1
#define AN NULL

typedef double TipoPeso;

typedef TipoAresta* TipoApontador;

bool inicializaGrafo(TipoGrafo* g, int nv){
    if (nv <= 0){
        printf("Número de vértices muito baixo!\n");
        return false;
    }
    TipoApontador* novo = (TipoApontador*) calloc(nv+1, sizeof(TipoApontador));
    if(!novo){
        printf("Espaço de memória insuficiente!\n");
        return false;
    }
    g->listaAdj = novo;
    g->numVertices = nv;
    g->numArestas = 0;
    int i;
    for (i = 1; i <= nv; i++){
        g->listaAdj[i] = AN;
    }
    return true;
}

int obtemNrVertices(TipoGrafo* grafo){
    return grafo->numVertices;
}

int obtemNrArestas(TipoGrafo* grafo){
    return grafo->numArestas;
}

bool verificaValidadeVertice(int v, TipoGrafo *grafo){
    if (v <= 0){
        printf("Valor de vértice muito baixo!\n");
        return true;
    }
    if (v > grafo->numVertices){
        printf("Valor de vértice muito alto!\n");
        return true;
    }
    return false;
}

TipoApontador primeiroListaAdj(int v, TipoGrafo* grafo){
    if (verificaValidadeVertice(v, grafo)){
        printf("Vértice v inválido!\n");
        return AN;
    }
    return grafo->listaAdj[v];
}

bool listaAdjVazia(int v, TipoGrafo* grafo){
    if (verificaValidadeVertice(v, grafo)){
        printf("Vértice v inválido!\n");
        return false;
    }
    TipoApontador apontadorDeArestasNoVertice = primeiroListaAdj(v, grafo);
    if (apontadorDeArestasNoVertice)
        return false;
    return true;
}

TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual){
    if (verificaValidadeVertice(v, grafo)){
        printf("Vértice v inválido!\n");
        return AN;
    }
    if (!atual)
        return AN;
    return atual->prox;
}

bool existeAresta(int v1, int v2, TipoGrafo *grafo){
    if (verificaValidadeVertice(v1, grafo)){
        printf("Vértice v1 inválido!\n");
        return false;
    }
    if (verificaValidadeVertice(v2, grafo)){
        printf("Vértice v2 inválido!\n");
        return false;
    }
    TipoApontador atual = primeiroListaAdj(v1, grafo);
    while(atual){
        if (atual->vdest == v2)
            return true;
        atual = proxListaAdj(v1, grafo, atual);
    }
    return false;
}

void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo){
    if (verificaValidadeVertice(v1, grafo)){
        printf("Vértice v1 inválido!\n");
        return;
    }
    if (verificaValidadeVertice(v2, grafo)){
        printf("Vértice v2 inválido!\n");
        return;
    }
    if (existeAresta(v1, v2, grafo)){
        printf("Aresta (v1, v2) já existe\n!");
        return;
    }
    TipoApontador atual = grafo->listaAdj[v1];
    TipoApontador novo = (TipoApontador)malloc(sizeof(TipoAresta));
    novo->peso = peso;
    novo->vdest = v2;
    novo->prox = atual;
    grafo->listaAdj[v1] = novo;
    grafo->numArestas = grafo->numArestas + 1;
}

TipoPeso obtemPesoAresta(int v1, int v2, TipoGrafo *grafo){
    if (verificaValidadeVertice(v1, grafo)){
        printf("Vértice v1 inválido!\n");
        return -1;
    }
    if (verificaValidadeVertice(v2, grafo)){
        printf("Vértice v2 inválido!\n");
        return -1;
    }
    TipoApontador atual = primeiroListaAdj(v1, grafo);
    while(atual){
        if (atual->vdest == v2)
            return atual->peso;
        atual = proxListaAdj(v1, grafo, atual);
    }
    printf("Aresta (v1, v2) não existe!\n");
    return -1;
}

bool removeAresta(int v1, int v2, TipoGrafo *grafo){
    if (verificaValidadeVertice(v1, grafo)){
        printf("Vértice v1 inválido!\n");
        return false;
    }
    if (verificaValidadeVertice(v2, grafo)){
        printf("Vértice v2 inválido!\n");
        return false;
    }
    TipoApontador anterior = AN;
    TipoApontador atual = primeiroListaAdj(v1, grafo);
    while(atual){
        if (atual->vdest == v2){
            if (!anterior)
                grafo->listaAdj[v1] = proxListaAdj(v1,grafo,atual);
            else
                anterior->prox = proxListaAdj(v1,grafo,atual);
            free(atual);
            grafo->numArestas = grafo->numArestas - 1;
            return true;
        }
        anterior = atual;
        atual = proxListaAdj(v1, grafo, atual);
    }
    printf("Aresta (v1, v2) não existe!\n");
    return false;
}

bool removeArestaObtendoPeso(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo){
    if (verificaValidadeVertice(v1, grafo)){
        printf("Vértice v1 inválido!\n");
        return false;
    }
    if (verificaValidadeVertice(v2, grafo)){
        printf("Vértice v2 inválido!\n");
        return false;
    }
    TipoApontador anterior = AN;
    TipoApontador atual = primeiroListaAdj(v1, grafo);
    while(atual){
        if (atual->vdest == v2){
            *peso = atual->peso;
            if (!anterior)
                grafo->listaAdj[v1] = proxListaAdj(v1,grafo,atual);
            else
                anterior->prox = proxListaAdj(v1,grafo,atual);
            free(atual);
            grafo->numArestas = grafo->numArestas - 1;
            return true;
        }
        anterior = atual;
        atual = proxListaAdj(v1, grafo, atual);
    }
    printf("Aresta (v1, v2) não existe!\n");
    return false;
}

void imprimeGrafo(TipoGrafo* grafo){
    int matriz[grafo->numVertices+1][grafo->numVertices+1];
    int i, j;
    for (i = 1; i <= grafo->numVertices; i++){
        for (j = 1; j <= grafo->numVertices; j++){
            matriz[i][j] = 0;
        }
    }
    for (i = 1; i <= grafo->numVertices; i++){
        TipoApontador atual = primeiroListaAdj(i, grafo);
        while(atual){
            matriz[i][(int)atual->vdest] = atual->peso;
            atual = proxListaAdj(i, grafo, atual);
        }
    }
    for (i = 1; i <= grafo->numVertices; i++){
        for (j = 1; j <= grafo->numVertices; j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}

void LiberaListaAdj (TipoApontador atual){
    if (atual){
        LiberaListaAdj(atual->prox);
        free(atual);
    }
    return;
}

void liberaGrafo(TipoGrafo* grafo){
    int i;
    for (i = grafo->numVertices; i >= 1; i--){
        LiberaListaAdj(grafo->listaAdj[i]);
        grafo->listaAdj[i] = AN;
    }
    free(grafo);
}

int verticeDestino(TipoApontador p, TipoGrafo* grafo){
    return p->vdest;
}

double obtemPesoInstantaneo (TipoApontador p){
    return p->peso;
}
