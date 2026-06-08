// Enfeite da Praça

#include <stdio.h>

void aplicarEnfeites(char original[100][101], char resultado[100][101], int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            resultado[i][j] = original[i][j];
        }
        resultado[i][n] = '\0';
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (original[i][j] == 'P') {
                if (i - 1 >= 0 && resultado[i - 1][j] == '-')
                    resultado[i - 1][j] = '+';

                if (i + 1 < m && resultado[i + 1][j] == '-')
                    resultado[i + 1][j] = '+';

                if (j - 1 >= 0 && resultado[i][j - 1] == '-')
                    resultado[i][j - 1] = '+';

                if (j + 1 < n && resultado[i][j + 1] == '-')
                    resultado[i][j + 1] = '+';

                if (i - 1 >= 0 && j - 1 >= 0 && resultado[i - 1][j - 1] == '-')
                    resultado[i - 1][j - 1] = 'x';

                if (i - 1 >= 0 && j + 1 < n && resultado[i - 1][j + 1] == '-')
                    resultado[i - 1][j + 1] = 'x';

                if (i + 1 < m && j - 1 >= 0 && resultado[i + 1][j - 1] == '-')
                    resultado[i + 1][j - 1] = 'x';

                if (i + 1 < m && j + 1 < n && resultado[i + 1][j + 1] == '-')
                    resultado[i + 1][j + 1] = 'x';
            }
        }
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (original[i][j] == 'P') {
                if (i - 1 >= 0 && resultado[i - 1][j] != 'P')
                    resultado[i - 1][j] = '+';

                if (i + 1 < m && resultado[i + 1][j] != 'P')
                    resultado[i + 1][j] = '+';

                if (j - 1 >= 0 && resultado[i][j - 1] != 'P')
                    resultado[i][j - 1] = '+';

                if (j + 1 < n && resultado[i][j + 1] != 'P')
                    resultado[i][j + 1] = '+';
            }
        }
    }
}

int main() {
    int m, n, i;
    char original[100][101];
    char resultado[100][101];

    scanf("%d %d", &m, &n);

    for (i = 0; i < m; i++) {
        scanf("%s", original[i]);
    }

    aplicarEnfeites(original, resultado, m, n);

    for (i = 0; i < m; i++) {
        printf("%s\n", resultado[i]);
    }

    return 0;
}
