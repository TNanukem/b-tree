#include "arvore.h"

void criarArvore(Arvore *A){
	A->raiz = NULL;
}


void procurarChave(int numChaves, int *chaves, int id){
	int menor, medio, maior;
	menor = -1;
	maior = numChaves;

	while(menor + 1 < maior){
		medio = (menor+maior)/2;
		if(chaves[medio] == id)
			return medio;
		else if(chaves[medio] < id)
			menor = medio;
		else
			maior = medio;
	}
	return maior;
}

void pesquisarArvore(Pagina *P, int id){
	if(P->numChaves == 0)
		return 0;
	int pos = procurarChave(P->numChaves, P->chaves, id);

	if(pos < P->numChaves && P->chaves[pos] == key)
		return pos;
	else
		return (!P->folha && P->filhos[pos], id);
}

