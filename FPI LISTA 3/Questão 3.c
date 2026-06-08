// Ana e os anagramas

#include <stdio.h>

int main() {
    char frase[101];
    int inicio[50], fim[50];
    int cont1[26], cont2[26];
    int totalpalavras = 0;
    int totalpares = 0;
    int i = 0, j, k;
    int tamanho1, tamanho2;
    int iguais;
    char letra;

    // para ler a frase inteira digitada pelo usuario
    fgets(frase, 101, stdin);

    // anda pela frase para descobrir onde cada palavra comeca e termina
    while (frase[i] != '\0') {
        // se encontrou uma letra, entao comecou uma palavra
        if ((frase[i] >= 'A' && frase[i] <= 'Z') || (frase[i] >= 'a' && frase[i] <= 'z')) {
            inicio[totalpalavras] = i;

            // continua andando enquanto estiver dentro da palavra
            while ((frase[i] >= 'A' && frase[i] <= 'Z') || (frase[i] >= 'a' && frase[i] <= 'z')) {
                i++;
            }

            // guarda onde a palavra terminou
            fim[totalpalavras] = i - 1;
            totalpalavras++;
        } else {
            // se nao for letra, apenas pula
            i++;
        }
    }

    // compara cada palavra com as proximas sem repetir pares
    for (i = 0; i < totalpalavras; i++) {
        for (j = i + 1; j < totalpalavras; j++) {
            tamanho1 = fim[i] - inicio[i] + 1;
            tamanho2 = fim[j] - inicio[j] + 1;

            // se os tamanhos forem diferentes, nao podem ser anagramas
            if (tamanho1 == tamanho2) {
                // zera os vetores que contam as letras
                for (k = 0; k < 26; k++) {
                    cont1[k] = 0;
                    cont2[k] = 0;
                }

                // conta as letras da primeira palavra
                for (k = inicio[i]; k <= fim[i]; k++) {
                    letra = frase[k];

                    if (letra >= 'A' && letra <= 'Z') {
                        letra = letra + 32;
                    }

                    cont1[letra - 'a']++;
                }

                // conta as letras da segunda palavra
                for (k = inicio[j]; k <= fim[j]; k++) {
                    letra = frase[k];

                    if (letra >= 'A' && letra <= 'Z') {
                        letra = letra + 32;
                    }

                    cont2[letra - 'a']++;
                }

                iguais = 1;

                // compara a quantidade de cada letra
                for (k = 0; k < 26; k++) {
                    if (cont1[k] != cont2[k]) {
                        iguais = 0;
                    }
                }

                // se forem iguais, entao sao anagramas
                if (iguais == 1) {
                    // mostra o titulo so na primeira vez
                    if (totalpares == 0) {
                        printf("Pares de anagramas encontrados:\n");
                    }

                    // imprime a primeira palavra
                    for (k = inicio[i]; k <= fim[i]; k++) {
                        printf("%c", frase[k]);
                    }

                    printf(" e ");

                    // imprime a segunda palavra
                    for (k = inicio[j]; k <= fim[j]; k++) {
                        printf("%c", frase[k]);
                    }

                    printf("\n");
                    totalpares++;
                }
            }
        }
    }

    // mostra o total ou avisa que nao existem anagramas
    if (totalpares > 0) {
        printf("\nTotal de pares: %d\n", totalpares);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }

    return 0;
}