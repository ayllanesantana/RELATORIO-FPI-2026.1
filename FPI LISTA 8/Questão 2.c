// Questão 2 — Processamento de Pacotes de Telemetria em Sistemas Embarcados (Tópico 1: Unions e Bitfields)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// union obrigatória: permite acessar o pacote inteiro ou os campos separados
typedef union
{
    uint32_t bruto; // pacote completo de 32 bits

    // bitfields na ordem do bit menos significativo para o mais significativo
    struct
    {
        unsigned int id : 10;        // 10 bits para o ID do sensor
        unsigned int status : 3;     // 3 bits para o status
        unsigned int bateria : 1;    // 1 bit para bateria baixa
        signed int temperatura : 12; // 12 bits com sinal
        unsigned int controle : 6;   // 6 bits para controle/paridade
    } bits;
} pacote;

int main(void)
{
    pacote *v = NULL; // vetor dinâmico
    pacote *novo;     // auxiliar para realloc
    uint32_t entrada; // valor hexadecimal lido
    int qtd = 0, capacidade = 0;
    int i;

    // lê até encontrar 0 ou 0x0
    while (scanf("%x", &entrada) == 1 && entrada != 0)
    {
        // dobra a capacidade quando o vetor fica cheio
        if (qtd == capacidade)
        {
            if (capacidade == 0)
                capacidade = 2;
            else
                capacidade = capacidade * 2;

            novo = realloc(v, capacidade * sizeof(pacote));

            if (novo == NULL)
            {
                free(v);
                return 1;
            }

            v = novo;
        }

        // guarda o dado bruto; os bitfields refletem os mesmos bits
        v[qtd].bruto = entrada;
        qtd++;
    }

    // imprime o relatório
    for (i = 0; i < qtd; i++)
    {
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, v[i].bruto);
        printf("ID do Sensor : %u\n", v[i].bits.id);
        printf("Status : %u\n", v[i].bits.status);

        if (v[i].bits.bateria)
            printf("Bateria Baixa: SIM (ALERTA)\n");
        else
            printf("Bateria Baixa: Nao\n");

        printf("Temperatura : %d graus\n", v[i].bits.temperatura);
        printf("--------------------------------------\n");
        printf("-----------\n");
    }

    free(v);

    return 0;
}