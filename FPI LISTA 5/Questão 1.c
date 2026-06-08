// Lista de Alocação Dinâmica de Vetores - O Vício de Krebs

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    scanf("%d", &N);
    // leitura de quantas strings o problema vai me dar

    if (N <= 0) {
        return 0;
        // se não tiver nenhuma string, já encerro
    }
    char *strings;
    int *tamanhos;
    char *merged;
    int i, j;
    // aloco um bloco grande para guardar todas as strings
    strings = (char *)malloc((size_t)N * 1001 * sizeof(char));

    if (strings == NULL) {
        return 0;
        // se der erro na alocação, encerro
    }

    // vetor para guardar o tamanho de cada string
    tamanhos = (int *)malloc((size_t)N * sizeof(int));
    if (tamanhos == NULL) {
        free(strings);
        return 0;
    }
    // leitura das strings
    for (i = 0; i < N; i++) {
        scanf("%s", &strings[i * 1001]);
        // cada string começa em uma posição diferente do bloco
    }

    int max = 0;
    for (i = 0; i < N; i++) {

        int tam = 0;

        // contando o tamanho da string manualmente
        while (strings[i * 1001 + tam] != '\0') {
            tam++;
        }

        tamanhos[i] = tam;
        // guardo o tamanho dessa string

        if (tam > max) {
            max = tam;
            // descubro qual é a maior string
        }
    }

    int total_caracteres = 0;
    // somo todos os tamanhos para saber quanto preciso alocar
    for (i = 0; i < N; i++) {
        total_caracteres += tamanhos[i];
    }

    // aloco a string mesclada
    merged = (char *)malloc((size_t)(total_caracteres + 1) * sizeof(char));
    if (merged == NULL) {
        free(strings);
        free(tamanhos);
        return 0;
    }

    int k = 0;
    // esse k é o "cursor" da nova string

    // lógica da mesclagem
    // percorro por coluna primeiro
    for (i = 0; i < max; i++) {

        // depois percorro cada string
        for (j = 0; j < N; j++) {

            // só pego o caractere se ele existir
            if (i < tamanhos[j]) {
                merged[k] = strings[j * 1001 + i];
                k++;
            }
        }
    }

    merged[k] = '\0';
    // finalizo a string

    printf("%s\n", merged);
    // imprimo a string mesclada

    char *fundida;

    // aloco a string final após fusão
    fundida = (char *)malloc((size_t)(total_caracteres + 1) * sizeof(char));

    if (fundida == NULL) {
        free(strings);
        free(tamanhos);
        free(merged);
        return 0;
    }
    int tamanho_fundida = 0;
    i = 0;

    // percorro a string mesclada
    while (merged[i] != '\0') {
        // vejo se tem dois iguais lado a lado
        if (merged[i] == merged[i + 1] && merged[i + 1] != '\0') {
            // faço a fusão
            if (merged[i] == 'z') {
                fundida[tamanho_fundida] = 'a';
            } else {
                fundida[tamanho_fundida] = merged[i] + 1;
            }

            tamanho_fundida++;
            i = i + 2;
            // pulo os dois caracteres
        } else {
            // se não forem iguais, só copio
            fundida[tamanho_fundida] = merged[i];
            tamanho_fundida++;
            i++;
        }
        // verifico se a fusão gerou novos pares
        while (tamanho_fundida > 1 &&
               fundida[tamanho_fundida - 1] == fundida[tamanho_fundida - 2]) {
            if (fundida[tamanho_fundida - 1] == 'z') {
                fundida[tamanho_fundida - 2] = 'a';
            } else {
                fundida[tamanho_fundida - 2] = fundida[tamanho_fundida - 1] + 1;
            }
            tamanho_fundida--;
            // removo o último caractere
        }
    }
    fundida[tamanho_fundida] = '\0';
    printf("%s\n", fundida);
    // imprimo a string final
    free(strings);
    free(tamanhos);
    free(merged);
    free(fundida);
    // libero toda a memória usada

    return 0;
}