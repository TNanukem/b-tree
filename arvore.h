#ifndef _ARVORE
#define _ARVORE

#define ORDEM 5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


typedef struct pagina{

	int numChaves;			// Número de chaves armazenadas na página
	int chaves[ORDEM];
	int byteOffset[ORDEM];	//
	int filhos[ORDEM+1]; // Guarda o RRN de cada filho dessa pagina
	int folha;				// Booleano (1/true)(0/false);

} Pagina;

typedef struct{
	int raiz;
	int estaAtualizado; // Flag que mostra se a arvore-B (indice) esta atualizada com o arquivo de dados
} Arvore;

void criarArvore(Arvore *A, FILE *indice, int *RRNtotal);

/* Pesquisa, por meio de busca binária, a posição de uma chave dentro
	de uma página da B-Tree.
*/

int procurarChave(int numChaves, int *chaves, int id);

/* Funcao que pesquisa recursivamente a arvore-B procurando um registro
	de chave igual a id. Caso a chave seja encontrada, retorna o ponteiro
	da pagina onde foi encontrado o registro, alem da posicao desse
	registro na pagina (via *pos - passagem por parametro). Tambem deixa
	a flag *encontrado (por parametro) como 1. Caso contrario, retorna o
	ponteiro da pagina e a posicao *pos onde o registro de chave id deveria
	estar na arvore, alem de deixar a flag *encontrado como 0.

	Resumo:
	Retorna: Um ponteiro para a pagina onde se encontra (ou deveria estar)
		o registro procurando
	Parametros:
		- *P: Pagina atual da recursao
		- id: chave procurada
		- pos: referencia para a posicao da chave dentro da pagina
		- encontrado: referencia para dizer se a funcao encontrou ou nao um registro com chave igual a id
*/
int pesquisarArvore(Pagina *P, int RRN, int id, int &pos, int &encontrado, FILE* indice);

//int adicionarArvore(Arvore *A, int id);
void inserirId(int RRN_P, int id, int byteOffset, FILE *indice, int *RRNtotal, FILE *log, int *duplication);


#endif
