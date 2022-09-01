#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

arvore adicionar (tipo_dado *valor, arvore raiz) {
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_bst));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}

	if(valor->codigo > raiz->dado->codigo) {
		raiz->dir = adicionar(valor, raiz->dir);
	} else {
		raiz->esq = adicionar(valor, raiz->esq);
	}
	return raiz;
}

int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

tipo_dado * maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

tipo_dado * menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz) {
	printf("[%d - %s] ", raiz->dado->codigo, raiz->dado->titulo);
}

arvore remover (int valor, arvore raiz) {
	if(raiz == NULL) 
		return NULL;
	
	if(raiz->dado->codigo == valor) {		
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado->codigo, raiz->esq);
		return raiz;
	}	
	if(valor > raiz->dado->codigo) {
			raiz->dir = remover(valor, raiz->dir);
	} else {
			raiz->esq = remover(valor, raiz->esq);
	}
	return raiz;
}

tipo_dado * ler_dados() {
	tipo_dado *novo = (tipo_dado *) malloc(sizeof(tipo_dado));
	char * buffer = (char *) malloc(256 * sizeof(char));
	
	getchar();
	printf("Titulo: ");
	fgets(buffer, 256,  stdin);
	tirar_enter(buffer);
	
/*	novo->titulo = (char *) malloc ((strlen(buffer) + 1) * sizeof(char));
	strcpy(novo->titulo, buffer);*/
	
	novo->titulo =  strdup(buffer);

	printf("Autor: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	novo->autor = strdup(buffer);

	printf("Isbn: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	novo->isbn = strdup(buffer);

	printf("Codigo: ");
	scanf("%d", &novo->codigo);
	free(buffer);

	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "w");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq){
	if(raiz != NULL) {
        //Escrever uma função para implementar uma estratégia de separação de campos.
       	// fprintf("%s|%s|%s|%d\n",raiz->dado->titulo, ..... );				
		//fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		fprintf(arq,"%s|%s|%s|%d\n",raiz->dado->titulo, raiz->dado->autor, raiz->dado->isbn, raiz->dado->codigo );	
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}

}

arvore carregar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "r");
	char * temp = (char *) malloc(sizeof(char)*3000);
	tipo_dado * novo;
	if(arq != NULL) {		
		while(fgets(temp,3000, arq)!= NULL){
			//Leu uma linha e atribuiu a temp
			printf("%zu %s",strlen(temp), temp);
			
			novo = (tipo_dado *) malloc(sizeof(tipo_dado));

			//Split na string do livro "Senhor dos PCs|Bill Gates|546|2"
			char* split = strtok(temp,"|");

			//Leitura do Split
			for (int i = 0; i < 4; i++)
			{
				//printf("split: %s\n", split);
				switch (i){
					case 0:
						novo->titulo = split;
						break;	
					case 1:
						novo->autor = split;
						break;
					case 2:
						novo->isbn = split;
						break;
					case 3:
						novo->codigo = atoi(split);
						break;
				}
				//leitura do proximo split
				split = strtok(NULL, "|");

			}
			a = adicionar(novo, a);			
			printf("[%d - %s] \n", novo->codigo, novo->titulo);
			temp = (char *) malloc(sizeof(char)*3000);
		}
		fclose(arq);
	}
	return a;
}
