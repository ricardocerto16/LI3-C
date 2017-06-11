#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "headers/avl.h"
#include "headers/heap.h"
#include "../interface.h"


void count(xmlChar *key,int *contagem){

	int l= 0, n = 0;
	char* s = (char*) key;
	l = strlen(s);
	for(s=strtok(s, " \n\t"); s; s=strtok(NULL, " \n\t")) n++;
	contagem[0] = l;
	contagem[1] = n;
}

void parseToStruct(char* title, long idCont, char* nameCont, int totalWords, char* timestamp, long revisionId, long id, int nBytes, TAD_istruct parser){
	Heap article;
	int used, i;
	int r = 0;

	if(existMyAvl(parser, id) == 0){
		article = initHeap(10);
		insertMyAvl(parser, id, article);
	}
    else{
    	article = findMyInfo(parser, id);
    	used = getHeapUsed(article);
    	for(i=0; i<used; i++){
    		if(getRevisionId(article, i) == revisionId) r=1;
    	}
    }

    if(!r) insertHeap(article, idCont, nameCont, (long)totalWords, (long)nBytes, timestamp, revisionId, title);
    else setHeapTotal(article, 1);
}


void parsePage (int number, xmlDocPtr doc, xmlNodePtr cur, TAD_istruct parser) {

	xmlChar *key;
	xmlNodePtr cur1;
	xmlNodePtr cur2;

	char* title = (char*)malloc(sizeof(char)*100);
	long idCont;
	char* nameCont = (char*)malloc(sizeof(char)*100);
	int totalWords;
	char* timestamp = (char*)malloc(sizeof(char)*100);
	long revisionId;
	long id;
	int nBytes;
	int contagem[2];

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"title"))){
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    strcpy(title, (const char*)key);
		    xmlFree(key);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"id"))){
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			id = atol((const char*)key);
		    xmlFree(key);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"revision"))){
			cur1 = cur->xmlChildrenNode;
			while (cur1 && doc) {
			    if ((!xmlStrcmp(cur1->name, (const xmlChar *)"id"))) {
				    key = xmlNodeListGetString(doc, cur1->xmlChildrenNode, 1);
				    revisionId = atol((const char*)key);
				    xmlFree(key);
		 	    }
		 	    if ((!xmlStrcmp(cur1->name, (const xmlChar *)"timestamp"))) {
				    key = xmlNodeListGetString(doc, cur1->xmlChildrenNode, 1);
				    strcpy(timestamp, (const char*)key);
				    xmlFree(key);
		 	    }
		 	    if ((!xmlStrcmp(cur1->name, (const xmlChar *)"contributor"))) {
		 	    	cur2 = cur1->xmlChildrenNode;
					while (cur2 != NULL) {
					    if ((!xmlStrcmp(cur2->name, (const xmlChar *)"ip"))) {
						    key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
						    strcpy(nameCont, (const char*)key);
						    idCont = -1;
						    xmlFree(key);
				 	    }						
					    if ((!xmlStrcmp(cur2->name, (const xmlChar *)"username"))) {
						    key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
						    strcpy(nameCont, (const char*)key);
						    xmlFree(key);
				 	    }
				 	    if ((!xmlStrcmp(cur2->name, (const xmlChar *)"id"))) {
						    key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
						    idCont = atol((const char*)key);
						    xmlFree(key);
				 	    }
						cur2 = cur2->next;
					}
		 	    }
		 	    if ((!xmlStrcmp(cur1->name, (const xmlChar *)"text"))) {
		 	    	if(xmlStrcmp((const xmlChar*)cur1->properties, NULL)){
				    	key = xmlNodeListGetString(doc, cur1->xmlChildrenNode, 1);
				    	count(key,contagem);
				    	totalWords = contagem[1];
				    	nBytes = contagem[0];
				    	contagem[0] = 0;
				    	contagem[1] = 0;
				    	xmlFree(key);
					}		
		 	    }
				cur1 = cur1->next;
			}
		}
	cur = cur->next;
	}
	parseToStruct(title, idCont, nameCont, totalWords, timestamp, revisionId, id, nBytes, parser);
    return;
}


TAD_istruct parseDoc(char *docname, TAD_istruct parser){
	
	int number = 0;

	//clock_t tpf;

	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr aux;

	doc = xmlParseFile(docname);

	if (doc == NULL){
		fprintf(stderr,"Falha no parse do documento. \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL){
		fprintf(stderr,"Documento vazio!\n");
		return NULL;
	}

	cur = cur->xmlChildrenNode;
	cur = cur->next;
// METER A PERCORRER O FICHEIRO todo
	for( ; cur ; number++){
		aux = cur;
		if (!xmlStrcmp(cur->name,(const xmlChar *) "page")){
			parsePage (number, doc, cur, parser);
		}
		cur = aux->next;
	}

	xmlFreeDoc(doc);

	/*tpf = clock() - tpf;
	printf("Demorou %f segundos a ler o ficheiro.\n",((float)tpf)/CLOCKS_PER_SEC);*/

	return parser;
}