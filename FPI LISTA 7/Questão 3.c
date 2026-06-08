// Lista 7 (Structs) - Operação: Lança de Netuno

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[];
};

void defesa(Mecha *m, int s, int in, int *out) {
    *out = in - m->sistemas[s].atrib1 - s * m->sistemas[s].atrib2;
    if (*out < 0) *out = 0;
}

void utilidade(Mecha *m, int s, int in, int *out) {
    (void)in;
    m->energia_atual += m->sistemas[s].atrib1 + s * m->sistemas[s].atrib2;
    *out = m->energia_atual;
}

void ataque(Mecha *m, int s, int in, int *out) {
    if (m->energia_atual < m->sistemas[s].atrib2) {
        *out = 0;
    } else {
        *out = m->sistemas[s].atrib1 + m->energia_atual + s - in;
        m->energia_atual -= m->sistemas[s].atrib2;
    }
}

int main(void) {
    int n, i, j, id, energia, q, out, falhou;
    char tipo, modelo[50];
    Mecha **v, *m;

    scanf("%d", &n);
    v = malloc(n * sizeof(Mecha *));

    for (i = 0; i < n; i++) {
        scanf("%d %49s %d %d", &id, modelo, &energia, &q);

        m = malloc(sizeof(Mecha) + q * sizeof(SubSistema));

        m->id = id;
        strcpy(m->modelo, modelo);
        m->energia_atual = energia;
        m->num_sistemas = q;

        for (j = 0; j < q; j++) {
            scanf(" %c %29s %d %d", &tipo, m->sistemas[j].nome,
                  &m->sistemas[j].atrib1, &m->sistemas[j].atrib2);

            if (tipo == 'D') {
                m->sistemas[j].subrotina = defesa;
            } else if (tipo == 'U') {
                m->sistemas[j].subrotina = utilidade;
            } else {
                m->sistemas[j].subrotina = ataque;
            }
        }

        scanf("%d", &m->valor_wintermute);
        v[id] = m;
    }

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (i = 0; i < n; i++) {
        m = v[i];

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n",
               m->id, m->modelo, m->energia_atual);

        for (j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == defesa) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &out);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n",
                       m->sistemas[j].nome, out);
            }
        }

        for (j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == utilidade) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &out);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n",
                       m->sistemas[j].nome, out);
            }
        }

        for (j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == ataque) {
                falhou = m->energia_atual < m->sistemas[j].atrib2;

                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &out);

                if (falhou) {
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n",
                           m->sistemas[j].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n",
                           m->sistemas[j].nome, out, m->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    for (i = 0; i < n; i++) {
        free(v[i]);
    }

    free(v);

    return 0;
}
