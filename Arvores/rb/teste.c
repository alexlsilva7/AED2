#include <stdlib.h>
#include <stdio.h>
#include "rb.h"

int main(int argc, char * argv[]){
	arvore a;
	//inicialização da árvore vazia
	inicializar(&a);
	
	int opcao;    
	int valor;
	
	//MENU
	while(1){
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				//INSERIR
				scanf("%d", &valor);
				inserir(valor,&a);
				break;
			
			case 2:
				//REMOVER
				scanf("%d", &valor);
				remover(valor,&a);
				break;
			case 3:
				//IMPRIMIR
				imprimir(a);
				printf("\n");
				break;
			case 10:
				printf("%d\n", altura(a));
				break;
			case 99:
				exit(0);
		}
	}
}
