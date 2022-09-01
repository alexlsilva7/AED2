#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

#include "rb.h"

void printMenu(){
	printf("\n------------------- MENU -------------------\n");
	printf("1 - Adicionar livro\n");
	printf("2 - Buscar livro pelo codigo\n");
	printf("3 - Imprimir altura da árvore de indices\n");
	printf("4 - Pre order (com cores)\n");
	printf("5 - In order (com cores)\n");
	printf("6 - Pos order (com cores)\n");
	printf("99 - Sair e salvar\n");
	printf("----------------------------------------------\n");
	printf("Digite uma opção: ");
}

int main(int argc, char * argv[]) {

	tabela tab;
	int opcao;
	inicializarTabela(&tab);
	printf("\nImplementação de Indexação - AED 2021.1\n");
	while(1) {
		printMenu();
		scanf("%d", &opcao);
		printf("\n");
		switch(opcao) {
				int valor;
				case 1:
						adicionarLivro(&tab, ler_dados());
						break;
				
				case 2:	
						printf("Digite o codigo do livro: ");
						int livroBusca;
						scanf("%d", &livroBusca);
						dado* livroEncontrado = buscarLivro(&tab, livroBusca);
						if (livroEncontrado != NULL){
							printf("\n-----LIVRO ENCONTRADO-----\n-Codigo: %d \n-Titulo: %s \n-Autor: %s \n-Ano: %s\n--------------------------\n", livroEncontrado->codigo, livroEncontrado->titulo, livroEncontrado->autor, livroEncontrado->ano);
						}else{
							printf("\nLivro não encontrado! ( ͠° ͟ʖ ͡°)\n");
						}
						
						break;
				case 3:
						printf("%d\n", altura(tab.indices));
						break;
				
				case 4:
						pre_order(tab.indices, &tab);
						printf("\n");
						break;
				case 5:
						in_order(tab.indices, &tab);
						printf("\n");
						break;
				case 6:
						pos_order(tab.indices, &tab);
						printf("\n");
						break;
				case 99:
						finalizar(&tab);
						exit(0);
		}
		//usleep(1200*1000);//1,2 segundos
		// printf("Pressione qualquer tecla para continuar...");
		// int s = getchar();
		printf("\n");
		system("read -p 'Pressione Enter para continuar...' var");
	}
}
