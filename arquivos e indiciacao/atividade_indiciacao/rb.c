#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "rb.h"
#include <string.h>

arvore no_null;

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

//Adiciona no arquivo de dados o livro
void adicionarLivro(tabela *tab, dado *livro){
	if(tab->arquivo_dados != NULL) {
			//tipo_dado = struct da arvore
			//dado = livro do arquivo
			tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));
			novo->chave = livro->codigo;
			//Deslocando o cursor do arquivo para o fim do arquivo
            fseek(tab->arquivo_dados, 0L, SEEK_END);
            novo->indice = ftell(tab->arquivo_dados);

            //Modificar de acordo com a estratégia de separacao de campos adotada
			fprintf(tab->arquivo_dados,"%s|%s|%s|%d\n",livro->titulo, livro->autor, livro->ano, livro->codigo);
			adicionar(novo, &tab->indices);
	}
}

void adicionar(tipo_dado* valor, arvore *a){
	arvore temp, pai, novo;
    //utiliza-se *raiz, por ser um ponteiro de ponteiro
	temp = *a;
	pai = NULL;
	
	//navega na árvore até encontrar a posição vaga apropriada para o elemento
	 while(temp != NULL) {
			pai = temp;
			if(valor->chave > temp->dado.chave) 
					temp = temp->dir;
			else 
					temp = temp->esq;
	}

    //Após achar a posição, inicializa o novo elemento
	novo = (arvore) malloc(sizeof(struct no));
	novo->dado.chave = valor->chave;
	novo->dado.indice = valor->indice;
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
		if(valor->chave > pai->dado.chave)
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

void remover (int valor, arvore *raiz) {
	arvore posicao;
	posicao = *raiz;

	while(posicao != NULL) {
		if(valor == posicao->dado.chave) {
			//elemento possui dois filhos
            if(posicao->esq != NULL && posicao->dir != NULL) { 
				//printf("Remov-2 Filhos\n");
				tipo_dado * maiorelemento = maior_elemento(posicao->esq);
    			posicao->dado.chave = maiorelemento->chave;   
				posicao->dado.indice = maiorelemento->indice;  
	    		remover(posicao->dado.chave, &(posicao->esq));
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
		if(valor > posicao->dado.chave) 
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

//ARQUIVOS
dado * buscarLivro(tabela *tab, int chave) {
    if(tab->arquivo_dados != NULL) {
    no_rb *temp;
    temp = tab->indices;
		while(temp!=NULL){
			if(temp->dado.chave == chave) {
				dado * encontrado = (dado*) malloc(sizeof(dado));
				//printf("%d %s",encontrado->codigo, encontrado->titulo);
				fseek(tab->arquivo_dados, temp->dado.indice, SEEK_SET);
				//Modificar de acordo com a estratégia de separacao de campos adotada
				//fread(encontrado, sizeof(dado), 1, tab->arquivo_dados);
				char * linha = (char *) malloc(sizeof(char)*3000);

				if(tab->arquivo_dados != NULL) {		
					fgets(linha,3000, tab->arquivo_dados);
						//Leu uma linha e atribuiu a linha
						///printf("%zu %s",strlen(linha), linha);

						//Split na string do livro "Senhor dos PCs|Bill Gates|546|2"
						char* split = strtok(linha,"|");

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
				return encontrado;
			} else {
				if(chave > temp->dado.chave)
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
			return &raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

tipo_dado * menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return &raiz->dado;
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
	int result = fseek(tab->arquivo_dados, raiz->dado.indice, SEEK_SET);
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
	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d, %s, %s, %s]\x1b[0m", raiz->dado.chave, encontrado->titulo, encontrado->autor, encontrado->ano);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d, %s, %s, %s]\x1b[0m", raiz->dado.chave, encontrado->titulo, encontrado->autor, encontrado->ano);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d, %s, %s, %s]\x1b[0m", raiz->dado.chave, encontrado->titulo, encontrado->autor, encontrado->ano);
			break;
	}
	//printf("[%d, %s, %s, %s ]", raiz->dado.chave, encontrado->titulo, encontrado->autor, encontrado->ano);
	free(temp);
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
		fwrite(&raiz->dado, sizeof(tipo_dado), 1, arq);
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
			
			adicionar(temp, &a);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);

	}
	return a;
}

int altura(arvore a){
	if(a == NULL){
		return 0;
	}else{
		return 1 + maior(altura(a->esq), altura(a->dir));
	}
}