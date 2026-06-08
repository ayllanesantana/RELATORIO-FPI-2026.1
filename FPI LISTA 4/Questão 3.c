// Investimentos N3

#include <stdio.h>

void contarmov(int matriz[4][4]) {
    int lin = 0, col = 0;
    char mov;

    for (int i = 0; i < 20; i++) {
        scanf(" %c", &mov);

        if (mov == 'c' && lin > 0) {
            lin--;
            matriz[lin][col]++;
        } else if (mov == 'b' && lin < 3) {
            lin++;
            matriz[lin][col]++;
        } else if (mov == 'e' && col > 0) {
            col--;
            matriz[lin][col]++;
        } else if (mov == 'd' && col < 3) {
            col++;
            matriz[lin][col]++;
        }
    }
}

int main() {
    int matriz[4][4] = {0};
    int maior = matriz[0][0];
    int linmaior = 0, colmaior = 0;

    contarmov(matriz);

    for (int lin = 0; lin < 4; lin++) {
        for (int col = 0; col < 4; col++) {
            if (matriz[lin][col] > maior) {
                maior = matriz[lin][col];
                linmaior = lin;
                colmaior = col;
            }
        }
    }

    printf("Coordenada X:%d, Y:%d\n", colmaior, linmaior);

    return 0;
}
