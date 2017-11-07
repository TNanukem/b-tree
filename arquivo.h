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

#endif
