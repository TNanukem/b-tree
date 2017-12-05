#ifndef _ARQUIVO
#define _ARQUIVO

#include "arvore.h"

#define ORDEM 5

typedef struct{

	int id;
	char titulo[30];
	char genero[20];

} Registro;

/* Função que realiza a criação do arquivo de índice, baseado no arquivo de
   dados já existente.
*/

void criarIndice(Arvore *A, FILE *dados, FILE *log, FILE **indice, int *byteOffset, int *RRN);

/* Função que insere um registro no arquivo de dados */

void inserirMusica(int id, char titulo[30], char genero[20], FILE *dados, FILE *log, FILE **indice, int *byteOffset, int *RRNtotal, Arvore *A);

/* Função que pesquisa na árvore B o offset do registro cujo id foi passado
   como parâmetro
*/


void removeMusicaID(int id, FILE *log);

/* Função que imprime na tela da Árvore B */

void mostraArvoreB(FILE *log);

/* Função utilizada para verificar se o input digitado é válido
   utiliza comparações com a tabela ASCII para permitir somente
   a entrada de letras, espaços e números. Recebe o ponteiro para a string.
*/

int caractereValido(char *string);

/* Função responsável por formatar o registro da maneira adequada
   antes de inseri-lo no arquivo de dados. Ele realiza essa operação
   por meio do buffer e retorna o tamanho do buffer, ou seja, o
   tamanho do registro para que isso também seja colocado no arquivo
*/

int regVariavel(Registro r, char *buffer);

/* Função que separa os campos que foram salvos no arquivo. Eles foram
   salvos como char e separados por '|', essa função permite que peguemos
   individualmente cada campo salvo
*/

char *separaCampos(char *buffer, int *p);

/* Função que, dado um offset recebido do arquivo de índice, realiza a pesquisa
   do registro associado ao offset no arquivo de dados.
  */

void pesquisaDados(int offset, char *titulo, char *genero, FILE *Dados);

/* Função utilizada para converter o ID, que é salvo como uma string, para
   um inteiro.
  */


#endif
