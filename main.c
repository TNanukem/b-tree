#include "arquivo.h"

int main (void){

	int auxID; char auxTitulo[30], auxGenero[20], auxSize;
	int inputMenu, outLoop = 0;
	int tamTitulo, tamGenero;
	char buffer[200];

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
	return 0;
}
