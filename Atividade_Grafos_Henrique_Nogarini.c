#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;


typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo{
 int vertices;
 int arestas;
 VERTICE *adj;
}GRAFO;

GRAFO *criaGrafo (int v){
 int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g -> vertices = v;
    g -> arestas = 0;
    g -> adj = (VERTICE *)malloc(v*sizeof(VERTICE));

    for (i=0; i<v; i++){
        g -> adj[i].cab=NULL;
    }
    return (g);
}

ADJACENCIA *criadAdj(int v, int peso){
ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
temp -> vertice =v;
temp -> peso = peso;
temp -> prox = NULL;
return(temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
if(!gr) return(false);
if((vf<0)||(vf>=gr->vertices))return(false);
if((vi<0)||(vf>=gr->vertices))return(false);

ADJACENCIA *novo = criadAdj(vf,p);

novo->prox = gr->adj[vi].cab;
gr->adj[vi].cab=novo;
gr->arestas++;
return (true);
}


void imprime(GRAFO *gr){

printf("Vertices: %d. Arestas: %d \n",gr->vertices,gr->arestas);
int i;

for(i = 0; i<gr->vertices; i++){
    printf("v%d:",i+1);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad){
        printf("v%d(%d) ",ad->vertice+1,ad->peso);
        ad=ad->prox;
    }
    printf("\n");

	}
}

void Matriz(GRAFO *gr){ 
printf("\n\nMatriz de Adjacencia:\n");
    for (int i = 0; i < gr->vertices; i++) {
        for (int j = 0; j < gr->vertices; j++) {
            int adjacencia = 0;
            ADJACENCIA *ad = gr->adj[i].cab;
            while (ad) {
                if (ad->vertice == j) {
                    adjacencia = ad->peso;
                }
                ad = ad->prox;
            }
            printf("%d\t", adjacencia);
        }
        printf("\n");
    }
}

int calculaValorTotalCaminho(GRAFO* grafo, int* caminho, int numVertices) {
    int valorTotal = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int verticeInicial = caminho[i] - 1; // Convertemos o vertice do caminho para um indice (subtraindo 1)
        int verticeFinal = caminho[i + 1] - 1; // O mesmo para o vertice seguinte
        ADJACENCIA* adjacencia = grafo->adj[verticeInicial].cab;
        bool encontrou = false;

        while (adjacencia) {
            if (adjacencia->vertice == verticeFinal) {
                valorTotal += adjacencia->peso;
                encontrou = true;
                break;
            }
            adjacencia = adjacencia->prox;
        }

        if (!encontrou) {
		// Caso a aresta entre os vertices nao for encontrada, o caminho é devolvido como inválido.
            return -1;
        }
    }

    return valorTotal;
}

int somaCaminhosDFS(GRAFO *grafo, int inicio, int destino, int *visitados) {
    if (inicio == destino) {
        return 0;
    }

    visitados[inicio] = 1;
    ADJACENCIA *adjacencia = grafo->adj[inicio].cab;
    int somaCaminhos = 0;

    while (adjacencia != NULL) {
        int proximoVertice = adjacencia->vertice;
        int pesoAresta = adjacencia->peso;

        if (!visitados[proximoVertice]) {
            somaCaminhos += pesoAresta + somaCaminhosDFS(grafo, proximoVertice, destino, visitados);
        }

        adjacencia = adjacencia->prox;
    }

    visitados[inicio] = 0;
    return somaCaminhos;
}

int somaCaminhos(GRAFO *grafo, int inicio, int destino) {
    int *visitados = (int *)malloc(grafo->vertices * sizeof(int));
    for (int i = 0; i < grafo->vertices; i++) {
        visitados[i] = 0;
    }
    int soma = somaCaminhosDFS(grafo, inicio, destino, visitados);
    free(visitados);
    return soma;
}


int main (){

	GRAFO * grafo = criaGrafo(5);
	
	// Criar Arestas
	criaAresta(grafo, 0,0,0);
	criaAresta(grafo, 0,2,0);
	criaAresta(grafo, 1,2,0);
	criaAresta(grafo, 1,3,0);
	criaAresta(grafo, 1,4,0);
	criaAresta(grafo, 2,3,0);
	criaAresta(grafo, 3,4,0);
	
	//Lista de adjacencia
	printf("\nImpressão do grafo em lista de adjacencia:\n");
	imprime(grafo);
	
	//Matriz de adjacencia
	Matriz(grafo);
	
	//Segundo Grafo
	printf("\n");
	for (int i = 0; i < 25; i++)
	        if (i < 24)
	            printf("-");
	        else
	            printf("\n");
	
	GRAFO *grafoOrientado = criaGrafo(5);
	
	criaAresta(grafoOrientado, 0, 0, 2); 
	criaAresta(grafoOrientado, 0, 2, 7);
	criaAresta(grafoOrientado, 2, 1, 5);
	criaAresta(grafoOrientado, 2, 3, 10);
	criaAresta(grafoOrientado, 3, 1, 9);
	criaAresta(grafoOrientado, 3, 4, 1);
	criaAresta(grafoOrientado, 4, 1, 12);
	
	printf("Lista de Adjacencia (Grafo Orientado e Ponderado):\n");
	imprime(grafoOrientado);
	Matriz(grafoOrientado);
	
	//Soma dos caminhos {0,4}
	printf("\nValor total do caminho: %d ",somaCaminhos(grafoOrientado,0,4));
	    
	free(grafo->adj);
	free(grafo);
	free(grafoOrientado->adj);
	free(grafoOrientado);
	
    return 0;
}
