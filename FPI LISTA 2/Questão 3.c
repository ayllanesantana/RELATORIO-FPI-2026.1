// Ingressos do Lulupalooza

#include <stdio.h>

int main(){

    int X, N;
    scanf("%d", &X);
    scanf("%d", &N);

    int melhor_canal = 0;
    int melhor_minuto = 0;
    int melhor_dist = 1000000000;
    int melhor_valor = 0;

    for(int c = 1; c <= N; c++){

        int a, b;
        scanf("%d %d", &a, &b);

        int f1 = a;
        int f2 = b;

        int minuto = 1;

        int melhor_local_valor = f1;
        int melhor_local_minuto = 1;

        int dist = f1 - X;
        if(dist < 0) dist = -dist;

        int dist2 = f2 - X;
        if(dist2 < 0) dist2 = -dist2;

        if(dist2 < dist || (dist2 == dist && f2 < f1)){
            melhor_local_valor = f2;
            melhor_local_minuto = 2;
            dist = dist2;
        }

        int anterior = f1;
        int atual = f2;
        minuto = 3;

        while(atual <= X + melhor_dist){

            int proximo = anterior + atual;

            int d = proximo - X;
            if(d < 0) d = -d;

            if(d < dist || (d == dist && proximo < melhor_local_valor)){
                dist = d;
                melhor_local_valor = proximo;
                melhor_local_minuto = minuto;
            }

            anterior = atual;
            atual = proximo;
            minuto++;
        }

        if(dist < melhor_dist || (dist == melhor_dist && c > melhor_canal)){
            melhor_dist = dist;
            melhor_canal = c;
            melhor_minuto = melhor_local_minuto;
            melhor_valor = melhor_local_valor;
        }
    }

    int soma = 0;
    int temp = melhor_valor;

    while(temp > 0){
        soma += temp % 10;
        temp /= 10;
    }

    if(soma > 10){
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", melhor_canal, melhor_minuto);
    }
    else{
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP n�o vai rolar :(\n", melhor_canal, melhor_minuto);
    }

}