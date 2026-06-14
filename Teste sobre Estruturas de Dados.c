#include <stdio.h>
#include <stdlib.h>

// ESTRUTURAS DE DADOS

typedef struct NoLista {
    int valor;
    struct NoLista *prox;
} NoLista;

typedef struct NoPilha {
    int valor;
    struct NoPilha *prox;
} NoPilha;

typedef struct NoABB {
    int valor;
    struct NoABB *esq;
    struct NoABB *dir;
} NoABB;

// LISTA ENCADEADA

// Insere na cauda. Se o valor já existe, ignora.
NoLista* inserirLista(NoLista *head, NoLista **cauda, int valor) {
    NoLista *cur = head;
    while (cur) {
        if (cur->valor == valor) return head; // duplicata: ignora
        cur = cur->prox;
    }
    NoLista *novo = (NoLista*)malloc(sizeof(NoLista));
    novo->valor = valor;
    novo->prox  = NULL;
    if (!head) { *cauda = novo; return novo; }
    (*cauda)->prox = novo;
    *cauda = novo;
    return head;
}

// Busca sequencial. 1 comparação por nó visitado.
// Retorna 1 se encontrado, 0 caso contrário.
int buscarLista(NoLista *head, int valor, long long *comp) {
    NoLista *cur = head;
    while (cur) {
        (*comp)++;
        if (cur->valor == valor) return 1;
        cur = cur->prox;
    }
    return 0;
}

// Antecessor: percorre toda a lista mantendo melhor candidato (maior valor <= x).
// Parada antecipada somente quando valor == x.
int antecessorLista(NoLista *head, int x, long long *comp) {
    int melhor = -1;
    NoLista *cur = head;
    while (cur) {
        (*comp)++;
        if (cur->valor == x) return cur->valor; // igualdade: para imediatamente
        if (cur->valor < x && cur->valor > melhor)
            melhor = cur->valor;
        cur = cur->prox;
    }
    return melhor;
}

// Deleção com busca sequencial. Conta comparações durante a localização.
// Retorna 1 se o elemento foi encontrado e removido, 0 caso contrário.
// O valor de *deletado indica se a remoção ocorreu.
NoLista* deletarLista(NoLista *head, NoLista **cauda, int valor,
                      long long *comp, int *deletado) {
    NoLista *cur  = head;
    NoLista *prev = NULL;
    *deletado = 0;

    while (cur) {
        (*comp)++;
        if (cur->valor == valor) {
            // Encontrou: reencadeia e remove
            if (prev) prev->prox = cur->prox;
            else       head = cur->prox;
            if (cur == *cauda) *cauda = prev;
            free(cur);
            *deletado = 1;
            return head;
        }
        prev = cur;
        cur  = cur->prox;
    }
    return head; // não encontrado
}

void liberarLista(NoLista *head) {
    while (head) { NoLista *t = head; head = head->prox; free(t); }
}

// PILHA (inserção pelo topo)

// Empilha no topo. Ignora duplicatas.
NoPilha* empilhar(NoPilha *topo, int valor) {
    NoPilha *cur = topo;
    while (cur) {
        if (cur->valor == valor) return topo;
        cur = cur->prox;
    }
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));
    novo->valor = valor;
    novo->prox  = topo;
    return novo;
}

// Busca do topo para a base. 1 comparação por nó visitado.
int buscarPilha(NoPilha *topo, int valor, long long *comp) {
    NoPilha *cur = topo;
    while (cur) {
        (*comp)++;
        if (cur->valor == valor) return 1;
        cur = cur->prox;
    }
    return 0;
}

// Antecessor: percorre toda a pilha mantendo melhor candidato.
// Parada antecipada somente por igualdade.
int antecessorPilha(NoPilha *topo, int x, long long *comp) {
    int melhor = -1;
    NoPilha *cur = topo;
    while (cur) {
        (*comp)++;
        if (cur->valor == x) return cur->valor;
        if (cur->valor < x && cur->valor > melhor)
            melhor = cur->valor;
        cur = cur->prox;
    }
    return melhor;
}

// Deleção em qualquer posição da pilha.
// Conta comparações durante a localização.
NoPilha* deletarPilha(NoPilha *topo, int valor, long long *comp, int *deletado) {
    NoPilha *cur  = topo;
    NoPilha *prev = NULL;
    *deletado = 0;

    while (cur) {
        (*comp)++;
        if (cur->valor == valor) {
            if (prev) prev->prox = cur->prox;
            else       topo = cur->prox;
            free(cur);
            *deletado = 1;
            return topo;
        }
        prev = cur;
        cur  = cur->prox;
    }
    return topo;
}

void liberarPilha(NoPilha *topo) {
    while (topo) { NoPilha *t = topo; topo = topo->prox; free(t); }
}

// ÁRVORE BINÁRIA DE BUSCA (ABB)

// Inserção recursiva. Ignora duplicatas.
NoABB* inserirABB(NoABB *raiz, int valor) {
    if (!raiz) {
        NoABB *novo = (NoABB*)malloc(sizeof(NoABB));
        novo->valor = valor; novo->esq = NULL; novo->dir = NULL;
        return novo;
    }
    if      (valor < raiz->valor) raiz->esq = inserirABB(raiz->esq, valor);
    else if (valor > raiz->valor) raiz->dir = inserirABB(raiz->dir, valor);
    return raiz;
}

// Busca iterativa. 1 comparação por nó visitado.
int buscarABB(NoABB *raiz, int valor, long long *comp) {
    NoABB *cur = raiz;
    while (cur) {
        (*comp)++;
        if      (valor == cur->valor) return 1;
        else if (valor <  cur->valor) cur = cur->esq;
        else                          cur = cur->dir;
    }
    return 0;
}

// Antecessor: segue um único caminho da raiz.
// valor == x → retorna imediatamente.
// valor < x  → atualiza candidato e vai para direita.
// valor > x  → vai para esquerda.
int antecessorABB(NoABB *raiz, int x, long long *comp) {
    int melhor = -1;
    NoABB *cur = raiz;
    while (cur) {
        (*comp)++;
        if (cur->valor == x) return cur->valor;
        else if (cur->valor < x) { melhor = cur->valor; cur = cur->dir; }
        else                       cur = cur->esq;
    }
    return melhor;
}

// Retorna o nó de menor valor na subárvore (sucessor in-order).
// NÃO incrementa comparações.
NoABB* minimoABB(NoABB *no) {
    while (no->esq) no = no->esq;
    return no;
}

// Deleção iterativa na ABB.
// Conta comparações somente durante a localização do nó.
// Trata: (1) folha, (2) um filho, (3) dois filhos (usa sucessor in-order).
NoABB* deletarABB(NoABB *raiz, int valor, long long *comp, int *deletado) {
    NoABB *cur  = raiz;
    NoABB *prev = NULL;
    *deletado = 0;

    // Localiza o nó, contando comparações
    while (cur) {
        (*comp)++;
        if      (valor == cur->valor) break;
        prev = cur;
        if (valor < cur->valor) cur = cur->esq;
        else                    cur = cur->dir;
    }

    if (!cur) return raiz; // não encontrado

    *deletado = 1;

    // Caso 3: dois filhos → substitui pelo sucessor in-order
    if (cur->esq && cur->dir) {
        // Encontra o mínimo da subárvore direita (SEM contar comparações)
        NoABB *pai_suc = cur;
        NoABB *suc     = cur->dir;
        while (suc->esq) { pai_suc = suc; suc = suc->esq; }

        // Copia o valor do sucessor para o nó atual
        cur->valor = suc->valor;

        // Remove o nó sucessor (tem no máximo filho direito)
        if (pai_suc == cur) pai_suc->dir = suc->dir;
        else                pai_suc->esq = suc->dir;
        free(suc);
        return raiz;
    }

    // Casos 1 e 2: folha ou um único filho
    NoABB *filho = cur->esq ? cur->esq : cur->dir;

    if (!prev) { free(cur); return filho; } // removendo a raiz

    if (prev->esq == cur) prev->esq = filho;
    else                   prev->dir = filho;
    free(cur);
    return raiz;
}

void liberarABB(NoABB *raiz) {
    if (!raiz) return;
    liberarABB(raiz->esq);
    liberarABB(raiz->dir);
    free(raiz);
}

// VENCEDORA: menor número de comparações, com regras de empate
void imprimirVencedora(long long cL, long long cP, long long cA) {
    long long mn = cL;
    if (cP < mn) mn = cP;
    if (cA < mn) mn = cA;

    int vL = (cL == mn), vP = (cP == mn), vA = (cA == mn);

    if      (vL && vP && vA) printf("VENCEDORA: EMPATE\n");
    else if (vL && vP)       printf("VENCEDORA: LISTA e PILHA\n");
    else if (vL && vA)       printf("VENCEDORA: ABB e LISTA\n");
    else if (vP && vA)       printf("VENCEDORA: ABB e PILHA\n");
    else if (vL)             printf("VENCEDORA: LISTA\n");
    else if (vP)             printf("VENCEDORA: PILHA\n");
    else                     printf("VENCEDORA: ABB\n");
}

// MAIN
int main() {
    NoLista *headL = NULL, *caudaL = NULL;
    NoPilha *topoP = NULL;
    NoABB   *raizA = NULL;

    // Acumuladores de comparações por categoria
    long long compBuscaL = 0, compBuscaP = 0, compBuscaA = 0;
    long long compAntL   = 0, compAntP   = 0, compAntA   = 0;
    long long compDelL   = 0, compDelP   = 0, compDelA   = 0;

    // Contadores de operações totais e bem-sucedidas
    int nB = 0, encL = 0, encP = 0, encA = 0;
    int nA = 0, resL = 0, resP = 0, resA = 0;
    int nD = 0, delL = 0, delP = 0, delA = 0;

    int M;
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        char op;
        int x;
        scanf(" %c %d", &op, &x);

        if (op == 'I') {
            // Insere nas três estruturas (duplicatas ignoradas)
            headL = inserirLista(headL, &caudaL, x);
            topoP = empilhar(topoP, x);
            raizA = inserirABB(raizA, x);

        } else if (op == 'B') {
            nB++;
            if (buscarLista(headL, x, &compBuscaL)) encL++;
            if (buscarPilha(topoP, x, &compBuscaP)) encP++;
            if (buscarABB(raizA,   x, &compBuscaA)) encA++;

        } else if (op == 'A') {
            nA++;
            if (antecessorLista(headL, x, &compAntL) != -1) resL++;
            if (antecessorPilha(topoP, x, &compAntP) != -1) resP++;
            if (antecessorABB(raizA,   x, &compAntA) != -1) resA++;

        } else if (op == 'D') {
            nD++;
            int dL = 0, dP = 0, dA = 0;
            // Cada função de deleção conta suas próprias comparações
            // e sinaliza se o elemento foi encontrado via *deletado
            headL = deletarLista(headL, &caudaL, x, &compDelL, &dL);
            topoP = deletarPilha(topoP,          x, &compDelP, &dP);
            raizA = deletarABB(raizA,            x, &compDelA, &dA);
            if (dL) delL++;
            if (dP) delP++;
            if (dA) delA++;
        }
    }

    // Saída formatada
    printf("=== BUSCA ===\n");
    printf("[LISTA] Encontrados: %d/%d | Comparacoes: %lld\n", encL, nB, compBuscaL);
    printf("[PILHA] Encontrados: %d/%d | Comparacoes: %lld\n", encP, nB, compBuscaP);
    printf("[ABB] Encontrados: %d/%d | Comparacoes: %lld\n",   encA, nB, compBuscaA);
    imprimirVencedora(compBuscaL, compBuscaP, compBuscaA);

    printf("=== ANTECESSOR ===\n");
    printf("[LISTA] Resolvidos: %d/%d | Comparacoes: %lld\n", resL, nA, compAntL);
    printf("[PILHA] Resolvidos: %d/%d | Comparacoes: %lld\n", resP, nA, compAntP);
    printf("[ABB] Resolvidos: %d/%d | Comparacoes: %lld\n",   resA, nA, compAntA);
    imprimirVencedora(compAntL, compAntP, compAntA);

    printf("=== DELECAO ===\n");
    printf("[LISTA] Deletados: %d/%d | Comparacoes: %lld\n", delL, nD, compDelL);
    printf("[PILHA] Deletados: %d/%d | Comparacoes: %lld\n", delP, nD, compDelP);
    printf("[ABB] Deletados: %d/%d | Comparacoes: %lld\n",   delA, nD, compDelA);
    imprimirVencedora(compDelL, compDelP, compDelA);

    // Libera toda a memória
    liberarLista(headL);
    liberarPilha(topoP);
    liberarABB(raizA);

    return 0;
}