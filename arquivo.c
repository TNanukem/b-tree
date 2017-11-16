#include "arquivo.h"


// Tem que verificar se o arquivo de índice já existe Miss
void criarIndice(Arvore* A, FILE *log){

	// Escrita no arquivo de log
	printf("Execucao da criacao do arquivo de indice <indice.idx> com base no arquivo dados <dados.dat>.\n");

	A->raiz = NULL;
}

int regVariavel(Registro r, char *buffer){

	// Imprime no buffer os dados do registro, formatados da maneira necessária
	sprintf(buffer, "%d|%s|%s|", r.id, r.titulo, r.genero);
	return strlen(buffer);
}

char *separaCampos(char *buffer, int *p) {
    int pos = *p;

    // Troca todos os '|' por '\0' e permite que tenhamos acesso individual a cada campo
    while(buffer[*p]!='|')
        (*p)++;
    buffer[*p] = '\0';
    (*p)++;
    return &buffer[pos];
}

void inserirMusica(int id, char titulo[30], char genero[20], FILE *dados, FILE *log, int *tamTitulo, int *tamGenero){

	// Parte do código responsável por inserir a música no arquivo de dados
	Registro *r = malloc(sizeof(Registro)); // Aloca um novo registro

	// Salva as varíaveis passadas como parâmetro no registro
	r->id = id;
	strcpy(r->titulo, titulo);
	strcpy(r->genero, genero);

	// Criação do log para inserção da música
	fprintf(log, "Execucao de operacao de INSERCAO de <%d>, <%s>, <%s>.\n", id, titulo, genero);
	// O resto precisa da B-TREE.

	// Variáveis para identificar o real tamanho das strings
	*tamTitulo = strlen(r->titulo);
	*tamGenero = strlen(r->genero);

	// Aloca no buffer os dados do registro
	char buffer[200];
	int size = regVariavel(*r, buffer);

	fwrite(&size, sizeof(int), 1, dados);	// Escreve o tamanho do registro no começo dele
	fwrite(&buffer, sizeof(buffer), 1, dados);	// Escreve o buffer (os dados formatados do registro)

	// Parte do código responsável por atualizar o índice

	free(r);

}

int pesquisaMusicaID(int id, FILE *log){

	// Escrita no arquivo de Log
	fprintf(log, "Execucao de operacao de PESQUISA de <%d>.\n", id);
	// O resto precisa da B-TREE
}

void removeMusicaID(int id, FILE *log){

	// Escrita no arquivo de log
	fprintf(log, "Execucao de operacao de REMOCAO de <%d>.\n", id);
	// Precisa da B-TREE pro resto

}

void mostraArvoreB(FILE *log){

	// Escrita no arquivo de log
	fprintf(log, "Execucao de operacao para mostrar a arvore-B gerada:\n");
	// Precisa da B-TREE pro resto

}

/*int caractereValido(char *string){
	int i, comp;
	comp = strlen((string));
	for(i = 0; i < comp; i++){
		if(*string[i] < 65 || (*string[i] > 90 && *string[i] < 97) || *string[i] > 122){
			return 0;
		}
	}
	return 1;

} */
