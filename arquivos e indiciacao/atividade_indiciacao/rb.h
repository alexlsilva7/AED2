#ifndef RB_H
#define RB_H
enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct livro {
	char * titulo;
	char * autor;
	char * ano;
	int codigo;
} dado;

typedef struct indice {
	int chave; //codigo
	int indice; //posição relativa do registro dentro do arquivo
                //byte onde o registro "começa" no arquivo
} tipo_dado;

//ARVORE RED-BLACK
typedef struct no{
	tipo_dado dado;
	enum cor cor;
	struct no *esq, *dir, *pai;
} no_rb;

typedef no_rb* arvore;

typedef struct tabela {
	FILE *arquivo_dados;
	arvore indices;
} tabela;


int inicializarTabela(tabela *tab);
void finalizar (tabela *tab);
void adicionarLivro(tabela *tab, dado *livro);
	

void inicializar(arvore *raiz);
//RB TREE
void adicionar (tipo_dado *valor, arvore *raiz);
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
//FIM RB TREE

int altura(arvore raiz);
int maior(int a, int b);
tipo_dado * maior_elemento(arvore raiz);
tipo_dado * menor_elemento(arvore raiz);
void pre_order(arvore raiz, tabela *tab);
void pos_order(arvore raiz, tabela *tab);
void in_order(arvore raiz, tabela *tab);

void imprimir_elemento(arvore raiz, tabela *tab);

//Arquivos
dado * buscarLivro(tabela *tab, int chave); 

dado * ler_dados();
void tirar_enter(char *string);

void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
arvore carregar_arquivo(char *nome, arvore a);




#endif

