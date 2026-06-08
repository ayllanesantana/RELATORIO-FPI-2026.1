// Questão 4 — Atualização de Estoque com Arquivos (Tópico 2: Arquivos)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    double preco;
} produto;

typedef struct {
    int codigo;
    char tipo;
    int quantidade;
    char motivo[30];
} inconsistencia;

int buscar_produto(produto v[], int n, int codigo) {
    int i;

    // Procura o produto pelo código.
    for (i = 0; i < n; i++)
        if (v[i].codigo == codigo)
            return i;

    return -1;
}

void adicionar_inconsistencia(inconsistencia **inc, int *qtd, int *cap,
                              int codigo, char tipo, int quantidade, char motivo[]) {
    inconsistencia *novo;

    // Aumenta o vetor de inconsistências quando necessário.
    if (*qtd == *cap) {
        if (*cap == 0)
            *cap = 2;
        else
            *cap = *cap * 2;

        novo = realloc(*inc, (*cap) * sizeof(inconsistencia));

        if (novo == NULL)
            return;

        *inc = novo;
    }

    // Guarda a inconsistência.
    (*inc)[*qtd].codigo = codigo;
    (*inc)[*qtd].tipo = tipo;
    (*inc)[*qtd].quantidade = quantidade;
    strcpy((*inc)[*qtd].motivo, motivo);
    (*qtd)++;
}

int main(void) {
    FILE *arq_produtos, *arq_movimentos, *arq_estoque, *arq_relatorio;
    produto *produtos = NULL;
    produto *novo_produto;
    inconsistencia *inc = NULL;
    int qtd_produtos = 0, cap_produtos = 0;
    int qtd_inc = 0, cap_inc = 0;
    int aplicados = 0, recusadas = 0, sem_cadastro = 0;
    int codigo, quantidade, pos, i;
    char nome[50], tipo;
    double preco;

    // Abre os arquivos de entrada.
    arq_produtos = fopen("produtos.txt", "r");
    arq_movimentos = fopen("movimentos.txt", "r");

    if (arq_produtos == NULL || arq_movimentos == NULL) {
        printf("Erro ao abrir arquivo.\n");

        if (arq_produtos != NULL)
            fclose(arq_produtos);
        if (arq_movimentos != NULL)
            fclose(arq_movimentos);

        return 0;
    }

    // Lê os produtos do arquivo mestre.
    while (fscanf(arq_produtos, "%d %49s %d %lf", &codigo, nome, &quantidade, &preco) == 4) {
        if (qtd_produtos == cap_produtos) {
            if (cap_produtos == 0)
                cap_produtos = 2;
            else
                cap_produtos = cap_produtos * 2;

            novo_produto = realloc(produtos, cap_produtos * sizeof(produto));

            if (novo_produto == NULL) {
                free(produtos);
                free(inc);
                fclose(arq_produtos);
                fclose(arq_movimentos);
                return 0;
            }

            produtos = novo_produto;
        }

        produtos[qtd_produtos].codigo = codigo;
        strcpy(produtos[qtd_produtos].nome, nome);
        produtos[qtd_produtos].quantidade = quantidade;
        produtos[qtd_produtos].preco = preco;
        qtd_produtos++;
    }

    fclose(arq_produtos);

    // Processa os movimentos.
    while (fscanf(arq_movimentos, "%d %c %d", &codigo, &tipo, &quantidade) == 3) {
        pos = buscar_produto(produtos, qtd_produtos, codigo);

        if (pos == -1) {
            sem_cadastro++;
            adicionar_inconsistencia(&inc, &qtd_inc, &cap_inc,
                                     codigo, tipo, quantidade, "PRODUTO_INEXISTENTE");
        } else if (tipo == 'E') {
            produtos[pos].quantidade += quantidade;
            aplicados++;
        } else if (tipo == 'S') {
            if (produtos[pos].quantidade >= quantidade) {
                produtos[pos].quantidade -= quantidade;
                aplicados++;
            } else {
                recusadas++;
                adicionar_inconsistencia(&inc, &qtd_inc, &cap_inc,
                                         codigo, tipo, quantidade, "ESTOQUE_INSUFICIENTE");
            }
        }
    }

    fclose(arq_movimentos);

    // Cria os arquivos de saída.
    arq_estoque = fopen("estoque_atualizado.txt", "w");
    arq_relatorio = fopen("relatorio.txt", "w");

    if (arq_estoque == NULL || arq_relatorio == NULL) {
        printf("Erro ao abrir arquivo.\n");

        if (arq_estoque != NULL)
            fclose(arq_estoque);
        if (arq_relatorio != NULL)
            fclose(arq_relatorio);

        free(produtos);
        free(inc);
        return 0;
    }

    // Escreve o estoque atualizado.
    for (i = 0; i < qtd_produtos; i++)
        fprintf(arq_estoque, "%d %s %d %.2lf\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].quantidade,
                produtos[i].preco);

    // Escreve os dados do relatório.
    fprintf(arq_relatorio, "PRODUTOS PROCESSADOS: %d\n", qtd_produtos);
    fprintf(arq_relatorio, "MOVIMENTOS APLICADOS: %d\n", aplicados);
    fprintf(arq_relatorio, "SAIDAS RECUSADAS: %d\n", recusadas);
    fprintf(arq_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", sem_cadastro);

    fprintf(arq_relatorio, "ESTOQUE BAIXO:\n");
    for (i = 0; i < qtd_produtos; i++) {
        if (produtos[i].quantidade <= 5)
            fprintf(arq_relatorio, "%d %s %d\n",
                    produtos[i].codigo,
                    produtos[i].nome,
                    produtos[i].quantidade);
    }

    fprintf(arq_relatorio, "INCONSISTENCIAS:\n");
    for (i = 0; i < qtd_inc; i++) {
        fprintf(arq_relatorio, "%d %c %d %s\n",
                inc[i].codigo,
                inc[i].tipo,
                inc[i].quantidade,
                inc[i].motivo);
    }

    // Fecha os arquivos de saída.
    fclose(arq_estoque);
    fclose(arq_relatorio);

    // Libera a memória dinâmica.
    free(produtos);
    free(inc);

    return 0;
}