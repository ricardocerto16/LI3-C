/** @file array.h
 *  @brief Protótipos das funções que trabalham com Arrays.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Array
 *
 *  @author Grupo 63
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <string.h>
#include <stdlib.h>

/**
 * @brief Declaração do tipo Array, um tipo abstrato. 
 */


typedef struct array *Array;

/** @brief Inicia a estrutura Array com um dado tamanho, alocando espaço para a mesma. 
 *  @param size Tamanho.
 *  @return Array.
 */

Array initArray(int size);
/** @brief Insere num Array a informação pretendida.
 *
 *  @param a Array.
 *  @param info Key.
 *  @param total Value.
 *  @return int.
 */

int insertInf(Array a, long info, long total);
/** @brief Retorna o tamanho do Array utilizado até ao momento.
 *
 *  @param a Array.
 *  @return Tamanho usado.
 */

int getArrayUsed(Array a);
/** @brief Retorna o total da inf 
 *
 *  @param a Array.
 *  @param i índice.
 *  @return Total.
 */

long getInfTotal(Array a, int i);

/** @brief Retorna a Info da inf 
 *
 *  @param a Array.
 *  @param i índice.
 *  @return Info.
 */

long getInfInfo(Array a, int i);
/** @brief Retorna o índice do id pretendido 
 *
 *  @param id Id.
 *  @param a Array.
 *  @return índice.
 */

int findIndex(long id, Array a);

/** @brief altera o total da inf de um Array
 *
 *  @param a Array.
 *  @param index índice
 *  @param i incremento
 *  @return Void.
 */

void setInfTotal(Array a, int index, long i);

#endif