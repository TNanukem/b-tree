#include "arquivo.h"


// Tem que verificar se o arquivo de índice já existe Miss
void criarIndice(Arvore* A, FILE *dados, FILE *log, FILE *indice){

	int tamTitulo = 0, tamGenero = 0;
	Registro *registro = NULL;
	// Pagina *pagina = calloc(1, sizeof(Pagina));

	// Escrita no arquivo de log
	printf("Execucao da criacao do arquivo de indice <indice.idx> com base no arquivo dados <dados.dat>.\n");

	// Abre o ponteiro do arquivo de indice
	indice = fopen("arvore.idx", "a+b");
	// Confere se foi aberto com sucesso
	if (!indice) {
		printf("Erro na leitura/escrita de arvore.idx\n");
		return;
	}

	// Deixa o ponteiro de dados no inicio do arquivo
	fseek(dados, 0, SEEK_SET);

	// Enquanto existirem dados para serem obtidos
	// fread retorna a quantidade de elementos de tamanho sizeof(Registro) se conseguir obter dados.
	// Em especifico, essa quantidade eh 1 (Segundo parametro). Caso chegue no End of File (EOF),
	// essa igualdade nao se verifica.
	while(fread(registro, 1, sizeof(Registro), dados) == 1) {
		// TODO
	}

	A->raiz = NULL;
}

int regVariavel(Registro r, char *buffer){

	// Imprime no buffer os dados do registro, formatados da maneira necessária
	char char_id[5];
	// Imprime no buffer os dados do registro, formatados da maneira necessária
	if(r.id <= 0xff){
		char_id[0] = r.id & 0xff;
		char_id[1] = '\0';
	}
	else if(r.id <= 0xffff){
		char_id[0] = r.id & 0xff;
		char_id[1] = (r.id >> 8) & 0xff;
		char_id[2] = '\0';
	}
	else if(r.id <=0xffffff){
		char_id[0] = r.id & 0xff;
		char_id[1] = (r.id >> 8) & 0xff;
		char_id[2] = (r.id >> 16) & 0xff;
		char_id[3] = '\0';
	}
	else {
		char_id[0] = r.id & 0xff;
		char_id[1] = (r.id >> 8) & 0xff;
		char_id[2] = (r.id >> 16) & 0xff;
		char_id[3] = (r.id >> 24) & 0xff;
		char_id[4] = '\0';
	}
	sprintf(buffer, "%s|%s|%s|", char_id, r.titulo, r.genero);
	return strlen(buffer);}

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

	// Insere os dados no arquivo de log
	fprintf(log, "Execucao de operacao de INSERCAO de <%d>, <%s>, <%s>.\n", id, titulo, genero);
	// Precisa fazer a escrita no arquivo de log para as coisas da B-Tree também.

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

int pesquisaMusicaID(int id, FILE *log, Arvore *A){

	// Escrita no arquivo de Log
	fprintf(log, "Execucao de operacao de PESQUISA de <%d>.\n", id);

	int encontrado = 0, pos = -1;
	pesquisarArvore(A->raiz, id, &pos, &encontrado);

	if(encontrado == 0){
		fprintf(log, "Chave <%d> nao encontrada\n", id);
	}
	else if(encontrado == 1){
		// Pega o offset de algum modo
		// fprintf(log, "Chave <%d> encontrada, offset <%d>\n", id, offset);
		// Pesquisa no arquivo de dados com o offset
		// fprintf(log, "Titulo: <%s>, Genero: <%s>\n", titulo, genero);
	}

	return encontrado;
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

int caractereValido(char *string){
	int i, comp, aux;
	comp = strlen((string));

	// Verifica se cada caractere inserido está de acordo com as especificações:
	// 65 - 90 => Letras Maiúsculas
	// 97 - 122 => Letras Minúsculas
	// 32 => Espaço
	// 48 - 57 => Números

	for(i = 0; i < comp; i++){

		if((string[i] >= 65 && string[i] <= 90) || (string[i] >= 97 && string[i] <= 122) || (string[i] == 32) 
			|| (string[i] >= 48 && string[i] <= 57))
				aux = 1;
		else{
			aux = 0;
			break;
		}
	}
	return aux;	

}