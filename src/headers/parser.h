/** @file parser.h
 *  @brief Protótipos das funções responsáveis por tratar dos ficheiros.
 *
 *  O ficheiro contem os prototipos das funçoes que implementam o parser.
 *
 *  @author Grupo 63
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "../../interface.h"

/** @brief Resposável por contar as palavras e bytes do texto.
 *
 *  @param key Texto xml.
 *  @param contagem array que contém a informação da contagem das palavras e dos bytes.
 *  @return Apontador.
 */

int* count(xmlChar *key,int *contagem);

/** @brief Resposável por guardar o parsing na estrutura.
 *
 *  @param title Titulo do artigo.
 *  @param idCont Id do Contribuidor.
 *  @param nameCont Username do Contribuidor.
 *  @param totalWords Número de palavras presentes no texto do artigo.
 *  @param timestamp Timestamp da revisão.
 *  @param revisionId Id da revisão.
 *  @param id Id do artigo.
 *  @param nBytes Número de bytes presentes no texto do artigo.
 *  @return Void.
 */

void parseToStruct(char* title, long idCont, char* nameCont, int totalWords, char* timestamp, long revisionId, long id, int nBytes);

/** @brief Resposável por fazer o parsing das páginas do documento.
 *
 *  @param number Número da página.
 *  @param doc Apontador para o documento xml.
 *  @param cur Apontador para o nodo xml.
 *  @return Void.
 */
void parsePage (int number, xmlDocPtr doc, xmlNodePtr cur);

/** @brief Resposável por fazer o parsing do documento.
 *
 *  @param docname Nome do ficheiro.
 *  @param parser Estrutura TAD_istruct.
 *  @return TAD_istruct Estrutura.
 */
TAD_istruct parseDoc(char *docname, TAD_istruct parser);

#endif
