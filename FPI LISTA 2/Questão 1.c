// Triangulo do Vinicius

#include <stdio.h> // biblioteca padrão da linguagem C.

int main(){  // função principal.
    // para guardar um caractere: char.
    // para guardar números inteiros: int.
    char c;
    // entradas 
    scanf("%c", &c);

    // cálculo usando ASCII
    // ASCII  é uma tabela que associa cada caractere a um número
    // ou seja dentro do computador: 'A'= 65; 'B'= 66; 'C'= 67; 'D'= 
    // em C, um char na verdade guarda um número da tabela ASCII, por isso dá para fazer contas com letras
    // EXEMPLO
    // linhas = 'D' - 'A' + 1
    // linhas = 68 - 65 + 1
    // linhas = 4
    // A - linha 1
    // B - linha 2
    // C - linha 3
    // D - linha 4
    int linhas = c - 'A' + 1;

    // laço das linha do triângulo
    for(int i = 0; i < linhas; i++){
        // pontos da esquerda
        for(int j = 0; j < linhas - i - 1; j++){
            printf(".");
        }
        // letras crescendo
        for(int j = 0; j <= i; j++){
            printf("%c", 'A' + j);
        }
        // letras decrescendo
        for(int j = i - 1; j >= 0; j--){
            printf("%c", 'A' + j);
        }
        // pontos da direita
        for(int j = 0; j < linhas - i - 1; j++){
            printf(".");
        }
        printf("\n");
    }
    return 0;
}