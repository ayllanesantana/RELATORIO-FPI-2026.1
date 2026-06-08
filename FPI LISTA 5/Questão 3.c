// Lista de Alocação Dinâmica de Vetores - Mapa vazio

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Ponteiro que vai apontar para o nosso vetor dinâmico
    // Começa como NULL porque ainda não temos espaço alocado
    int *vetor = NULL;
    // Ponteiro auxiliar pra não perder a memória caso o realloc falhe
    int *temp;
    // Guarda quantos números já foram lidos
    int tamanho = 0;
    // Variável para armazenar cada número digitado
    int numero;
    // Variável de controle dos loops
    int i;

    // para ler os números até acabar a entrada
    while (scanf("%d", &numero) == 1) {

        // Tentamos aumentar o vetor em +1 posição
        // realloc pode mover o vetor pra outro lugar na memória
        temp = realloc(vetor, (tamanho + 1) * sizeof(int));

        // Se der erro na alocação
        if (temp == NULL) {
            // Liberamos o que já foi alocado pra não dar vazamento
            free(vetor);
            // Encerramos o programa com erro
            return 1;
        }

        // Agora vetor aponta pro novo espaço (já aumentado)
        vetor = temp;
        // Guardamos o número na nova posição
        // *(vetor + tamanho) é a mesma coisa que vetor[tamanho]
        *(vetor + tamanho) = numero;
        // Aumentamos o tamanho do vetor
        tamanho++;
    }

    printf("Mais um bom dia de trabalho!\n");

    // Primeiro: imprimir apenas os números ímpares
    for (i = 0; i < tamanho; i++) {
        // Se o número NÃO for divisível por 2, ele é ímpar
        if (*(vetor + i) % 2 != 0) {
            printf("%d\n", *(vetor + i));
        }
    }

    // Depois: imprimir os números pares
    for (i = 0; i < tamanho; i++) {
        // Se o número for divisível por 2, ele é par
        if (*(vetor + i) % 2 == 0) {
            printf("%d\n", *(vetor + i));
        }
    }

    printf("Vou visitar esses lugares de novo... algum dia.\n");

    // Liberamos a memória usada pelo vetor
    free(vetor);

    return 0;
}