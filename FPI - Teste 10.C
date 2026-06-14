#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Número máximo de membros suportados pelo sistema
#define MAX_MEMBROS 100
// Tamanho máximo para strings de nome
#define MAX_NOME 50
// Tamanho máximo para uma linha lida de arquivo
#define MAX_LINHA 200

// Estrutura que representa um membro da academia
typedef struct {
    int codigo;          // Código numérico único do membro
    char nome[MAX_NOME]; // Nome do membro
    int creditos;        // Saldo atual de créditos
} Membro;

// Array global de membros e contador de quantos estão carregados
Membro membros[MAX_MEMBROS];
int total_membros = 0;

// Busca um membro pelo código. Retorna o índice no array ou -1 se não existe.
int buscar_membro(int codigo) {
    for (int i = 0; i < total_membros; i++) {
        if (membros[i].codigo == codigo)
            return i;
    }
    return -1;
}

// Carrega membros.txt para o array global.
// Formato de cada linha: codigo nome creditos
void carregar_membros() {
    FILE *f = fopen("membros.txt", "r");
    if (!f) {
        // Arquivo ainda não existe (primeira execução): começa vazio
        total_membros = 0;
        return;
    }
    total_membros = 0;
    // Lê cada linha até EOF ou limite do array
    while (total_membros < MAX_MEMBROS &&
           fscanf(f, "%d %s %d",
                  &membros[total_membros].codigo,
                  membros[total_membros].nome,
                  &membros[total_membros].creditos) == 3) {
        total_membros++;
    }
    fclose(f);
}

// Salva o estado atual de todos os membros em membros.txt (sobrescreve).
void salvar_membros() {
    FILE *f = fopen("membros.txt", "w");
    if (!f) {
        printf("Erro ao salvar membros.txt\n");
        return;
    }
    for (int i = 0; i < total_membros; i++) {
        fprintf(f, "%03d %s %d\n",
                membros[i].codigo,
                membros[i].nome,
                membros[i].creditos);
    }
    fclose(f);
}

// Processa o lote de operações do dia e gera os resultados.
//
// Parâmetros:
//   data_fmt  — string no formato "DD/MM/AAAA" (para cabeçalho do histórico)
//   arq_ops   — caminho para operacoes_DDMMAAAA.txt
//   arq_hist  — caminho para historico.txt (modo append)
//   arq_rel   — caminho para relatorio_DDMMAAAA.txt
void processar_operacoes(const char *data_fmt,
                          const char *arq_ops,
                          const char *arq_hist,
                          const char *arq_rel) {
    // Abre arquivo de operações do dia para leitura
    FILE *fops = fopen(arq_ops, "r");
    if (!fops) {
        printf("Arquivo %s nao encontrado.\n", arq_ops);
        return;
    }

    // Abre histórico em modo append (nunca sobrescreve)
    FILE *fhist = fopen(arq_hist, "a");
    if (!fhist) {
        printf("Erro ao abrir historico.txt\n");
        fclose(fops);
        return;
    }

    // Escreve cabeçalho do bloco do dia no histórico
    fprintf(fhist, "[%s]\n", data_fmt);

    // Contadores para o relatório
    int op_aplicadas   = 0;
    int cred_insuf     = 0;
    int membro_inex    = 0;

    // Buffer para armazenar as inconsistências (linhas recusadas)
    char inconsistencias[MAX_MEMBROS * MAX_LINHA];
    inconsistencias[0] = '\0';

    char linha[MAX_LINHA];

    // Lê cada linha do arquivo de operações
    while (fgets(linha, sizeof(linha), fops)) {
        // Remove newline do final da linha
        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) == 0) continue; // ignora linhas em branco

        char resultado[50]; // texto do resultado: APLICADA ou código de erro
        char tipo;
        int cod1, cod2, qtd;

        // Tenta ler como operação de Presente: cod_orig P cod_dest quantidade
        int lidos_p = sscanf(linha, "%d P %d %d", &cod1, &cod2, &qtd);

        if (lidos_p == 3) {
           
            // Operação PRESENTE (P): transfere créditos de cod1 para cod2

            int idx_orig = buscar_membro(cod1);
            int idx_dest = buscar_membro(cod2);

            if (idx_orig == -1) {
                // Origem não existe
                strcpy(resultado, "MEMBRO_INEXISTENTE");
                membro_inex++;
            } else if (idx_dest == -1) {
                // Destino não existe
                strcpy(resultado, "MEMBRO_DESTINO_INEXISTENTE");
                membro_inex++;
            } else if (membros[idx_orig].creditos < qtd) {
                // Origem sem créditos suficientes
                strcpy(resultado, "CREDITOS_INSUFICIENTES");
                cred_insuf++;
            } else {
                // Transferência bem-sucedida
                membros[idx_orig].creditos -= qtd;
                membros[idx_dest].creditos += qtd;
                strcpy(resultado, "APLICADA");
                op_aplicadas++;
            }

            // Registra no histórico
            fprintf(fhist, "%03d P %03d %d %s\n", cod1, cod2, qtd, resultado);

            // Se recusada, guarda para o relatório
            if (strcmp(resultado, "APLICADA") != 0) {
                char buf[MAX_LINHA];
                sprintf(buf, "%03d P %03d %d %s\n", cod1, cod2, qtd, resultado);
                strcat(inconsistencias, buf);
            }

        } else {
          
            // Operação de Recarga (R) ou Check-in (C): codigo TIPO quantidade

            if (sscanf(linha, "%d %c %d", &cod1, &tipo, &qtd) != 3) continue;

            int idx = buscar_membro(cod1);

            if (tipo == 'R') {
                // Recarga: adiciona créditos
                if (idx == -1) {
                    strcpy(resultado, "MEMBRO_INEXISTENTE");
                    membro_inex++;
                } else {
                    membros[idx].creditos += qtd;
                    strcpy(resultado, "APLICADA");
                    op_aplicadas++;
                }
            } else if (tipo == 'C') {
                // Check-in: consome créditos se saldo suficiente
                if (idx == -1) {
                    strcpy(resultado, "MEMBRO_INEXISTENTE");
                    membro_inex++;
                } else if (membros[idx].creditos < qtd) {
                    strcpy(resultado, "CREDITOS_INSUFICIENTES");
                    cred_insuf++;
                } else {
                    membros[idx].creditos -= qtd;
                    strcpy(resultado, "APLICADA");
                    op_aplicadas++;
                }
            } else {
                // Tipo desconhecido: ignora
                continue;
            }

            // Registra no histórico
            fprintf(fhist, "%03d %c %d %s\n", cod1, tipo, qtd, resultado);

            // Se recusada, guarda para o relatório
            if (strcmp(resultado, "APLICADA") != 0) {
                char buf[MAX_LINHA];
                sprintf(buf, "%03d %c %d %s\n", cod1, tipo, qtd, resultado);
                strcat(inconsistencias, buf);
            }
        }
    }

    // Fecha bloco do dia no histórico
    fprintf(fhist, "[/%s]\n", data_fmt);
    fclose(fhist);
    fclose(fops);

    // Gera o relatório diário

    FILE *frel = fopen(arq_rel, "w");
    if (!frel) {
        printf("Erro ao criar relatorio.\n");
        return;
    }

    fprintf(frel, "DATA: %s\n", data_fmt);
    fprintf(frel, "MEMBROS NO SISTEMA: %d\n", total_membros);
    fprintf(frel, "OPERACOES APLICADAS: %d\n", op_aplicadas);
    fprintf(frel, "CREDITOS INSUFICIENTES: %d\n", cred_insuf);
    fprintf(frel, "MEMBRO INEXISTENTE: %d\n", membro_inex);

    // Lista membros com saldo abaixo de 5
    fprintf(frel, "CREDITOS BAIXOS (< 5):\n");
    int algum_baixo = 0;
    for (int i = 0; i < total_membros; i++) {
        if (membros[i].creditos < 5) {
            fprintf(frel, "%03d %s %d\n",
                    membros[i].codigo,
                    membros[i].nome,
                    membros[i].creditos);
            algum_baixo = 1;
        }
    }
    if (!algum_baixo)
        fprintf(frel, "(nenhum)\n");

    // Lista inconsistências do dia
    fprintf(frel, "INCONSISTENCIAS:\n");
    if (strlen(inconsistencias) == 0)
        fprintf(frel, "(nenhuma)\n");
    else
        fprintf(frel, "%s", inconsistencias);

    fclose(frel);
}

// Gera o extrato de um membro varrendo todo o historico.txt.
// Cria o arquivo extrato_CCC.txt onde CCC é o código do membro.
void gerar_extrato(int codigo_membro) {
    // Busca o nome do membro nos dados em memória
    int idx = buscar_membro(codigo_membro);
    if (idx == -1) {
        printf("Membro %03d nao encontrado.\n", codigo_membro);
        return;
    }

    // Monta o nome do arquivo de saída
    char arq_extrato[50];
    sprintf(arq_extrato, "extrato_%03d.txt", codigo_membro);

    FILE *fext = fopen(arq_extrato, "w");
    if (!fext) {
        printf("Erro ao criar %s\n", arq_extrato);
        return;
    }

    // Cabeçalho do extrato
    fprintf(fext, "EXTRATO - MEMBRO %03d (%s)\n",
            codigo_membro, membros[idx].nome);
    fprintf(fext, "%-12s %-20s %-10s %s\n",
            "DATA", "TIPO", "CREDITOS", "STATUS");

    FILE *fhist = fopen("historico.txt", "r");
    if (!fhist) {
        // Histórico vazio: extrato sem movimentações
        fclose(fext);
        return;
    }

    char linha[MAX_LINHA];
    char data_bloco[15] = ""; // data atual dentro do bloco [DD/MM/AAAA]

    // Varre todo o histórico linha a linha
    while (fgets(linha, sizeof(linha), fhist)) {
        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) == 0) continue;

        // Detecta abertura de bloco de data: [DD/MM/AAAA]
        if (linha[0] == '[' && linha[1] != '/') {
            // Extrai a data sem os colchetes
            strncpy(data_bloco, linha + 1, strlen(linha) - 2);
            data_bloco[strlen(linha) - 2] = '\0';
            continue;
        }

        // Detecta fechamento de bloco: [/DD/MM/AAAA] — apenas reseta
        if (linha[0] == '[' && linha[1] == '/') {
            continue;
        }

        // Tenta interpretar como Presente: cod_orig P cod_dest quantidade status
        int cod_orig, cod_dest, qtd;
        char status[50];
        int lidos_p = sscanf(linha, "%d P %d %d %s",
                             &cod_orig, &cod_dest, &qtd, status);

        if (lidos_p == 4) {
            // O membro é origem (enviou presente)
            if (cod_orig == codigo_membro) {
                if (strcmp(status, "APLICADA") == 0)
                    fprintf(fext, "%-12s %-20s %-10d %s\n",
                            data_bloco, "PRES. ENVIADO", -qtd, status);
                else
                    fprintf(fext, "%-12s %-20s %-10s %s\n",
                            data_bloco, "PRES. ENVIADO", "-", status);
            }
            // O membro é destino (recebeu presente)
            if (cod_dest == codigo_membro) {
                if (strcmp(status, "APLICADA") == 0)
                    fprintf(fext, "%-12s %-20s %-10d %s\n",
                            data_bloco, "PRES. RECEBIDO", qtd, status);
                else
                    fprintf(fext, "%-12s %-20s %-10s %s\n",
                            data_bloco, "PRES. RECEBIDO", "-", status);
            }
        } else {
            // Tenta interpretar como R ou C: codigo TIPO quantidade status
            int cod;
            char tipo;
            if (sscanf(linha, "%d %c %d %s", &cod, &tipo, &qtd, status) != 4)
                continue;

            // Só processa se for o membro solicitado
            if (cod != codigo_membro) continue;

            if (tipo == 'C') {
                // Check-in: créditos negativos
                if (strcmp(status, "APLICADA") == 0)
                    fprintf(fext, "%-12s %-20s %-10d %s\n",
                            data_bloco, "CHECK-IN", -qtd, status);
                else
                    fprintf(fext, "%-12s %-20s %-10s %s\n",
                            data_bloco, "CHECK-IN", "-", status);
            } else if (tipo == 'R') {
                // Recarga: créditos positivos
                if (strcmp(status, "APLICADA") == 0)
                    fprintf(fext, "%-12s %-20s %-10d %s\n",
                            data_bloco, "RECARGA", qtd, status);
                else
                    fprintf(fext, "%-12s %-20s %-10s %s\n",
                            data_bloco, "RECARGA", "-", status);
            }
        }
    }

    fclose(fhist);

    // Saldo atual do membro (estado em memória após o processamento do dia)
    fprintf(fext, "SALDO ATUAL: %d\n", membros[idx].creditos);
    fclose(fext);

    printf("Extrato gerado: %s\n", arq_extrato);
}

// Função principal: orquestra o fluxo completo de uma execução diária.
int main() {
    char data[9]; // Formato DDMMAAAA (8 chars + '\0')

    // Etapa 1: lê a data do dia informada pelo usuário
    printf("Informe a data (DDMMAAAA): ");
    scanf("%8s", data);

    // Monta a data formatada para exibição (DD/MM/AAAA)
    char data_fmt[11];
    sprintf(data_fmt, "%c%c/%c%c/%c%c%c%c",
            data[0], data[1], data[2], data[3],
            data[4], data[5], data[6], data[7]);

    // Etapa 2: carrega o estado atual dos membros
    carregar_membros();

    // Monta os nomes dos arquivos diários usando a data informada
    char arq_ops[50], arq_rel[50];
    sprintf(arq_ops, "operacoes_%s.txt", data);   // ex: operacoes_15112025.txt
    sprintf(arq_rel, "relatorio_%s.txt", data);   // ex: relatorio_15112025.txt

    // Etapa 3: processa operações, Etapa 5: salva histórico, Etapa 6: relatório
    processar_operacoes(data_fmt, arq_ops, "historico.txt", arq_rel);

    // Etapa 4: salva o novo estado dos membros (sobrescreve membros.txt)
    salvar_membros();

    printf("Processamento concluido. Relatorio: %s\n", arq_rel);

    // Etapa 7: loop de extrato — permite consultar múltiplos membros
    char resp;
    // Consome o '\n' que ficou no buffer após o scanf da data
    getchar();

    while (1) {
        printf("Solicitar extrato? (S/N): ");
        scanf(" %c", &resp);
        if (resp == 'N' || resp == 'n') break;

        int cod_ext;
        printf("Codigo do membro: ");
        scanf("%d", &cod_ext);
        gerar_extrato(cod_ext);
    }

    return 0;
}