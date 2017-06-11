/** @file avl.h
 *  @brief Protótipos das funções que trabalham com AVL's.
 *
 *  O ficheiro contem os prototipos das funçoes
 *  AVL assim como a implementação das estruturas necessárias e macros.
 *
 *  @author Grupo 63
 */

#ifndef __AVL_H__
#define __AVL_H__

#include <string.h>
#include <stdlib.h>
#include "../../interface.h"


#define TRUE 1
#define FALSE 0

/**
 * @brief Declaração do tipo Avl, um tipo abstrato. 
 */
typedef struct avl *Avl;

/** @brief Declaração do tipo BOOL
*/
typedef int BOOL;

/**
 * @brief Declaração do tipo Func, apontador para uma função. 
 */
typedef void(*Func)(void*);


/** @brief Inicia a Avl, colocando-a a NULL.
*  @return Avl.
 */
Avl initAvl();

/** @brief Inicia a estrutura TAD_istruct, alocando espaço para a mesma.
*  @return Estrutura TAD_îstruct.
 */
TAD_istruct initMyAvl();

/** @brief Insere uma string e uma info numa TAD_istruct.
*  @param a A estrutura na qual será inserida as informações.
 *  @param id IdArtigo que será inserido.
 *  @param info Apontador para uma estrutura relativo à informação.
*  @return Estrutura TAD_îstruct.
 */
TAD_istruct insertMyAvl(TAD_istruct a,long id,void* info);

/** @brief Retorna a altura de uma dada Avl.
 *
 *  @param a Arvore com uma dada altura.
 *  @return Altura da Avl.
 */
int heightAvl(Avl a);

/** @brief Insere um id e uma info num dado nodo de uma Avl.
 *
 *  @param estrutura Arvore na qual será inserida a string.
 *  @param id Id que será inserida.
 *  @param info Informaçao que será inserida.
 *  @return Arvore que já contem a respetiva string.
 */
Avl insertINFO(Avl estrutura,long id,void* info);

/** @brief Remove uma dada Avl, libertando o espaço ocupado pela mesma.
 *
 *  @param estrutura Arvore que se pretende remover.
 *  @param freeInfo Apontador para uma Função que vai libertar o espaço ocupado pela Info.
 *  @return Void.
 */
void removeAvl(Avl estrutura,Func freeInfo);

/** @brief Remove uma estrutura TAD_îstruct, libertando o espaço ocupado pela mesma.
 *
 *  @param estrutura Estrutura TAD_îstruct que se pretende remover.
 *  @param f Apontador para uma Função que vai libertar o espaço ocupado pela Info.
 *  @return Void.
 */
void removeMyAvl(TAD_istruct estrutura,Func f);
/** @brief Remove a estrutura, libertando o espaço ocupado por esta.
 *
 *  @param estrutura TAD_istruct.
 *  @return Void.
 */
void freeTAD(TAD_istruct estrutura);

/** @brief Remove um nodo de uma Avl, libertando o espaço ocupado por este.
 *
 *  @param a Árvore.
 *  @return Void.
 */
void freeNodo(Avl a);

/** @brief Verifica se um dado Id existe numa dada estrutura TAD_istruct.
 *
 *  @param estrutura Estrutura TAD_istruct que contém ou nao o Id em questao.
 *  @param id Id que será procurada na TAD_istruct.
 *  @return BOOL.
 */
BOOL existMyAvl(TAD_istruct estrutura,long id);

/** @brief Verifica se um dado Id existe numa dada Avl.
 *
 *  @param estrutura Avl que contém ou nao o Id em questao.
 *  @param id Id que será procurada na Avl.
 *  @return BOOL.
 */
BOOL existAvl(Avl estrutura, long id);

/** @brief Retorna o numero de elementos de uma dada estrutura TAD_istruct.
 *
 *  @param estrutura Estrutura TAD_istruct com um dado numero de elementos.
 *  @return Numero de elementos da TAD_istruct.
 */
int totalElements(TAD_istruct estrutura);
/** @brief Procura um Id que exista na TAD_istruct e retorna a info que lá se encontra
 *  retorna NULL caso nao exista. 
 *
 *  @param a Estrutura que contém ou nao um dado Id.
 *  @param id Id que pretendemos encontrar.
 *  @return *Void.
 */
void* findMyInfo(TAD_istruct a, long id);

/** @brief Procura um Id que exista na Avl e retorna a info que lá se encontra
 *  retorna NULL caso nao exista. 
 *
 *  @param a Avl que contém ou nao um dado Id.
 *  @param id Id que pretendemos encontrar.
 *  @return *Void.
 */
void* findInfo (Avl a, long id);

/** @brief Faz um clone de uma dada Avl.
 *
 *  @param estrutura Avl a ser clonada. 
 *  @return Arvore clonada.
 */
Avl cloneAvl (Avl estrutura);

/** @brief Faz um clone de uma dada TAD_îstruct.
 *
 *  @param estrutura TAD_îstruct a ser clonada. 
 *  @return TAD_îstruct clonada.
 */
TAD_istruct cloneMyAvl (TAD_istruct estrutura);


//void removeFromTAD_istruct (TAD_istruct* estrutura,int x);

/** @brief Conta em quantos nodos de uma Avl nao existe Info.
 *
 *  @param a Árvore.
 *  @return Número de nodos sem Info.
 */
int infoNULL(Avl a);


/* GETS E SETS */

/** @brief Retorna a Avl que se encontra numa estrutura TAD_istruct.
 *
 *  @param estrutura Estrutura TAD_istruct que contem uma Avl.
 *  @return Arvore que se encontra na TAD_istruct.
 */
Avl getAvl(TAD_istruct estrutura);

/** @brief Retorna a Sub-arvore do lado esquerdo de uma dada Avl.
 *
 *  @param a Arvore.
 *  @return Sub-arvore esquerda da Avl.
 */
Avl getAvlLeft(Avl a);

/** @brief Retorna a Sub-arvore do lado direito de uma dada Avl.
 *
 *  @param a Arvore.
 *  @return Sub-arvore direita da Avl.
 */
Avl getAvlRight(Avl a);

/** @brief Retorna a Info presente no nodo de uma dada Avl.
 *
 *  @param a Arvore.
 *  @return Info do nodo da Avl.
 */
void* getInfo(Avl a);

/** @brief Retorna o tamanho de uma dada estrutura TAD_istruct.
 *
 *  @param a Estrutura TAD_istruct com um dado numero de elementos.
 *  @return Numero de elementos da TAD_istruct.
 */
int getSize(TAD_istruct a);

/** @brief Altera a Info presente no nodo de uma dada Avl.
 *
 *  @param a Arvore.
 *  @param i Info.
 *  @return Void.
 */
void setInfo(Avl a,void* i);

/** @brief Coloca a Avl b numa TAD_istruct.
 *
 *  @param a TAD_istruct com uma dada Avl.
 *  @param b Avl.
 *  @return Void.
 */
void setAvl(TAD_istruct a,Avl b);

/** @brief Retorna o IdArtigo respetivo de um dado nodo.
 *
 *  @param a Arvore.
 *  @return Id do artigo.
 */
long getAvlIdArt(Avl a);

#endif