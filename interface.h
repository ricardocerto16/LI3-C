/** @file parser.h
 *  @brief Protótipos das funções relacionadas com a interface.
 *
 *  O ficheiro contem os prototipos das funçoes que implementam o parser.
 *
 *  @author Grupo 63
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

/**
 * @brief Declaração do tipo TAD_istruct, um tipo abstrato. 
 */

typedef struct TCD_istruct * TAD_istruct;

/** @brief Inicialização da estrutura.
 *  @return TAD_istruct.
 */
TAD_istruct init();
/** @brief Carregamento dos ficheiros.
 *  @param nsnaps Número de ficheiros.
 *  @param snaps_paths Ficheiros.
 *  @return TAD_istruct.
 */
TAD_istruct load(TAD_istruct qs, int nsnaps , char * snaps_paths[]);

/* Protótipo das queries
*/
/** @brief retorna todos os artigos encontrados nos backups analisados.
 *  @param TAD_istruct Estrutura.
 *  @return Número de artigos.
 */
long all_articles(TAD_istruct qs);
/** @brief retorna todos os artigos únicos encontrados nos backups analisados.
 *  @param TAD_istruct Estrutura.
 *  @return Número de artigos únicos.
 */
long unique_articles(TAD_istruct qs);
/** @brief retorna quantas revisões foram efetuadas nos backups analisados.
 *  @param TAD_istruct Estrutura.
 *  @return Número de revisões.
 */
long all_revisions(TAD_istruct qs);
/** @brief devolve um array com os identificadores dos 10 autores que contribuíram para um maior número de versões de artigos.
 *  @param TAD_istruct Estrutura.
 *  @return array com os top10 contribuidores.
 */
long * top_10_contributors(TAD_istruct qs);
/** @brief devolve o nome do autor com um determinado identificador.
 *  @param contributor_id Id do Contribuidor
 *  @param TAD_istruct Estrutura.
 *  @return username do contribuidor.
 */
char * contributor_name(long contributor_id, TAD_istruct qs);
/** @brief devolve um array com os identificadores dos 20 artigos que possuem textos com um maior tamanho em bytes.
 *  @param TAD_istruct Estrutura.
 *  @return array com os top20 artigos.
 */
long * top_20_largest_articles(TAD_istruct qs);
/** @brief devolve o título do artigo com um determinado identificador.
 *  @param article_id Id do Artigo
 *  @param TAD_istruct Estrutura.
 *  @return título do artigo.
 */
char *  article_title(long article_id , TAD_istruct qs);
/** @brief devolve um array com os identificadores dos N artigos que possuem textos com um maior número de palavras.
 *  @param n Números de artigos pretendidos.
 *  @param TAD_istruct Estrutura.
 *  @return array com os topN artigos.
 */
long * top_N_articles_with_more_words(int n, TAD_istruct qs);
/** @brief devolve um array de títulos de artigos que começam com um determinado prefixo.
 *  @param prefix Prefixo pretendido.
 *  @param TAD_istruct Estrutura.
 *  @return array com os títulos de artigos.
 */
char ** titles_with_prefix(char *prefix, TAD_istruct qs);
/** @brief devolve o timestamp para uma certa revisão de um artigo.
 *  @param article_id Id do Artigo.
 *  @param revision_id Id da Revisão.
 *  @param TAD_istruct Estrutura.
 *  @return timestamp do artigo.
 */
char * article_timestamp(long article_id, long revision_id, TAD_istruct qs);
/** @brief dá free na estrutura
 *  @param TAD_istruct Estrutura
 */
TAD_istruct clean(TAD_istruct qs);

#endif