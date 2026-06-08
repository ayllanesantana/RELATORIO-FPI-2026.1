// Ajude a dudinha!

#include <stdio.h>

int main(){

    int N, K, P;
    scanf("%d %d %d", &N, &K, &P);

    int primeiro = -1;
    int Q = 0;

    for(int num = N; num < K; num++){

        int n = num;
        int fatores = 0;
        int valido = 1;

        for(int d = 2; d <= n; d++){

            int cont = 0;

            while(n % d == 0){
                n = n / d;
                cont++;
            }

            if(cont > 0){

                if(d % 2 == 1){

                    if(cont > 1){
                        valido = 0;
                    }

                    fatores++;
                }
            }
        }

        if(valido && fatores == P){

            if(primeiro == -1){
                primeiro = num;
            }
            else{
                Q++;
            }
        }
    }

    if(primeiro == -1){
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }
    else{
        printf("%d %d\n", primeiro, Q);
    }

}