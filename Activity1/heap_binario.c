/*
    Nome: Guilherme Oliveira Goularte
    n°USP: 10387748
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "heap_binario.h"

#define DBL_MAX 2147483647

void inverterNaArvore (HeapBinario* heap, int v1, int v2){
    int aux1 = heap->arvore[v1].distancia;
    int aux2 = heap->arvore[v1].mapaDeRetorno;
    heap->arvore[v1].distancia = heap->arvore[v2].distancia;
    heap->arvore[v1].mapaDeRetorno = heap->arvore[v2].mapaDeRetorno;
    heap->arvore[v2].distancia = aux1;
    heap->arvore[v2].mapaDeRetorno = aux2;
}

void inverter (HeapBinario* heap, int v1, int v2){
    if (v1 <= 0){
        printf("Valor de v1 , %d,muito baixo!\n", v1);
        return;
    }
    if (v1 > heap->maxElementos){
        printf("Valor de v1 , %d,muito alto!\n", v1);
        return;
    }
    if (v2 <= 0){
        printf("Valor de v2 , %d,muito baixo!\n", v2);
        return;
    }
    if (v2 > heap->maxElementos){
        printf("Valor de v2 , %d,muito alto!\n", v2);
        return;
    }
    int aux2 = heap->mapa[v1];
    heap->mapa[v1] = heap->mapa[v2];
    heap->mapa[v2] = aux2;
    inverterNaArvore(heap, heap->mapa[v1], heap->mapa[v2]);
}

void alteraElemento (HeapBinario* heap, int elementoAlterado, double valor){
    if (valor < 0){
        printf("Novo valor muito baixo!\n");
        return;
    }
    if (elementoAlterado <= 0){
        printf("Elemento alterado muito baixo!\n");
        return;
    }
    if (elementoAlterado > heap->maxElementos){
        printf("Elemento alterado muito alto!\n");
        return;
    }
    if (heap->mapa[elementoAlterado] > heap->numElementos){
        printf("Elemento já foi alterado!\n");
        return;
    }
    int indice = heap->mapa[elementoAlterado];
    heap->arvore[indice].distancia = valor;
    int indicePai;
    while(true){
        indicePai = (indice - (indice%2))/2;
        if (indice <= 1 ||
                heap->arvore[indice].distancia >= heap->arvore[indicePai].distancia){
            break;
        }
        inverter(heap, heap->arvore[indice].mapaDeRetorno, heap->arvore[indicePai].mapaDeRetorno);
        indice = indicePai;
    }
}

bool buildHeap (HeapBinario* heap, int nn, int verticeS){
    if (nn <= 0){
        printf("Quantidade de nós muito baixa!\n");
        return false;
    }
    if (verticeS <= 0){
        printf("Valor do vertice origem muito baixo!\n");
        return false;
    }
    if (verticeS > nn){
        printf("Valor do vertice origem muito alto!\n");
        return false;
    }
    NO* novaArvore = (NO*)calloc(nn+1, sizeof(NO));
    int* novoMapa = (int*)calloc(nn+1, sizeof(int));
    heap->arvore = novaArvore;
    heap->mapa = novoMapa;
    heap->numElementos = nn;
    heap->maxElementos = nn;
    int i;
    for (i = 1; i <= nn; i++){
        heap->arvore[i].distancia = DBL_MAX;
        heap->arvore[i].mapaDeRetorno = i;
        heap->mapa[i] = i;
    }
    alteraElemento(heap, verticeS, 0);
    return true;
}

void heapify (HeapBinario* heap){
    int indice = 1;
    int indiceFilho;
    while (true){
        if (indice >= heap->numElementos)
            break;
        indiceFilho = 2*indice;
        if (indiceFilho > heap->numElementos)
            break;
        if (indiceFilho+1 <= heap->numElementos
                && heap->arvore[indiceFilho].distancia > heap->arvore[indiceFilho+1].distancia)
            indiceFilho++;
        if (heap->arvore[indice].distancia <= heap->arvore[indiceFilho].distancia)
            break;
        inverter(heap, heap->arvore[indice].mapaDeRetorno, heap->arvore[indiceFilho].mapaDeRetorno);
        indice = indiceFilho;
    }
}

bool possuiElementos (HeapBinario* heap){
    return heap->numElementos > 0;
}

double popElementoPrioritario (HeapBinario* heap){
    if (!possuiElementos(heap)){
        printf("Não há mais elementos nesse Heap!\n");
        return -1;
    }
    return heap->arvore[1].mapaDeRetorno;
}

void excluiElementoPrioritario(HeapBinario* heap){
    if (!possuiElementos(heap)){
        printf("Não há mais elementos nesse Heap!\n");
        return;
    }
    if (heap->numElementos == 1){
        heap->numElementos = heap->numElementos-1;
        return;
    }
    inverter(heap, heap->arvore[1].mapaDeRetorno, heap->arvore[heap->numElementos].mapaDeRetorno);
    heap->numElementos = heap->numElementos-1;
    heapify(heap);
}

double retornaDistancia(HeapBinario* heap, int vertice){
    if (vertice <= 0){
        printf("Valor do vertice , %d,muito baixo!\n", vertice);
        return -1;
    }
    if (vertice > heap->maxElementos){
        printf("Valor do vertice , %d,muito alto!\n", vertice);
        return -1;
    }
    return heap->arvore[heap->mapa[vertice]].distancia;
}

void printHeap (HeapBinario* heap){
    int i;
    for (i = 1; i <= heap->numElementos; i++)
        printf("%d\n",heap->arvore[i].mapaDeRetorno);
    printf("\n");
}
