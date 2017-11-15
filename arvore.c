#include "arvore.h"

void criarArvore(Arvore *A){
	//A->raiz = NULL;
}

int procurarChave(int numChaves, int *chaves, int id){
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

int pesquisarArvore(Pagina *P, int id){
	if(P->numChaves == 0)
		return 0;
	int pos = procurarChave(P->numChaves, P->chaves, id);

	if(pos < P->numChaves && P->chaves[pos] == id)
		return pos;
	else
		pesquisarArvore(!P->folha && P->filhos[pos], id);
}

