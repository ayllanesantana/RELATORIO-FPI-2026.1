// Numerologia de Monalisa 

#include <stdio.h> // entrada e saída padrão
#include <assert.h> // usada para testar se algo no programa está correto. (Ela é muito usada para testes unitários(verificar se partes do código funcionam corretamente))

// RESUMO RÁPIDO:
// stdio.h ? ler datas e mostrar previsões
//assert.h ? permitir testes para validar cálculos

// Todo programa em C começa pela função main()
int main() {

    // Variáveis inteiras (int) para armazenar as datas.
    // Data de Nascimento: d1 (dia), m1 (mês), a1 (ano).
    // Data Atual: d2 (dia), m2 (mês), a2 (ano).
    int d1, m1, a1;
    int d2, m2, a2;

    // scanf lá os dados digitados pelo usuário
    // o formato: %d/%d/%d %d/%d/%d; significa: numero/numero/numero numero/numero/numero; Ou seja: DD/MM/AAAA DD/MM/AAAA
    scanf("%d/%d/%d %d/%d/%d", &d1, &m1, &a1, &d2, &m2, &a2);

    // AMOR

    // somamos todos os números das duas datas.
    int soma = d1 + m1 + a1 + d2 + m2 + a2;
    // O que acontece aqui:
    // 1?? multiplica por 7
    // 2?? divide por 101
    // 3?? pega o resto da divisão
    // O operador % significa módulo (resto da divisão).
    int amor = (soma * 7) % 101;

    // %d ? mostra um número inteiro.
    // %% ? imprime o símbolo %.
    printf("Amor: %d%% ", amor);

    if (amor < 20) {
        printf("Pessimo dia para se apaixonar.\n");
    }
    else if (amor <= 40) {
        printf("Melhor manter o coracao <3 longe de perigo.\n");
    }
    else if (amor <= 69) {
        printf("Se o papo e as ideias baterem, esta liberado pensar em algo.\n");
    }
    else if (amor <= 80) {
        printf("Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n");
    }
    else {
        printf("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n");
    }

    // SORTE

    // somamos os dias
    int dias = d1 + d2;
    // somamos os meses
    int meses = m1 + m2;

    // calculamos a diferença entre os anos
    int diff = a2 - a1;
    // mas o problema pede diferença positiva
    if (diff < 0) {
        // isso transforma o número em positivo
        diff = diff * -1;
    }

    // cálculo final:
    // 1?? soma dias e meses
    // 2?? multiplica por 9
    // 3?? soma a diferença dos anos
    // 4?? pega resto da divisão por 101
    int sorte = ((dias + meses) * 9 + diff) % 101;

    printf("Sorte: %d%% ", sorte);

    if (sorte < 30) {
        printf("Nem jogue moedas pra cima hoje.");
    }
    else if (sorte <= 50) {
        printf("Melhor nao arriscar.");
    }
    else if (sorte <= 79) {
        printf("Por sua conta em risco.");
    }
    else if (sorte <= 90) {
        printf("Hoje vale a pena arriscar.");
    }
    else {
        printf("Nao tenha medo de virar cartas hoje.");
    }

    printf(" Sem tigrinho nem jogos de azar, por favor!\n");

    // TRABALHO
  
    // cálculo do trabalho
    int anos = a1 + a2;
    // dias + meses, multiplicado por 8
    int dm = (d1 + d2 + m1 + m2) * 8;

    // subtrai e pega o resto da divisão.
    int trabalho = (anos - dm) % 101;

    // o operador % pode gerar um número negativo.
    // por isso corrigimos ( dessa forma garantimos que o valor fique entre: 0 e 100):
    if (trabalho < 0) {
        trabalho = trabalho + 101;
    }

    printf("Trabalho: %d%% ", trabalho);

    if (trabalho < 40) {
        printf("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n");
    }
    else if (trabalho <= 50) {
        printf("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n");
    }
    else if (trabalho <= 69) {
        printf("Um dia proveitoso com certeza, leve sua simpatia consigo.\n");
    }
    else if (trabalho <= 84) {
        printf("Boas vibracoes hoje, chances podem estar ao seu redor.\n");
    }
    else {
        printf("Use do maximo de networking poss�vel hoje, dia bom para negocios.\n");
    }

    // COR

    // aqui usamos o quadrado do número, depois dividimos por 11 e pegamos o resto.
    // esse resto sempre será: 0 até 10
    int cor = (d1*d1 + d2*d2 + m1*m1 + m2*m2 + a1*a1 + a2*a2) % 11;

    printf("Cor: ");

    if (cor == 0) {
        printf("Cinza.\n");
    }
    else if (cor == 1) {
        printf("Vermelho.\n");
    }
    else if (cor == 2) {
        printf("Laranja.\n");
    }
    else if (cor == 3) {
        printf("Amarelo.\n");
    }
    else if (cor == 4) {
        printf("Verde.\n");
    }
    else if (cor == 5) {
        printf("Azul.\n");
    }
    else if (cor == 6) {
        printf("Roxo.\n");
    }
    else if (cor == 7) {
        printf("Marrom.\n");
    }
    else if (cor == 8) {
        printf("Rosa.\n");
    }
    else if (cor == 9) {
        printf("Preto.\n");
    }
    else {
        printf("Branco.\n");
    }

    return 0;
}