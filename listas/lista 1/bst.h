#ifndef BST_H
#define BST_H
//Declarações de Structs, constantes, funções

//ARVORE BINARIA DE BUSCA
typedef struct no{
	int valor;
	struct no *esq, *dir;
} no;

typedef no* arvore;

arvore inserir (arvore a, int v);//insere um elemento na arvore

arvore remover (arvore a, int v);//pode retornar uma arvore modificada

void preOrder(arvore a);//reconstroi na mesma ordem

void inOrder(arvore a);//ordenado crescente

void posOrder(arvore a);//usado em calculos de processador

void reverso(arvore a);//ordenado decrescente

int isPrimo(int num);//verifica se o numero é primo

int qtdPrimo(arvore a);//retorna a quantidade de nos que armazenam um número primo

int qtdNos(arvore a);//retorna a quantidade de nos de uma arvore

int sucessor(arvore a,int n);//retorna o sucessor de um numero n

arvore busca(arvore a,int n);//busca um elemento

void caminho(arvore a,int n);//imprime na tela os elementos existentes no caminho da raiz até o nó n

int maior(arvore a);//retorna o maior elemento, mas só funciona em uma arvore nao nula

int menor(arvore a);//retorna o menor elemento, mas só funciona em uma arvore nao nula

int somatorio(arvore a);//retorna o somatorio dos valores dos nos de uma arvore

int ancestralMaisBaixo(arvore a, int valor);
//LISTA SIMPLESMENTE ENCADEADA
typedef struct nolista{
	int valor;
	struct nolista *prox;
} nolista;

typedef nolista* listaNo;

listaNo alocaLista();

void addItemLista(listaNo cabeca, int v);

void inOrderAddLista(arvore a, listaNo lista);

void imprimeLista(listaNo cabeca);

#endif
