/*
    Guilherme Oliveira Goularte
    10387748

    Vinícius Roque
    9779259
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 10
#define MAX 2147483647

typedef struct {
    int pesos [N][N];
    bool orientacao [N][N];
}GRAFO_BIPARTIDO;

bool matching [2*N], alcancaveis [2*N];
int potencial [2*N];
bool restantesS[N], restantesT[N];
int custoMin;

void InicializaGrafo (GRAFO_BIPARTIDO* g){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            g->orientacao[i][j] = true;
            g->pesos[i][j] = 0;
        }
    }
}

void DFSTVisit (int x, GRAFO_BIPARTIDO* g, int cor[2*N], int pai[2*N], bool isS){
    cor[x] = 2;
    int i;
    if (isS){
        for (i = 0; i < N; i++){
            int y = i+N;
            int custo = (int)(g->pesos[x][i] - potencial[x] - potencial[y]);
            if(cor[y] == 1 && g->orientacao[x][i] && custo == 0){
                pai[y] = x;
                alcancaveis[y] = true;
                DFSTVisit(y,g,cor,pai, false);
            }
        }
    }else{
        int y = x-N;
        for (i = 0; i < N; i++){
            int custo = (int)(g->pesos[i][y] - potencial[i] - potencial[x]);
            if(cor[i] == 1 && g->orientacao[i][y] && custo == 0){
                pai[i] = x;
                alcancaveis[i] = true;
                DFSTVisit(i,g,cor,pai,true);
            }

        }
    }
    cor[x] = 3;
}

void DFST (int x, GRAFO_BIPARTIDO* g, bool restantesT[N]){
    //Setup do DFST, 1 = branco, 2 = cinza, 3 = preto
    int i;
    int pai[2*N], cor[2*N];
    for (i = 0; i < 2*N; i++){
        pai[i] = -1;
        cor[i] = 1;
    }

    DFSTVisit(x,g,cor,pai,true);

    for (i = N; i < 2*N; i++){
        if(pai[i] > -1 && restantesT[i-N]){
            int x1 = i;
            int x2 = pai[i];
            while (x2 > -1){
                g->orientacao[x2%10][x1%10] = !g->orientacao[x2][x1];
                x1 = x2;
                x2 = pai[x2];
            }
        }
    }
}

void MetodoHungaro(GRAFO_BIPARTIDO* g, FILE* saida){
    int i,j;
    for(i = 0; i < 2*N; i++){
        matching[i] = false;
        alcancaveis[i] = false;
        potencial[i] = 0;
    }

    for(i = 0; i < N; i++){
        restantesS[i] = true;
        restantesT[i] = true;
    }

    bool matchingIncompleto = true;

    while(matchingIncompleto){
        for (i = 0; i < N; i++){
            if (matching[i]){
                restantesS[i] = false;
                alcancaveis[i] = false;
            }
            else{
                restantesS[i] = true;
                alcancaveis[i] = true;
            }
        }
        for (i = N; i < 2*N; i++){
            if (matching[i])
                restantesT[i-N] = false;
            else
                restantesT[i-N] = true;
        }

        for (i = 0; i < N; i++){
            if (restantesS[i]&&alcancaveis[i])
                DFST(i,g,restantesT);
        }

        custoMin = 0;
        for (i = 0; i < 2*N; i++){
            matching[i] = false;
        }
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                if(!g->orientacao[i][j]){
                    matching[i] = true;
                    matching[j+N] = true;
                    custoMin += g->pesos[i][j];
                    break;
                }
            }
        }

        int delta = MAX;
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                if(alcancaveis[i]&&alcancaveis[j+N]){
                    int alfa = g->pesos[i][j] - potencial[i] - potencial[j+N];
                    if(alfa < delta)
                        delta = alfa;
                }
            }
        }
        for (i = 0; i < N; i++){
            if (alcancaveis[i])
                potencial[i] += delta;
            if (alcancaveis[i+N])
                potencial[i+N] -= delta;
        }

        matchingIncompleto = false;
        for(i = 0; i < 2*N; i++){
            if (!matching[i]){
                matchingIncompleto = true;
                break;
            }
        }
    }

    fprintf(saida, "%d\n",custoMin);
}

int main(int argc, char** argv){
    FILE* entrada = fopen("entrada.txt","rt");
    FILE* saida = fopen("saida.txt","rt");

    GRAFO_BIPARTIDO g;
    InicializaGrafo(&g);

    int i,j;

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            fscanf(entrada,"%d ",&g.pesos[i][j]);
        }
    }

    MetodoHungaro(&g,saida);

    return 0;
}

/*
    Resultados:

    a) 6
    b) 34
*/
