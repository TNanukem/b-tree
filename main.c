// Algoritmos e Estruturas de Dados 2
// Implementação de uma árvore B
// 
// Guilherme Lima Blatt		9771470
// Lucas Akira Morishita	9771320
// Thiago Músico			9771567
// Tiago Toledo Junior		9771309

#include "arquivo.h"

int main (void){
	int byteOffset = 0, RRNtotal = 0;
	int auxID; char auxTitulo[30], auxGenero[20];
	int inputMenu, outLoop = 0;
	int pos, encontrado = 0;
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
		printf("\n(1 - Criar Índice) \n(2 - Inserir Música) \n(3 - Pesquisar Música) \n(5 - Mostrar Árvore) \n(6 - Sair e Salvar)\n");
		printf("Observacao: E necessario sair do programa (funcionalidade 6) para atualizar o arquivo de log\n");
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
					printf("\nTitulo Invalido! Caraceteres especiais nao sao aceitos\n\n");

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
					printf("\nGenero Invalido! Caraceteres especiais nao sao aceitos\n\n");

					// Dá um reset nos inputs em caso de entrada inválida
					auxID = -1;
					strcpy(auxTitulo, "\0"); strcpy(auxGenero, "\0");

					break;
				}
				inserirMusica(auxID, auxTitulo, auxGenero, dados, log, &indice, &byteOffset, &RRNtotal, A);
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
					printf("\nNao existe chave com id <%d>\n", auxID);
				}
				
				break;

			case 5:
				EntraFila((&F), 0);
				fprintf(log, "Execucao de operacao para mostrar a arvore-B gerada: \n");
				printBTree(P, &F, indice, log);
				break;

			case 6:
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
