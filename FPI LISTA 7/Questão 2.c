// Lista 7 (Structs) - Espionagem na COPA

#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[201];
    char funcao[201];
    int populacao;
    int perigo;
} Cidadela;

int letra(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int maiuscula(char c) {
    return c >= 'A' && c <= 'Z';
}

char para_minuscula(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

char para_maiuscula(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    return c;
}

// deixa primeira letra maiuscula e o resto minusculo 
void ajustar(char s[]) {
    int i;

    for (i = 0; s[i] != '\0'; i++) s[i] = para_minuscula(s[i]);
    if (s[0] != '\0') s[0] = para_maiuscula(s[0]);
}

// verifica se a linha e a mensagem especial 
int tem_exclamacao(char linha[]) {
    int i;

    for (i = 0; linha[i] != '\0'; i++)
        if (linha[i] == '!') return 1;

    return 0;
}

// junta todos os digitos da frase em um numero 
int pegar_numero(char linha[]) {
    int i, num = 0;

    for (i = 0; linha[i] != '\0'; i++)
        if (linha[i] >= '0' && linha[i] <= '9')
            num = num * 10 + (linha[i] - '0');

    return num;
}

// conta os asteriscos da periculosidade 
int contar_perigo(char linha[]) {
    int i, cont = 0;

    for (i = 0; linha[i] != '\0'; i++)
        if (linha[i] == '*') cont++;

    return cont;
}

// letras maiusculas formam o nome da cidadela 
void pegar_nome(char linha[], char nome[]) {
    int i, j = 0;

    for (i = 0; linha[i] != '\0'; i++)
        if (maiuscula(linha[i])) nome[j++] = linha[i];

    nome[j] = '\0';
    ajustar(nome);
}

// depois de espaço duplo, pega a proxima letra para formar a função 
void pegar_funcao(char linha[], char funcao[]) {
    int i, j = 0, k;

    for (i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == ' ' && linha[i + 1] == ' ') {
            k = i + 2;

            while (linha[k] == ' ') k++;
            while (linha[k] != '\0' && !letra(linha[k])) k++;

            if (letra(linha[k])) funcao[j++] = linha[k];

            while (linha[i + 1] == ' ') i++;
        }
    }

    funcao[j] = '\0';
    ajustar(funcao);
}

// regra de ordenaçao das cidadelas
int vem_antes(Cidadela a, Cidadela b) {
    if (a.populacao != b.populacao) return a.populacao > b.populacao;
    if (a.perigo != b.perigo) return a.perigo > b.perigo;
    return strcmp(a.nome, b.nome) < 0;
}

int main(void) {
    Cidadela c[1000], aux;
    char linha[205];
    int qtd = 0, chave = -1;
    int i, j;

    while (fgets(linha, 205, stdin) != NULL) {
        if (tem_exclamacao(linha)) {
            chave = pegar_numero(linha);
        } else {
            pegar_nome(linha, c[qtd].nome);
            pegar_funcao(linha, c[qtd].funcao);
            c[qtd].populacao = pegar_numero(linha);
            c[qtd].perigo = contar_perigo(linha);
            qtd++;
        }
    }

    if (chave == -1) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        return 0;
    }

    // bubble sort
    for (i = 0; i < qtd - 1; i++) {
        for (j = 0; j < qtd - 1 - i; j++) {
            if (!vem_antes(c[j], c[j + 1])) {
                aux = c[j];
                c[j] = c[j + 1];
                c[j + 1] = aux;
            }
        }
    }

    chave--; // chave começa em 1, vetor começa em 0 

    printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ",
           c[chave].nome, c[chave].populacao, c[chave].funcao);

    for (i = 0; i < c[chave].perigo; i++) printf("*");
    printf(".");

    if (c[chave].populacao >= 1000 && c[chave].perigo > 3)
        printf(" Talvez seja melhor desistir...");
    else if (c[chave].populacao >= 1000)
        printf(" Um lugar denso, vai ser difícil achar ela.");
    else if (c[chave].perigo > 3)
        printf(" Vai ser complicado entrar lá.");

    printf("\n");

    return 0;
}