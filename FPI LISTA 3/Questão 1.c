// Maior sequência decrescente

#include <stdio.h>

int main() {
    int t, n, i;
    int v[100]; // vetor para guardar os valores da sequencia

    scanf("%d", &t); // para ler a quantidade de casos de teste

    while (t--) { // repete para cada caso de teste
        int inicioatual = 0, tamatual = 1;
        int melhorinicio = 0, melhortam = 0;

        scanf("%d", &n); // para ler o tamanho da sequencia

        // para ler os valores do vetor
        for (i = 0; i < n; i++) {
            scanf("%d", &v[i]);
        }

        // percorre o vetor procurando a maior sequencia decrescente
        for (i = 1; i < n; i++) {
            if (v[i - 1] > v[i]) {
                // se o valor anterior for maior, continua decrescendo
                tamatual++;
            } else {
                // se parou de decrescer, verifica se a sequencia atual eh a maior
                if (tamatual > 1 && tamatual > melhortam) {
                    melhortam = tamatual;
                    melhorinicio = inicioatual;
                }

                // come?a uma nova sequencia a partir da posicao atual
                inicioatual = i;
                tamatual = 1;
            }
        }

        // para verificar a ultima sequencia, pois ela pode ser a maior
        if (tamatual > 1 && tamatual > melhortam) {
            melhortam = tamatual;
            melhorinicio = inicioatual;
        }

        // imprime o tamanho da maior sequencia decrescente
        printf("%d\n", melhortam);

        // se existir sequencia decrescente, imprime seus elementos
        if (melhortam > 0) {
            for (i = melhorinicio; i < melhorinicio + melhortam; i++) {
                printf("%d ", v[i]);
            }
            printf("\n");
        }
    }

    return 0;
}