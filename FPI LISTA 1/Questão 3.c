// Rebeka e a volta para casa

#include <stdio.h>

int main() {
    int total, x, y, z;
    if (scanf("%d %d %d %d", &total, &x, &y, &z) != 4) return 0;

    int investiu = -1;
    int a = 0, b = 0, c = 0;
    int sobra = 0;
    int novo;

    if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0) {
        a = (total * x) / 100;
        b = (total * y) / 100;
        c = (total * z) / 100;
        sobra = total - (a + b + c);
        investiu = 0;
    }

    if (investiu == -1) {
        novo = total + 1;
        if ((novo * x) % 100 == 0 && (novo * y) % 100 == 0 && (novo * z) % 100 == 0) {
            a = (novo * x) / 100;
            b = (novo * y) / 100;
            c = (novo * z) / 100;
            sobra = novo - (a + b + c);
            if (sobra >= 2) investiu = 1;
        }
    }

    if (investiu == -1) {
        novo = total + 2;
        if ((novo * x) % 100 == 0 && (novo * y) % 100 == 0 && (novo * z) % 100 == 0) {
            a = (novo * x) / 100;
            b = (novo * y) / 100;
            c = (novo * z) / 100;
            sobra = novo - (a + b + c);
            if (sobra >= 3) investiu = 2;
        }
    }

    if (investiu == -1) {
        novo = total + 3;
        if ((novo * x) % 100 == 0 && (novo * y) % 100 == 0 && (novo * z) % 100 == 0) {
            a = (novo * x) / 100;
            b = (novo * y) / 100;
            c = (novo * z) / 100;
            sobra = novo - (a + b + c);
            if (sobra >= 4) investiu = 3;
        }
    }

    if (investiu == -1) {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    } else {
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);

        int dinheiro_final = (3 - investiu) + sobra;

        if (investiu == 2) {
            char l1, l2, l3;
            scanf(" %c %c %c", &l1, &l2, &l3);
            int soma_letras = (l1 - 'a' + 1) + (l2 - 'a' + 1) + (l3 - 'a' + 1);
            printf("%d\n", soma_letras);
        }

        if (investiu == 3) {
            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);
            int parcelas = 0;
            if (i1 % 3 == 0 || i2 % 3 == 0 || i3 % 3 == 0) {
                if (i1 % 3 == 0) parcelas += (i1 / 3);
                if (i2 % 3 == 0) parcelas += (i2 / 3);
                if (i3 % 3 == 0) parcelas += (i3 / 3);
            }
            printf("%d\n", parcelas);
        }

        if (dinheiro_final >= 7) {
            printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
        } else {
            printf("E parece que Rebeka vai ter que voltar andando...\n");
        }
    }

    return 0;
}