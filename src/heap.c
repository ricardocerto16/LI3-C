#include "headers/heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PARENT(i) (i-1)/2               /* Determina o índice do Pai de um determinado Nodo. */
#define LEFT(i) 2*i + 1                 /* Determina o Nodo à esquerda de um determinado Nodo. */   
#define RIGHT(i) 2*i + 2 				/* Determina o Nodo à direita de um determinado Nodo */

/* Funções privadas ao módulo. */
static void swap(Heap h, int a, int b);
static void bubbleUp(Heap h, int i);
//static void bubbleDown(Heap h, int N);

/* Estrutura de um elemento do parsing */
struct elem{
    long idCont;
    char* nameCont;
    int totalWords;
    int nbytes;
    char* timestamp;
    long revisionId;
    char* title; 
};

/* Estrutura da Heap. */
struct heap{    
    int size;               /* Tamanho alocado para a Heap.*/
    int used;               /* Número de elementos da Heap. */
    long total;             /* Número total de revisions */
    struct elem *values;    /* Array de elementos que formam a Heap. */
};

/* Função que inicia a estrutura dados */
Heap initHeap(int size) {
	Heap h = malloc(sizeof(struct heap));
    h->size = size;
    h->used = 0;
    h->total = 0;
    h->values = malloc(size*sizeof(struct elem));
	return h;
}

/* Insere numa Heap. */
int insertHeap(Heap h, long a, char* b, long c, long d, char* e, long f, char* g){
    if (h->used == h->size) {
        h->values = realloc(h->values, 2*(h->size)*sizeof(struct elem)); 
        h->size *= 2;
    }
    h->values[h->used].idCont = a;
    h->values[h->used].nameCont = b;
    h->values[h->used].totalWords = c;
    h->values[h->used].nbytes = d;
    h->values[h->used].timestamp = e;
    h->values[h->used].revisionId = f;
    h->values[h->used].title = g;
    (h->total)++;
    (h->used)++;
    bubbleUp(h, (h->used)-1);
    return 1;
}

/* Gets */
int getHeapUsed(Heap h){
    return h->used;
}

long getHeapTotal(Heap h){
    return h->total;
}

long getIdCont(Heap h, int i){
	long aux = h->values[i].idCont;
	return aux;
}

char* getNameCont(Heap h, int i){
	char* aux=malloc((strlen(h->values[i].nameCont)+1)*sizeof(char));
	strcpy(aux,h->values[i].nameCont);
	return aux;
    free(aux);
}

long getNBytes(Heap h, int i){
    int aux = h->values[i].nbytes;
    return aux;
}

long getTotalWords(Heap h, int i){
	int aux = h->values[i].totalWords;
	return aux;
}

char* getTimestamp(Heap h, int i){
	char* aux=malloc((strlen(h->values[i].timestamp)+1)*sizeof(char));
	strcpy(aux,h->values[i].timestamp);
	return aux;
}

long getRevisionId(Heap h, int i){
	long aux = h->values[i].revisionId;
	return aux;
}

char * getTitle(Heap h, int i){
	char* aux = malloc((strlen(h->values[i].title)+1)*sizeof(char));
    strcpy(aux,h->values[i].title);
	return aux;
    free(aux);
}

void setHeapTotal(Heap h, long i){
    h->total += i;
}

void freeHeap(Heap h){
    int i;
    for(i=0;i<h->used;i++){
        free(h->values[i].nameCont);
        free(h->values[i].timestamp);
        free(h->values[i].title); 
    }
    free(h);
}

/* Função responsável por fazer swap numa Heap. */
static void swap(Heap h, int a, int b){
    struct elem t = h->values[a];
    h->values[a] = h->values[b];
    h->values[b] = t;
}

/* Função que faz Bubble-Up na Heap, questões de algoritmo. */
static void bubbleUp(Heap h, int i){
    while (i!=0 && h->values[i].revisionId > h->values[PARENT(i)].revisionId) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }    
}

/*void show(Heap article, int i){
    printf("----------------------------------\n");
    printf("%ld\n", article->values[i].idCont);
    printf("%s\n", article->values[i].nameCont);
    printf("%d\n", article->values[i].totalWords);
    printf("%s\n", article->values[i].timestamp);
    printf("%ld\n", article->values[i].revisionId);
    printf("%s\n", article->values[i].title);
}*/