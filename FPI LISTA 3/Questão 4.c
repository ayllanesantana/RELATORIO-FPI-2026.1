// faísca e fumaça

#include <stdio.h>

int main() {
    int r;
    int caso;
    char s[65];
    char final_led[65];
    char gigante[70000];
    int tamanho_gigante;

    tamanho_gigante = 0;
    scanf("%d", &r);

    for (caso = 0; caso < r; caso++) {
        int c;
        int tamanho;
        int i;
        int j;
        int leds[65];

        // para ler a configuracao inicial e a quantidade de clocks. 
        scanf("%s %d", s, &c);

        // para calcular o tamanho da string. 
        tamanho = 0;
        while (s[tamanho] != '\0') {
            tamanho++;
        }

        // para converter a string para um vetor numerico:
          // O = 1 (ligado), X = 0 (desligado).
        for (i = 0; i < tamanho; i++) {
            if (s[i] == 'O') {
                leds[i] = 1;
            } else {
                leds[i] = 0;
            }
        }

        /* simula os clocks.
           primeiro o led da esquerda troca de estado.
           sempre que um led fica desligado, o proximo tambem troca. */
        for (i = 0; i < c; i++) {
            leds[0] = 1 - leds[0];

            j = 0;
            while (j < tamanho - 1 && leds[j] == 0) {
                leds[j + 1] = 1 - leds[j + 1];
                j++;
            }
        }

        // para montar a resposta final do caso novamente em formato de string. 
        for (i = 0; i < tamanho; i++) {
            if (leds[i] == 1) {
                final_led[i] = 'O';
            } else {
                final_led[i] = 'X';
            }
        }
        final_led[tamanho] = '\0';

        printf("%s\n", final_led);

        if (caso == 0) {
            // o primeiro caso inicia a luz gigante.
            for (i = 0; i < tamanho; i++) {
                gigante[tamanho_gigante] = final_led[i];
                tamanho_gigante++;
            }
        } else {
            char ultimo;
            char primeiro_novo;
            char ornamento;

            ultimo = gigante[tamanho_gigante - 1];
            primeiro_novo = final_led[0];

            // para escolher o ornamento de acordo com:
            //  - paridade do tamanho atual da luz gigante
            //  - comparacao entre o ultimo led atual e o primeiro do novo fio 
            if (tamanho_gigante % 2 == 0) {
                if (ultimo == primeiro_novo) {
                    ornamento = '@';
                } else {
                    ornamento = '$';
                }
            } else {
                if (ultimo == primeiro_novo) {
                    ornamento = '#';
                } else {
                    ornamento = '%';
                }
            }

            // para anexar o ornamento e depois o novo fio na luz gigante.
            gigante[tamanho_gigante] = ornamento;
            tamanho_gigante++;

            for (i = 0; i < tamanho; i++) {
                gigante[tamanho_gigante] = final_led[i];
                tamanho_gigante++;
            }
        }
    }

    gigante[tamanho_gigante] = '\0';
    printf("%s\n", gigante);

    return 0;
}
