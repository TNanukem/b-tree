#include "arquivo.h"

int main (void){

	int auxID; char auxTitulo[30], auxGenero[20];
	int inputMenu, outLoop = 0;

	// Abre o arquivo de dados e o cria se ele não existir
	// Permite a leitura no arquivo todo e a escrita no fim
	FILE *dados = fopen("dados.dad", "a+b");

	while(!outLoop){

		printf("\nInsira a funcionalidade desejada: ");
		fscanf(stdin, "%d", &inputMenu);

		
		// Switch responsável por controlar as opções do menu
		switch(inputMenu){
			case 1:
				CriarIndice();
				break;

			case 2:
				printf("\n Insira o ID da musica: ");
				fscanf(stdin, "%d", &auxID);

				printf("\n Insira o Titulo da Musica: ");
				fgets(auxTitulo, 30, stdin);
				
				//if(!caractereValido(auxTitulo)){
				//	printf("Titulo Invalido! Caraceteres especiais nao sao aceitos");
				//	break;
				//}

				printf("\n Insira o Genero da Musica: ");
				fgets(auxGenero, 20, stdin);
				
				//if(!caractereValido(auxGenero)){
				//	printf("Genero Invalido! Caraceteres especiais nao sao aceitos");
				//	break;
				//}

				InserirMusica(auxID, auxTitulo, auxGenero, reg, dados);
				break;

			case 3:
				PesquisaMusicaID();
				break;

			case 4:
				RemoveMusicaID();
				break;

			case 5:
				MostraArvoreB();
				break;

			case 6:
				outLoop = 1;
				break;

			default:
				printf("\n Entrada Invalida!\n");
				break;
		}
	}
	fclose(dados);
	return 0;
}