#include "arquivo.h"


// Tem que verificar se o arquivo de índice já existe Miss
void criarIndice(Arvore* A){
	A->raiz = NULL;
}

int regVariavel(Registro r, char *buffer){
	sprintf(buffer, "%d|%s|%s|", r.id, r.titulo, r.genero);
	return strlen(buffer);
}

void inserirMusica(int id, char titulo[30], char genero[20], FILE *dados){

	// Parte do código responsável por inserir a música no arquivo de dados
	Registro *r = malloc(sizeof(Registro));

	r->id = id;
	strcpy(r->titulo, titulo);
	strcpy(r->genero, genero);

	char buffer[200];
	int size = regVariavel(*r, buffer);
	fwrite(&size, sizeof(size), 1, dados); // Escreve o tamanho do registro
	fwrite(&buffer, size, 1, dados); // Escreve os dados com as |

	// Parte do código responsável por atualizar o índice
	if(A->raiz == NULL){
		Pagina p = (Pagina*) malloc(sizeof(Pagina));
		A->raiz = p;
		p->folha = 0;
		p->numChaves = 1;
		p->chaves[0] = id;
		p->byteoffset[0] = 0;	
	}

	free(r);

}

int pesquisaMusicaID(int id){

}

void removeMusicaID(){

}

void mostraArvoreB(){
	
}

int caractereValido(char *string){
	int i, comp;
	comp = strlen((string));
	for(i = 0; i < comp; i++){
		if(*string[i] < 65 || (*string[i] > 90 && *string[i] < 97) || *string[i] > 122){
			return 0;
		}
	}
	return 1;

}