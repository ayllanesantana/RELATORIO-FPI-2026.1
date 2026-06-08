// Fuga no escuro

#include <stdio.h>

int main() {
    int q;
    scanf("%d", &q);

    int coluna = 0;       // posição atual do cursor
    int temPonto = 0;     // verifica se já existe ponto na linha
    int esq = 0, dir = 0; // inicio e fim do desenho na linha atual

    for (int i = 0; i < q; i++) {
        int x;
        char c;
        scanf("%d %c", &x, &c);

        if (c == 'D') {
            // se a linha estiver vazia, começa a desenhar
            if (!temPonto) {
                esq = coluna;
                dir = coluna + x - 1;
                coluna = dir;
                temPonto = 1;
            } else {
                // se já tiver desenho, continua para a direita
                coluna += x;
                if (coluna > dir)
                    dir = coluna;
            }
        }

        else if (c == 'E') {
            // se passar da coluna 0, a entrada e invalida
            if (coluna - x < 0) {
                printf("Informacao invalida");
                return 0;
            }

            // se ainda nao tiver desenho, cria o primeiro trecho
            if (!temPonto) {
                esq = coluna - x;
                dir = coluna;
                coluna -= x;
                temPonto = 1;
            } else {
                // se j� tiver desenho, so atualiza a nova posição
                coluna -= x;
                if (coluna < esq)
                    esq = coluna;
            }
        }

        else if (c == 'B') {
            // imprime a linha atual antes de descer
            if (temPonto) {
                for (int j = 0; j < esq; j++)
                    printf(" ");
                for (int j = esq; j <= dir; j++)
                    printf(".");
                printf("\n");
            }

            // imprime as linhas da descida
            for (int k = 1; k < x; k++) {
                for (int j = 0; j < coluna; j++)
                    printf(" ");
                printf(".\n");
            }

            // o cursor continua na mesma coluna depois da descida
            esq = coluna;
            dir = coluna;
            temPonto = 1;
        }
    }

    // imprime a última linha que ficou guardada
    if (temPonto) {
        for (int j = 0; j < esq; j++)
            printf(" ");
        for (int j = esq; j <= dir; j++)
            printf(".");
        printf("\n");
    }

    return 0;
}
