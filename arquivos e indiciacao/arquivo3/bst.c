#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>


void inicializar(arvore *raiz) {
	*raiz = NULL;
}

int inicializarTabela(tabela *tab) {
	inicializar(&tab->indices);	
	tab->arquivo_dados = fopen("dados.txt", "a+");
	tab->indices = carregar_arquivo("indices.dat", tab->indices);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo("indices.dat", tab->indices);
}

void adicionarLivro(tabela *tab, dado *livro){
	if(tab->arquivo_dados != NULL) {
			//Deslocando o cursor do arquivo para o fim do arquivo
			tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));
			novo->chave = livro->codigo;

            fseek(tab->arquivo_dados, 0L, SEEK_END);
            novo->indice = ftell(tab->arquivo_dados);

            //Modificar de acordo com a estratégia de separacao de campos adotada
			fprintf(tab->arquivo_dados,"%s|%s|%s|%d\n",livro->titulo, livro->autor, livro->ano, livro->codigo);
			tab->indices = adicionar(novo, tab->indices);
	}
}

arvore adicionar (tipo_dado *valor, arvore raiz) {
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_bst));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}

	if(valor->chave > raiz->dado->chave) {
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

dado * buscarLivro(tabela *tab, int chave) {
    if(tab->arquivo_dados != NULL) {
    no_bst *temp;
    temp = tab->indices;

    while(temp!=NULL){
        if(temp->dado->chave == chave) {
            dado * encontrado = (dado*) malloc(sizeof(dado));
            fseek(tab->arquivo_dados, temp->dado->indice, SEEK_SET);
            //Modificar de acordo com a estratégia de separacao de campos adotada
            //fread(encontrado, sizeof(dado), 1, tab->arquivo_dados);
			char * temp = (char *) malloc(sizeof(char)*3000);

			if(tab->arquivo_dados != NULL) {		
				while(fgets(temp,3000, tab->arquivo_dados)!= NULL){
					//Leu uma linha e atribuiu a temp
					printf("%zu %s",strlen(temp), temp);

					//Split na string do livro "Senhor dos PCs|Bill Gates|546|2"
					char* split = strtok(temp,"|");

					//Leitura do Split
					for (int i = 0; i < 4; i++)
					{
						//printf("split: %s\n", split);
						switch (i){
							case 0:
								encontrado->titulo = split;
								break;	
							case 1:
								encontrado->autor = split;
								break;
							case 2:
								encontrado->ano = split;
								break;
							case 3:
								encontrado->codigo = atoi(split);
								break;
						}
						//leitura do proximo split
						split = strtok(NULL, "|");
					}
				}
			}
            return encontrado;
        } else {
            if(chave > temp->dado->chave)
                temp = temp->dir;
            else
                temp = temp->esq;                
        }
    }
    }
    return NULL;
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

void pre_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		pre_order(raiz->esq, tab);
		pre_order(raiz->dir, tab);
	}
}

void pos_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order(raiz->esq, tab);
		pos_order(raiz->dir, tab);
		imprimir_elemento(raiz, tab);
	}

}

void in_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order(raiz->esq, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->dir, tab);
	}
	
}

void imprimir_elemento(arvore raiz, tabela * tab) {
	//printf("raiz %d chave%d", raiz->dado->indice, raiz->dado->chave);
	dado * encontrado = (dado *) malloc (sizeof(dado));
	int result = fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
	//printf("result %d", result);
	char * temp = (char *) malloc(sizeof(char)*3000);

	if(tab->arquivo_dados != NULL) {		
		fgets(temp,3000, tab->arquivo_dados);
		//Leu uma linha e atribuiu a temp
		//printf("%s", temp);
		//Split na string do livro "Senhor dos PCs|Bill Gates|546|2"
		char* split = strtok(temp,"|");

		//Leitura do Split
		for (int i = 0; i < 4; i++){
			//printf("split: %s\n", split);
			switch (i){
				case 0:
					encontrado->titulo = split;
					break;	
				case 1:
					encontrado->autor = split;
					break;
				case 2:
					encontrado->ano = split;
					break;
				case 3:
					encontrado->codigo = atoi(split);
					break;
			}	//leitura do proximo split
			split = strtok(NULL, "|");
		}
				
	}
	printf("[%d, %s, %s, %s ]", raiz->dado->chave, encontrado->titulo, encontrado->autor, encontrado->ano);
	free(temp);
}
  
arvore remover (int valor, arvore raiz) {
	if(raiz == NULL) 
		return NULL;
	
	if(raiz->dado->chave == valor) {		
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado->chave, raiz->esq);
		return raiz;
	}	
	if(valor > raiz->dado->chave) {
			raiz->dir = remover(valor, raiz->dir);
	} else {
			raiz->esq = remover(valor, raiz->esq);
	}
	return raiz;
}

dado * ler_dados() {
	dado *novo = (dado *) malloc(sizeof(dado));
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

	printf("Ano: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	novo->ano = strdup(buffer);

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
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}
}

arvore carregar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
			
			a = adicionar(temp, a);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);

	}
	return a;
}
