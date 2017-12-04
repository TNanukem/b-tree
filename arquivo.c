#include "arquivo.h"


// Tem que verificar se o arquivo de índice já existe Miss
void criarIndice(Arvore *A, FILE *dados, FILE *log, FILE **indice, int *byteOffset, int *RRNtotal){

	int tamTitulo = 0, tamGenero = 0;
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
		/*
		Pagina *p = calloc(1, sizeof(Pagina));
		int j = 0, k;

		if (p) {

			while (fread(p, sizeof(Pagina), 1, *indice)) {
				inserirId(j, int id, int byteOffset, FILE *indice, int *RRNtotal, FILE *log, int *duplication)
				j++;
			}

			free(p);
		} else {
			printf("Erro\n");
		}
		*/
	}


	// Deixa o ponteiro de dados no inicio do arquivo
	//fseek(dados, 0, SEEK_SET);

	// Enquanto existirem dados para serem obtidos
	// fread retorna a quantidade de elementos de tamanho sizeof(Registro) se conseguir obter dados.
	// Em especifico, essa quantidade eh 1 (Segundo parametro). Caso chegue no End of File (EOF),
	// essa igualdade nao se verifica.
	/*
	while(fread(registro, 1, sizeof(Registro), dados) == 1) {
		// TODO
	}
	*/
	//A->raiz = NULL;
}

int regVariavel(Registro r, char *buffer){
	/*
	// Imprime no buffer os dados do registro, formatados da maneira necessária
	char char_id[5];

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
	*/
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

void inserirMusica(int id, char titulo[30], char genero[20], FILE *dados, FILE *log, FILE **indice, int *tamTitulo, int *tamGenero, int *byteOffset, int *RRNtotal, Arvore *A){
	int i;
	int duplication = 0;
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

	fwrite(&size, sizeof(size), 1, dados);	// Escreve o tamanho do registro no começo dele
	fwrite(buffer, size, 1, dados);	// Escreve o buffer (os dados formatados do registro)

	// Parte do código responsável por atualizar o índice
	inserirId(0, id, *byteOffset, *indice, RRNtotal, log, &duplication);
	*byteOffset += sizeof(size) + size;

	//Alterando o Arquivo de log
	if(duplication == 0) {
		printf("Registro de id %d inserido na arvore!\n",id);
		fprintf(log, "Chave <%d> inserida com sucesso\n", id);
	}
	free(r);
	r = NULL;

}

int pesquisaMusicaID(int id, FILE *log, Arvore *A, FILE *dados){
	char titulo[30]; char genero[20];

	// Escrita no arquivo de Log
	fprintf(log, "Execucao de operacao de PESQUISA de <%d>.\n", id);

	int encontrado = 0, pos = -1;
	//pesquisarArvore(A->raiz, id, &pos, &encontrado);

	if(encontrado == 0){
		fprintf(log, "Chave <%d> nao encontrada\n", id);
	}
	else if(encontrado == 1){

		fprintf(log, "Chave <%d> encontrada, offset <%d>,\n", id, pos);

		// Pesquisa no arquivo de dados com o offset
		pesquisaDados(pos, titulo, genero, dados);

		fprintf(log, "Titulo: <%s>, Genero: <%s>\n", titulo, genero);
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

int idConvert(char *idString){
	int id = 0;
	int temp = 0;
	int i = 0;
	char char_id[5];
	char t;


	while(idString[i] != '\0'){
		temp = idString[i];

		if(temp<0)
			temp += 256;

		id += exp5(256, i) * temp;
		i++;
	}

	/*
	if(strlen(idString) <= 1){
		id = idString[0];
		printf("ID 1 = %d\n", id);
	}
	else if(strlen(idString) <= 2){

		id = ((256 + idString[0]) + (idString[1]));
		printf("ID 2 = %d\n", id);
	}
	else if(strlen(idString) <= 3){
		id = ((idString[0] <<16) | (idString [1] << 8)| idString[2]);
		printf("ID 3 = %d\n", id);
	}
	else {
		id = ((idString[0] << 24) | (idString [1] << 16) | (idString[2] << 8) | idString[3]);
		printf("ID 4 = %d\n", id);
	}
*/
	return id;
}

int exp5(int e, int a){
		int i, temp = e;
		if(a == 0)
			e = 1;
		for(i = 1; i< a; i++){
			e *= temp;
		}

		return e;
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

	printf("%d||%d|%s|%s\n", size, id, titulo, genero);

}
/*
int mostrarArvore(int RRN_P, FILE *indice) {
	int i;
	if (RRN_P >= 0) {
		// Carrega Pagina de RRN igual a P
		fseek(indice, RRN_P*sizeof(Pagina), SEEK_SET);
		P = calloc(1, sizeof(Pagina));
		if (!P) {
			printf("Memoria Heap insuficente!\n");
			return;
		}
		fread(P, sizeof(Pagina), 1, indice);
		for (i = 0; i < ORDEM; i++) {
			return mostrarArvore(P->filhos[i]);
		}
		free(P);
	} else {

		return -1;
	}

}*/
