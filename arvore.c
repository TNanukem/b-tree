#include "arvore.h"

void criarArvore(Arvore *A, FILE *indice, int *RRNtotal) {
	Pagina *P = calloc(1, sizeof(Pagina));
	if (!P) {
		printf("Memoria Heap insuficiente!\n");
		return;
	}
	P->numChaves = 0;
	P->folha = 1;
	fwrite(P, sizeof(Pagina), 1, indice);	// Guarda raiz no indice
	A->raiz = *RRNtotal;
	(*RRNtotal)++;
	free(P);
	P = NULL;
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
	/*
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
	*/
}

int verificaSplit(int RRN_P, int id, int byteOffset, int *chaveMedia, int *byteMedio, FILE *indice, int *RRNtotal, FILE *log) {
    int pos,mid, byte, RRN_P2;
		Pagina *P, *P2;

		// Carrega Pagina de RRN igual a P
		fseek(indice, RRN_P*sizeof(Pagina), SEEK_SET);
		P = calloc(1, sizeof(Pagina));
		if (!P) {
			printf("Memoria Heap insuficente!\n");
			return -1;
		}
		fread(P, sizeof(Pagina), 1, indice);

		/* Retorna a posicao de id, se encontrado na pagina, ou a posicao que id
		   deveria ficar caso nao encontrado */
    pos = procurarChave(P->numChaves, P->chaves, id);

    if(pos < P->numChaves && P->chaves[pos] == id) {
        /* Se achou a chave na arvore B, nao precisa inserir */
		//Salva alteracao no arquivo de log
        fprintf(log, "Chave <%d> duplicada\n", id);
        return -1;
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
        RRN_P2 = verificaSplit(P->filhos[pos], id, byteOffset, &mid, &byte, indice, RRNtotal, log);

        /* Se o split foi feito: */
        if(RRN_P2 != -1) {

			/* Desloca as chaves para dar lugar a nova chave (id)*/
            memmove(&P->chaves[pos+1], &P->chaves[pos], sizeof(*(P->chaves)) * (P->numChaves - pos));

			/* Inclusive o vetor que guarda os filhos tambem deve ser deslocado em um espaco
			   para a direita, para dar lugar ao filho de id */
            memmove(&P->filhos[pos+2], &P->filhos[pos+1], sizeof(*(P->filhos)) * (P->numChaves - pos));

			/* Mesmo deslocamento das chaves para os byteOffset*/
            memmove(&P->byteOffset[pos+1], &P->byteOffset[pos], sizeof(*(P->byteOffset)) * (P->numChaves - pos));

			// Atualiza os valores
            P->chaves[pos] = mid;
            P->byteOffset[pos] = byte;

			/* Se pos+1 == ORDEM da arvore-b, o indice [pos+1] existe no
			   vetor filhos (serve apenas para armazenar o overflow) */
          	P->filhos[pos+1] = RRN_P2;
            P->numChaves++;
        }
    }


	/* Verifica se ira ocorrer um overflow na pagina apos a insercao de um proximo id */
    if(P->numChaves >= ORDEM) {
        mid = P->numChaves/2;

        *chaveMedia = P->chaves[mid];
        *byteMedio = P->byteOffset[mid];

		// Aloca nova pagina para receber (a segunda) metade das chaves
		// P2 esta na mesma profundidade que o P chamado
				P2 = calloc(1, sizeof(Pagina));
				if (!P2) {
					printf("Memoria Heap insuficente!\n");
					return -1;
				}
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


        		//Salva alteracao no arquivo de log
				fprintf(log, "Divisao de no - pagina %d\n", RRN_P);

				// Atualiza P no arquivo de indice
				fseek(indice, RRN_P*sizeof(Pagina), SEEK_SET);
				fwrite(P, sizeof(Pagina), 1, indice);
				free(P);
				P = NULL;

				// Salva P2 no final do arquivo de indice
				fseek(indice, 0, SEEK_END);
				fwrite(P2, sizeof(Pagina), 1, indice);
				(*RRNtotal)++;
				free(P2);
				P2 = NULL;

        return (*RRNtotal);
    }
    else { // Se nao ocorrer overflow na proxima insercao, retornar nulo (nao sera necessario criar nova pagina)
			// Atualiza P no arquivo de indice
			fseek(indice, RRN_P*sizeof(Pagina), SEEK_SET);
			fwrite(P, sizeof(Pagina), 1, indice);
			free(P);
			P = NULL;
      return -1;
    }
}

void inserirId(int RRN_P, int id, int byteOffset, FILE *indice, int *RRNtotal, FILE *log) {
    Pagina *P1;
    Pagina *P;
    int chaveMedia, byteMedio;
		/* Possivel nova pagina filha a esquerda tem RRN igual ao total (ultima pagina a ser inserida)*/
		int RRN_P2; /* Possivel nova pagina filha a direita */

	// Verifica se o split deve ser feito, e o faz em caso afirmativo
    RRN_P2 = verificaSplit(RRN_P, id, byteOffset, &chaveMedia, &byteMedio, indice, RRNtotal, log);


	/* Se split foi feito na raiz (para isso P2 deve ser nao-nulo nessa linha),
	   deve-se criar uma nova raiz */
    if(RRN_P2 != -1) {

    	//Aloca memória para novo filho
      P1 = malloc(sizeof(Pagina));
			if (!P1) {
				printf("Memoria Heap insuficente!\n");
				return;
			}

			// Carrega Pagina de RRN igual a P
			fseek(indice, RRN_P*sizeof(Pagina), SEEK_SET);
			P = calloc(1, sizeof(Pagina));
			if (!P) {
				printf("Memoria Heap insuficente!\n");
				return;
			}
			fread(P, sizeof(Pagina), 1, indice);

      //Copia para P1 o filho ja dividido
      memmove(P1, P, sizeof(*P));

      //Faz nova raiz que aponta para P1 e P2
      P->numChaves = 1;
      P->folha = 0;
      P->chaves[0] = chaveMedia;
      P->byteOffset[0] = byteMedio;
      P->filhos[0] = *RRNtotal;
      P->filhos[1] = RRN_P2;

			// Atualiza P no arquivo de indice
			fseek(indice, RRN_P*sizeof(Pagina), SEEK_SET);
			fwrite(P, sizeof(Pagina), 1, indice);
			free(P);
			P = NULL;

			// Salva P1 no final do arquivo de indice
			fseek(indice, 0, SEEK_END);
			fwrite(P1, sizeof(Pagina), 1, indice);
			(*RRNtotal)++;
			free(P1);
			P1 = NULL;

    }

}
