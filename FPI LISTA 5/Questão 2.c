// Lista de Alocação Dinâmica de Vetores - Sistema de Notas da Escola CInal do Saber

#include <stdio.h>
#include <stdlib.h>

// para calcular a média das notas
float media(float *v, int n) {
    float soma = 0;
    int i;

    for (i = 0; i < n; i++) {
        soma += v[i];
    }
    return soma / n;
}

// para encontrar a maior nota e seu índice
void maior(float *v, int n, float *valor, int *indice) {
    int i;
    *valor = v[0];
    *indice = 1;

    for (i = 1; i < n; i++) {
        if (v[i] > *valor) {
            *valor = v[i];
            *indice = i + 1;
        }
    }
}

// para encontrar a menor nota e seu índice
void menor(float *v, int n, float *valor, int *indice) {
    int i;
    *valor = v[0];
    *indice = 1;

    for (i = 1; i < n; i++) {
        if (v[i] < *valor) {
            *valor = v[i];
            *indice = i + 1;
        }
    }
}

// para contar quantos estão acima da média
int acima_media(float *v, int n, float m) {
    int i, cont = 0;

    for (i = 0; i < n; i++) {
        if (v[i] > m) {
            cont++;
        }
    }
    return cont;
}

// para ordenar o vetor (bubble sort)
void ordenar(float *v, int n) {
    int i, j;
    float temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// para calcular a mediana sem alterar o vetor original
float mediana(float *v, int n) {
    float *copia;
    int i;

    copia = (float *) malloc(n * sizeof(float));

    for (i = 0; i < n; i++) {
        copia[i] = v[i];
    }

    ordenar(copia, n);

    float med;

    if (n % 2 == 1) {
        med = copia[n / 2];
    } else {
        med = (copia[n / 2 - 1] + copia[n / 2]) / 2;
    }

    free(copia);
    return med;
}

// para calcular e imprime a moda
void moda(float *v, int n) {
    int i, j;
    int maior_cont = 0, repeticoes = 0;
    float moda = 0;

    for (i = 0; i < n; i++) {
        int cont = 0;

        for (j = 0; j < n; j++) {
            if (v[i] == v[j]) {
                cont++;
            }
        }

        if (cont > maior_cont) {
            maior_cont = cont;
            moda = v[i];
            repeticoes = 1;
        } else if (cont == maior_cont && v[i] != moda) {
            repeticoes++;
        }
    }

    if (maior_cont == 1 || repeticoes > 1) {
        printf("Moda: Nao ha moda unica\n");
    } else {
        printf("Moda: %.2f\n", moda);
    }
}

// imprime o relatório
void relatorio(float *v, int n, char titulo[]) {
    float m, maior_val, menor_val;
    int ind_maior, ind_menor, acima;

    printf("%s\n", titulo);

    m = media(v, n);
    maior(v, n, &maior_val, &ind_maior);
    menor(v, n, &menor_val, &ind_menor);
    acima = acima_media(v, n, m);

    printf("Media: %.2f\n", m);
    printf("Maior nota: %.2f (aluno %d)\n", maior_val, ind_maior);
    printf("Menor nota: %.2f (aluno %d)\n", menor_val, ind_menor);
    printf("Acima da media: %d\n", acima);
    printf("Mediana: %.2f\n", mediana(v, n));
    moda(v, n);

    printf("\n");
}

int main() {
    float *notas;
    int n, k, i;

    scanf("%d", &n);

    // aloca vetor inicial
    notas = (float *) malloc(n * sizeof(float));

    for (i = 0; i < n; i++) {
        scanf("%f", &notas[i]);
    }

    relatorio(notas, n, "Relatorio inicial");

    scanf("%d", &k);

    // para redimensionar vetor
    notas = (float *) realloc(notas, (n + k) * sizeof(float));

    for (i = n; i < n + k; i++) {
        scanf("%f", &notas[i]);
    }

    n += k;

    relatorio(notas, n, "Relatorio atualizado");

    free(notas);

    return 0;
}