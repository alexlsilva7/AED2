#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char * argv[]) {
	arvore a;
	int opcao;
	int controleFB;
	inicializar(&a);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						scanf("%d", &valor);
						a = adicionar(valor, a, &controleFB);
						break;
				case 2:
						scanf("%d", &valor);
						a = remover(valor, a);
						break;
				case 3:
						imprimir(a);
						printf("\n");
						break;
				case 99:
						exit(0);
		}
	}
}
