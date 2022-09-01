#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int main(int argc, char * argv[]){
	arvore a = NULL;
	int aumentou = 0;
	int *cresceu = &aumentou;
	
	int abaixou = 0;
	int *diminuiu = &abaixou;
	
	int opcao;
	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						scanf("%d", &valor);
						a = inserir(a, valor, cresceu);
						break;
				case 2:
						scanf("%d", &valor);
						a = remover(a, valor, diminuiu);
						break;
				case 3:
						imprimir(a);
						printf("\n");
						break;
				case 99:
						exit(0);
		}
	}
	
	/*a = remover(a, 28, diminuiu);
	preOrderPrintFB(a);
	printf("\n");
	
	a = remover(a, 26, diminuiu);
	preOrderPrintFB(a);
	printf("\n");
	
	a = remover(a, 18, diminuiu);
	preOrderPrintFB(a);
	printf("\n"); 
	//DEBUGAR NO CODEBLOCKS*/
}
