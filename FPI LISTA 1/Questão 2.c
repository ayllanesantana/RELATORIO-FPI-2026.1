// Xupenio Bordões

#include <stdio.h>

int main() {

    long long N, A, B;

    scanf("%lld", &N);
    scanf("%lld %lld", &A, &B);

    long long soma_total = N * (N + 1) / 2;

    long long kA = N / A;
    long long somaA = A * (kA * (kA + 1) / 2);

    long long kB = N / B;
    long long somaB = B * (kB * (kB + 1) / 2);

    long long AB = A * B;
    long long kAB = N / AB;
    long long somaAB = AB * (kAB * (kAB + 1) / 2);

    long long resultado = soma_total - somaA - somaB + somaAB;

    printf("%lld\n", resultado);

    if (resultado % 2 == 0)
        printf("L� ele!!!\n");
    else
        printf("Opa xupenio AULAS...\n");

    return 0;
}