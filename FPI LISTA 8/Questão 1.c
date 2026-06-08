// Questão 1 — Simulador de Registro de Sensor IoT (Tópico 1: Unions e Bitfields)

#include <stdio.h>

// union obrigatória: permite acessar o mesmo dado de duas formas
typedef union {
    unsigned char bytebruto; // byte completo recebido do sensor

    // struct com campos de bits dentro da union
    struct {
        unsigned char erro : 1;    // 1 bit para indicar erro
        unsigned char modo : 3;    // 3 bits para o modo de operação
        unsigned char leitura : 4; // 4 bits para a leitura do sensor
    } bits;
} sensor;

int main(void) {
    sensor s;
    int entrada;

    // lê o valor inteiro enviado pelo sensor
    scanf("%d", &entrada);

    // guarda o valor no byte bruto da union
    s.bytebruto = (unsigned char)entrada;

    // imprime o byte e os campos separados pelos bitfields
    printf("Byte bruto: %u | Erro: %u | Modo: %u | Leitura: %u\n",
           s.bytebruto,
           s.bits.erro,
           s.bits.modo,
           s.bits.leitura);

    return 0;
}