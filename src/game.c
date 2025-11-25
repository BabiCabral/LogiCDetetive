#include "../include/game.h"
#include "../include/cli_lib.h"
#include "../include/save.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

static int historiaAtual = 1; // por enquanto só existe história 1

static void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* -------------------  FUNÇÃO PARA PISTAS RANDOMIZADAS  ------------------- */

static void pista_random(const char *pistas[], int quantidade) {
    int r = rand() % quantidade;
    printf("Pista encontrada: %s\n", pistas[r]);
}

/* -------------------  MENU DA HISTÓRIA 1  ------------------- */

static void menuHistoria1() {
    printf("\n========= LOCAIS =========\n");
    printf("1. Prefeitura\n");
    printf("2. Casa do Prefeito\n");
    printf("3. Banco\n");
    printf("4. Floricultura\n");
    printf("5. Bar\n");
    printf("6. Estação de Trem\n");
    printf("7. Biblioteca\n");
    printf("8. Teatro\n");
    printf("S. Ver solução\n");
    printf("X. Sair\n");
}

/* -------------------  PISTAS DA HISTÓRIA 1  ------------------- */

static void salaHistoria1(int opcao) {

    /* PREFEITURA */
    const char *prefeitura[] = {
        "As flores na sala de João ou são compradas por Madalena, ou por Lúcia.",
        "João só vai ao bar após o trabalho quando tem reunião com Paulinho ou Lúcia à tarde.",
        "As reuniões só acontecem durante horário de trabalho.",
        "As flores da sala de João são azuis."
    };

    /* CASA DO PREFEITO */
    const char *casaPrefeito[] = {
        "Se as flores da sala de João são azuis, elas não foram compradas por Madalena.",
        "Se João não tem reunião à tarde, ele vai com Madalena ao teatro após o trabalho.",
        "Olívia e Madalena foram à estação de trem na sexta-feira."
    };

    /* BANCO */
    const char *banco[] = {
        "Às sextas-feiras, Paulinho só trabalha pela manhã.",
        "Se o cofre foi aberto, Paulinho ou Zé Caduco estavam no banco.",
        "Se o castiçal do banco foi emprestado a alguém, o cofre foi aberto."
    };

    /* FLORICULTURA */
    const char *floricultura[] = {
        "Apenas pessoas da prefeitura podem comprar substâncias venenosas na floricultura.",
        "Se alguém da prefeitura comprou flores na sexta-feira, também comprou substância venenosa.",
        "As flores da sala de João são sempre frescas."
    };

    /* BAR */
    const char *bar[] = {
        "João esteve no bar às 20h.",
        "João nunca vai ao bar sozinho.",
        "Uma pessoa foi vista com uma mala saindo do bar."
    };

    /* ESTAÇÃO DE TREM */
    const char *estacao[] = {
        "Se Jonas não estava distribuindo panfletos na estação, ele estava no evento da biblioteca.",
        "Se alguém da família Pífio esteve na estação de trem, Jonas não distribuiu panfletos por lá.",
        "Se a arma for o cano, o crime ocorreu na estação de trem."
    };

    /* BIBLIOTECA */
    const char *biblioteca[] = {
        "O castiçal do banco foi emprestado à biblioteca na sexta-feira para um evento.",
        "Todos que participaram do evento ficaram na biblioteca até 22h.",
        "Se o corpo possui hematoma na cabeça, a arma foi o castiçal ou o cano."
    };

    /* TEATRO */
    const char *teatro[] = {
        "João e Madalena não foram ao teatro na sexta-feira.",
        "Se João saiu na sexta-feira à noite, estava acompanhado da pessoa com quem se reuniu à tarde.",
        "O corpo não possui qualquer hematoma na cabeça."
    };

    printf("\n>>> Investigando...\n");

    switch (opcao) {
        case 1: pista_random(prefeitura, 4); break;
        case 2: pista_random(casaPrefeito, 3); break;
        case 3: pista_random(banco, 3); break;
        case 4: pista_random(floricultura, 3); break;
        case 5: pista_random(bar, 3); break;
        case 6: pista_random(estacao, 3); break;
        case 7: pista_random(biblioteca, 3); break;
        case 8: pista_random(teatro, 3); break;
        default: printf("Local inválido.\n");
    }
}

/* -------------------  TELA INICIAL DA HISTÓRIA  ------------------- */

static void escolherHistoria(void) {

    historiaAtual = 1; // só existe história 1
    printf("\n============== QUEM MATOU JOÃO PÍFIO? ==============\n");

    printf(
        " Na noite desta sexta-feira, às vésperas da festa de aniversário da\n"
        "cidade, a primeira-dama de Logicópolis reportou às autoridades que seu\n"
        "marido, o Prefeito João Pífio, estaria desaparecido.\n"
        "No dia seguinte, pela manhã, seu corpo apareceu inesperadamente dentro de\n"
        "uma mala de viagem no meio da praça central, onde a festa aconteceria. O\n"
        "departamento investigativo de Logicópolis logo foi acionado, e levantou\n"
        "os seguintes questionamentos:\n\n"
        "Quem matou o prefeito?\n"
        "Onde ocorreu o crime?\n"
        "Que arma foi utilizada?\n\n"
        "Os suspeitos apontados foram:\n"
        "- Dona Madalena Pífio: Esposa de João. Além de ter sido a primeira a\n"
        "reportar o desaparecimento, conhece sua rotina\n"
        "como ninguém.\n\n"
        "- Paulinho Malandro: Vice-prefeito de Logicópolis. Há rumores de que\n"
        "João não o manteria em sua chapa no próximo mandato por\n"
        "divergências internas.\n\n"
        "- Zé Caduco: Grande rival político de João. Por décadas, as famílias\n"
        "Pífio e Caduco disputam pelo “controle” da cidade.\n\n"
        "- Lúcia Paixão: Secretária de João. Os colegas de trabalho comentam\n"
        "que Lúcia é chamada à sala do prefeito com frequência e passa longas\n"
        "horas lá dentro…\n\n"
        "- Olívia Pífio:  Única filha de João. Conhecida por seu estilo de vida\n"
        "extravagante, e, até o momento, única herdeira do patrimônio de seu\n"
        "pai.\n\n"
        "- Jonas Bolchevique: Líder do movimento estudantil da cidade. Há\n"
        "tempos critica o cenário político de Logicópolis, e propõe uma revolução\n"
        "popular.\n\n"
        "Possíveis Locais do crime:\n\n"
        "Prefeitura, Casa do Prefeito, Banco, Floricultura,\n"
        "Bar, Estação de Trem, Biblioteca, Teatro.\n\n"
        "Possíveis armas do crime:\n\n"
        "Faca, Revólver, Castiçal, Cano, Soco Inglês, Veneno\n"
    );

    printf("=================================\n\n");
}

/* -------------------  LOOP PRINCIPAL DO JOGO  ------------------- */

int game_run(void) {

    cli_init();
    srand(time(NULL));

    escolherHistoria();

    char escolha;

    while (1) {

        menuHistoria1();

        printf("\nEscolha: ");
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        limparBufferEntrada();

        if (escolha == 'X') {
            printf("Saindo do jogo...\n");
            break;
        }

        if (escolha == 'S') {
            printf("\n===== SOLUÇÃO DO CASO =====\n");
            printf("Assassino: Lúcia Paixão\n");
            printf("Local: Bar\n");
            printf("Arma: Veneno\n");
            printf("===========================\n");
        } else {
            int opcao = escolha - '0';
            salaHistoria1(opcao);
        }
    
    }

    return 0;
}