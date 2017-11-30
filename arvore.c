#include "arvore.h"

void criarArvore(Arvore *A) {

	A->raiz = calloc(1, sizeof(Pagina));
	A->raiz->numChaves = 0;
	A->raiz->folha = 1;
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

Pagina* verificaSplit(Pagina* P, int id, int byteOffset, int *chaveMedia, int *byteMedio) {
    int pos;
    int mid;
    int byte;
    Pagina* P2;

		/* Retorna a posicao de id, se encontrado na pagina, ou a posicao que id
		   deveria ficar caso nao encontrado */
    pos = procurarChave(P->numChaves, P->chaves, id);

    if(pos < P->numChaves && P->chaves[pos] == id) {
        /* Se achou a chave na arvore B, nao precisa inserir */
        return NULL;
    }

		// Se a pagina for folha, deve-se tentar inserir id nela
    if(P->folha) {
				/* Todas as chaves maiores que id devem ser deslocados em 1 espaco para a direita*/
        memmove(&P->chaves[pos+1], &P->chaves[pos], sizeof(*(P->chaves)) * (P->numChaves - pos));
        memmove(&P->byteOffset[pos+1], &P->byteOffset[pos], sizeof(*(P->byteOffset)) * (P->numChaves - pos));
        P->chaves[pos] = id;
        P->byteOffset[pos] = byteOffset;
        P->numChaves++;

    } else {

				/* Se nao for folha, chamar verificaSplit na pagina filha recursivamente
					 ate chegar em uma pagina folha. Note que mid e byte nesse caso guardam
					 os valores do id "promovido" (que vai para a pagina pai) e seu byteoffset,
					 respectivamente */
        P2 = verificaSplit(P->filhos[pos], id, byteOffset, &mid, &byte);

        /* Se o split foi feito: */
        if(P2) {

            /* every key above pos moves up one space */
						/* Desloca as chaves para dar lugar a nova chave (id)*/
            memmove(&P->chaves[pos+1], &P->chaves[pos], sizeof(*(P->chaves)) * (P->numChaves - pos));
            /* new kid goes in pos + 1*/
						/* Inclusive o vetor que guarda os filhos tambem deve ser deslocado em um espaco
						   para a direita, para dar lugar ao filho de id */
            memmove(&P->filhos[pos+2], &P->filhos[pos+1], sizeof(*(P->filhos)) * (P->numChaves - pos));

            /* every key above pos moves up one space */
						/* Mesmo deslocamento das chaves para os byteOffset*/
            memmove(&P->byteOffset[pos+1], &P->byteOffset[pos], sizeof(*(P->byteOffset)) * (P->numChaves - pos));

						// Atualiza os valores 
            P->chaves[pos] = mid;
            P->byteOffset[pos] = byte;
            P->filhos[pos+1] = P2;
            P->numChaves++;
        }
    }

    /* we waste a tiny bit of space by splitting now
     * instead of on next insert */
		/* Verifica se ocorreu overflow na pagina apos a insercao de id */
    if(P->numChaves >= ORDEM) {
        mid = P->numChaves/2;

        *chaveMedia = P->chaves[mid];
        *byteMedio = P->byteOffset[mid];

				// Aloca nova pagina para receber (a segunda) metade das chaves
				// P2 esta na mesma profundidade que o P chamado
        P2 = malloc(sizeof(Pagina));

				// A nova pagina vai receber a metade dos dados menos 1 chave (a que vai ser promovida)
        P2->numChaves = P->numChaves - mid - 1;
				// Se P for folha, entao P2 tambem sera (mesma profundidade)
        P2->folha = P->folha;

				// Copia a segunda metade de P para P2; P fica com a primeira metade das chaves
        memmove(P2->chaves, &P->chaves[mid+1], sizeof(*(P->chaves)) * P2->numChaves);
				// Analogo com os byteOffset de cada chave
        memmove(P2->byteOffset, &P->byteOffset[mid+1], sizeof(*(P->byteOffset)) * P2->numChaves);

				/* Os filhos das chaves as quais foram para P2 tambem devem ser colocados
				   em P2 */
        if(!P->folha) {
            memmove(P2->filhos, &P->filhos[mid+1], sizeof(*(P->filhos)) * (P2->numChaves + 1));
        }
				// P agora fica com a primeira metade das chaves, e por consequencia o numero de
				// chaves cai pela metade
        P->numChaves = mid;

        return P2;
    }
    else { // Se nao teve overflow, retornar nulo (nao sera necessario criar nova pagina)
        return NULL;
    }
}

void inserirId(Pagina* P, int id, int byteOffset) {
    Pagina *P1;   /* Possivel nova pagina filha a esquerda */
    Pagina *P2;   /* Possivel nova pagina filha a direita */
    int chaveMedia;
    int byteMedio;

		// Verifica se o split deve ser feito, e o faz em caso afirmativo
    P2 = verificaSplit(P, id, byteOffset, &chaveMedia, &byteMedio);

		/* Se split foi feito na raiz (para isso P2 deve ser nao-nulo nessa linha),
		   deve-se criar uma nova raiz */
    if(P2) {
        /* basic issue here is that we are at the root */
        /* so if we split, we have to make a new root */

        P1 = malloc(sizeof(Pagina));
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
