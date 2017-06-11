#include "headers/array.h"
#include <string.h>
#include <stdlib.h>

/* Funções privadas ao módulo. */
static void swap(Array a, int x, int y);
static void sortInf(Array a);

struct inf{
	long info;
	long total;
};

/* Estrutura do Array. */
struct array{    
    int size;               /* Tamanho alocado para a Array.*/
    int used;               /* Número de elementos da Array. */
    struct inf *values;     /* Array de elementos que formam a Array. */
};

Array initArray(int size){
    Array a = malloc(sizeof(struct array));
    a->size = size;
    a->used = 0;
    a->values = malloc(size*sizeof(struct inf));
    return a;
}

int insertInf(Array a, long info, long total){
    if (a->used == a->size) {
        a->values = realloc(a->values, 2*(a->size)*sizeof(struct inf)); 
        a->size *= 2;
    }
    a->values[a->used].info = info;
    a->values[a->used].total = total;
    (a->used)++;
    sortInf(a);
    return 1;
}


int findIndex(long id, Array a){
	int i;
	for(i=0;i<a->used;i++){
		if(id == getInfInfo(a,i)) return i;
	}
	return -1;
}


/* GETS E SETS */

int getArrayUsed(Array a){
    int used = a->used;
    return used;
}

long getInfTotal(Array a, int i){
    long total = a->values[i].total;
    return total;
}

long getInfInfo(Array a, int i){
    long info = a->values[i].info;
    return info;
}

void setInfTotal(Array a, int index, long i){
    a->values[index].total += i;
}

/* Função responsável por fazer swap numa Array. */
static void swap(Array a, int x, int y){
    struct inf t = a->values[x];
    a->values[x] = a->values[y];
    a->values[y] = t;
}

/* Função que faz Bubble-Up na Array, questões de algoritmo. */
static void sortInf(Array a){
    int i;
    long x, y;
    long b, c;

    for(i=a->used-1;i>0;i--){
        x = getInfTotal(a, i);
        y = getInfTotal(a, i-1);
        if(y<x) swap(a, i-1, i);
        if(x == y){
            b = getInfInfo(a, i);
            c = getInfInfo(a, i-1);
            if(c > b) swap(a, i-1, i);
        }
    }
}
