#include "arquivo.h"

void criarIndice(Arvore* A){
	A->raiz = NULL;
}


void inserirMusica(int id, char titulo[30], char genero[20], Registro r){
	r.id = id;
	strcpy(r.titulo, titulo);
	strcpy(r.genero, genero);

	// Parte do código responsável por atualizar o índice
	if(A->raiz == NULL){
		Pagina p = (Pagina*) malloc(sizeof(Pagina));
		A->raiz = p;
		p->folha = 0;
		p->numChaves = 1;
		p->chaves[0] = id;
		p->byteoffset[0] = 0;	
	}

}

int pesquisaMusicaID(int id){

}

void removeMusicaID(){

}

void mostraArvoreB(){
	
}