#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_FILA  100

#define NONE  -1
#define BRANCO 0
#define CINZA  1
#define PRETO  2
#define MAX_QUEUE  100

typedef struct aresta{
	int nome;
	struct aresta *prox;
}Aresta;

typedef struct vert{
	int nome;
	int cor;
	Aresta *prim;
}Vertice;


typedef struct queue{
    int vector[MAX_QUEUE];
    int front;
    int back;
}Queue;

void initializeEmpty(Queue *f);
int isEmpty(Queue f);
void enqueue(Queue *f, int elem);
int dequeue(Queue *f);
void imprimeGrafo(Vertice G[], int ordem);
void criaGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
int  calcumaTamanho(Vertice G[], int ordem);
void initializeEmpty(Queue *f);
int isEmpty(Queue f);
void enqueue(Queue *f, int elem);
int dequeue(Queue *f);
void percorreGrafo(Vertice G[], int vInicial, int ordem);


void criaGrafo(Vertice **G, int ordem){
	int i;
	*G= (Vertice*) malloc(sizeof(Vertice)*ordem);
	
	for(i=0; i<ordem; i++){
		(*G)[i].nome= i;
		(*G)[i].cor= NONE;
		(*G)[i].prim= NULL;
	}
}

int acrescentaAresta(Vertice G[], int ordem, int v1, int v2){
	if (v1<0 || v1 >= ordem)
	   return 0;
	if (v2<0 || v2 >= ordem)
	   return 0;
	
	Aresta *A1= (Aresta *) malloc(sizeof(Aresta));
	A1->nome= v2;
	A1->prox= G[v1].prim;
	G[v1].prim= A1;

	Aresta *A2= (Aresta *) malloc(sizeof(Aresta));
	A2->nome= v1;
	A2->prox= G[v2].prim;
	G[v2].prim= A2;
}


int  calcumaTamanho(Vertice G[], int ordem){
	int i;
	int totalArestas=0;
	
	for (i=0; i<ordem; i++){
		int j;
		Aresta *aux= G[i].prim;
		for(j=0; aux != NULL; aux= aux->prox, j++);
		totalArestas += j;	
	}
	return totalArestas/2 + ordem;
}

void imprimeGrafo(Vertice G[], int ordem){
	int i;

	for (i=0; i<ordem; i++){
		printf("\nV%d: ", i);
		Aresta *aux= G[i].prim;
		for( ; aux != NULL; aux= aux->prox)
			printf("%3d", aux->nome);
	}
	printf("\n\n");
}

void percorreGrafo(Vertice G[], int vInicial, int ordem){
	for (int i=0; i<ordem; i++){
		G[i].cor = BRANCO;
		}
	G[vInicial].cor	= CINZA;
	for (int i=0; i<ordem; i++){
		
		printf("vertice %3d\n", G[i].nome);
		printf("cor %3d\n", G[i].cor);
		}
}

int main(int argc, char *argv[]) {
	Vertice *G;
	int ordemG= 10;

		
	criaGrafo(&G, ordemG);
	acrescentaAresta(G,ordemG,3,4);
	acrescentaAresta(G,ordemG,4,2);
	acrescentaAresta(G,ordemG,5,4);
	acrescentaAresta(G,ordemG,2,3);
	acrescentaAresta(G,ordemG,3,7);
	
	printf("\nTamanho: %d\n",calcumaTamanho(G, ordemG));

	imprimeGrafo(G, ordemG);
    percorreGrafo(G, 1, ordemG);
	return 0;
}
