#ifndef AVL_H
#define AVL_H
//Declarações de Structs, constantes, funções

typedef int tipo_dado;

typedef struct no{
	tipo_dado valor;
	int fb;
	struct no *esq, *dir;
} no;

typedef no* arvore;

arvore inserir (arvore a, int v, int *cresceu);//insere um elemento na arvore

arvore remover (arvore a, int v, int *diminuiu);//pode retornar uma arvore modificada

arvore rotacionar(arvore a);//realiza a operacao de rotacao adequada

arvore rotacao_simples_direita(arvore a);

arvore rotacao_dupla_direita(arvore a);

arvore rotacao_simples_esquerda(arvore a);

arvore rotacao_dupla_esquerda(arvore a);

int max(int a, int b);//retorna o maior elemento entre a e b

//int altura(arvore a);//retorna a altura de uma arvore

int maior(arvore a);//retorna o maior elemento em uma arvore
int altura(arvore a);
void imprimir(arvore raiz);//funciona como um pre-order, mas mostrando o fb.

void imprimir_elemento(arvore raiz);// Auxiliar de imprimir
#endif
