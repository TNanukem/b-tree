#include <stdio.h>
#include <stdlib.h>

#define ORDEM 5

typedef struct{

	int id;
	char titulo[30];
	char genero[20];

} Registro;

typedef struct{

	int numChaves;			// Número de chaves armazenadas na página
	int chaves[ORDEM-1];
	int byteoffset[ORDEM-1];	// 	
	int filhos[ORDEM];
	int folha;				// Booleano (1/true)(0/false);

} Pagina;

typedef struct{

	Pagina *raiz;

} Arvore;


void criarIndice();
void inserirMusica(int id, char titulo[30], char genero[20], Registro r);
int pesquisaMusicaID();
void removeMusicaID();
void mostraArvoreB();
