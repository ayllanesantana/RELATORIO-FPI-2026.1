// Marquinhos e a goteira

#include <stdio.h>

void simula(int x, int y, int m, int n, char parede[m][n + 1]) {
    if (x < 0 || x >= m || y < 0 || y >= n) return;

    if (x + 1 < m && parede[x + 1][y] == '.') {
        parede[x + 1][y] = 'o';
        simula(x + 1, y, m, n, parede);
    }
    else if (x + 1 < m && parede[x + 1][y] == '#') {
        if (y - 1 >= 0 && parede[x][y - 1] == '.') {
            parede[x][y - 1] = 'o';
            simula(x, y - 1, m, n, parede);
        }
        if (y + 1 < n && parede[x][y + 1] == '.') {
            parede[x][y + 1] = 'o';
            simula(x, y + 1, m, n, parede);
        }
    }
}

int main() {
    int m, n, i, j;
    int inicio_x = -1, inicio_y = -1;

    scanf("%d %d", &m, &n);

    char parede[m][n + 1];

    for (i = 0; i < m; i++) {
        scanf("%s", parede[i]);
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (parede[i][j] == 'o') {
                inicio_x = i;
                inicio_y = j;
            }
        }
    }

    simula(inicio_x, inicio_y, m, n, parede);

    for (i = 0; i < m; i++) {
        printf("%s\n", parede[i]);
    }

    return 0;
}