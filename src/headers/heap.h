/** @file heap.h
 *  @brief Protótipos das funções que trabalham com Heaps.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Heap
 *
 *  @author Grupo 63
 */

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <string.h>

/**
 * @brief Declaração do tipo Heap, um tipo abstrato. 
 */

typedef struct heap *Heap;

/** @brief Inicia a estrutura Heap com um dado tamanho, alocando espaço para a mesma. 
 *  @param size Tamanho.
 *  @return Heap.
 */
Heap initHeap (int size);

/** @brief Insere numa Heap a informação pretendida.
 *
 *  @param h Heap.
 *  @param a IdContribuidor.
 *  @param b Username.
 *  @param c TotalPalavras.
 *  @param d TotalBytes.
 *  @param e Timestamp.
 *  @param f IdRevisao.
 *  @param g Titulo.
 *  @return int.
 */
int insertHeap(Heap h, long a, char* b, long c, long d, char* e, long f, char* g);

/** @brief Retorna o tamanho da Heap utilizado até ao momento.
 *
 *  @param h Heap.
 *  @return Tamanho usado.
 */
int getHeapUsed(Heap h);

/** @brief Retorna o número total de revisões.
 *
 *  @param h Heap.
 *  @return Total de revisões.
 */
long getHeapTotal(Heap h);

/** @brief Retorna o idContribuidor do elem 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return IdContribuidor.
 */
long getIdCont(Heap h, int i);

/** @brief Retorna o username do contribuidor
 *
 *  @param h Heap.
 *  @param i índice
 *  @return String.
 */
char* getNameCont(Heap h, int i);

/** @brief Retorna o total de palavras do elem 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return TotalPalavras.
 */
long getTotalWords(Heap h, int i);

/** @brief Retorna o total de bytes do elem 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return TotalBytes.
 */
long getNBytes(Heap, int i);

/** @brief Retorna o timestamp do elem 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return timestamp.
 */
char* getTimestamp(Heap h, int i);

/** @brief Retorna o IdRevisao 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return IdRevisao.
 */
long getRevisionId(Heap h, int i);

/** @brief Retorna o IdArtigo 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return IdArtigo.
 */
long getArticleId(Heap h, int i);

/** @brief Retorna o Titulo 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return String.
 */
char* getTitle(Heap h, int i);

/** @brief altera o total de revisãoes de uma Heap 
 *
 *  @param h Heap.
 *  @param i índice
 *  @return Void.
 */
void setHeapTotal(Heap h, long i);

/** @brief Liberta o espaço ocupado pela Heap
 *
 *  @param h Heap.
 *  @return Void.
 */
void freeHeap(Heap h);

//void show(Heap article, int i);

#endif