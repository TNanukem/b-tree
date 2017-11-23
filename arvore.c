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

Pagina* inserirSplit(Pagina* P, int id, int byteOffset, int *chaveMedia, int *byteMedio)
{
    int pos;
    int mid;
    int byte;
    Pagina* P2;

    pos = procurarChave(P->numChaves, P->chaves, id);

    if(pos < P->numChaves && P->chaves[pos] == id) {
        /* nothing to do */
        return 0;
    }

    if(P->folha) {

        /* everybody above pos moves up one space */
        memmove(&P->chaves[pos+1], &P->chaves[pos], sizeof(*(P->chaves)) * (P->numChaves - pos));
        memmove(&P->byteOffset[pos+1], &P->byteOffset[pos], sizeof(*(P->byteOffset)) * (P->numChaves - pos));
        P->chaves[pos] = id;
        P->byteOffset[pos] = byteOffset;
        P->numChaves++;

    } else {

        /* insert in child */
        P2 = inserirSplit(P->filhos[pos], id, byteOffset, &mid, &byte);
        
        /* maybe insert a new key in b */
        if(P2) {

            /* every key above pos moves up one space */
            memmove(&P->chaves[pos+1], &P->chaves[pos], sizeof(*(P->chaves)) * (P->numChaves - pos));
            /* new kid goes in pos + 1*/
            memmove(&P->filhos[pos+2], &P->filhos[pos+1], sizeof(*(P->chaves)) * (P->numChaves - pos));

            /* every key above pos moves up one space */
            memmove(&P->byteOffset[pos+1], &P->byteOffset[pos], sizeof(*(P->byteOffset)) * (P->numChaves - pos));
            /* new kid goes in pos + 1*/
            memmove(&P->byteOffset[pos+2], &P->byteOffset[pos+1], sizeof(*(P->byteOffset)) * (P->numChaves - pos));
            P->chaves[pos] = mid;
            P->byteOffset[pos] = byte;
            P->filhos[pos+1] = P2;
            P->numChaves++;
        }
    }

    /* we waste a tiny bit of space by splitting now
     * instead of on next insert */
    if(P->numChaves >= ORDEM) {
        mid = P->numChaves/2;

        *chaveMedia = P->chaves[mid];
        *byteMedio = P->byteOffset[mid];

        P2 = malloc(sizeof(*P2));

        P2->numChaves = P->numChaves - mid - 1;
        P2->folha = P->folha;

        memmove(P2->chaves, &P->chaves[mid+1], sizeof(*(P->chaves)) * P2->numChaves);
        memmove(P2->byteOffset, &P->byteOffset[mid+1], sizeof(*(P->byteOffset)) * P2->numChaves);
        if(!P->folha) {
            memmove(P2->filhos, &P->filhos[mid+1], sizeof(*(P->filhos)) * (P2->numChaves + 1));
        }

        P->numChaves = mid;

        return P2;
    }
    else {
        return 0;
    }
}

void inserirPagina(Pagina* P, int id, int byteOffset)
{
    Pagina* P1;   /* new left child */
    Pagina* P2;   /* new right child */
    int chaveMedia;
    int byteMedio;

    P2 = inserirSplit(P, id, byteOffset, &chaveMedia, &byteMedio);

    if(P2) {
        /* basic issue here is that we are at the root */
        /* so if we split, we have to make a new root */

        P1 = malloc(sizeof(*P1));
        assert(P1);

        /* copy root to b1 */
        memmove(P1, P, sizeof(*P));

        /* make root point to b1 and b2 */
        P->numChaves = 1;
        P->folha = 0;
        P->chaves[0] = chaveMedia;
        P->byteOffset[0] = byteOffset;
        P->filhos[0] = P1;
        P->filhos[1] = P2;
    }
}