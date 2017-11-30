#include "arquivo.h"



int main (void){
	int i;
	int auxID; char auxTitulo[30], auxGenero[20], auxSize;
	int inputMenu, outLoop = 0;
	int tamTitulo, tamGenero;
	char buffer[200];
	Arvore *A = calloc(1, sizeof(Arvore));
	assert(A);
	// Abre o arquivo de dados e o cria se ele não existir
	// Permite a leitura no arquivo todo e a escrita no fim
	FILE *dados = fopen("dados.dat", "a+b");
	FILE *indice = NULL;
	FILE *log = fopen("log_TToledo.txt", "a");

	// Verifica se algum deles nao foi aberto
	if (!dados || !log) {
		printf("Memoria Heap insuficente!\n");
		return -1;
	}


	while(!outLoop){

		printf("\nInsira a funcionalidade desejada: ");
		fscanf(stdin, "%d", &inputMenu);


		// Switch responsável por controlar as opções do menu
		switch(inputMenu){
			case 1:
				//criarIndice();
				break;

			case 2:
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

				inserirMusica(auxID, auxTitulo, auxGenero, dados, log, &tamTitulo, &tamGenero);
				break;

			case 3:
				//pesquisaMusicaID();
				break;

			case 4:
				//removeMusicaID();
				break;

			case 5:
				//mostraArvoreB();
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

			case 89:
				printf("Teste de insercao de indice na arvore (RAM)\n");
				criarArvore(A);
				/*
				inserirId(A->raiz, 3, 7);
				printf("Pagina de id 3 inserido na arvore!\n");
				inserirId(A->raiz, 19, 7);
				printf("Pagina de id 19 inserido na arvore!\n");
				inserirId(A->raiz, 4, 7);
				printf("Pagina de id 4 inserido na arvore!\n");
				inserirId(A->raiz, 20, 7);
				printf("Pagina de id 20 inserido na arvore!\n");
				inserirId(A->raiz, 1, 7);
				printf("Pagina de id 1 inserido na arvore!\n");
				inserirId(A->raiz, 13, 7);
				printf("Pagina de id 13 inserido na arvore!\n");
				inserirId(A->raiz, 16, 7);
				printf("Pagina de id 16 inserido na arvore!\n");
				inserirId(A->raiz, 9, 7);
				printf("Pagina de id 9 inserido na arvore!\n");
				inserirId(A->raiz, 2, 7);
				printf("Pagina de id 2 inserido na arvore!\n");
				inserirId(A->raiz, 23, 7);
				printf("Pagina de id 23 inserido na arvore!\n");
				inserirId(A->raiz, 14, 7);
				printf("Pagina de id 14 inserido na arvore!\n");
				inserirId(A->raiz, 7, 7);
				printf("Pagina de id 7 inserido na arvore!\n");
				inserirId(A->raiz, 21, 7);
				printf("Pagina de id 21 inserido na arvore!\n");
				inserirId(A->raiz, 11, 7);
				printf("Pagina de id 11 inserido na arvore!\n");
				inserirId(A->raiz, 5, 7);
				printf("Pagina de id 5 inserido na arvore!\n");
				inserirId(A->raiz, 8, 7);
				printf("Pagina de id 8 inserido na arvore!\n");
				inserirId(A->raiz, 15, 7);
				printf("Pagina de id 15 inserido na arvore!\n");
				inserirId(A->raiz, 12, 7);
				printf("Pagina de id 12 inserido na arvore!\n");
				inserirId(A->raiz, 10, 7);
				printf("Pagina de id 10 inserido na arvore!\n");
				inserirId(A->raiz, 25, 7);
				printf("Pagina de id 25 inserido na arvore!\n");
				inserirId(A->raiz, 17, 7);
				printf("Pagina de id 17 inserido na arvore!\n");
				inserirId(A->raiz, 26, 7);
				printf("Pagina de id 26 inserido na arvore!\n");
				inserirId(A->raiz, 6, 7);
				printf("Pagina de id 6 inserido na arvore!\n");
				inserirId(A->raiz, 24, 7);
				printf("Pagina de id 24 inserido na arvore!\n");
				inserirId(A->raiz, 22, 7);
				printf("Pagina de id 22 inserido na arvore!\n");
				*/

				for (i = 0; i < 50; i++) {
					inserirId(A->raiz, 50-i, 7);
					printf("Pagina de id %d inserido na arvore!\n",50-i);
				}

				break;
			case 90:
				outLoop = 1;
				break;
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
	if (A) {
		free(A);
		A = NULL;
	}
	return 0;
}
