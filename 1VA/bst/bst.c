#include "bst.h"
#include <stdlib.h>
#include <stdio.h>


arvore inserir (arvore a, int v){
	//caso base da recursão
	//inserir numa (sub)árvore vazia
	if(a == NULL) {
		//alocar espaço para o nó
		arvore no = (arvore) malloc(sizeof(no));
		//inicializar os valores das variáveis
		no->valor = v;
		no->esq = NULL;
		no->dir = NULL;
		return no;
	
	}else{
		//se o valor que eu quero inserir (v) for menor que a raiz relativa(a->valor),inserir na sub-arvore esquerda
		if(v < a->valor){
			a->esq = inserir(a->esq, v);
		}else{
			a->dir = inserir(a->dir, v);
		}
		return a;
	}
}

int maior(arvore a){
	//só funciona em arvore nao nula,
	
	int m;
	if(a != NULL){
		m = a->valor;
		if(a->dir != NULL){
			int maxdir = maior(a->dir);
			if(m < maxdir){
				m = maxdir;
			}
			
		}
	}
	return m;
}

int menor(arvore a){
	//só funciona em arvore nao nula,
	
	int m;
	if(a != NULL){
		m = a->valor;
		if(a->esq != NULL){ 
			int minesq = menor(a->esq);
			if(m > minesq){
				m = minesq;
			}
			
		}
	}
	return m;
}
arvore remover (arvore a, int v){
	//caso base da recursão
	//árvore vazia => não faz nada
	if(a == NULL) {	
		return NULL;
	}else{
		//caso base elemento encontrado
		if(a->valor == v){
			//elemento encontrado
			//verificar a quantidade de filhos
			
			//zero filhos -> remoção de folhas
			if(a->esq == NULL && a->dir == NULL){
				//limpar da memoria
				free(a);
				return NULL;
			}
			
			//um filho esquerda 
			if(a->esq != NULL && a->dir == NULL){
				arvore esq = a->esq;
				free(a);
				return esq;
			}
			
			//um filho direito
			if(a->esq == NULL && a->dir != NULL){
				arvore dir = a->dir;
				free(a);
				return dir;
			}
			
			//dois filhos
			if(a->esq != NULL && a->dir != NULL){
				//procura o maior elemento da sub-árvore esq com uma funcção auxiliar maior()
				int mesq = maior(a->esq);
				//copia o valor para o valor de a->valor
				a->valor = mesq;
				//chama recursivamente o remover com os parametros remover(a->esq, maior)
				a->esq = remover(a->esq,mesq);
				return a;
			}
		}
		//Chamadas recursivas para remover da sub-árvore esquerda ou direita, dependendo do valor
		else{
			//a->esq = remover(a->esq, v);
			//a->dir =remover(a->dir, v);
			if(a->valor > v){
				a->esq = remover(a->esq, v);
			}else{
				a->dir =remover(a->dir, v);
			}
			return a;
		}
	}
	
}



void preOrder(arvore a){
	//reconstroi na mesma ordem
	if(a != NULL){
		printf("[%d]",a->valor);
		preOrder(a->esq);
		preOrder(a->dir);
	}
}

void inOrder(arvore a){
	//ordenado crescente
	if(a != NULL){
		inOrder(a->esq);
		printf("[%d]",a->valor);
		inOrder(a->dir);
	}
}

void posOrder(arvore a){
	//usado em calculos de processador
	if(a != NULL){
		posOrder(a->esq);
		posOrder(a->dir);
		printf("[%d]",a->valor);
	}
}

void reverso(arvore a){
	//ordenado decrescente
	if(a != NULL){
		reverso(a->dir);
		printf("[%d]",a->valor);
		reverso(a->esq);
	}
}
int isPrimo(int num){
	//verifica se o numero é primo
	int i;
	int resultado = 0;
	if(num == 1){
		return 0;//NAO-PRIMO false
	}
	for(i = 2; i <= num / 2; i++){
    	if (num % i == 0) {
    		
       		resultado++;
       		break;
    	}
    }
	if(resultado == 0){
		return 1;//PRIMO true
	}else{
		return 0;//NAO-PRIMO false
	}
}

int qtdPrimo(arvore a){
	//retorna a quantidade de nos que armazenam um número primo
	if(a != NULL){
		//printf("isPrimo %d: %d\n", a->valor, isPrimo(a->valor));
		return isPrimo(a->valor) + qtdPrimo(a->esq)+ qtdPrimo(a->dir);
	}else{
		return 0;
	}
	 
}

int qtdNos(arvore a){
	//retorna a quantidade de nos de uma arvore
	if(a != NULL){
		return 1 + qtdNos(a->esq)+ qtdNos(a->dir);
	}
}

listaNo alocaLista (){
	//aloca um no da lista encadeada na memoria
	return malloc(sizeof (listaNo));
}

void imprimeLista(listaNo cabeca){
	//imprime uma lista encadeada
	listaNo aux;
	aux = cabeca;
	while(aux->prox != NULL){
		printf("[%d]", aux->valor);
		aux = aux->prox;
	}	
}
void addItemLista(listaNo cabeca, int v){
	//adiciona um item em uma lista encadeada
	listaNo aux, novo;
	aux = cabeca;
	while(aux->prox != NULL){
		aux = aux->prox;
	}
	novo = alocaLista();
	novo->valor = v;
	novo->prox = NULL;

	aux->prox = novo;
	
	
	
}

void inOrderAddLista(arvore a, listaNo lista){
	//InOrder Transgenico
	//em vez de imprimir adiciona em uma lista encadeada
	
	if(a != NULL){
		inOrderAddLista(a->esq, lista);
		addItemLista(lista, a->valor);
		inOrderAddLista(a->dir, lista);
	}
}

int sucessor(arvore a,int n){
	//busca o elemento n na lista para verificar se existe
	arvore existeN = busca(a,n);
	
	//Se n não existe na arvore ou não possui sucessor
	if(existeN == NULL){
		return -1;
	}else{
		//buscar o sucessor atravez de uma lista encadeada com os elementos ordenados
		
		//encontra o valor
		//se tiver ponteiro para o proximo, existe um sucessor
		// ->valor [ 2 ][ 3 ][ 5 ][ 8 ]
		//  ->prox [->3][->5][->8][NULL]
		
		listaNo lista;
		//cria a cabeça da lista encadeada com valor -1
		lista = alocaLista();
		lista->valor = -1;
		lista->prox = NULL;
		//cria uma lista encadeada ordenada dos valores da arvore começando com -1;
		inOrderAddLista(a, lista);
		//remove o primeiro elemento -1
		lista = lista->prox;
		//imprimeLista(lista);
		listaNo aux = lista;
		int numsucessor = -1;
	
		while(aux->prox != NULL){
			//encontrou o número
			if(aux->valor == n){
				//tem um sucessor
				if(aux->prox != NULL){
					numsucessor = aux->prox->valor;
					break;
				}
			}
			aux = aux->prox;
		}
		return numsucessor;
	}
}

arvore busca(arvore a,int v){
	//caso base
	if (a == NULL || v == a->valor){
		return a;
	}
	if(v < a->valor){
		//procura a esquerda | valores menores
		return busca(a->esq, v);
	}else{
		//procura a direita | valores maiores
		return busca(a->dir, v);
	}
}

void caminho(arvore a,int n){
	//imprime na tela os elementos existentes no caminho da raiz até o nó n
	arvore aux = busca(a,n);
	
	if(aux != NULL){
		printf("[%d]", a->valor);
		if(n < a->valor){
			caminho(a->esq, n);
		}else{
			caminho(a->dir,n);
		}
	}
}


int somatorio(arvore a){	
	//int v = a == NULL ? 0 : a->valor + somatorio(a->esq) + somatorio(a->dir);
	if(a == NULL){
		return 0;
	}else{
		return a->valor + somatorio(a->esq) + somatorio(a->dir);
	}
}

int max(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int altura(arvore a){
	if(a == NULL){
		return 0;
	}else{
		return 1 + max(altura(a->esq), altura(a->dir));
	}
}
	

