// Lista 10 - Parte 2 (Árvores Binárias) - Ranking de Pontuações

#include <stdio.h>
#include <stdlib.h>

// Estrutura de cada nó da árvore
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

// Cria um novo nó com o valor informado
No *criar_no(int valor) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL)
        return NULL;

    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

// Insere um valor na árvore
// Valores repetidos são ignorados
No *inserir(No *raiz, int valor) {
    if (raiz == NULL)
        return criar_no(valor);

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);

    return raiz;
}

// Imprime um valor controlando os espaços entre eles
void imprimir_valor(int valor, int *primeiro) {
    if (!*primeiro)
        printf(" ");

    printf("%d", valor);
    *primeiro = 0;
}

// Percurso em pré-ordem:
// raiz -> esquerda -> direita
void preordem(No *raiz, int *primeiro) {
    if (raiz == NULL)
        return;

    imprimir_valor(raiz->valor, primeiro);
    preordem(raiz->esq, primeiro);
    preordem(raiz->dir, primeiro);
}

// Percurso em ordem:
// esquerda -> raiz -> direita
void emordem(No *raiz, int *primeiro) {
    if (raiz == NULL)
        return;

    emordem(raiz->esq, primeiro);
    imprimir_valor(raiz->valor, primeiro);
    emordem(raiz->dir, primeiro);
}

// Percurso em pós-ordem:
// esquerda -> direita -> raiz
void posordem(No *raiz, int *primeiro) {
    if (raiz == NULL)
        return;

    posordem(raiz->esq, primeiro);
    posordem(raiz->dir, primeiro);
    imprimir_valor(raiz->valor, primeiro);
}

// Conta a quantidade total de nós
int contar_nos(No *raiz) {
    if (raiz == NULL)
        return 0;

    return 1 + contar_nos(raiz->esq) + contar_nos(raiz->dir);
}

// Conta quantas folhas existem na árvore
int contar_folhas(No *raiz) {
    if (raiz == NULL)
        return 0;

    if (raiz->esq == NULL && raiz->dir == NULL)
        return 1;

    return contar_folhas(raiz->esq) + contar_folhas(raiz->dir);
}

// Calcula a altura da árvore
// Árvore vazia possui altura -1
int altura(No *raiz) {
    int alt_esq, alt_dir;

    if (raiz == NULL)
        return -1;

    alt_esq = altura(raiz->esq);
    alt_dir = altura(raiz->dir);

    if (alt_esq > alt_dir)
        return alt_esq + 1;

    return alt_dir + 1;
}

// Procura o menor valor seguindo pela esquerda
int menor_valor(No *raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;

    return raiz->valor;
}

// Procura o maior valor seguindo pela direita
int maior_valor(No *raiz) {
    while (raiz->dir != NULL)
        raiz = raiz->dir;

    return raiz->valor;
}

// Libera toda a memória utilizada pela árvore
void liberar_arvore(No *raiz) {
    if (raiz == NULL)
        return;

    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

// Imprime qualquer percurso recebido por parâmetro
void imprimir_percurso(char nome[], void (*percurso)(No *, int *), No *raiz) {
    int primeiro = 1;

    printf("%s: ", nome);
    percurso(raiz, &primeiro);
    printf("\n");
}

int main(void) {
    No *raiz = NULL;
    int valor;

    // Lê os valores até encontrar -1
    while (scanf("%d", &valor) == 1 && valor != -1)
        raiz = inserir(raiz, valor);

    // Caso nenhum valor tenha sido inserido
    if (raiz == NULL) {
        printf("ARVORE VAZIA\n");
        return 0;
    }

    imprimir_percurso("PREORDEM", preordem, raiz);
    imprimir_percurso("EMORDEM", emordem, raiz);
    imprimir_percurso("POSORDEM", posordem, raiz);

    printf("NOS: %d\n", contar_nos(raiz));
    printf("FOLHAS: %d\n", contar_folhas(raiz));
    printf("ALTURA: %d\n", altura(raiz));
    printf("MENOR: %d\n", menor_valor(raiz));
    printf("MAIOR: %d\n", maior_valor(raiz));

    liberar_arvore(raiz);

    return 0;
}