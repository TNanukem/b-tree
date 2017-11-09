#include <stdio.h>
#include <stdlib.h>

#ifndef _ARQUIVO
#define _ARQUIVO

#include "arvore.h"

#define ORDEM 5

typedef struct{

	int id;
	char titulo[30];
	char genero[20];

} Registro;

void criarIndice();
void inserirMusica(int id, char titulo[30], char genero[20], Registro r);
int pesquisaMusicaID();
void removeMusicaID();
void mostraArvoreB();

/* Função utilizada para verificar se o input digitado é válido 
   utiliza comparações com a tabela ASCII para permitir somente
   a entrada de letras. Recebe o ponteiro para a string.
   AINDA NÃO FUNCIONA E EU NÃO SEI PQ
*/
int caractereValido(char *string);

/* Função responsável por formatar o registro da maneira adequada
   antes de inseri-lo no arquivo de dados. Ele realiza essa operação
   por meio do buffer e retorna o tamanho do buffer, ou seja, o 
   tamanho do registro para que isso também seja colocado no arquivo*/
int regVariavel(Registro r, char *buffer);

#endif
