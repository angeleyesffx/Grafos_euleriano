#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_FILA  100

#define NONE  -1
#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct aresta{
	int nome;
	struct aresta *prox;
}Aresta;

typedef struct vert{
	int nome;
	int cor;
	Aresta *prim;
}Vertice;



void imprimeGrafo(Vertice G[], int ordem);
void criaGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
int  calcumaTamanho(Vertice G[], int ordem);
void percorreGrafo(Vertice G[], int vInicial, int ordem);


typedef struct queue{
    int vector[MAX_FILA];
    int front;
    int back;
    int tam;
}Queue;

void initializeEmpty(Queue *f);
int isEmpty(Queue f);
void enqueue(Queue *f, int elem);
int dequeue(Queue *f);

void initializeEmpty(Queue *Q){
    Q->front = Q->back= 0;
}
int isEmpty(Queue Q){
    return Q.back == Q.front;
}

void enqueue(Queue *Q, int elem){ 
     Q->vector[Q->back] = elem;
     Q->back += 1;
     if(Q->back == MAX_FILA) {
        Q->back = 0;
     }
}
int dequeue(Queue *Q){
	if(Q->front == Q->back) {
       printf("fila vazia.\n");
       exit(1);
    }
    int back = Q->vector[Q->front];
    Q->front += 1;
    if(Q->front == MAX_FILA) {
       Q->front = 0;
    }
    return back;              
 }
 
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
	int i;					
	Queue *q = (Queue*) malloc(sizeof(Queue));	
	q->front = NULL;		
	q->back = NULL;
	
    for (i=0; i<ordem; i++){
		int j;
		Aresta *aux= G[i].prim;
		for(j=0; aux != NULL; aux= aux->prox, j++);
	    	G[j].cor = BRANCO;	
	}
	
    G[vInicial].cor = CINZA;
    enqueue(q, G[vInicial].nome);
    while(q != 0){
	    dequeue(q);
	    int i=0;
	    i++;
		printf(" %d vertice %3d\n", i,q->back);
		printf("cor %3d\n", G[vInicial].cor);
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
