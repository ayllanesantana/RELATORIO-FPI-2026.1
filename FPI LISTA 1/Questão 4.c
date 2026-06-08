// Caminhada estratégica

#include <stdio.h>

int main() {

    int x, y, c;
    int destino_x, destino_y;
    int passos_x, passos_y;

    scanf("%d %d %d", &x, &y, &c);

    int quadrante;

    if (x > 0 && y > 0) {
        quadrante = 1;
    }
    else if (x < 0 && y > 0) {
        quadrante = 2;
    }
    else if (x < 0 && y < 0) {
        quadrante = 3;
    }
    else if (x > 0 && y < 0) {
        quadrante = 4;
    }
    else {
        printf("caminhada invalida\n");
        return 0;
    }

    if (quadrante == 1) {
        destino_x = -1;
        destino_y = -1;

        if (c == 2) {
            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
        }
        else if (c == 4) {
            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
        }
        else {
            printf("caminhada invalida\n");
        }
    }

    else if (quadrante == 2) {
        destino_x = 1;
        destino_y = -1;

        if (c == 1) {
            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
        }
        else if (c == 3) {
            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
        }
        else {
            printf("caminhada invalida\n");
        }
    }

    else if (quadrante == 3) {
        destino_x = 1;
        destino_y = 1;

        if (c == 2) {
            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
        }
        else if (c == 4) {
            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
        }
        else {
            printf("caminhada invalida\n");
        }
    }

    else if (quadrante == 4) {
        destino_x = -1;
        destino_y = 1;

        if (c == 1) {
            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
        }
        else if (c == 3) {
            passos_y = y - destino_y;
            if (passos_y < 0) passos_y = -passos_y;

            passos_x = x - destino_x;
            if (passos_x < 0) passos_x = -passos_x;

            printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
        }
        else {
            printf("caminhada invalida\n");
        }
    }

    return 0;
}