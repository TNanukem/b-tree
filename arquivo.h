#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _ARQUIVO
#define _ARQUIVO

#include "arvore.h"

#define ORDEM 5

typedef struct{

	int id;
	char titulo[30];
	char genero[20];

} Registro;

void criarIndice(Arvore* A, FILE *log);
void inserirMusica(int id, char titulo[30], char genero[20], FILE *dados, FILE *log, int *tamTitulo, int *tamGenero);
int pesquisaMusicaID(int id, FILE *log);
void removeMusicaID(int id, FILE *log);
void mostraArvoreB(FILE *log);

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

/* Função que separa os campos que foram salvos no arquivo. Eles foram
   salvos como char e separados por '|', essa função permite que peguemos
   individualmente cada campo salvo */
char *separaCampos(char *buffer, int *p);

#endif


/* Como realizar a leitura do arquivo de dados? O trecho de código a seguir
   demonstra como você pode ler UM registro do arquivo de dados. No caso, do
   primeiro registro.

    printf("\n\n IMPRESSAO DO ARQUIVO \n\n");

	fread(&auxsize, sizeof(int), 1, dados);
	fread(&buffer, sizeof(buffer), 1, dados);

	pos = 0;

	sscanf(separaCampos(buffer, &pos), "%d", &auxID);
	strcpy(auxTitulo, separaCampos(buffer, &pos));
	strcpy(auxGenero, separaCampos(buffer, &pos));

	printf("%d%d|%s|%s", auxsize, auxID, auxTitulo, auxGenero);

*/