// A Fuga de Rebeka

#include <stdio.h>

char mapa[1000][1000];
int dist[1000][1000];

int qtdlin, qtdcol;

int linorig, colorig;
int lindest, coldest;

void lermapa() {
    for (int lin = 0; lin < qtdlin; lin++) {
        scanf("%s", mapa[lin]);

        for (int col = 0; col < qtdcol; col++) {
            dist[lin][col] = -1;

            if (mapa[lin][col] == 'o') {
                linorig = lin;
                colorig = col;
            }

            if (mapa[lin][col] == 'd') {
                lindest = lin;
                coldest = col;
            }
        }
    }
}

int menordist() {
    int filalin[1000000];
    int filacol[1000000];

    int ini = 0;
    int fim = 0;

    int movlin[4] = {-1, 1, 0, 0};
    int movcol[4] = {0, 0, -1, 1};

    filalin[fim] = linorig;
    filacol[fim] = colorig;
    fim++;

    dist[linorig][colorig] = 0;

    while (ini < fim) {
        int linatual = filalin[ini];
        int colatual = filacol[ini];
        ini++;

        for (int dir = 0; dir < 4; dir++) {
            int proxlin = linatual + movlin[dir];
            int proxcol = colatual + movcol[dir];

            if (proxlin >= 0 && proxlin < qtdlin &&
                proxcol >= 0 && proxcol < qtdcol) {

                if (mapa[proxlin][proxcol] != '#' &&
                    dist[proxlin][proxcol] == -1) {

                    dist[proxlin][proxcol] = dist[linatual][colatual] + 1;

                    filalin[fim] = proxlin;
                    filacol[fim] = proxcol;
                    fim++;
                }
            }
        }
    }

    return dist[lindest][coldest];
}

int main() {
    scanf("%dx%d", &qtdlin, &qtdcol);

    lermapa();

    int resp = menordist();

    if (resp != -1) {
        printf("Apos correr %d metros e quase desistir por causa da dist�ncia, Rebeka conseguiu escapar!\n", resp);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}