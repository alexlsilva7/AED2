#ifndef RB_H
#define RB_H
//Declarações de Structs, constantes, funções

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef int tipo_dado;

//ARVORE RED-BLACK
typedef struct no{
	tipo_dado valor;
	enum cor cor;
	struct no *esq, *dir, *pai;
} no;

typedef no* arvore;
void inicializar(arvore *raiz);
void inserir (int valor,arvore *a);//insere um elemento na arvore
void ajustar(arvore *a, arvore elemento);//pode retornar uma arvore modificada

void remover (int valor, arvore *raiz);
void reajustar(arvore *raiz, arvore elemento);

void rotacao_simples_direita(arvore *raiz, arvore pivo);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);
void rotacao_dupla_direita(arvore *raiz, arvore pivo);
void rotacao_dupla_esquerda(arvore *raiz, arvore pivo);

enum cor cor(arvore elemento);
int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
arvore irmao(arvore elemento);
arvore tio(arvore elemento);

void retira_duplo_preto(arvore *raiz, arvore elemento);

int maior(arvore a);

void imprimir_elemento(arvore a);
void imprimir(arvore raiz);

int altura(arvore a);
int max(int a, int b);

#endif
