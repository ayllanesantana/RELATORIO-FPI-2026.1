// Lista 10 - Parte 1 (Pilhas, Filas e Listas Encadeadas) - Gerenciador de Fila de Tarefas

#include <stdio.h>
#include <stdlib.h>

// Estrutura de cada tarefa da fila
typedef struct Tarefa {
    int id;
    int prioridade;
    struct Tarefa *prox;
} Tarefa;

// Insere nova tarefa no final da fila
void inserir(Tarefa **head, Tarefa **tail, int id, int prioridade) {
    Tarefa *nova = malloc(sizeof(Tarefa));

    // Verifica se a alocação deu certo
    if (nova == NULL)
        return;

    nova->id = id;
    nova->prioridade = prioridade;
    nova->prox = NULL;

    // Se a fila estiver vazia
    if (*head == NULL) {
        *head = nova;
        *tail = nova;
    }

    // Caso contrário, adiciona no final
    else {
        (*tail)->prox = nova;
        *tail = nova;
    }
}

// Remove tarefa do início da fila
void remover(Tarefa **head, Tarefa **tail) {
    Tarefa *removida;

    // Se a fila estiver vazia
    if (*head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    removida = *head;

    printf("Removida: id=%d prioridade=%d\n",
           removida->id,
           removida->prioridade);

    *head = (*head)->prox;

    // Se a fila ficou vazia
    if (*head == NULL)
        *tail = NULL;

    free(removida);
}

// Lista todas as tarefas
void listar(Tarefa *head) {

    // Se a fila estiver vazia
    if (head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    // Percorre toda a fila
    while (head != NULL) {
        printf("id=%d prioridade=%d\n",
               head->id,
               head->prioridade);

        head = head->prox;
    }
}

int main(void) {
    Tarefa *head = NULL;
    Tarefa *tail = NULL;
    Tarefa *aux;

    char comando;
    int id, prioridade;

    // Lê comandos até encontrar F
    while (scanf(" %c", &comando) == 1) {

        // Inserir
        if (comando == 'I') {
            scanf("%d %d", &id, &prioridade);
            inserir(&head, &tail, id, prioridade);
        }

        // Remover
        else if (comando == 'R') {
            remover(&head, &tail);
        }

        // Listar
        else if (comando == 'L') {
            listar(head);
        }

        // Finalizar
        else if (comando == 'F') {
            break;
        }
    }

    // Libera memória restante
    while (head != NULL) {
        aux = head;
        head = head->prox;
        free(aux);
    }

    return 0;
}