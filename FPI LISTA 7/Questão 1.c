// Lista 7 (Structs) - A coleção

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titulo[101];
    char genero[101];
    char estudio[101];
    char console[101];
    int nota;
    int ano;
} Jogo;

void avaliar(Jogo j) {
    if (j.nota > 7)
        printf("AWESOME! Mais um GOTY pra minha coleção!\n");
    else if (j.nota < 4)
        printf("Era melhor jogar mais um jogo de Mahjong.\n");
}

void printColecao(Jogo jogos[], int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%s %d\n", jogos[i].titulo, jogos[i].nota);
}

void printAno(Jogo jogos[], int n, int ano) {
    int i, cont = 0;

    for (i = 0; i < n; i++) {
        if (jogos[i].ano == ano) {
            printf("%s\n", jogos[i].titulo);
            cont++;
        }
    }

    if (cont == 0)
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    else
        printf("Tenho %d jogos || %d.\n", cont, ano);
}

void printLetra(Jogo jogos[], int n, char letra) {
    int i, cont = 0;

    for (i = 0; i < n; i++) {
        if (jogos[i].titulo[0] == letra) {
            printf("%s\n", jogos[i].titulo);
            cont++;
        }
    }

    if (cont == 0)
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    else
        printf("Tenho %d jogos || %c.\n", cont, letra);
}

void printStudio(Jogo jogos[], int n, char estudio[]) {
    int i, cont = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(jogos[i].estudio, estudio) == 0) {
            printf("%s\n", jogos[i].titulo);
            cont++;
        }
    }

    if (cont == 0)
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    else
        printf("Tenho %d jogos || %s.\n", cont, estudio);
}

void printConsole(Jogo jogos[], int n, char console[]) {
    int i, cont = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(jogos[i].console, console) == 0) {
            printf("%s\n", jogos[i].titulo);
            cont++;
        }
    }

    if (cont == 0)
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    else
        printf("Tenho %d jogos || %s.\n", cont, console);
}

int main(void) {
    Jogo jogos[100];
    int n, i;
    char funcao[30], parametro[101];

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%100s %100s %100s %100s %d %d",
              jogos[i].titulo,
              jogos[i].genero,
              jogos[i].estudio,
              jogos[i].console,
              &jogos[i].nota,
              &jogos[i].ano);

        avaliar(jogos[i]);
    }

    while (scanf("%29s", funcao) != EOF) {
        if (strcmp(funcao, "printColecao") == 0) {
            printColecao(jogos, n);
        } else {
            scanf("%100s", parametro);

            if (strcmp(funcao, "printAno") == 0)
                printAno(jogos, n, atoi(parametro));
            else if (strcmp(funcao, "printLetra") == 0)
                printLetra(jogos, n, parametro[0]);
            else if (strcmp(funcao, "printStudio") == 0)
                printStudio(jogos, n, parametro);
            else if (strcmp(funcao, "printConsole") == 0)
                printConsole(jogos, n, parametro);
        }
    }

    printf("Enjoei de jogar, agora vou ver TV.\n");

    return 0;
}
