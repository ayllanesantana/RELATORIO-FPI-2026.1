// Promoção de energético

#include <stdio.h>

int main() {
    int N, X, Y;
    scanf("%d%d%d", &N, &X, &Y);

    int latas[10001] = {0};

    for (int i = 0; i < Y; i++) {
        int h, m, z;
        scanf("%d:%d %d", &h, &m, &z);

        int minutos = (h - 7) * 60 + m;
        int cliente = minutos / 3;

        if (cliente >= 1 && cliente <= N) {
            latas[cliente] = z;
        }
    }

    int soma = 0;
    int vencedor = 0;
    int comprou = 0;

    for (int i = 1; i <= N; i++) {
        int atual = 0;

        if (latas[i] > 1) {
            atual = latas[i];
        } else if (X != 0 && i % X == 0) {
            atual = 1;
        }

        if (soma < 50 && soma + atual >= 50) {
            vencedor = i;
            comprou = atual;
            break;
        }

        soma += atual;
    }

    if (vencedor == 0) {
        int faltam = 50 - soma;

        if (faltam == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta %d lata.\n", faltam);
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", faltam);
        }
    } else {
        int totalmin = vencedor * 3;
        int hora = 7 + totalmin / 60;
        int minuto = totalmin % 60;

        if (comprou == 1) {
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.\n",
                   vencedor, hora, minuto, comprou);
        } else {
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n",
                   vencedor, hora, minuto, comprou);
        }
    }

    return 0;
}
