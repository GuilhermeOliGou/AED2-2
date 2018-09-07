/*
    heap_binario.h
    Nome: Guilherme Oliveira Goularte
    n°USP: 10387748
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Implementação usando vetores

typedef struct {
    double distancia;/* Representa a distância de um vértice em relação ao S*/
    int mapaDeRetorno;/* Indica a qual vértice do grafo representa essa determinada distância*/
}NO;

typedef struct {
    NO* arvore; /* Cada índice representa um nó da árvore heap
                Organizado na ordem correta
                O índice 1 representa a raiz, ou aquele que tem amior prioridade*/

    int* mapa; /* Os índices representam os vértices do grafo
                Os valores representam a posição deles na árvore Heap
                Índice 1 representa o primeiro vértice do grafo*/
    int numElementos;
    int maxElementos;
}HeapBinario;

/* Essa função inverte dois vértices na estrutura interna da árvore
Ela pega como parâmetro o heap de onde os NOs tem origem
E os dois nós que ela deve alterar*/
void inverterNaArvore (HeapBinario* heap, int v1, int v2);

/* Essa função inverte dois vértices na estrutura do mapa de indexação
Ela pega como parâmetro o heap de onde os Vertices tem origem
E os dois Vertices que ela deve alterar*/
void inverter (HeapBinario* heap, int v1, int v2);

/* Essa função modifica o valor de algum elemento na árvore do heap
E no mapa de indexação
E o realoca adequadamente nas estruturas
Ela pega como parâmetro o heap de onde o Vértice tem origem
O vértice que deverá ser alterado e o valor que ele assumirá*/
void alteraElemento (HeapBinario* heap, int elementoAlterado, double valor);

/* Essa função inicializa o heap e define o vértice origem como tendo distância 0
Ela pega como parâmetros o heap onde os dados serão colocados,
Além do número de vértice alocados e o vértice origem do percurso*/
bool buildHeap (HeapBinario* heap, int nn, int verticeS);

/* Essa função reorganiza o heap depois que a raiz recebe um pop
Ela pega como parâmetros somente o heap cuja raiz recebeu o pop*/
void heapify (HeapBinario* heap);

/* Essa função retorna verdadeiro caso o heap ainda possua elementos*/
bool possuiElementos (HeapBinario* heap);

/* Essa função retorna o valor do elemento de maior prioridade no heap (pop)
Ela pega como parâmetro o heap cuja raiz receberá o pop*/
double popElementoPrioritario (HeapBinario* heap);

/* Essa função exclui o elemento de maior prioridade
E reorganiza o grafo para que ele se mantenha ordenado
Ela pega como parâmetro o grafo que será reorganizado*/
void excluiElementoPrioritario(HeapBinario* heap);

/* Essa função retorna a distância de um vértice específico da raiz
Ela pega como parâmetros o heap de onde o vértice tem origem e o vértice*/
double retornaDistancia(HeapBinario* heap, int vertice);

void printHeap (HeapBinario* heap);
