#include "arquivo.h"

// Tem que verificar se o arquivo de índice já existe Miss
void criarIndice(Arvore *A, FILE *dados, FILE *log, FILE **indice, int *byteOffset, int *RRNtotal){

	int duplication = 0;
	int pos, bufferSize, id = -1;
	char buffer[200];
	*byteOffset = 0;
	*RRNtotal = 0;
	// Pagina *pagina = calloc(1, sizeof(Pagina));


	// Verifica se existe arquivo de indice
	//*indice = fopen("arvore.idx", "r");


	if (!*indice) { // Criar um novo arvore.idx caso nao exista
		printf("arvore.idx nao encontrado. Criando...\n");
		*indice = fopen("arvore.idx", "w+");
		if (!(*indice)) {
			printf("Erro na criacao de arvore.idx! Cancelando...\n");
			return;
		}
		// Escrita no arquivo de log
		fprintf(log, "Execucao da criacao do arquivo de indice <arvore.idx> com base no arquivo dados <dados.dat>.\n");
		printf("Execucao da criacao do arquivo de indice <arvore.idx> com base no arquivo dados <dados.dat>.\n");

		// Cria e guarda arvore em disco
		criarArvore(A, *indice,RRNtotal);

		fseek(dados, 0, SEEK_SET);

		// Leitura de dados.dat
		while(fread(&bufferSize, sizeof(bufferSize), 1, dados)) {

			fread(buffer, bufferSize, 1, dados);
			pos = 0;
			sscanf(separaCampos(buffer, &pos), "%d", &id);

			inserirId(A->raiz, id, *byteOffset, *indice, RRNtotal, log, &duplication);
			*byteOffset += bufferSize + sizeof(bufferSize);
			printf("Registro de id %d inserido na arvore!\n",id);

			//Salva alteracao no arquivo de log
			if(duplication==0)
    			fprintf(log, "Chave <%d> inserida com sucesso\n", id);
			///////
		}
		A->estaAtualizado = 1;

	}
	else { // Se arvore.idx ja existe, verificar se esta atualizado
		printf("arvore.idx ja criado!\n");
		fclose(*indice);
		*indice = fopen("arvore.idx", "a+");
		return;

	}
}

int regVariavel(Registro r, char *buffer){

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

void inserirMusica(int id, char titulo[30], char genero[20], FILE *dados, FILE *log, FILE **indice, int *byteOffset, int *RRNtotal, Arvore *A){
	int pos, encontrado = 0;
	int duplication = 0;
	char buffer[200];
	// Parte do código responsável por inserir a música no arquivo de dados
	Registro *r = malloc(sizeof(Registro)); // Aloca um novo registro

	// Salva as varíaveis passadas como parâmetro no registro
	r->id = id;
	strcpy(r->titulo, titulo);
	strcpy(r->genero, genero);

	Pagina *P = malloc(sizeof(Pagina));

	pesquisarArvore(P, 0, id, &pos, &encontrado, *indice);
	
	if(encontrado){
		fprintf(log, "Execucao de operacao de INSERCAO de <%d>, <%s>, <%s>.\n", id, titulo, genero);
		fprintf(log, "Chave <%d> duplicada\n", id);
	}
	else{
		// Insere os dados no arquivo de log
		fprintf(log, "Execucao de operacao de INSERCAO de <%d>, <%s>, <%s>.\n", id, titulo, genero);
		// Precisa fazer a escrita no arquivo de log para as coisas da B-Tree também.

		// Variáveis para identificar o real tamanho das strings

		// Aloca no buffer os dados do registro
		int size = regVariavel(*r, buffer);

		fseek(dados, 0, SEEK_END);
		*byteOffset = ftell(dados);

		fseek(*indice, 0, SEEK_END);
		*RRNtotal = ftell(*indice)/sizeof(Pagina);

		fwrite(&size, sizeof(size), 1, dados);	// Escreve o tamanho do registro no começo dele
		fwrite(buffer, size, 1, dados);	// Escreve o buffer (os dados formatados do registro)

		// Parte do código responsável por atualizar o índice
		inserirId(0, id, *byteOffset, *indice, RRNtotal, log, &duplication);
		*byteOffset += sizeof(size) + size;		

		fprintf(log, "Chave <%d> inserida com sucesso\n", id);
	}
	
	free(r);
	free(P);
	r = NULL;

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


void pesquisaDados(int offset, char *titulo, char *genero, FILE *dados){
	int size, id, pos;
	char buffer[200];

	fseek(dados, offset, SEEK_SET);
	fread(&size, sizeof(size), 1, dados);

	fread(buffer, size, 1, dados);

	pos = 0;
	sscanf(separaCampos(buffer, &pos), "%d", &id);

	strcpy(titulo, separaCampos(buffer, &pos));
	strcpy(genero, separaCampos(buffer, &pos));

	printf("\nId = %d, Titulo = %s, Genero = %s\n", id, titulo, genero);

}
