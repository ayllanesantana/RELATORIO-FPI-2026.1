// Questão 3 — Processamento de Arquivos CSV (Tópico 2: Arquivos)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char species[50];
} flor;

void remover_quebra(char s[])
{
    int i;

    // Remove \n ou \r do final da linha.
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '\n' || s[i] == '\r')
        {
            s[i] = '\0';
            return;
        }
    }
}

int vem_antes(char a[], char b[])
{
    // Usado para desempate em ordem lexicográfica.
    return strcmp(a, b) < 0;
}

void calcular_moda(flor v[], int n, char moda[])
{
    int i, j;
    int cont, maior = 0;

    moda[0] = '\0';

    // Conta quantas vezes cada espécie aparece.
    for (i = 0; i < n; i++)
    {
        cont = 0;

        for (j = 0; j < n; j++)
        {
            if (strcmp(v[i].species, v[j].species) == 0)
                cont++;
        }

        // Atualiza a moda; em empate, pega a menor lexicográfica.
        if (cont > maior || (cont == maior && vem_antes(v[i].species, moda)))
        {
            maior = cont;
            strcpy(moda, v[i].species);
        }
    }
}

void imprimir_arquivo(char nome[])
{
    FILE *arquivo;
    char linha[300];

    arquivo = fopen(nome, "r");

    if (arquivo == NULL)
        return;

    printf("Conteudo de %s:\n", nome);

    // Imprime todo o conteúdo do arquivo.
    while (fgets(linha, 300, arquivo) != NULL)
        printf("%s", linha);

    printf("\n");

    fclose(arquivo);
}

void processar_arquivo(char nome[])
{
    FILE *arquivo;
    flor *dados = NULL;
    flor *novo;
    char linha[300];
    char moda[50];
    int qtd = 0, capacidade = 0;
    int lidos;
    double soma_sl = 0, soma_sw = 0, soma_pl = 0, soma_pw = 0;

    arquivo = fopen(nome, "r");

    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir %s.\n\n", nome);
        return;
    }

    // Ignora o cabeçalho.
    fgets(linha, 300, arquivo);

    while (fgets(linha, 300, arquivo) != NULL)
    {
        remover_quebra(linha);

        if (linha[0] == '\0')
            continue;

        // Aumenta o vetor quando ele fica cheio.
        if (qtd == capacidade)
        {
            if (capacidade == 0)
                capacidade = 2;
            else
                capacidade = capacidade * 2;

            novo = realloc(dados, capacidade * sizeof(flor));

            if (novo == NULL)
            {
                free(dados);
                fclose(arquivo);
                return;
            }

            dados = novo;
        }

        // Lê uma linha CSV.
        lidos = sscanf(linha, "%lf,%lf,%lf,%lf,%49[^,\n]",
                       &dados[qtd].sepal_length,
                       &dados[qtd].sepal_width,
                       &dados[qtd].petal_length,
                       &dados[qtd].petal_width,
                       dados[qtd].species);

        if (lidos == 5)
        {
            soma_sl += dados[qtd].sepal_length;
            soma_sw += dados[qtd].sepal_width;
            soma_pl += dados[qtd].petal_length;
            soma_pw += dados[qtd].petal_width;
            qtd++;
        }
    }

    fclose(arquivo);

    if (qtd > 0)
    {
        calcular_moda(dados, qtd, moda);

        arquivo = fopen(nome, "a");

        if (arquivo != NULL)
        {
            // Grava os resultados no final do mesmo arquivo.
            fprintf(arquivo, "\nResultados\n");
            fprintf(arquivo, "media_sepal_length,%.2lf\n", soma_sl / qtd);
            fprintf(arquivo, "media_sepal_width,%.2lf\n", soma_sw / qtd);
            fprintf(arquivo, "media_petal_length,%.2lf\n", soma_pl / qtd);
            fprintf(arquivo, "media_petal_width,%.2lf\n", soma_pw / qtd);
            fprintf(arquivo, "especie_predominante,%s\n", moda);
            fclose(arquivo);
        }
    }

    free(dados);
    imprimir_arquivo(nome);
}

int main(void)
{
    int n, i;
    char nome[30];

    scanf("%d", &n);

    // Processa iris1.csv, iris2.csv, ...
    for (i = 1; i <= n; i++)
    {
        sprintf(nome, "iris%d.csv", i);
        processar_arquivo(nome);
    }

    return 0;
}