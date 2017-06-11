#include "../interface.h"
#include "headers/parser.h"
#include "headers/avl.h"
#include "headers/heap.h"
#include "headers/array.h"
#include "headers/interpretador.h"

/*FUNÇÔES PRIVADAS AO MÓDULO */
static long travessiaT(Avl a);
static long travessiaRev(Avl avl);
static char* findContId(Avl a, long id);
static char* findIdHeap(Heap h, long id);
static long verificaHeapBytes(Heap hp);
static void insertCont(Array a, Avl avl);
static void getContrib(Heap h_avl, Array a);
static int findCont(Array a, long cont);
static void insertArticle(Array arr , Avl avl);
static void getArt(Heap hp , Array a, long id);
static void insertArticleN(Array a, Avl avl);
static void getArtN(Heap h_avl, Array a, long id);
static long maiorWords(Heap h);
static void insertArticlePref(Array a, Avl avl, char* prefix);
static void insertPrefix(Array a, char* prefix, char* title, long id);
static void ordena(char ** s, int size);

/*Função de init da estrutura */
TAD_istruct init(){
	TAD_istruct parser = initMyAvl();
	return parser;
}

/*Função de load de uma estrutura */
TAD_istruct load(TAD_istruct qs, int nsnaps, char * snaps_paths[]){

	int i;

	if (nsnaps <= 1){
		printf("Uso correto: %s nomeFicheiro\n", snaps_paths[0]);
		return NULL;
	}

	for(i = 1 ; i < nsnaps; i++){
		parseDoc(snaps_paths[i], qs);
	}

	//interpretador(qs);

	return qs;

}


/** QUERIE 1 */
long all_articles(TAD_istruct qs){
	
	long all;
	Avl a = getAvl(qs);
	
	all = travessiaT(a);

	return all;
}

static long travessiaT(Avl a) {
	long x=0, l=0, r=0;
	Heap hp;

	if(a){
		hp = getInfo(a);
		Avl left = getAvlLeft(a);
		Avl right = getAvlRight(a);

		if(left) {
			l = travessiaT(left);
		}
		if(right) {
			r = travessiaT(right);
		}

		x = getHeapTotal(hp) + l + r;
	}

	return x;
}


/** QUERIE 2 */
long unique_articles(TAD_istruct qs){
	long nart = 0;
	if(qs)
		nart = getSize(qs);
	return nart; 
}


/** QUERIE 3 */
long all_revisions(TAD_istruct qs){
	
	long all;
	Avl a = getAvl(qs);
	
	all = travessiaRev(a);

	return all;
}

static long travessiaRev(Avl avl) {
	long x = 0, l = 0, r = 0;
	Avl left = getAvlLeft(avl);
	Avl right = getAvlRight(avl);
	Heap hp;

	if(avl) {
		if(left)
			l = travessiaRev(getAvlLeft(avl));
		if(right)
			r = travessiaRev(getAvlRight(avl));
		hp = getInfo(avl);
		x += getHeapUsed(hp) + l + r;
	}

	return x;
}

/* QUERIE 4 */
long * top_10_contributors(TAD_istruct qs){
	Avl avl = getAvl(qs);
	Array a = initArray(20);
	long* contributors = malloc(sizeof(long)*10);
	int i;
	
	insertCont(a, avl);

	for(i=0;i<10;i++){
		contributors[i] = getInfInfo(a,i);
	}

	return contributors;
	free(a);

}

static void insertCont(Array a, Avl avl){
	if(avl){
		Avl left = getAvlLeft(avl);
		Avl right = getAvlRight(avl);
		Heap h_avl = getInfo(avl);
		getContrib(h_avl, a);

		if(left){
			insertCont(a, left);
		}

		if(right){
			insertCont(a, right);
		}
	}
}

static void getContrib(Heap h_avl, Array a){
	int i;
	int used = getHeapUsed(h_avl);
	long cont;
	for(i=0;i<used;i++){
		cont = getIdCont(h_avl, i);
		if(!findCont(a, cont) && cont != -1) insertInf(a, cont, 1);
	}
}

static int findCont(Array a, long cont){
	int used = getArrayUsed(a);
	int i, res = 0;
	long contrib;
	for(i=0;i<used;i++){
		contrib = getInfInfo(a,i);
		if(contrib == cont){
			setInfTotal(a, i, 1);
			res = 1;
		}
	}
	return res;
}


/** QUERIE 5 */

char* contributor_name(long contributor_id, TAD_istruct qs){

	char* user = malloc(sizeof(char ) * 100);

	Avl a = getAvl(qs);

	user = findContId(a,contributor_id);

	return user;
}

static char* findContId(Avl a, long id){
	char* user = malloc(sizeof(char ) * 100);;
	Heap h;

	if(a){ 
		h = getInfo(a);
		user = findIdHeap(h,id);
		if(user) return user;
	}
	
		if(getAvlLeft(a)){
			user = findContId(getAvlLeft(a),id);
			if(user) return user;
			}
		if(getAvlRight(a)){
			char* right = findContId(getAvlRight(a),id);
			if(right) return right;
			}
		
	return NULL;
}


static char* findIdHeap(Heap h, long id){
	char* user = (char*)malloc(sizeof(char)*100);
	int used = getHeapUsed(h);
	long contId;
	int i;

	for(i=0;i<used;i++){
		contId = getIdCont(h,i);
		if(contId == id){
			user = getNameCont(h,i);
			return user;
			break;
		}
	}

	return NULL;
}


/** QUERIE 6 */
long * top_20_largest_articles(TAD_istruct qs){
		Avl avl = getAvl(qs);
		Array arr = initArray(20);
		long * articles = malloc(sizeof(long)*20);
		int i;

		insertArticle(arr,avl);

		for(i=0;i<20;i++){
			articles[i] = getInfInfo(arr,i);
		}

		return articles;
		free(arr);
}

static void insertArticle(Array arr , Avl avl){
	long idArt = getAvlIdArt(avl);

	if(avl){
		
		Avl left = getAvlLeft(avl);
		Avl right = getAvlRight(avl);
		Heap hp = getInfo(avl);
		getArt(hp,arr,idArt);

		if(left){
			insertArticle(arr, left);
		}

		if(right){
			insertArticle(arr, right);
		}
	} 
}


static void getArt(Heap hp , Array a, long id) {
	long maior = verificaHeapBytes(hp);
	insertInf(a,id,maior);
}


static long verificaHeapBytes(Heap hp) {
	
	long maior = 0;
	int used = getHeapUsed(hp);
	int i;
	long contbytes;

	for(i=0;i<used;i++) {
		contbytes = getNBytes(hp,i);

		if(contbytes > maior) {
			maior = contbytes;
		}
	}
	return maior;
}


/** QUERIE 7 */
char * article_title(long article_id , TAD_istruct qs){
	if(!qs) return NULL;
	
	Heap est = findMyInfo(qs,article_id);

	if(!est) return NULL;

	return getTitle(est, 0);
}


/** QUERIE 8 */
long * top_N_articles_with_more_words(int n, TAD_istruct qs){
	Avl avl = getAvl(qs);
	Array a = initArray(20);
	long* articles = malloc(sizeof(long)*n);
	int i;

	insertArticleN(a, avl);

	for(i=0;i<n;i++){
		articles[i] = getInfInfo(a, i);
	}

	return articles;
	free(a);
}

static void insertArticleN(Array a, Avl avl){
	if(avl){
		Avl left = getAvlLeft(avl);
		Avl right = getAvlRight(avl);
		Heap h_avl = getInfo(avl);
		long id = getAvlIdArt(avl);
		getArtN(h_avl, a, id);

		if(left){
			insertArticleN(a, left);
		}

		if(right){
			insertArticleN(a, right);
		}
	}
}

static void getArtN(Heap h_avl, Array a, long id){
	long words = maiorWords(h_avl);
	insertInf(a, id, words);
}

static long maiorWords(Heap h){
	int i;
	int used = getHeapUsed(h);
	long words = 0;
	long aux;

	for(i=0;i<used;i++){
		aux = getTotalWords(h, i);
		if(words < aux) words = aux;
	}

	return words;
}


/** QUERIE 9 */
char ** titles_with_prefix(char *prefix, TAD_istruct qs){
	Avl avl = getAvl(qs);
	Array a = initArray(20);
	char* title;
	char ** preftitles = (char**)malloc(sizeof(char *));

	insertArticlePref(a, avl, prefix);

	int used = getArrayUsed(a);
	int i;
	for(i=0;i<used;i++){
		Heap h = findMyInfo(qs, getInfInfo(a,i));
		title = getTitle(h, 0);
		preftitles[i] = (char*)malloc(sizeof(char)*100);
		strcpy(preftitles[i], title);
	}

	ordena(preftitles, used);
	preftitles[used] = NULL;

	return preftitles;
	free(a);
}

static void insertArticlePref(Array a, Avl avl, char* prefix){
	if(avl){
		Heap h = getInfo(avl);
		char* title = getTitle(h,0);
		int id = getAvlIdArt(avl);
		Avl left = getAvlLeft(avl);
		Avl right = getAvlRight(avl);

		insertPrefix(a, prefix, title, id);

		if(left){
			insertArticlePref(a, left, prefix);
		}

		if(right){
			insertArticlePref(a, right, prefix);
		}
	}
}

static void insertPrefix(Array a, char* prefix, char* title, long id){
	int length = strlen(prefix);
	int i;

	for(i=0;i<length;i++){
		if(prefix[i] != title[i])
			return;
	}

	insertInf(a, id, 0);
}

static void ordena(char ** s, int size){
	int i, j;
	char* t = (char*)malloc(sizeof(char)*100);
	for (i = 1; i < size; i++) {
      for (j = 1; j < size; j++) {
         if (strcmp(s[j - 1], s[j]) > 0) {
            strcpy(t, s[j - 1]);
            strcpy(s[j - 1], s[j]);
            strcpy(s[j], t);
         }
      }
   }
}

/** QUERIE 10 */
char * article_timestamp(long article_id, long revision_id, TAD_istruct qs){
	if(!qs) return NULL;
	int i;
	Heap est = findMyInfo(qs,article_id);
	char* tstamp = malloc(sizeof(char) * 64);
	tstamp = NULL;
	int used = getHeapUsed(est);

	for(i=0;i<used;i++){
		long revisionId = getRevisionId(est, i);
		if(revisionId == revision_id){
			tstamp = getTimestamp(est, i);
			break;
		}	
	}
	
	return tstamp;
}

/** Função clean */

TAD_istruct clean(TAD_istruct qs){
	freeTAD(qs);
	return qs;
}
