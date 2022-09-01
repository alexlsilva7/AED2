#include "rb.h"
#include <stdlib.h>
#include <stdio.h>

arvore no_null;

void inicializar(arvore *raiz) {
	*raiz = NULL;
	no_null = (arvore) malloc(sizeof(struct no));
	no_null->cor = DUPLO_PRETO;
	no_null->valor = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
}

void inserir ( int valor,arvore *a){
	arvore temp, pai, novo;
    //utiliza-se *raiz, por ser um ponteiro de ponteiro
	temp = *a;
	pai = NULL;
	
	//navega na árvore até encontrar a posição vaga apropriada para o elemento
	 while(temp != NULL) {
			pai = temp;
			if(valor > temp->valor) 
					temp = temp->dir;
			else 
					temp = temp->esq;
	}

    //Após achar a posição, inicializa o novo elemento
	novo = (arvore) malloc(sizeof(struct no));
	novo->valor = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

    //Atualiza a raiz da árvore, caso esteja inserindo o primeiro elemento
    //Observe novamente o uso do ponteiro de ponteiro
	if(eh_raiz(novo))	
			*a = novo;
	else {
        //Se não for a raiz, é preciso realizar a ligação do pai(direita ou esquerda) com o novo elemento
		if(valor > pai->valor)
			pai->dir = novo;
		else
			pai->esq = novo;
	}
	//printf("adicionou %d\n", valor);
    //Após inserir, verifica e ajusta a árvore resultante
	ajustar(a, novo);
}

void ajustar(arvore *a, arvore elemento){
    //A árvore está desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
    //Utilizamos um while para continuar a verificação até chegar a raiz, quando necessário
    
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
			//printf("Ajustar While %d\n", elemento->valor);
			//caso 1: Cor do tio é vermelha, desce o preto do avô
			if(cor(tio(elemento)) == VERMELHO) {
				//printf("\nCaso1\n");
				tio(elemento)->cor = PRETO;
				elemento->pai->cor = PRETO;
				elemento->pai->pai->cor = VERMELHO;
				//Continua a verificação a partir do avô, que mudou para vermelho e pode ter 
				//gerado uma sequência vermelho-vermelho				
				elemento = elemento->pai->pai;
				continue;
			} 
			//caso 2a: rotação simples direita
			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
					//printf("\nCaso2a\n");
					rotacao_simples_direita(a, elemento->pai->pai);
					elemento->pai->cor = PRETO;
					elemento->pai->dir->cor = VERMELHO;
					//não precisa continuar pois a raiz relativa termina em preto
					//elemento = elemento->pai;
					continue;
			}
			//caso 2b: rotação simples esquerda
			if(!eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)) {
					//printf("\nCaso2b\n");
					rotacao_simples_esquerda(a, elemento->pai->pai);
					elemento->pai->cor = PRETO;
					elemento->pai->esq->cor = VERMELHO;
					//não precisa continuar pois a raiz relativa termina em preto
					//elemento = elemento->pai;
					continue;			
			}
			//caso 3a: rotação dupla direita
			if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {	
					//printf("\nCaso3a\n");
					rotacao_dupla_direita(a, elemento->pai->pai);
					elemento->cor = PRETO;
					elemento->dir->cor = VERMELHO;
					elemento->esq->cor = VERMELHO;
					//não precisa continuar pois a raiz relativa termina em preto
					//elemento = elemento->pai;
					continue;
			}
			//caso 3b: rotação dupla esquerda
			if(eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)) {
					//printf("\nCaso3b\n");
					
					rotacao_dupla_esquerda(a, elemento->pai->pai);
					elemento->cor = PRETO;
					elemento->dir->cor = VERMELHO;
					elemento->esq->cor = VERMELHO;
					
					//não precisa continuar pois a raiz relativa termina em preto
					//elemento = elemento->pai;
					continue;
			}

	}
    //Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta - CASO 0
	(*a)->cor = PRETO;
}

void rotacao_simples_direita(arvore *raiz, arvore pivo){
	//printf("\nRSD");
	arvore u, t1;
			u = pivo->esq;
            t1 = u->dir;
            //t1 = u->esq;

            //Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito
			int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			//Atualização dos ponteiros
			pivo->esq = t1;
            if(t1 != NULL)
				t1->pai = pivo;

			u->pai = pivo->pai;

			u->dir = pivo;
			pivo->pai = u;


            //Se não existir árvore acima de u, u passa a ser a raiz da árvore
			if(eh_raiz(u))
				*raiz = u;
			else {
              //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
					if(posicao_pivo_esq)
							u->pai->esq = u;
					else
							u->pai->dir = u;
			}
	
};

void rotacao_dupla_direita(arvore *raiz, arvore pivo){
	//printf("\nRDD");
	
	arvore u,v, t2, t3;
	u = pivo->esq;
	v = u->dir;
    t2 = v->esq;
    t3 = v->dir;

	//Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
	//Atualização dos ponteiros
	pivo->esq = t3;
	if(t3 != NULL){
		t3->pai = pivo;
	}
	
	v->pai = pivo->pai;
	u->dir = t2;
	if(t2 != NULL){
		t2->pai = u;
	}
	pivo->pai = v;
	u->pai = v;
	
	v->dir = pivo;
	v->esq = u;
	
	//Se não existir árvore acima de u, u passa a ser a raiz da árvore
	if(eh_raiz(v)){
		*raiz = v;
	}else {
	//Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
		if(posicao_pivo_esq){
			v->pai->esq = v;
		}
		else{
			v->pai->dir = v;
		}
	}		
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo){
	//printf("\nRSE");
	arvore u, t1;
	u = pivo->dir;
    t1 = u->esq;

	//Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
	//Atualização dos ponteiros
	pivo->dir = t1;
	if(t1 != NULL){
		t1->pai = pivo;
	}
	u->pai = pivo->pai;
	u->esq = pivo;
	pivo->pai = u;
	
	


	//Se não existir árvore acima de u, u passa a ser a raiz da árvore
	if(eh_raiz(u)){
	*raiz = u;
	}else {
	//Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
		if(posicao_pivo_esq){
			u->pai->esq = u;
		}
		else{
			u->pai->dir = u;
		}
	}	
};

void rotacao_dupla_esquerda(arvore *raiz, arvore pivo){
	//printf("\nRDE");
	
	arvore u,v, t2, t3;
	u = pivo->dir;
	v = u->esq;
    t2 = v->dir;
    t3 = v->esq;

	//Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
			
	//Atualização dos ponteiros
	pivo->dir = t3;
	if(t3 != NULL){
		t3->pai = pivo;
	}
	
	v->pai = pivo->pai;
	u->esq = t2;
	if(t2 != NULL){
		t2->pai = u;
	}
	pivo->pai = v;
	u->pai = v;
	
	v->dir = u;
	v->esq = pivo;
	
	//Se não existir árvore acima de u, u passa a ser a raiz da árvore
	if(eh_raiz(v)){
		*raiz = v;
	}else {
	//Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
		if(posicao_pivo_esq){
			v->pai->esq = v;
		}
		else{
			v->pai->dir = v;
		}
	}	
};

enum cor cor(arvore elemento) {
	enum cor c;
	if(elemento==NULL)
		c = PRETO;
	else
		c = elemento->cor;
	return c;
}

int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento) {
	return (!eh_raiz(elemento) && elemento == elemento->pai->esq);
}

arvore tio(arvore elemento) {
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
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

void imprimir_elemento(arvore a) {
	switch(a->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", a->valor);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", a->valor);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", a->valor);
			break;
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

void remover (int valor, arvore *raiz) {
	arvore posicao;
	posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->valor) {
			//elemento possui dois filhos
            if(posicao->esq != NULL && posicao->dir != NULL) { 
				//printf("Remov-2 Filhos\n");
    			posicao->valor = maior(posicao->esq);   
	    		remover(posicao->valor, &(posicao->esq));
                break;
            }
	
			//O elemento possui apenas um filho (direito)
			if(posicao->esq == NULL && posicao->dir != NULL) {
				//printf("Remov-1 Filho Dir\n");
                arvore filhoDireito;
            //O seu filho direito sobe para a posição do elemento  a ser removido e recebe a cor preta
                filhoDireito = posicao->dir;
				filhoDireito->cor = PRETO;
                filhoDireito->pai = posicao->pai;

				if(eh_raiz(posicao)) {
					*raiz = posicao->dir;
				} else {
					if(eh_filho_esquerdo(posicao)) {
    					posicao->pai->esq = filhoDireito;
					} else {
						posicao->pai->dir = filhoDireito;
    				}
                         
				}
				free(posicao);
				break;
			}


			//O elemento possui apenas um filho (esquerdo)
			if(posicao->esq != NULL && posicao->dir == NULL) {
				//printf("Remov-1 Filho Esq\n");
				arvore filhoEsquerdo;
            //O seu filho esquerdo sobe para a posição do elemento  a ser removido e recebe a cor preta
                filhoEsquerdo = posicao->esq;
				filhoEsquerdo->cor = PRETO;
                filhoEsquerdo->pai = posicao->pai;

				if(eh_raiz(posicao)) {
					*raiz = posicao->esq;
				} else {
					if(eh_filho_esquerdo(posicao)) {
    					posicao->pai->esq = filhoEsquerdo;
					} else {
						posicao->pai->dir = filhoEsquerdo;
    				}
                         
				}
				free(posicao);
				break;	
			}

			//O elemento não possui filhos
			if(posicao->esq == NULL && posicao->dir == NULL) {
				//printf("Remov-Sem Filhos\n");
				//Remover raiz sem filhos					
				if(eh_raiz(posicao)) {
					*raiz = NULL;
					free(posicao);
					break;
				}

				//Remover elemento que não possui filhos e não é raiz
				//Se for vermelho, apenas remove atualizando o ponteiro 
				//correspondente do pai
				if(posicao->cor == VERMELHO) {
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
					free(posicao);
					break;
				} else {
					//Se o elemento for preto, substitui pelo duplo preto e depois ajusta a árvore
					no_null->cor = DUPLO_PRETO;
					no_null->pai = posicao->pai;
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = no_null;
					else
						posicao->pai->dir = no_null;
					
					free(posicao);
					reajustar(raiz, no_null);
					break;
				}
			}
		}
		if(valor > posicao->valor) 
				posicao = posicao->dir;
		else 
				posicao = posicao->esq;
	}  // Fim while
}

/*Realiza a correção da árvore após a remoção de um elemento preto que não possui filhos, ou seja, elimina o nó null o duplo-preto.*/

void reajustar(arvore *raiz, arvore elemento){
//	cor(irmao(elemento)->dir), cor(irmao(elemento)->esq));
	//caso 1	
	if(eh_raiz(elemento)) {
		//printf("Remov-Caso1\n");
		elemento->cor = PRETO;
        if(elemento == no_null)
            *raiz = NULL;
		return;
	}

	//caso 2
	if(  cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == VERMELHO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO ) {
         //printf("Remov-Caso2\n");
                //Verifica se é o caso 2 esquerdo ou direito
				if(eh_filho_esquerdo(elemento))
						rotacao_simples_esquerda(raiz, elemento->pai);
				else
						rotacao_simples_direita(raiz, elemento->pai);	
				elemento->pai->pai->cor = PRETO;
				elemento->pai->cor = VERMELHO;
				
                //Atenção à chamada recursiva do reajustar.
                //O caso 2 não remove o duplo-preto
                reajustar(raiz, elemento);
				return;
	}

	//caso 3
	if(cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO ) {
		//printf("Remov-Caso3\n");
		
		
		elemento->cor = PRETO;
		elemento->pai->cor = DUPLO_PRETO;
		irmao(elemento)->cor = VERMELHO;
		//Verificar e remover o no_null
		if(eh_filho_esquerdo(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;
		
        //Chamada recursiva para eliminar o duplo preto do elemento P
		reajustar(raiz, elemento->pai);
		return;
	}	

	//caso 4
	if(cor(elemento->pai) == VERMELHO &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO) {	
		//printf("Remov-Caso4\n");

		elemento->cor = PRETO;
		elemento->pai->cor = PRETO;
		irmao(elemento)->cor = VERMELHO;
		//Verificar e remover o no_null
		if(eh_filho_esquerdo(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;

		return;
	}

    //Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
	//caso 5a
	if(  eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == VERMELHO) {	
		//printf("Remov-Caso5a\n");
		
		rotacao_simples_direita(raiz,irmao(elemento));
		
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->dir->cor = VERMELHO;

		//Chamada recursiva para eliminar o duplo preto do elemento N
		reajustar(raiz, elemento);
		return;
	}

	//caso 5b
	if(!eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == VERMELHO &&
		 cor(irmao(elemento)->esq) == PRETO) {	
		//printf("Remov-Caso5b\n");
		rotacao_simples_esquerda(raiz,irmao(elemento));
		
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->esq->cor = VERMELHO;

		//Chamada recursiva para eliminar o duplo preto do elemento N
		reajustar(raiz, elemento);
		return;
	}

	//caso 6a
	if(cor(elemento->pai->dir) == PRETO &&
		cor(irmao(elemento)->dir) == VERMELHO) {	
		//printf("Remov-Caso6a\n");
		
		enum cor cor_topo = elemento->pai->cor;

		rotacao_simples_esquerda(raiz, elemento->pai);

		elemento->pai->pai->cor = cor_topo;
		elemento->pai->cor = PRETO;
		elemento->pai->pai->dir->cor = PRETO;
		retira_duplo_preto(raiz, elemento);

		return;
	}

	//caso 6b
	if(cor(elemento->pai->esq) == PRETO &&
		cor(irmao(elemento)->esq) == VERMELHO) {
		//printf("Remov-Caso6b\n");
		
		enum cor cor_topo = elemento->pai->cor;

		rotacao_simples_direita(raiz, elemento->pai);

		elemento->pai->pai->cor = cor_topo;
		elemento->pai->cor = PRETO;
		elemento->pai->pai->esq->cor = PRETO;
		retira_duplo_preto(raiz, elemento);

		return;
	}
}

void retira_duplo_preto(arvore *raiz, arvore elemento) {
			if(elemento == no_null)
				if(eh_filho_esquerdo(elemento))
						elemento->pai->esq = NULL;
				else
						elemento->pai->dir = NULL;
			else
				elemento->cor = PRETO;
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

	

