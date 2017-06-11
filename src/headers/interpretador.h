/** @file interpretador.h
 *  @brief Protótipos das funções relacionadas com o interpretador.
 *
 *  O ficheiro contem os prototipos das funçoes que implementam o interpretador.
 *
 *  @author Grupo 63
 */
#ifndef __INTERPRETADOR_H__
#define __INTERPRETADOR_H__


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../interface.h"
#include "avl.h"

/** @brief Resposável por apresentar o menu ao utilizador.
 *
 *  @param qs Estrutura TAD_istruct.
 *  @return Void.
 */
void menu();
/** @brief Resposável por implementar o interpretador.
 *
 *  @param qs Estrutura TAD_istruct.
 *  @return Void.
 */
void interpretador(TAD_istruct qs);

#endif