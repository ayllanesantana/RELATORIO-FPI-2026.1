// Lista 10 - Parte 1 (Pilhas, Filas e Listas Encadeadas) - Attack the Stack

#include <stdio.h>
#include <stdlib.h>

// Estrutura de cada bloco da pilha
typedef struct bloco {
    char cor;
    struct bloco *prox;
} bloco;

// Adiciona um bloco no topo da pilha
void empilhar(bloco **pilha, char cor) {
    bloco *novo = malloc(sizeof(bloco));

    // Se não conseguiu alocar memória
    if (novo == NULL)
        return;

    novo->cor = cor;      // Define a cor do bloco
    novo->prox = *pilha;  // Aponta para o antigo topo
    *pilha = novo;        // Novo bloco vira o topo
}

// Remove o bloco do topo
void desempilhar(bloco **pilha) {
    bloco *removido;

    // Se a pilha estiver vazia
    if (*pilha == NULL)
        return;

    removido = *pilha;
    *pilha = (*pilha)->prox;
    free(removido);
}

// Verifica se duas cores primárias podem ser combinadas
int primarias_combinam(char a, char b, char *resultado) {

    // Verde + Azul = Ciano
    if ((a == 'g' && b == 'b') || (a == 'b' && b == 'g')) {
        *resultado = 'c';
        return 1;
    }

    // Vermelho + Azul = Magenta
    if ((a == 'r' && b == 'b') || (a == 'b' && b == 'r')) {
        *resultado = 'm';
        return 1;
    }

    // Vermelho + Verde = Amarelo
    if ((a == 'r' && b == 'g') || (a == 'g' && b == 'r')) {
        *resultado = 'y';
        return 1;
    }

    // Não combinam
    return 0;
}

// Resolve todas as reações possíveis na pilha
void resolver_pilha(bloco **pilha) {
    char resultado;
    int mudou = 1;

    // Continua enquanto houver mudanças
    while (mudou && *pilha != NULL) {
        mudou = 0;

        // Verifica se existem 3 blocos iguais no topo
        if ((*pilha)->prox != NULL &&
            (*pilha)->prox->prox != NULL &&
            (*pilha)->cor == (*pilha)->prox->cor &&
            (*pilha)->cor == (*pilha)->prox->prox->cor) {

            // Remove os 3 blocos
            desempilhar(pilha);
            desempilhar(pilha);
            desempilhar(pilha);

            mudou = 1;
        }

        // Verifica se os 2 blocos do topo podem combinar
        else if ((*pilha)->prox != NULL &&
                 primarias_combinam((*pilha)->cor,
                                    (*pilha)->prox->cor,
                                    &resultado)) {

            // Remove os 2 blocos
            desempilhar(pilha);
            desempilhar(pilha);

            // Empilha o bloco resultante
            empilhar(pilha, resultado);

            mudou = 1;
        }
    }
}

// Imprime a pilha do topo para a base
void imprimir_pilha(bloco *pilha) {

    // Se estiver vazia
    if (pilha == NULL) {
        printf("Pilha vazia!\n\n");
        return;
    }

    // Percorre e imprime
    while (pilha != NULL) {
        printf("%c\n", pilha->cor);
        pilha = pilha->prox;
    }

    printf("\n");
}

// Libera toda memória da pilha
void liberar_pilha(bloco **pilha) {
    while (*pilha != NULL)
        desempilhar(pilha);
}

int main(void) {
    bloco *pilha = NULL;
    char cor;

    // Lê até EOF
    while (scanf(" %c", &cor) == 1) {

        // Adiciona o bloco
        empilhar(&pilha, cor);

        // Resolve reações
        resolver_pilha(&pilha);

        // Mostra estado atual
        imprimir_pilha(pilha);
    }

    printf("Thank You So Much For Playing My Game!\n");

    // Libera memória
    liberar_pilha(&pilha);

    return 0;
}