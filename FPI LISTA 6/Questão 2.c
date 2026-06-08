// Lista 6 (Matrizes Dinâmicas e Ponteiros para Funções) - Sistema de Combate em MMORPG: Simulando AoE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// aloca matriz dinâmica
int **alocar_matriz(int l, int c) {
    int **m;
    int i;
    // vetor de linhas
    m = (int **)malloc(l * sizeof(int *));
    // erro de alocação
    if (m == NULL) {
        return NULL;
    }
    // aloca cada linha
    for (i = 0; i < l; i++) {
        m[i] = (int *)malloc(c * sizeof(int));
        // se falhar libera tudo
        if (m[i] == NULL) {
            int j;
            for (j = 0; j < i; j++) {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }
    return m;
}

// libera matriz
void liberar_matriz(int **m, int l) {
    int i;
    for (i = 0; i < l; i++) {
        free(m[i]);
    }
    free(m);
}


// lê hp do mapa
void ler_matriz(int **m, int l, int c) {
    int i,j;
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            scanf("%d",&m[i][j]);

        }
    }
}

// imprime matriz
void imprimir_matriz(int **m,int l,int c){
    int i,j;
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            // evita espaço no começo
            if(j>0){
                printf(" ");
            }
            printf("%d",m[i][j]);
        }
        printf("\n");
    }
}

// cria cópia da matriz
int **copiar_matriz(int **m,int l,int c){
    int **n;
    int i,j;
    n = alocar_matriz(l,c);
    if(n==NULL){
        return NULL;
    }
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            n[i][j]=m[i][j];
        }
    }
    return n;
}

// verifica limites
int dentro(int x,int y,int l,int c){
    if(x>=0 && x<l && y>=0 && y<c){
        return 1;
    }
    return 0;
}

// marca camada 1 e camada 2
void marcar_area(int **a,int l,int c,int x,int y){
    int dx[5]={0,-1,1,0,0};
    int dy[5]={0,0,0,-1,1};
    int i,j,k;

    // camada 1
    for(i=0;i<5;i++){
        int nx=x+dx[i];
        int ny=y+dy[i];
        if(dentro(nx,ny,l,c)){
            a[nx][ny]=1;
        }
    }

    // camada 2
    for(i=0;i<5;i++){
        int bx=x+dx[i];
        int by=y+dy[i];
        if(dentro(bx,by,l,c)){
            for(j=-1;j<=1;j++){
                for(k=-1;k<=1;k++){
                    int nx=bx+j;
                    int ny=by+k;
                    if(
                        dentro(nx,ny,l,c)
                        &&
                        a[nx][ny]==0
                    ){
                        a[nx][ny]=2;
                    }
                }
            }
        }
    }
}

// conta vizinhos vivos
int vivos_vizinhos(
    int **m,
    int l,
    int c,
    int x,
    int y
){
    int i,j;
    int cont=0;
    for(i=-1;i<=1;i++){
        for(j=-1;j<=1;j++){
            int nx=x+i;
            int ny=y+j;
            if(
                !(i==0 && j==0)
                &&
                dentro(nx,ny,l,c)
                &&
                m[nx][ny]>0
            ){
                cont++;
            }
        }
    }
    return cont;
}

// verifica se tudo morreu
int todos_zerados(
    int **m,
    int **a,
    int l,
    int c
){

    int i,j;
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            if(
                a[i][j]>0
                &&
                m[i][j]>0
            ){
                return 0;
            }
        }
    }

    return 1;
}

// ataque explosão arcana
int **explosao_arcana(
    int **m,
    int **a,
    int l,
    int c
){
    int **n;
    int i,j;
    n=copiar_matriz(m,l,c);

    if(n==NULL){
        return NULL;
    }
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            if(a[i][j]==1){
                n[i][j]=m[i][j]-50;

            }
            else if(a[i][j]==2){
                n[i][j]=m[i][j]-25;
            }
            if(n[i][j]<0){
                n[i][j]=0;
            }
        }
    }

    return n;
}

// ataque nuvem venenosa
int **nuvem_venenosa(
    int **m,
    int **a,
    int l,
    int c
){
    int **n;
    int i,j;
    n=copiar_matriz(m,l,c);
    if(n==NULL){
        return NULL;
    }
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            if(a[i][j]>0){
                int d;
                d=5+8*vivos_vizinhos(
                    m,l,c,i,j
                );
                n[i][j]=m[i][j]-d;
                if(n[i][j]<0){
                    n[i][j]=0;
                }
            }
        }
    }

    return n;
}

int main(void){
    int l,c;
    int x,y;
    int **m;
    int **a;
    char t[30];
    // ponteiro do ataque
    int **(*atk)(
        int **,
        int **,
        int,
        int
    );

    scanf("%d %d",&l,&c);
    m=alocar_matriz(l,c);

    if(m==NULL){
        return 0;
    }

    ler_matriz(m,l,c);
    scanf("%d %d",&x,&y);
    scanf("%s",t);
    a=alocar_matriz(l,c);

    if(a==NULL){
        liberar_matriz(m,l);
        return 0;

    }

    {
        int i,j;
        // zera mapa de áreas
        for(i=0;i<l;i++){
            for(j=0;j<c;j++){
                a[i][j]=0;

            }
        }
    }


    // marca região do ataque
    marcar_area(a,l,c,x,y);
    printf("Estado inicial do mapa:\n");
    imprimir_matriz(m,l,c);
    printf("\n");

    if(
      strcmp(
        t,
        "EXPLOSAO_ARCANA"
      )==0
    ){
        int **r;
        // escolhe ataque
        atk=explosao_arcana;
        r=atk(m,a,l,c);
        if(r==NULL){
            liberar_matriz(a,l);
            liberar_matriz(m,l);
            return 0;
        }

        printf(
         "Estado do mapa após usar a Explosão Arcana:\n"
        );
        imprimir_matriz(r,l,c);
        liberar_matriz(r,l);
    }

    else{
        int i;
        // escolhe veneno
        atk=nuvem_venenosa;
        printf(
        "Estado do mapa, por turno, após usar a Nuvem Venenosa:\n"
        );
        for(i=0;i<3;i++){
            int **r;
            r=atk(m,a,l,c);
            if(r==NULL){
                liberar_matriz(a,l);
                liberar_matriz(m,l);
                return 0;
            }

            imprimir_matriz(r,l,c);
            if(
                i<2
                &&
                !todos_zerados(
                    r,a,l,c
                )
            ){
                printf("\n");
            }
            liberar_matriz(m,l);
            m=r;
            if(
               todos_zerados(
                 m,a,l,c
               )
            ){
                break;
            }
        }
    }
    liberar_matriz(a,l);
    liberar_matriz(m,l);
    return 0;
}