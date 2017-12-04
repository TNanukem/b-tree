#include "fila.h"

void CriaFila(Fila* F){
	F->inicio = 0;
	F->fim= 0;
	F->total = 0;
}

void EsvaziaFila(Fila* F){
	F->inicio = 0;
	F->fim = 0;
	F->total = 0;
}

void EntraFila(Fila* F, elem X){
	if(F->total >= TAMANHO - 1)
		return;
	F->total++;
	F->itens[F->fim] = X;
	if(F->fim == TAMANHO - 1) F->fim = 0;
	else F->fim++;
}

elem SaiFila(Fila* F){
	if(F->total == 0)
		return -1;
	F->total--;
	elem aux = F->itens[F->inicio];
	if(F->inicio == TAMANHO - 1) F->inicio = 0;
	else F->inicio++;
	return aux;
}

int TotalFila(Fila *F){
	return F->total;
}