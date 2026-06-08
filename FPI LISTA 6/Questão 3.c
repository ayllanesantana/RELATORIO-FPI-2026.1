// Lista 6 (Matrizes Dinâmicas e Ponteiros para Funções) - Torneio pokemon

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tipos
typedef enum{
FOGO,AGUA,ELETRICIDADE,PLANTA
}Tipo;

// pokemon
typedef struct{
int id;
char nome[101];
Tipo tipo;
int xp;
int atk;
int ord; // ordem cadastro
}Pokemon;

// treinador
typedef struct{
char nome[101];
int cpf;
int idade;
Pokemon *p; // vetor dinamico
int qnt,cap,niv,ord;
}Treinador;

// sistema
typedef struct{
Treinador *t;
int qnt,cap;
int prox_t,prox_p;
}Sistema;

// struct funções
typedef struct{
void (*cad_t)(Sistema *);
void (*cad_p)(Sistema *);
void (*listar)(Sistema *);
void (*rem_t)(Sistema *);
void (*att_p)(Sistema *);
void (*liberar)(Sistema *);
}Funcoes;


// força pokemon
int forca(Pokemon p){
return 2*p.xp+p.atk;
}

// recalcula nivel
void calc_niv(Treinador *t){
int i;
t->niv=0;
for(i=0;i<t->qnt;i++){
t->niv+=forca(t->p[i]);
}
}

// nome do tipo
char *nome_tipo(Tipo t){
if(t==FOGO) return "Fogo";
if(t==AGUA) return "Agua";
if(t==ELETRICIDADE) return "Eletricidade";
return "Planta";
}

// busca treinador
int buscar_t(Sistema *s,int cpf){
int i;
for(i=0;i<s->qnt;i++){
if(s->t[i].cpf==cpf){
return i;
}
}
return -1;
}

// busca pokemon
int buscar_p(Treinador *t,int id){
int i;
for(i=0;i<t->qnt;i++){
if(t->p[i].id==id){
return i;
}
}
return -1;
}

// aumenta treinadores
void garantir_t(Sistema *s){
Treinador *novo;
int nc;
if(s->qnt<s->cap) return;
if(s->cap==0) nc=2;
else nc=s->cap*2;

novo=(Treinador*)
realloc(
s->t,
nc*sizeof(Treinador)
);

if(novo==NULL){
exit(0);
}

s->t=novo;
s->cap=nc;
}

// aumenta pokemons
void garantir_p(Treinador *t){
Pokemon *novo;
int nc;

if(t->qnt<t->cap) return;

if(t->cap==0) nc=2;
else nc=t->cap*2;

novo=(Pokemon*)
realloc(
t->p,
nc*sizeof(Pokemon)
);

if(novo==NULL){
exit(0);
}

t->p=novo;
t->cap=nc;
}


// cadastra treinador
void cad_treinador(Sistema *s){Treinador *t;char nome[101];
int cpf,idade;

scanf("%s %d %d",nome,&cpf,&idade);

// ignora cpf repetido
if(buscar_t(s,cpf)!=-1){
return;
}

garantir_t(s);

t=&s->t[s->qnt];

strcpy(t->nome,nome);

t->cpf=cpf;
t->idade=idade;

t->p=NULL;
t->qnt=0;
t->cap=0;
t->niv=0;

t->ord=s->prox_t;

s->prox_t++;
s->qnt++;
}


// cadastra pokemon
void cad_pokemon(Sistema *s){
int cpf,id,xp,atk,tipo,i;
char nome[101];
Treinador *t;

scanf("%d %d %s %d %d %d",&cpf,&id,nome,&xp,&atk,&tipo);

i=buscar_t(s,cpf);

if(i==-1) return;

t=&s->t[i];

// ignora id repetido
if(buscar_p(t,id)!=-1){
return;
}

garantir_p(t);

t->p[t->qnt].id=id;
strcpy(
t->p[t->qnt].nome,
nome
);

t->p[t->qnt].xp=xp;
t->p[t->qnt].atk=atk;
t->p[t->qnt].tipo=(Tipo)tipo;
t->p[t->qnt].ord=t->qnt;
t->qnt++;

calc_niv(t);
}

// ordena treinadores
int cmp_t(const void *a,const void *b){
Treinador *x=(Treinador*)a;
Treinador *y=(Treinador*)b;

if(x->niv!=y->niv){
return y->niv-x->niv;
}

return x->ord-y->ord;
}

// ordena pokemons
int cmp_p(
const void *a,
const void *b
){
Pokemon *x=(Pokemon*)a;
Pokemon *y=(Pokemon*)b;

int fx=forca(*x);
int fy=forca(*y);

if(fx!=fy){
return fy-fx;
}

return x->ord-y->ord;
}


// ranking
void listar_classificacao(Sistema *s){
Treinador *vt;
int i;

printf("Classificação atual\n");

if(s->qnt==0) return;

vt=(Treinador*)
malloc(
s->qnt*
sizeof(Treinador)
);

for(i=0;i<s->qnt;i++){
vt[i]=s->t[i];
}

qsort(
vt,
s->qnt,
sizeof(Treinador),
cmp_t
);

for(i=0;i<s->qnt;i++){

Pokemon *vp;
int j;

printf("T: %s, CPF: %d, Nivel: %d\n",vt[i].nome,vt[i].cpf,vt[i].niv);

if(vt[i].qnt>0){

vp=(Pokemon*)
malloc(
vt[i].qnt*
sizeof(Pokemon)
);

for(j=0;j<vt[i].qnt;j++){
vp[j]=vt[i].p[j];
}

qsort(
vp,
vt[i].qnt,
sizeof(Pokemon),
cmp_p
);

for(j=0;j<vt[i].qnt;j++){

printf("  P: %d, %s, %d, %d, %s\n",vp[j].id,vp[j].nome,vp[j].xp,vp[j].atk,nome_tipo(vp[j].tipo));

}

free(vp);
}
}

free(vt);
}

// remove treinador
void remover_treinador(Sistema *s){
int cpf,i;

scanf("%d",&cpf);

i=buscar_t(s,cpf);

if(i==-1) return;

free(s->t[i].p);

for(;i<s->qnt-1;i++){
s->t[i]=s->t[i+1];
}

s->qnt--;
}

// atualiza pokemon
void atualizar_pokemon(Sistema *s){
int cpf,id,xp,atk,tipo;
int i,j;
char nome[101];

scanf("%d %d %s %d %d %d",&cpf,&id,nome,&xp,&atk,&tipo);

i=buscar_t(s,cpf);
if(i==-1) return;

j=buscar_p(
&s->t[i],
id
);

if(j==-1) return;

strcpy(
s->t[i].p[j].nome,
nome
);

s->t[i].p[j].xp=xp;
s->t[i].p[j].atk=atk;
s->t[i].p[j].tipo=(Tipo)tipo;

calc_niv(
&s->t[i]
);
}


// libera memoria
void liberar_sistema(
Sistema *s
){
int i;

for(i=0;i<s->qnt;i++){
free(s->t[i].p);
}

free(s->t);
}

int main(void){
Sistema s;
Funcoes f;
int cmd;

s.t=NULL;
s.qnt=0;
s.cap=0;
s.prox_t=0;
s.prox_p=0;


// liga funções
f.cad_t=cad_treinador;
f.cad_p=cad_pokemon;
f.listar=listar_classificacao;
f.rem_t=remover_treinador;
f.att_p=atualizar_pokemon;
f.liberar=liberar_sistema;

scanf("%d",&cmd);

while(cmd!=0){

if(cmd==1){
f.cad_t(&s);
}
else if(cmd==2){
f.cad_p(&s);
}
else if(cmd==3){
f.listar(&s);
}
else if(cmd==4){
f.rem_t(&s);
}
else if(cmd==5){
f.att_p(&s);
}

scanf("%d",&cmd);
}

f.liberar(&s);

return 0;
}