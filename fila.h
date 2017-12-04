#ifndef _FILA
#define _FILA
#define TAMANHO 100

typedef int elem;

typedef struct Fila_struct{
	elem itens[TAMANHO];
	int inicio;
	int fim;
	int total;
} Fila;


void CriaFila(Fila* F);
void EntraFila(Fila* F, elem X);
elem SaiFila(Fila *F);
int TotalFila(Fila *F);
void EsvaziaFila(Fila* F);

#endif