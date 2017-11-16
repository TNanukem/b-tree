#include "arvore.h"

void criarArvore(Arvore *A){
	//A->raiz = NULL;
}

// Funcao procura chave dentro de uma pagina, usando busca binaria
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

Pagina* pesquisarArvore(Pagina *P, int id, int *pos, int *encontrado){
	// Se a pagina passada for nula, nao ha nada a ser feito
	if(P == NULL) {
		*encontrado = 0;
		return NULL;
	}

	// Procura dentro da pagina
	*pos = procurarChave(P->numChaves, P->chaves, id);

	// Verifica se a posicao contem o registro procurado
	if(*pos < P->numChaves && id == P->chaves[*pos]) {
		*encontrado = 1;
		return P;
	}

	// Se a pagina nao for folha, entao deve-se procurar a esquerda ou a direita do indice
	else if (!P->folha){
		if (id < P->chaves[*pos]) // Se id for menor, ir para a pagina da esquerda
			return pesquisarArvore(P->filhos[*pos], id, pos, encontrado);
		else // Caso contrario, ir para a pagina da direita
			return pesquisarArvore(P->filhos[(*pos)+1], id, pos, encontrado);
	}
	else {	// Se for folha
		*encontrado = 0;	// A pagina retornada aqui seria a pagina que o indice ficaria
		return P;					// se estivesse na arvore junto com a posicao *pos correspondente
	}
}

int inserirPagina(int id, int tamTitulo, int tamGenero) {
	// Implementar
	
	return 0;
}
