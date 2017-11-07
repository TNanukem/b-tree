#ifndef _ARVORE
#define _ARVORE

#include "arquivo.h"

typedef struct{

	int numChaves;			// Número de chaves armazenadas na página
	int chaves[ORDEM-1];
	int byteoffset[ORDEM-1];	// 	
	struct Pagina *filhos[ORDEM];
	int folha;				// Booleano (1/true)(0/false);

} Pagina;

typedef struct{

	Pagina *raiz;

} Arvore;

void criarArvore(Arvore *A);
int procurarArvore(Arvore *A, int id);
int adicionarArvore(Arvore *A, int id);

#endif
