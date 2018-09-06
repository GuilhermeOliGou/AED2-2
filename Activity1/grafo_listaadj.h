#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#define VN -1  /* numero de vertice invalido ou ausente */
#define AN NULL                /* aresta nula */

typedef double TipoPeso;

/*
  tipo estruturado taresta:
      vertice destino, peso, ponteiro p/ prox. aresta
*/
typedef struct taresta {
  double vdest;
  TipoPeso peso;
  struct taresta * prox;
} TipoAresta;

typedef TipoAresta* TipoApontador;

/*
  tipo estruturado grafo:
      vetor de listas de adjacencia (cada posicao contem o ponteiro
                    para o inicio da lista de adjacencia do vertice)
      numero de vertices
*/
typedef struct {
  TipoApontador *listaAdj;
  int numVertices;
  int numArestas;
} TipoGrafo;

/********************

  Prototipos dos metodos sobre grafos

*********************/

/*
  bool inicializaGrafo(TipoGrafo* grafo, int nv): Inicializa um grafo com nv vertices.
  Vertices vao de 0 a nv-1.
  Aloca o vetor listaAdj e o inicializa com null.
  Retorna true se inicializou com sucesso e false caso contrario
*/
bool inicializaGrafo(TipoGrafo* g, int nv);

/* int obtemNrVertices(TipoGrafo* grafo): retorna o numero de vertices do grafo */
int obtemNrVertices(TipoGrafo* grafo);

/* int obtemNrArestas(TipoGrafo* grafo): retorna o numero de arestas do grafo */
int obtemNrArestas(TipoGrafo* grafo);

/*
  bool verificaValidadeVertice(int v, TipoGrafo *grafo): verifica se o nr do vertice eh valido no grafo,
  ou seja, se ele é maior que zero e menor ou igual ao nr total de vertices do grafo.
*/
bool verificaValidadeVertice(int v, TipoGrafo *grafo);

/*
  void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo):
  Insere a aresta (v1, v2) com peso "peso" no grafo.
  Nao verifica se a aresta ja existia.
*/
void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo);

/*
  bool existeAresta(int v1, int v2, TipoGrafo *grafo):
  Retorna true se existe a aresta (v1, v2) no grafo e false caso contrário
*/
bool existeAresta(int v1, int v2, TipoGrafo *grafo);

/*
  TipoPeso obtemPesoAresta(int v1, int v2, TipoGrafo *grafo):
  Retorna o peso da aresta (v1, v2) no grafo se ela existir e AN caso contrário
*/
TipoPeso obtemPesoAresta(int v1, int v2, TipoGrafo *grafo);

/*
  bool removeArestaObtendoPeso(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo);
  Remove a aresta (v1, v2) do grafo colocando AN em sua celula (representando ausencia de aresta).
  Se a aresta existia, coloca o peso dessa aresta em "peso" e retorna true,
  caso contrario retorna false (e "peso" é inalterado).
*/
bool removeArestaObtendoPeso(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo);

/*
  bool removeAresta(int v1, int v2, TipoGrafo *grafo);
  Remove a aresta (v1, v2) do grafo colocando AN em sua celula (representando ausencia de aresta).
  Se a aresta existia, retorna true,
  caso contrario retorna false.
*/
bool removeAresta(int v1, int v2, TipoGrafo *grafo);

/*
   bool listaAdjVazia(int v, TipoGrafo* grafo):
   Retorna true se a lista de adjacencia (de vertices adjacentes) do vertice v é vazia, e false caso contrário.
*/
bool listaAdjVazia(int v, TipoGrafo* grafo);

/*
   TipoApontador primeiroListaAdj(int v, TipoGrafo* grafo):
   Retorna o primeiro vertice da lista de adjacencia de v
   ou VERTICE_INVALIDO se a lista de adjacencia estiver vazia.
*/
TipoApontador primeiroListaAdj(int v, TipoGrafo* grafo);

/*
   TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual):
   Trata-se de um iterador sobre a lista de adjacência do vertice v.
   Retorna o proximo vertice adjacente a v, partindo do vertice "atual" adjacente a v
   ou VERTICE_INVALIDO se a lista de adjacencia tiver terminado sem um novo proximo.
*/
TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual);

/*
    void imprimeGrafo(TipoGrafo* grafo):
    Imprime a matriz de adjacencia do grafo.
    Assuma que cada vértice e cada peso de aresta são inteiros de até 2 dígitos.
*/
void imprimeGrafo(TipoGrafo* grafo);

/* Nao precisa fazer nada para matrizes de adjacencia */
void liberaGrafo(TipoGrafo* grafo);

/* int verticeDestino(TipoApontador p):
   retorna o vertice destino da aresta apontada por p */
int verticeDestino(TipoApontador p, TipoGrafo* grafo);

double obtemPesoInstantaneo (TipoApontador p);

