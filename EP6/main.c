/*
    Nome: Guilherme Oliveira Goularte
    n°USP: 10387748
*/

#include<stdio.h>
#include<stdlib.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   100
#define TRUE            1
#define FALSE           0

typedef struct S{
    struct S* prox;
    int IDVertice;
}NO;

//IMPLEMENTAÇÃO LISTA

void InicializaLista (NO* raiz){
    raiz->prox = NULL;
    raiz->IDVertice = -1;
}

void InsereLista(NO* topo, int valor){
    if(valor <= 0){
        printf("Valor de vértice inválido!!");
        return;
    }
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->IDVertice = valor;
    novo->prox = topo;
    topo = novo;
}

void RemoveDaLista(NO* topo){
    printf("%d\n",topo->IDVertice);
    if(topo->prox){
        NO* aux = topo->prox;
        free(topo);
        topo = aux;
    }else{
        topo = NULL;
    }
}

//IMPLEMENTAÇÃO LISTA

typedef int TipoValorVertice;

typedef struct TipoItem {
    TipoValorVertice Vertice;
}TipoItem;

typedef struct TipoCelula* TipoApontador;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
}TipoCelula;

typedef struct TipoLista {
    TipoApontador Primeiro, Ultimo;
}TipoLista;

typedef struct TipoGrafo {
    TipoLista Adj[MAXNUMVERTICES + 1];
    int NumVertices;
    int NumArestas;
}TipoGrafo;

typedef short TipoValorTempo;

typedef enum {
    branco, cinza, preto
}TipoCor;

short i;
int FimListaAdj;
TipoValorVertice Adj;
TipoGrafo Grafo;
TipoItem x;

void FLVazia(TipoLista *Lista){
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

char Vazia(TipoLista Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem *x, TipoLista *Lista){
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoGrafo *Grafo){
    TipoItem x;
    x.Vertice = *V2;
    Insere(&x, &Grafo->Adj[*V1]);
}

void FGVazio(TipoGrafo *Grafo){
    short i;
    for (i = 0; i <= Grafo->NumVertices; i++)
        FLVazia(&Grafo->Adj[i]);
}

char ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo){
    TipoApontador Aux;
    char EncontrouAresta = FALSE;
    Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
    while (Aux != NULL && EncontrouAresta == FALSE){
        if (Vertice2 == Aux->Item.Vertice)
            EncontrouAresta = TRUE;
        Aux = Aux->Prox;
    }
    return EncontrouAresta;
}

char ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo){
    return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo){
    return (Grafo->Adj[*Vertice].Primeiro->Prox);
}

void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj,
             TipoApontador *Prox, char *FimListaAdj){
    *Adj = (*Prox)->Item.Vertice;
    *Prox = (*Prox)->Prox;
    if (*Prox == NULL)
        *FimListaAdj = TRUE;
}

void ImprimeLista(TipoLista Lista){
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL){
        printf("%3d ", Aux->Item.Vertice);
        Aux = Aux->Prox;
    }
}

void ImprimeGrafo(TipoGrafo *Grafo){
    short i;
    for (i = 1; i <= Grafo->NumVertices; i++){
        printf("Vertice%2d:", i);
        if (!Vazia(Grafo->Adj[i]))
            ImprimeLista(Grafo->Adj[i]);
        putchar('\n');
    }
}

void VisitaDfs(TipoValorVertice u, TipoGrafo *Grafo, TipoValorTempo* Tempo,
               TipoValorTempo* d, TipoValorTempo* t, TipoCor* Cor, short* Antecessor, NO* lista){

    char FimListaAdj;

    TipoApontador Aux;
    TipoValorVertice v;

    Cor[u] = cinza;
    (*Tempo)++;
    d[u] = (*Tempo);

    if (!ListaAdjVazia(&u, Grafo)){
        Aux = PrimeiroListaAdj(&u, Grafo);
        FimListaAdj = FALSE;
        while (!FimListaAdj){
            ProxAdj(&u, &v, &Aux, &FimListaAdj);
            if (Cor[v] == branco){
                Antecessor[v] = u;
                VisitaDfs(v, Grafo, Tempo, d, t, Cor, Antecessor, lista);
            }
        }
    }

    InsereLista(lista,u);

    Cor[u] = preto;
    (*Tempo)++;
    t[u] = (*Tempo);
}

void EscreveSaida(TipoGrafo *grafo, TipoValorTempo d[MAXNUMVERTICES + 1],
                  TipoValorTempo t[MAXNUMVERTICES + 1], short antecessor[MAXNUMVERTICES+1]){

    printf("Vertice | Pai | Tempo Descoberta | Tempo Finalização\n");
    int j;
    for (j = 1; j <= grafo->NumVertices; j++)
        printf("%d | %d | %d | %d\n",j,antecessor[j],d[j],t[j]);
}

void BuscaEmProfundidade(TipoGrafo *Grafo, NO* lista){
    TipoValorVertice x;
    TipoValorTempo Tempo;
    TipoValorTempo d[MAXNUMVERTICES + 1], t[MAXNUMVERTICES + 1];

    TipoCor Cor[MAXNUMVERTICES+1];
    short Antecessor[MAXNUMVERTICES+1];

    Tempo = 0;
    for (x = 0; x <= Grafo->NumVertices; x++){
        Cor[x] = branco;
        Antecessor[x] = -1;
    }
    for (x = 1; x <= Grafo->NumVertices; x++){
        if (Cor[x] == branco)
            VisitaDfs(x, Grafo, &Tempo, d, t, Cor, Antecessor, lista);
    }

    EscreveSaida(Grafo,d,t,Antecessor);
}

int main(int argc, char **argv){

    FILE* entrada = fopen("Entrada.txt","rt");

    int vertices = 0;
    int arestas;

    fscanf(entrada,"%d\n%d\n",&vertices,&arestas);

    Grafo.NumVertices = vertices;
    Grafo.NumArestas = 0;
    FGVazio(&Grafo);

    TipoValorVertice V1, V2;

    for (i = 0; i < arestas; i++){

        fscanf(entrada,"%d %d\n",&V1,&V2);

        Grafo.NumArestas++;
        InsereAresta(&V1, &V2, &Grafo);
        if(V1 != V2)
            InsereAresta(&V2, &V1, &Grafo);
    }

    fclose(entrada);

    NO lista;
    InicializaLista(&lista);

    //ImprimeGrafo(&Grafo);
    BuscaEmProfundidade(&Grafo, &lista);

    return 0;
}
