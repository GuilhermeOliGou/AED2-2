#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   100
#define FALSE           0
#define TRUE            1
#define INFINITO        INT_MAX

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

typedef struct TipoFila {
    TipoApontador Frente, Tras;
}TipoFila;

typedef struct TipoGrafo {
    TipoLista Adj[MAXNUMVERTICES + 1];
    int NumVertices;
    int NumArestas;
}TipoGrafo;

typedef short  TipoValorTempo;

typedef enum {
    branco, cinza, preto
}TipoCor;

int i;
short FimListaAdj;
TipoValorVertice Adj;
TipoGrafo Grafo;
TipoItem x;

/*--Entram aqui os operadores do Programa 2.4--*/
void FLVazia(TipoLista *Lista){
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

short ListaVazia(TipoLista Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem *x, TipoLista *Lista){
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
}

 void FFVazia(TipoFila *Fila){
    Fila->Frente = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
}

short FilaVazia(TipoFila Fila){
    return (Fila.Frente == Fila.Tras);
}

void Enfileira(TipoItem x, TipoFila *Fila){
    Fila->Tras->Prox =(TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->Item = x;
    Fila->Tras->Prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoItem *Item){
    TipoApontador q;
    if (FilaVazia(*Fila)){
        printf(" Erro   fila esta  vazia\n");
        return;
    }
    q = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;
    *Item = Fila->Frente->Item;
    free(q);
}

void ImprimeFila(TipoFila Fila){
    TipoApontador Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL){
        printf("%3d ", Aux->Item.Vertice);
        Aux = Aux->Prox;
    }
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoGrafo *Grafo){
    TipoItem x;
    x.Vertice = *V2;
    Insere(&x, &Grafo->Adj[*V1]);
}

void FGVazio(TipoGrafo *Grafo){
    short i;
    for (i = 0; i <= Grafo->NumVertices - 1; i++)
        FLVazia(&Grafo->Adj[i]);
}

short ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo){
    TipoApontador Aux;
    short EncontrouAresta = FALSE;
    Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
    while (Aux != NULL && EncontrouAresta == FALSE){
        if (Vertice2 == Aux->Item.Vertice)
            EncontrouAresta = TRUE;
        Aux = Aux->Prox;
    }
    return EncontrouAresta;
}

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo){
    return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo){
    return (Grafo->Adj[*Vertice].Primeiro->Prox);
}

void ProxAdj(TipoValorVertice *Vertice, TipoValorVertice *Adj, TipoApontador* Prox, short *FimListaAdj){
    *Adj = (*Prox)->Item.Vertice;
    *Prox = (*Prox)->Prox;
    if (*Prox == NULL)
    *FimListaAdj = TRUE;
}

void ImprimeLista(TipoLista Lista){
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL){
        printf("%d ", Aux->Item.Vertice);
        Aux = Aux->Prox;
    }
}

void ImprimeGrafo(TipoGrafo *Grafo){
    int i;
    for (i = 0; i <= Grafo->NumVertices - 1; i++){
    printf("Vertice %2d: ", i);
    if (!ListaVazia(Grafo->Adj[i]))
        ImprimeLista(Grafo->Adj[i]);
    putchar('\n');
    }
}

void VisitaBfs(TipoValorVertice u, TipoGrafo *Grafo, int *Dist, TipoCor *Cor, int *Antecessor){
    TipoValorVertice v;
    TipoApontador Aux;
    short FimListaAdj;

    TipoItem Item;
    TipoFila Fila;

    Cor[u] = cinza;
    Dist[u] = 0;

    FFVazia(&Fila);
    Item.Vertice = u;
    Enfileira(Item, &Fila);
    printf("Visita origem%2d cor: cinza F:", u);
    ImprimeFila(Fila);
    getchar();

    while (!FilaVazia(Fila)){
        Desenfileira(&Fila, &Item);
        u = Item.Vertice;
        if (!ListaAdjVazia(&u, Grafo)){
            Aux = PrimeiroListaAdj(&u, Grafo);
            FimListaAdj = FALSE;
            while (FimListaAdj == FALSE){
                ProxAdj(&u, &v, &Aux, &FimListaAdj);
                if (Cor[v] != branco) continue;

                Cor[v] = cinza; Dist[v] = Dist[u] + 1;
                Antecessor[v] = u;
                Item.Vertice = v;
                Enfileira(Item, &Fila);
            }
        }
        Cor[u] = preto;
        printf("Visita%2d Dist%2d cor: preto F:", u, Dist[u]);
        ImprimeFila(Fila); getchar();
    }
}

void BuscaEmLargura(TipoGrafo *Grafo){
    TipoValorVertice x;
    int Dist[MAXNUMVERTICES + 1];
    TipoCor Cor[MAXNUMVERTICES + 1];
    int Antecessor[MAXNUMVERTICES + 1];
    for (x = 0; x <= Grafo->NumVertices - 1; x++){
        Cor[x] = branco;
        Dist[x] = INFINITO;
        Antecessor[x] = -1;
    }
    for (x = 0; x <= Grafo->NumVertices - 1; x++){
        if (Cor[x] == branco)
            VisitaBfs(x, Grafo, Dist, Cor, Antecessor);
    }
}

int main(int argc, char *argv[]){

    FILE* entrada = fopen("Entrada","rt");
    FILE* saida = fopen("Saida","rt");

    int NVertices;
    int NArestas;

    fscanf(entrada,"%d\n%d\n",&NVertices,&NArestas);

    /*
    printf("No. vertices:");
    scanf("%d%*[^\n]", &NVertices);
    printf("No. arestas:");
    scanf("%d%*[^\n]", &NArestas);
    */

    Grafo.NumVertices = NVertices;
    Grafo.NumArestas = 0;
    FGVazio(&Grafo);

    TipoValorVertice V1, V2;

    for (i = 0; i <= NArestas - 1; i++){
        printf("Insere V1 -- V2 -- Peso:");

        fscanf(entrada,"%d %d",&V1,&V2);

        /*
        scanf("%d*[^\n]", &V1);
        scanf("%d*[^\n]", &V2);
        */

        getchar();
        Grafo.NumArestas++;
        InsereAresta(&V1, &V2, &Grafo);   /*1 chamada : G direcionado*/
        InsereAresta(&V2, &V1, &Grafo);   /*2 chamadas: G nao-direcionado*/
    }

    ImprimeGrafo(&Grafo);
    getchar();
    BuscaEmLargura(&Grafo);
    getchar();
    return 0;
}
