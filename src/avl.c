#include "headers/avl.h"
#include "headers/heap.h"
#include "../interface.h"

#define SIZE_title 7
#define LEFT -2
#define RIGHT 2

/* Estrutura de um nodo da Avl. */
struct avl {
	long idArticle; 								/* String com informação. */
	int height;									    /* Altura, auxiliar ao algoritmo. */
	void* info;								        /* Apontador para uma estrutura, se necessário. */
	struct avl *left, *right;				        /* Apontadores para outras Avl's (esquerda e direita). */
};

/* Estrutura TAD_istruct com uma Avl e um contador de elementos da mesma. */
struct TCD_istruct {
	int total;								/* Total de elementos na estrutura Avl. */
	Avl avl;								/* Estrutura Avl que lhe corresponde. */
};


/* Funções privadas ao módulo. */
static Avl rotateRight(Avl);
static Avl rotateLeft(Avl);
static int maior (int a, int b);
static Avl actualizarAltura(Avl,Avl);
//static Avl insertINFO(Avl,long,void*);

/* Função auxiliar que determina o maior de dois dados inteiros. */
static int maior(int a, int b){
	if(a>b)return a;
	else return b;
}

/* Função auxiliar responsável por actualizar a altura de uma Avl. */
static Avl actualizarAltura(Avl a, Avl b){
	a->height = maior(heightAvl(a->left), heightAvl(a->right))+1;
	b->height = maior(heightAvl(b->left), heightAvl(b->right))+1;
	return b;
}

/* Função auxiliar ao algoritmo que faz a rotação à direita de parte da Avl. */
static Avl rotateRight(Avl a) {
	Avl aux;
	aux = a->left;
	a->left=aux->right;
	aux->right=a;
	aux=actualizarAltura(a,aux);
	return aux;
}

/* Função auxiliar ao algoritmo que faz a rotação à esquerda de parte da Avl. */
static Avl rotateLeft(Avl a) {
	
	Avl aux;
	aux = a->right;
	a->right=aux->left;
	aux->left=a;
	aux=actualizarAltura(a,aux);
	return aux;
}

/* Função de inicialização de uma estrutura TAD_istruct */
TAD_istruct initMyAvl(){
	TAD_istruct a = malloc(sizeof(struct TCD_istruct));
	a->avl = initAvl();
	a->total = 0;
	return a;
}

/* Função de inicialização de uma estrutura Avl. */
Avl initAvl(){
	return NULL;
}

/* Função que retorna a altura de uma Avl. */
int heightAvl(Avl a){	
	if(a==NULL) return 0;
	else return a->height;
}

/* Inserir numa Avl. */
Avl insert(Avl estrutura, long id,void* info) {
	
	int bal,HL,HR;

	if(estrutura == NULL){
		estrutura= (Avl)malloc(sizeof(struct avl));
		estrutura->idArticle = id;
		estrutura->left=NULL;
		estrutura->right=NULL;
		estrutura->height=0;
		estrutura->info=info;
	}
	else {
		if( estrutura->idArticle > id){
			estrutura->left=insert(estrutura->left,id,info);

		}
		else if( estrutura->idArticle < id ){
			estrutura->right=insert(estrutura->right,id,info);
		}

		HL = heightAvl(estrutura->left);
		HR = heightAvl(estrutura->right);

		estrutura->height = maior(HL,HR)+1;

		bal = HL - HR;

		if(bal>1) bal=RIGHT;
		if(bal<-1) bal=LEFT;

		switch (bal){

			case 2: if( id < estrutura->left->idArticle ) 
						return rotateRight(estrutura);
					else if ( id > estrutura->left->idArticle ){
						estrutura->left =  rotateLeft(estrutura->left);
						return rotateRight(estrutura);
					}
					break;

			case -2: if(id > estrutura->right-> idArticle)
						return rotateLeft(estrutura);
					else if ( id < estrutura->right-> idArticle ){
						estrutura->right = rotateRight(estrutura->right);
						return rotateLeft(estrutura);
					}	
					break;
		}

	}
	return estrutura;
}

/* Inserir numa TAD_istruct. */
TAD_istruct insertMyAvl(TAD_istruct a,long id,void* info){

	if(!a) a = init();
	if(info) a->avl = insert(a->avl,id,info);
	(a->total)++;
	return a;
}

/* Verificar se uma determinada string existe na TAD_istruct. */
int existMyAvl(TAD_istruct estrutura,long id){
	int r = existAvl(estrutura->avl,id);
	return r;
}

/* Verificar se uma determinada string existe na Avl. */
int existAvl(Avl estrutura, long id){
	int r=0;
	if(estrutura == NULL) return r;
	if(estrutura->idArticle == id) r=1;
	else if(estrutura->left!=NULL && estrutura->idArticle > id ){
		r=existAvl(estrutura->left,id);
	}
	else if(estrutura->right!=NULL && estrutura->idArticle < id){
		r=existAvl(estrutura->right,id);
	}
	return r;
}

/* Função que retorna o número de elementos de uma TAD_istruct. */
int totalElements(TAD_istruct estrutura){
	if(estrutura) return estrutura->total;
	else return 0;
}

/* Função que liberta uma estrutura TAD_istruct. */
void removeMyAvl(TAD_istruct estrutura,Func f){
	if(estrutura){
		removeAvl(estrutura->avl,f);
		free(estrutura);
	}
}

/* Função que liberta uma estrutura Avl. */
void removeAvl(Avl estrutura,Func freeInfo){
	if(estrutura != NULL){
		removeAvl(estrutura->right,freeInfo);
		removeAvl(estrutura->left,freeInfo);
		//free(estrutura->idArticle);
		if(freeInfo!=NULL)
			freeInfo(estrutura->info);
		free(estrutura);
	}
}

void freeTAD(TAD_istruct estrutura){
	freeNodo(estrutura->avl);
	free(estrutura);
}

/* Função que liberta a memória de um Nodo da Avl. */
void freeNodo(Avl a){
	if(a){
	freeNodo(a->right);
	freeNodo(a->left);
	freeHeap(a->info);
	free(a);
	}
}

void* findMyInfo(TAD_istruct a, long id){
	void* x = findInfo(a->avl, id);
	return x;
}

/* Função que faz a procura de uma estrutura info. */
void* findInfo (Avl a,long id){
	while(a){
		if (a->idArticle > id) a=a->left;
		else if(a->idArticle < id) a=a->right;
		else break;
	}
	if(a) return a->info;
	else return NULL;
}

/* Função que faz um clone de uma Avl. */
Avl cloneAvl (Avl estrutura){
	Avl aux;
	if(estrutura){
		aux = malloc (sizeof(struct avl));
		aux->idArticle = estrutura->idArticle;
		aux->height=estrutura->height;
		aux->info=estrutura->info;
		aux->left=cloneAvl(estrutura->left);
		aux->right=cloneAvl(estrutura->right);
	}
	else return NULL;

	return aux;
}

/* Função que faz um clone de um TAD_istruct. */
TAD_istruct cloneMyAvl (TAD_istruct estrutura){
	TAD_istruct aux = malloc (sizeof(struct TCD_istruct));
	if(estrutura){
		aux->avl=cloneAvl(estrutura->avl);
		aux->total=estrutura->total;
	}
	else aux=NULL;
	return aux;
}

/* Função que calcula o número de nodos sem Info. */
int infoNULL(Avl a){
	int r=0;
	if(a){
		r+=infoNULL(a->left);
		r+=infoNULL(a->right);
		if(!a->info)r++;
	}
	return r;
}


/* GETS E SETS */ 

Avl getAvl(TAD_istruct estrutura){
	Avl aux;
	if(!estrutura) return NULL;
	if(estrutura->avl){
		aux = malloc (sizeof(struct avl));
		aux->idArticle = estrutura->avl->idArticle;
		aux->height=estrutura->avl->height;
		aux->info=estrutura->avl->info;
		aux->left=estrutura->avl->left;
		aux->right=estrutura->avl->right;
	}
	else return NULL;
	return aux;
}

Avl getAvlLeft(Avl a){
	if(!a) return NULL;
	Avl aux;
	if(a->left){
		aux = malloc (sizeof(struct avl));
		aux->idArticle = a->left->idArticle;
		aux->height=a->left->height;
		aux->info=a->left->info;
		aux->left=a->left->left;
		aux->right=a->left->right;
	}
	else return NULL;
	return aux;
}

Avl getAvlRight(Avl a){
	if(!a) return NULL;
	Avl aux;
	if(a->right){
		aux = malloc (sizeof(struct avl));
		aux->idArticle = a->right->idArticle; 
		aux->height=a->right->height;
		aux->info=a->right->info;
		aux->left=a->right->left;
		aux->right=a->right->right;
	}
	else return NULL;
	return aux;
}


int getSize(TAD_istruct a){
	return a->total;
}

void* getInfo(Avl a){
	return a->info;
}

void setInfo(Avl a,void* i){
	a->info=i;
}

long getAvlIdArt(Avl a){
	long r = a->idArticle;
	return r;
}

void setAvl(TAD_istruct a, Avl b){
	a->avl=b;
}