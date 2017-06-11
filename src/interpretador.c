#include "headers/interpretador.h"
#include "headers/heap.h"
#include "headers/avl.h"
#include "../interface.h"
#include "headers/parser.h"
#include "headers/array.h"

#define SIZE 128


static void querie1(TAD_istruct qs);
static void querie2(TAD_istruct qs);
static void querie3(TAD_istruct qs);
static void querie4(TAD_istruct qs);
static void querie5(TAD_istruct qs);
static void querie6(TAD_istruct qs);
static void querie7(TAD_istruct qs);
static void querie8(TAD_istruct qs);
static void querie9(TAD_istruct qs);
static void querie10(TAD_istruct qs);
static void clear();


static void clear(){
	int i;
	for(i=0;i<2;i++)
		printf("\n");
}

void menu() {

	printf("__________________________________ QUERIES _______________________________________\n");
	printf("	                                                                              \n");
	printf("	                                                                              \n");
	printf("	01. Total de Artigos.                                                         \n");
	printf("	02. Artigos Únicos.                                                           \n");
	printf("	03. Número de revisões.                                                       \n");
	printf("	04. Top 10 contribuidores.                                                    \n");
	printf("	05. Nome Contribuidor dado um id de um Contribuidor.                          \n");
	printf("	06. Top 20 artigos mais longos em bytes.                                      \n");
	printf("	07. Título de um artigo dado um respetivo id.                                 \n");
	printf("	08. Top N artigos com mais palavras.                                          \n");
	printf("	09. Titulos com um determinado prefixo.                                       \n");
	printf("	10. Timestamp de uma dada revisão de um artigo.                               \n");
	printf("	0. Sair.                                                                      \n");
	printf("	                                                                              \n");
	printf("__________________________________________________________________________________\n");

}

void interpretador(TAD_istruct qs) {

	char buffer[SIZE];
	int comando;
	menu();
	printf("\n________________________________________________________________________________\n");
	printf("										                                          \n");
	printf("     Introduza o número da querie desejada: ");
	scanf("%s",buffer);
	comando = atoi(buffer);


	if(buffer[0] == '0'){
		return;
	}

	switch(comando){

		case 1: 
			querie1(qs);
			clear();
			break;

		case 2: 
			querie2(qs);
			clear();
			break;

		case 3: 
			querie3(qs);
			clear();
			break;

		case 4: 
			querie4(qs);
			clear();
			break;

		case 5:
			querie5(qs);
			clear();
			break;

		case 6: 
			querie6(qs);
			clear();
			break;

		case 7:
			querie7(qs);
			clear();
			break;

		case 8:
			querie8(qs);
			clear();
			break;

		case 9:
			querie9(qs);
			clear();
			break;

		case 10:
			querie10(qs);
			clear();
			break;

		case 0:
			clean(qs);
			return;

			
		default:
			printf(" COMANDO INVÁLIDO!\n");
			printf("\n");
			break;
	}

	interpretador(qs);

}



/* QUERIE 1*/

static void querie1(TAD_istruct qs) {
	long all;

	all = all_articles(qs);
	clear();

	printf("\n");
	printf(" __________________________________________\n");
	printf("							                \n");
	printf("|_________________QUERIE 1_________________|\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("                                            \n");
	printf("       Total de Artigos: %ld                \n", all);
	printf("                                            \n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|__________________________________________|\n");
}


/* QUERIE 2 */

static void querie2(TAD_istruct qs) {
	long uni;

	uni = unique_articles(qs);
	clear();

	printf("\n");
	printf(" __________________________________________\n");
	printf("							                \n");
	printf("|_________________QUERIE 2_________________|\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("                                            \n");
	printf("      Artigos Únicos: %ld                   \n", uni);
	printf("                                            \n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|__________________________________________|\n");
}

/* QUERIE 3 */
static void querie3(TAD_istruct qs) {
	long rev;

	rev = all_revisions(qs);
	clear();

	printf("\n");
	printf(" __________________________________________\n");
	printf("							                \n");
	printf("|_________________QUERIE 3_________________|\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("                                            \n");
	printf("      Total de Revisões: %ld                \n", rev);
	printf("                                            \n");
	printf("|                                          |\n");
	printf("|                                          | \n");
	printf("|__________________________________________|\n");
}

/* QUERIE 4 */
static void querie4(TAD_istruct qs){
	long* rev;
	int i;

	rev = top_10_contributors(qs);
	clear();

	printf("\n");
	printf(" __________________________________________\n");
	printf("							                \n");
	printf("|_________________QUERIE 4_________________|\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("                                            \n");
	for(i=0;i<10;i++){
		printf("     Contribuidor %d: %ld                   \n", i+1, rev[i]);
	}
	printf("                                            \n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|__________________________________________|\n");

}



static void querie5(TAD_istruct qs) {
	long id;
	char buffer[SIZE];
	char* user = malloc(sizeof(char ) * 100);

	printf("\n________________________________________________________________________________\n");
	printf("										                                        \n");
	printf("     Introduza o id do contribuidor desejado: ");
	scanf("%s",buffer);
	id = atol(buffer);

	user = contributor_name(id,qs);
	clear();

	if(!user){
		printf(" ______________________________________________________________________________\n");
		printf("							                                                   \n");
		printf("|___________________________________QUERY 5___________________________________|\n");
		printf("										                                       \n");
		printf("     Contribuidor de id[%ld] não encontrado. (NULL)\n", id);
		printf("_______________________________________________________________________________\n");
	}
	else{
	printf("\n");
	printf(" __________________________________________\n");
	printf("							                \n");
	printf("|_________________QUERIE 5_________________|\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("                                            \n");
	printf("     Contribuidor id[%ld]: %s               \n", id,user);
	printf("                                            \n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|__________________________________________|\n");
	}
}


static void querie6(TAD_istruct qs){

	long * art20;
	int i;
	art20 = top_20_largest_articles(qs);
	clear();

	if(!art20){
		printf(" ______________________________________________________________________________\n");
		printf("							                                                   \n");
		printf("|___________________________________QUERY 6___________________________________|\n");
		printf("										                                       \n");
		printf("     Artigos não encontrados\n");
		printf("_______________________________________________________________________________\n");
	}
	else {
		printf("\n");
		printf(" __________________________________________\n");
		printf("							                \n");
		printf("|_________________QUERIE 6_________________|\n");
		printf("|                                          |\n");
		printf("|                                          |\n");
		printf("                                            \n");
		for(i=0;i<20;i++){
			printf("     Artigo %d: %ld                   \n", i+1, art20[i]);
		}
		printf("                                            \n");
		printf("|                                          |\n");
		printf("|                                          |\n");
		printf("|__________________________________________|\n");

	}
}


static void querie7(TAD_istruct qs) {
	long id;
	char buffer[SIZE];
	char * title;

	printf("\n________________________________________________________________________________\n");
	printf("										                                        \n");
	printf("     Introduza o id do artigo desejado: ");
	scanf("%s",buffer);
	id = atol(buffer);
	clear();

	title = article_title(id,qs);

	if(!title){
		printf(" ______________________________________________________________________________\n");
		printf("							                                                   \n");
		printf("|___________________________________QUERY 7___________________________________|\n");
		printf("										                                       \n");
		printf("     Artigo id[%ld] não encontrado\n", id);
		printf("_______________________________________________________________________________\n");
	}
	else{
	printf("\n");
	printf(" __________________________________________\n");
	printf("							                \n");
	printf("|_________________QUERIE 7_________________|\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("                                            \n");
	printf("     Artigo id[%ld]: %s           \n", id,title);
	printf("                                            \n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("___________________________________________|\n");
	}
}

static void querie8(TAD_istruct qs){

	char buffer[SIZE];
	int i;
	long* rev;
	printf("\n________________________________________________________________________________\n");
	printf("										                                        \n");
	printf("     Introduza o número de artigos desejado: ");
	scanf("%s",buffer);
	int n = atoi(buffer);

	rev = top_N_articles_with_more_words(n,qs);
	clear();

	printf("\n");
	printf(" __________________________________________\n");
	printf(" 							                \n");
	printf("|_________________QUERIE 8_________________|\n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("                                            \n");
	for(i=0;i<n;i++){
		printf("     Artigo %d: %ld\n", i+1, rev[i]);
	}
	printf("                                            \n");
	printf("|                                          |\n");
	printf("|                                          |\n");
	printf("|__________________________________________|\n");

}

static void querie9(TAD_istruct qs){
	char** titles;
	int i, tam = 0;
	char buffer[SIZE];
	char* prefix = malloc(sizeof(buffer));

	printf("\n________________________________________________________________________________\n");
	printf("										                                        \n");
	printf("     Introduza o prefixo desejado: ");
	scanf("%s",buffer);
	strcpy(prefix, buffer);
	clear();

	titles = titles_with_prefix(prefix, qs);

	while(titles[tam])
		tam++;

	if(tam == 0){
		printf(" ______________________________________________________________________________\n");
		printf("							                                                   \n");
		printf("|___________________________________QUERY 9___________________________________|\n");
		printf("										                                       \n");
		printf("     Não foram encontrados artigos com o prefixo %s\n", prefix);
		printf("_______________________________________________________________________________\n");
	}
	else{
		printf("\n");
		printf(" __________________________________________\n");
		printf("							                \n");
		printf("|_________________QUERIE 9_________________|\n");
		printf("|                                          |\n");
		printf("|                                          |\n");
		printf("                                            \n");
		for(i=0;i<tam;i++){
			printf("     Título %d: %s                          \n", i+1, titles[i]);
		}
		printf("                                            \n");
		printf("|                                          |\n");
		printf("|                                          |\n");
		printf("|__________________________________________|\n");
	}

}

static void querie10(TAD_istruct qs) {
	long artigo;
	long revisao;
	char buffer[SIZE];
	char * time;

	printf("\n________________________________________________________________________________\n");
	printf("										                                        \n");
	printf("     Introduza o id do artigo desejado: ");

	scanf("%s",buffer);
	artigo = atol(buffer);


	printf("\n________________________________________________________________________________\n");
	printf("										                                        \n");
	printf("     Introduza o id da revisão desejada: ");

	scanf("%s",buffer);
	revisao = atol(buffer);
	time = article_timestamp(artigo,revisao,qs);
	clear();

	if(!time){
		printf(" ______________________________________________________________________________\n");
		printf("							                                                   \n");
		printf("|___________________________________QUERY 10__________________________________|\n");
		printf("										                                       \n");
		printf("     Revisão id[%ld] do artigo id[%ld] não encontrado\n", revisao,artigo);
		printf("_______________________________________________________________________________\n");
	}else{
		printf("\n");
		printf(" __________________________________________\n");
		printf("							                \n");
		printf("|_________________QUERIE 10________________|\n");
		printf("|                                          |\n");
		printf("|                                          |\n");
		printf("                                            \n");
		printf("     Timestamp: %s                          \n", time);
		printf("                                            \n");
		printf("|                                          |\n");
		printf("|                                          |\n");
		printf("___________________________________________|\n");
	}
}