/* Algoritmos e Estruturas de Dados 2
 	 Trabalho 2 - B-Tree
	 Guilherme Blatt
	 Lucas Akira
	 Thiago Músico
	 Tiago Toledo */

#include "arquivo.h"

int main (void){

	int auxID; char auxTitulo[30], auxGenero[20];

	int inputMenu, outLoop = 0;

	while(!outLoop){

		printf("\nInsira a funcionalidade desejada: ");
		fscanf(stdin, "%d", &inputMenu);

		switch(inputMenu){
			case 1:
				CriarIndice();
				break;

			case 2:
				printf("\n Insira o ID da musica: ");
				fscanf(stdin, "%d", &auxID);

				printf("\n Insira o Titulo da Musica: ");
				fgets(auxTitulo, 30, stdin);

				printf("\n Insira o Genero da Musica: ");
				fgets(auxGenero, 20, stdin);

				InserirMusica(auxID, auxTitulo, auxGenero);
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
	return 0;
}
