// Lista 10 - Parte 1 (Pilhas, Filas e Listas Encadeadas) - Novo Sistema de Matrículas do SIGAA

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de cada aluno da fila
typedef struct aluno {
    char mat[12];
    int prioridade;
    double cr;
    long long chegada;
    long long timeout;
    struct aluno *prox;
} aluno;

// Estrutura da fila
typedef struct {
    aluno *inicio;
    aluno *fim;
} fila;

// Inicializa a fila vazia
void inicializar_fila(fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Verifica se a fila está vazia
int fila_vazia(fila *f) {
    return f->inicio == NULL;
}

// Insere aluno no final da fila
void enqueue(fila *f, char mat[], int prioridade, double cr,
             long long chegada, long long timeout) {

    aluno *novo = malloc(sizeof(aluno));

    // Se não conseguiu alocar memória
    if (novo == NULL)
        return;

    // Preenche os dados do novo aluno
    strcpy(novo->mat, mat);
    novo->prioridade = prioridade;
    novo->cr = cr;
    novo->chegada = chegada;
    novo->timeout = timeout;
    novo->prox = NULL;

    // Se a fila estiver vazia
    if (fila_vazia(f))
        f->inicio = novo;
    else
        f->fim->prox = novo;

    // Atualiza o fim
    f->fim = novo;
}

// Remove aluno do início da fila
aluno *dequeue(fila *f) {
    aluno *removido;

    if (fila_vazia(f))
        return NULL;

    removido = f->inicio;
    f->inicio = f->inicio->prox;

    // Se a fila ficou vazia
    if (f->inicio == NULL)
        f->fim = NULL;

    removido->prox = NULL;

    return removido;
}

// Libera toda memória da fila
void liberar_fila(fila *f) {
    aluno *removido;

    while (!fila_vazia(f)) {
        removido = dequeue(f);
        free(removido);
    }
}

// Calcula o score do aluno
int calcular_score(double cr, int prioridade) {
    int valor;

    // Arredonda corretamente
    valor = (int) round(cr * 100);

    return valor / prioridade;
}

int main(void) {
    fila requisicoes, confirmados;

    char comando[10];
    char disciplina[51];
    char mat[12];

    int vagas = 0;
    int prioridade;
    int qtd;
    int score;
    int posicao = 1;

    double cr;

    long long chegada;
    long long timeout;
    long long tempo = 1;

    aluno *atual;

    // Inicializa as duas filas
    inicializar_fila(&requisicoes);
    inicializar_fila(&confirmados);

    // Lê comandos até EOF
    while (scanf("%9s", comando) == 1) {

        // Inicia disciplina
        if (strcmp(comando, "START") == 0) {
            scanf("%50s %d", disciplina, &vagas);
        }

        // Adiciona aluno à fila
        else if (strcmp(comando, "ADD") == 0) {
            scanf("%11s %d %lf %lld %lld",
                  mat, &prioridade, &cr, &chegada, &timeout);

            enqueue(&requisicoes, mat, prioridade, cr, chegada, timeout);
        }

        // Processa alunos
        else if (strcmp(comando, "PROC") == 0) {
            scanf("%d", &qtd);

            while (qtd > 0 && !fila_vazia(&requisicoes)) {

                atual = dequeue(&requisicoes);

                // Se servidor estiver ocioso, avança até a chegada
                if (tempo < atual->chegada)
                    tempo = atual->chegada;

                // Verifica timeout
                if (tempo > atual->timeout) {
                    printf("[TIMEOUT] mat=%s | Desconectado da fila.\n",
                           atual->mat);

                    free(atual);
                }

                else {
                    score = calcular_score(atual->cr,
                                           atual->prioridade);

                    // Se houver vaga
                    if (vagas > 0) {
                        printf("[ALOCADO] mat=%s | score=%d | Processado no seg: %lld\n",
                               atual->mat, score, tempo);

                        // Move para confirmados
                        enqueue(&confirmados,
                                atual->mat,
                                atual->prioridade,
                                atual->cr,
                                atual->chegada,
                                atual->timeout);

                        vagas--;
                    }

                    // Sem vagas disponíveis
                    else {
                        printf("[LOTADO] mat=%s | score=%d | Processado no seg: %lld\n",
                               atual->mat, score, tempo);
                    }

                    // Avança relógio
                    tempo++;

                    free(atual);
                }

                qtd--;
            }
        }

        // Finaliza e imprime lista oficial
        else if (strcmp(comando, "FIM") == 0) {

            printf("--- LISTA OFICIAL: %s ---\n", disciplina);

            while (!fila_vazia(&confirmados)) {
                atual = dequeue(&confirmados);

                printf("%d. Matricula: %s\n",
                       posicao, atual->mat);

                posicao++;

                free(atual);
            }

            break;
        }
    }

    // Libera memória restante
    liberar_fila(&requisicoes);
    liberar_fila(&confirmados);

    return 0;
}