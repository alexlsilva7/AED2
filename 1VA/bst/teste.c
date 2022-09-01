#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int main(int argc, char * argv[]){
	arvore a;
	//inicialização da árvore vazia
	a = NULL;
	
	int opcao;
	int valor;
	
	//MENU
	while(1){
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				//ADICIONAR
				scanf("%d", &valor);
				a = inserir(a,valor);
				break;
			case 2:
				//PREORDER
				preOrder(a);
				printf("\n");
				break;
			case 3:
				//INORDER
				inOrder(a);
				printf("\n");
				break;
			case 4:
				//POSORDER
				posOrder(a);
				printf("\n");
				break;
			case 5:
				//REVERSO
				reverso(a);
				printf("\n");
				break;
			case 6:
				//QTDPRIMO
				printf("%d\n",qtdPrimo(a));
				break;
			case 7:
				//SUCESSOR
				scanf("%d", &valor);
				printf("%d\n", sucessor(a,valor));
				break;
			case 8:
				//CAMINHO
				scanf("%d", &valor);
				caminho(a,valor);
				printf("\n");
				break;
			case 9:
				//REMOVER
				scanf("%d", &valor);
				a = remover(a,valor);
				break;
			case 10:
				printf("%d\n", altura(a));
				break;
			case 99:
				exit(0);
		}
	}
}
