// Lista 6 (Matrizes Dinâmicas e Ponteiros para Funções) - Matriz dinâmica

#include <stdio.h>
#include <stdlib.h>

//função para alocar dinamicamente a matriz
int **alocar_matriz(int linhas, int colunas) {
    int **matriz;
    int i;
    //aloca o vetor de ponteiros (linhas)
    matriz = (int **)malloc(linhas * sizeof(int *));
    //para verificar se a alocação falhou
    if (matriz == NULL) {
        return NULL;
    }
    //aloca cada linha da matriz
    for (i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        //se alguma linha falhar, libera o que já foi alocado
        if (matriz[i] == NULL) {
            int j;
            for (j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }
    return matriz;
}


//função para ler os elementos da matriz
void ler_matriz(int **matriz, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            scanf("%d", &matriz[i][j]);

        }
    }
}


//função para imprimir a matriz formatada
void imprimir_matriz(int **matriz, int linhas, int colunas) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            //para evitar espaço antes do primeiro número
            if (j > 0) {
                printf(" ");
            }
            printf("%d", matriz[i][j]);
        }
        printf("\n");
    }
}


// libera toda memória alocada 
void liberar_matriz(int **matriz, int linhas) {
    int i;
    //libera cada linha
    for (i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    //libera vetor principal
    free(matriz);
}
//para retornar o dobro do valor
int dobro(int valor) {
    return valor * 2;
}
//retorna o quadrado do valor
int quadrado(int valor) {
    return valor * valor;
}
//retorna valor absoluto
int absoluto(int valor) {
    if (valor < 0) {
        return -valor;
    }
    return valor;
}


//função que percorre a matriz inteira e aplica a operação recebida pelo ponteiro para função
void aplicar_operacao(
    int **matriz,
    int linhas,
    int colunas,
    int (*operacao)(int)
) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            //aplica a função escolhida no elemento
            matriz[i][j] = operacao(matriz[i][j]);
        }
    }
}


int main(void) {
    int L, C;
    int op;
    int **matriz;
    //ponteiro para função: vai apontar para dobro, quadrado ou absoluto
    int (*operacao)(int);
    // lê dimensões da matriz
    scanf("%d %d", &L, &C);
    // aloca a matriz
    matriz = alocar_matriz(L, C);
    if (matriz == NULL) {
        return 0;
    }
    // lê os valores
    ler_matriz(matriz, L, C);
    // lê operação desejada
    scanf("%d", &op);
    // escolhe qual função o ponteiro vai guardar
    if (op == 1) {
        operacao = dobro;
    }
    else if (op == 2) {
        operacao = quadrado;
    }
    else {
        operacao = absoluto;
    }
    // aplica operação na matriz toda 
    aplicar_operacao(matriz, L, C, operacao);
    // imprime matriz resultante
    imprimir_matriz(matriz, L, C);
    // libera memória
    liberar_matriz(matriz, L);

    return 0;
}