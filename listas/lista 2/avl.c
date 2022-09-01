#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

/*
	Adiciona um novo elemento à árvore e realiza as operações de balanceamento se necessario
	v - elemento a ser inserido
	a - raiz da árvore onde o elemento será inserido
	cresceu - variável de econtrole que ajuda a calcular o fator de balanço
	
	retorno: Raiz da árvore resultante da operação de adicionar
	
*/
arvore inserir(arvore a, int v, int *cresceu){
	//caso base da recursão
	//inserir numa (sub)árvore vazia
	if(a == NULL) {
		//alocar espaço para o nó
		arvore novo = (arvore) malloc(sizeof(no));
		//inicializar os valores das variáveis
		novo->valor = v;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
		*cresceu = 1;
		return novo;
	}else{
		//se o valor que eu quero inserir (v) for meno que a raiz relativa(a->valor),inserir na sub-arvore esquerda
		if(v < a->valor){	
			//Adicionar na esquerda	
			a->esq = inserir(a->esq, v, cresceu);
			
			if(*cresceu == 1){
				//se cresceu recalcular o fator de balanco
				switch(a->fb){
					case 0:
						a->fb = -1;
						*cresceu = 1;
						break;	
					case 1:
						a->fb = 0;
						*cresceu = 0;
						break;	
					case -1:
						//o fator de balanço passaria a ser 2, mas a operação de rotação já e suficiente para recalcular os fatores de balanco
						*cresceu = 0;
						return rotacionar(a);
						
				}
			}
			
			
			
		}else{	
			//Adicionar na direita	
			a->dir = inserir(a->dir, v, cresceu);
				
			if(*cresceu == 1){
				//se cresceu recalcular o fator de balanco
				switch(a->fb){
					case 0:
						a->fb = 1;
						*cresceu = 1;
						break;	
					case -1:
						a->fb = 0;
						*cresceu = 0;
						break;	
					case 1:
						//o fator de balanço passaria a ser 2, mas a operação de rotação já e suficiente para recalcular os fatores de balanco
						*cresceu = 0;
						return rotacionar(a);
						
				}
			}
		}
		return a;
	}
}

arvore rotacionar(arvore a){
		if(a->fb> 0){
			//FB = 2
			switch(a->dir->fb){
				case 0:
					//só ocorre no remover
				case 1:
					return rotacao_simples_esquerda(a);
				case -1:	
					return rotacao_dupla_esquerda(a);						
			}			
		}else{
			//FB = 2
			switch(a->esq->fb){
				case 0:
					//só ocorre no remover
				case -1:
					return rotacao_simples_direita(a);
				case 1:	
					return rotacao_dupla_direita(a);						
			}
		}
}

arvore rotacao_simples_direita(arvore a){
	//printf("\nRSD");
	//declara e inicializa os ponteiros
	arvore p, u, t1, t2, t3;
	
	p = a;
	u = p->esq;
	t2 = u->dir;
	//t1 e t3 não mudam de lugar(em caso de duvida olhar desenho da rotacao);
	//t1 = p->esq;
	//t3 = u->dir;
	
	//atualiza os ponteiros
	p->esq = t2;
	u->dir = p; 
	
	//atualiza os fatores de balanço de acordo com o fb de u
	if(u->fb == -1){
		p->fb = 0;
		u->fb = 0;
	}else{
		//remover
		p->fb = -1;
		u->fb = 1;
	
	}
	//retorna nova raiz relativa
	return u;
};

arvore rotacao_dupla_direita(arvore a){
	//printf("\nRDD");
	//declara e inicializa os ponteiros
	arvore p, u, v, t1, t2, t3, t4;
	
	p = a;
	u = p->esq;
	v = u->dir;
	t2 = v->esq;
	t3 = v->dir;
	
	//atualiza os ponteiros
	p->esq = t3;
	u->dir = t2;
	v->dir = p;
	v->esq = u;
	
	//atualiza os fatores de balanço de acordo com o fb de v
	switch(v->fb){
		case -1:
			p->fb = 1;
			u->fb = 0;
			v->fb = 0;
			break;
		case 0:
			p->fb = 0;
			u->fb = 0;
			v->fb = 0;
			break;
		case 1:
			p->fb = 0;
			u->fb = -1;
			v->fb = 0;
			break;
	}
	//retorna nova raiz relativa
	return v;
}

arvore rotacao_simples_esquerda(arvore a){
	//printf("\nRSE");
	//declara e inicializa os ponteiros
	arvore p, u, t1, t2, t3;
	
	p = a;
	u = p->dir;
	t2 = u->esq;
	//t1 e t3 não mudam de lugar(em caso de duvida olhar desenho da rotacao);
	//t1 = p->esq;
	//t3 = u->dir;
	
	//atualiza os ponteiros
	p->dir = t2;
	u->esq = p; 
	
	//atualiza os fatores de balanço de acordo com o fb de u
	if(u->fb == 1){
		p->fb = 0;
		u->fb = 0;
	}else{
		//remover
		p->fb = 1;
		u->fb = -1;
	}
	//retorna nova raiz relativa
	return u;
};

arvore rotacao_dupla_esquerda(arvore a){
	//printf("\nRDE");
	//declara e inicializa os ponteiros
	arvore p, u, v, t1, t2, t3, t4;
	
	p = a;
	u = p->dir;
	v = u->esq;
	t2 = v->esq;
	t3 = v->dir;
	//atualiza os ponteiros
	p->dir = t2;
	u->esq = t3;
	v->dir = u;
	v->esq = p;
	
	//atualiza os fatores de balanço de acordo com o fb de v
	switch(v->fb){
		case -1:
			p->fb = 0;
			u->fb = 1;
			v->fb = 0;
			break;
		case 0:
			p->fb = 0;
			u->fb = 0;
			v->fb = 0;
			break;
		case 1:
			p->fb = -1;
			u->fb = 0;
			v->fb = 0;
			break;
	}
	//retorna nova raiz relativa
	return v;
};


arvore remover (arvore a, int v, int *diminuiu){
	//caso base da recursão
	//árvore vazia => não faz nada
	if(a == NULL) {
		return NULL;
	}else{
	    //printf("[%d]->", a->valor);
	    int valor_de_a = a->valor;
	    int fb_de_a = a->fb;
        int valor_do_diminuiu = *diminuiu;
		//caso base elemento encontrado
		if(a->valor == v){
			//printf("\nremoveu %d \n", a->valor);
			//elemento encontrado
			//verificar a quantidade de filhos
			*diminuiu = 1;

			//zero filhos -> remoção de folhas
			if(a->esq == NULL && a->dir == NULL){
				//printf("zero filhos \n");
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
				a->esq = remover(a->esq,mesq, diminuiu);

				if(*diminuiu == 1){
					//printf("\nmenu diminuiu esq no %d: fb= %d \n", a->valor, a->fb);
					switch(a->fb){
						case -1:
							a->fb = 0;
							*diminuiu = 1;
							break;
						case 0:
							a->fb = 1;
							*diminuiu = 0;
							break;
						case +1:
							//fb iria para +2
							*diminuiu = 1;
							//printf("rotacionar %d\n", a->valor);
							a = rotacionar(a);
							break;
					}
				}
				return a;
			}
		}
		//Chamadas recursivas para remover da sub-árvore esquerda ou direita, dependendo do valor
		else{
			//a->esq = remover(a->esq, v);
			//a->dir =remover(a->dir, v);
			if(a->valor > v){
				a->esq = remover(a->esq, v,diminuiu);
				if(*diminuiu == 1){
					//printf("\nmenu diminuiu esq no %d: fb= %d \n", a->valor, a->fb);
					switch(a->fb){
						case -1:
							a->fb = 0;
							*diminuiu = 1;
							break;
						case 0:
							a->fb = 1;
							*diminuiu = 0;
							break;
						case +1:
							//fb iria para +2

							//ajuste para funcionar no remover +2/0
							if(a->dir->fb != 0){
                                *diminuiu = 1;
							}else{
                                *diminuiu = 0;
							}
							a = rotacionar(a);
							break;
					}
				}
			}else{
				a->dir = remover(a->dir, v,diminuiu);
				if(*diminuiu == 1){
					switch(a->fb){
						case -1:
							//fb iria para +2
							*diminuiu = 1;
                            //ajuste para funcionar no remover -2/0
							if(a->esq->fb != 0){
                                *diminuiu = 1;
							}else{
                                *diminuiu = 0;
							}
							a = rotacionar(a);
							break;
						case 0:
 							a->fb = -1;
							*diminuiu = 0;
							break;
						case +1:
							a->fb = 0;
							*diminuiu = 1;
							break;
					}
				}
			}
			return a;
		}
	}

}
int max(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

/*
int altura(arvore a){
	if(a == NULL){
		return 0;
	}else{
		return 1 + max(altura(a->esq), altura(a->dir));
	}
}
*/


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

void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

/*---
Auxiliar de imprimir
---*/
void imprimir_elemento(arvore raiz) {
	printf("%d [%d]", raiz->valor, raiz->fb);
}

	

