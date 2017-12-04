#include "arquivo.h"

int main (void){
	int i, byteOffset = 0, RRNtotal = 0;
	int auxID; char auxTitulo[30], auxGenero[20], auxSize;
	int inputMenu, outLoop = 0;
	int nivel = 0, mudarnivel = -1;
	int tamTitulo, tamGenero, pos, encontrado = 0;
	char buffer[200];
	Arvore *A = (Arvore*) malloc(sizeof(Arvore));
	Pagina *P = malloc(sizeof(Pagina));
	Fila F; 
	CriaFila(&F);
	// Abre o arquivo de dados e o cria se ele não existir
	// Permite a leitura no arquivo todo e a escrita no fim
	FILE *dados = fopen("dados.dat", "a+b");
	FILE *indice = fopen("arvore.idx", "r");
	FILE *log = fopen("log_TToledo.txt", "a");

	//Coloca o tempo e a data no arquivo de log
	time_t tempoAtual;
	time(&tempoAtual);
	fprintf(log, "--------------------- %s", ctime(&tempoAtual));

	// Verifica se algum deles nao foi aberto
	if (!dados || !log) {
		printf("Memoria Heap insuficente!\n");
		return -1;
	}


	while(!outLoop){
		printf("(1 - Criar Índice) \n(2 - Inserir Música) \n(3 - Pesquisar Música) \n(5 - Mostrar Árvore) \n(6 - Sair)\n");
		printf("\nInsira a funcionalidade desejada: ");
		fscanf(stdin, "%d", &inputMenu);


		// Switch responsável por controlar as opções do menu
		switch(inputMenu){
			case 1:
				criarIndice(A, dados, log, &indice, &byteOffset, &RRNtotal);
				break;

			case 2:
				if (indice == NULL) {
					// Indice nao foi criado
					printf("Erro! Arquivo de indice nao criado! Retornando ao menu...\n");
					break;
				}
				fclose(indice);
				indice = fopen("arvore.idx", "r+");
				if (!indice) {
					printf("Erro\n");
					return -1;
				}

				printf("\n Insira o ID da musica: ");
				fscanf(stdin, "%d", &auxID);
				getchar();

				printf("\n Insira o Titulo da Musica: ");
				fgets(auxTitulo, 30, stdin);
				auxTitulo[strlen(auxTitulo) - 1] = '\0';	// Impede a leitura do \n no input

				// Verificando a validade dos caracteres do título
				if(!caractereValido(auxTitulo)){
					printf("Titulo Invalido! Caraceteres especiais nao sao aceitos\n");

					// Dá um reset nos inputs em caso de entrada inválida
					auxID = -1;
					strcpy(auxTitulo, "\0");

					break;
				}

				printf("\n Insira o Genero da Musica: ");
				fgets(auxGenero, 20, stdin);
				auxGenero[strlen(auxGenero) - 1] = '\0';	// Impede a leitura do \n no input

				// Verificando a validade dos caraceteres do gênero
				if(!caractereValido(auxGenero)){
					printf("Genero Invalido! Caraceteres especiais nao sao aceitos\n");

					// Dá um reset nos inputs em caso de entrada inválida
					auxID = -1;
					strcpy(auxTitulo, "\0"); strcpy(auxGenero, "\0");

					break;
				}
				inserirMusica(auxID, auxTitulo, auxGenero, dados, log, &indice, &tamTitulo, &tamGenero, &byteOffset, &RRNtotal, A);
				break;

			case 3:
				printf("\nInsira o ID da musica: ");
				fscanf(stdin, "%d", &auxID);
				getchar();

				fprintf(log, "Execucao de operacao de PESQUISA de <%d>.\n", auxID);

				byteOffset = pesquisarArvore(P, 0, auxID, &pos, &encontrado, indice);
				if(encontrado){
					pesquisaDados(byteOffset, auxTitulo, auxGenero, dados);
					fprintf(log, "Chave <%d> encontrada, Offset <%d>, Titulo: <%s>, Genero: <%s>\n", auxID, byteOffset, auxTitulo, auxGenero);
				}
				else{
					fprintf(log, "Chave nao <%d> encontrada\n", auxID);
					printf("Id nao encontrado!\n");
				}
				
				//pesquisaMusicaID();
				break;

			case 5:
				EntraFila((&F), 0);
				fprintf(log, "Execucao de operacao para mostrar a arvore-B gerada: \n");
				printBTree(P, &F, indice, &nivel, &mudarnivel, log);
				break;

			case 6:
				outLoop = 1;
				int pos, auxsize;
				char IDzin[5]; auxID = -1;

				// Testando a leitura do arquivo



				fseek(dados, 0, SEEK_SET);
				while(fread(&auxsize, sizeof(auxsize), 1, dados)){

					fread(buffer, auxsize, 1, dados);
					pos = 0;

					sscanf(separaCampos(buffer, &pos), "%d", &auxID);
					/*
					//auxID = (int) *(separaCampos(buffer, &pos));
					sscanf(separaCampos(buffer, &pos), "%s", IDzin);
					auxID = idConvert(IDzin);
					*/
					//memmove(&auxID, buffer, sizeof(auxID));
					//pos = sizeof(auxID);
					strcpy(auxTitulo, separaCampos(buffer, &pos));
					strcpy(auxGenero, separaCampos(buffer, &pos));

					printf("%d||%d|%s|%s|\n", auxsize, auxID, auxTitulo, auxGenero);
				}
				/*
				printf("PESQUISA: \n");
				pesquisaDados(67, auxTitulo, auxGenero, dados);
				*/
				break;
			case 88:
				/*
				printf("Noia\n");
				criarArvore(A, NULL);
				for(i = 0; i < 100; i++)
					inserirId(A->raiz, 100-i, 2*i, NULL);
				break;
				*/
			case 89:
				printf("Teste\n");
				FILE *i = fopen("arvore.idx", "r");
				Pagina *p = calloc(1, sizeof(Pagina));
				int folha, numChaves,j, k;



				if (p) {
					for (k = 0;k < 10;k++) {
						fseek(i, k*sizeof(Pagina), SEEK_SET);
						fread(p, sizeof(Pagina), 1, i);
						folha = p->folha;
						numChaves = p->numChaves;
						printf("RRN: %d\n", k);
						printf("Folha: %d\n", folha);
						printf("numChaves: %d\n", numChaves);
						printf("chaves: ");
						for (j = 0; j < (p->numChaves); j++) {
							printf("%d ", p->chaves[j]);
						}
						printf("\n");
						printf("byteOffset: ");
						for (j = 0; j < p->numChaves; j++) {
							printf("%d ", p->byteOffset[j]);
						}
						printf("\n");
						printf("RRN dos filhos: ");
						for (j = 0; j < (p->numChaves)+1; j++) {
							printf("%d ", p->filhos[j]);
						}
						printf("\n");
					}


					fclose(i);
				} else {
					printf("Erro\n");
				}



				//criarArvore(A);
				/*
				for (i = 0; i < 50; i++) {
					inserirId(A->raiz, 50-i, 7);
					printf("Pagina de id %d inserido na arvore!\n",50-i);
				}
				*/
				break;
			case 90:
				outLoop = 1;
				break;
			case 99:
			 	//mostrarArvore(A);
			default:
				printf("\n Entrada Invalida!\n");
				break;
		}
	}

	// Finaliza os ponteiros para FILE, sempre verificando se realmente nao sao nulos
	if (dados) {
		fclose(dados);
		dados = NULL;
	}

	if (indice) {
		fclose(indice);
		indice = NULL;
	}

	if (log) {
		fclose(log);
		log = NULL;
	}
	if (indice) {
		fclose(indice);
		indice = NULL;
	}
	if (A) {
		free(A);
		A = NULL;
	}

	return 0;
}
