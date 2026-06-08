// Lista 6 (Matrizes Dinâmicas e Ponteiros para Funções) - Rede de Sensores com Pipeline de Processamento

#include <stdio.h>
#include <stdlib.h>

// aloca matriz dinâmica
int **alocar_matriz(int l, int c) {
    int **m;
    int i;
    // vetor das linhas
    m = (int **)malloc(l * sizeof(int *));
    // verifica erro
    if (m == NULL) {
        return NULL;
    }
    // aloca cada linha
    for (i = 0; i < l; i++) {
        m[i] = (int *)malloc(c * sizeof(int));
        // se falhar libera tudo
        if (m[i] == NULL) {
            int j;
            for (j = 0; j < i; j++) {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }
    return m;
}


// lê matriz
void ler_matriz(int **m, int l, int c) {
    int i, j;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {

            scanf("%d", &m[i][j]);

        }
    }
}


// imprime matriz
void imprimir_matriz(int **m, int l, int c) {
    int i, j;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            // evita espaço no início
            if (j > 0) {
                printf(" ");
            }
            printf("%d", m[i][j]);
        }

        printf("\n");
    }
}


// libera memória
void liberar_matriz(int **m, int l) {
    int i;
    // libera linhas
    for (i = 0; i < l; i++) {
        free(m[i]);
    }
    // libera matriz principal
    free(m);
}

// filtro calibração
int f1(int v) {
    return v + 5;
}
// filtro saturação
int f2(int v) {

    if (v > 80) {
        return 80;
    }
    return v;
}

// filtro amplificador
int f3(int v) {
    return v * 2;
}

/*
modifica a matriz inteira
p = pipeline
q = quantidade de filtros
*/
void modificar(
    int **m,
    int l,
    int c,
    int (**p)(int),
    int q
) {
    int i, j, k;
    // percorre matriz
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            // aplica filtros em sequência
            for (k = 0; k < q; k++) {
                m[i][j] = p[k](m[i][j]);

            }
        }
    }
}

// acha maior sensor e posição
void encontrar_sensor_critico(
    int **m,
    int l,
    int c,
    int *maior,
    int *li,
    int *co
) {

    int i, j;
    // começa no primeiro elemento
    *maior = m[0][0];
    *li = 0;
    *co = 0;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            if (m[i][j] > *maior) {
                *maior = m[i][j];
                *li = i;
                *co = j;

            }
        }
    }
}

int main(void) {
    int l, c, cmd;
    int **m;
    // vetor dos filtros
    int (*f[3])(int);
    f[0] = f1;
    f[1] = f2;
    f[2] = f3;
    // dimensões
    scanf("%d %d", &l, &c);
    // cria matriz
    m = alocar_matriz(l, c);
    if (m == NULL) {
        return 0;
    }
    // valores dos sensores
    ler_matriz(m, l, c);
    // primeiro comando
    scanf("%d", &cmd);
    while (cmd != 0) {
        // comandos simples
        if (cmd >= 1 && cmd <= 3) {
            int (*p[1])(int);
            p[0] = f[cmd - 1];
            modificar(m, l, c, p, 1);
        }
        // pipeline
        else if (cmd == 4) {
            int q;
            int i;
            // pipeline dinâmico
            int (**p)(int);
            scanf("%d", &q);
            // aloca filtros
            p = (int (**)(int))
                malloc(q * sizeof(int (*)(int)));
            if (p == NULL) {
                liberar_matriz(m, l);
                return 0;
            }
            // lê ids dos filtros
            for (i = 0; i < q; i++) {
                int id;
                scanf("%d", &id);
                p[i] = f[id - 1];
            }
            // executa pipeline
            modificar(m, l, c, p, q);
            free(p);
        }
        // próximo comando
        scanf("%d", &cmd);
    }
    {
        int maior;
        int li;
        int co;
        encontrar_sensor_critico(
            m,
            l,
            c,
            &maior,
            &li,
            &co
        );

        printf("Matriz processada:\n");
        imprimir_matriz(m, l, c);

        printf("\n");

        printf("Sensor critico: %d\n", maior);

        printf(
            "Posicao: (%d,%d)\n",
            li,
            co
        );
    }


    liberar_matriz(m, l);

    return 0;
}