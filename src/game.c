#include "../include/game.h"
#include "../include/cli_lib.h"
#include "../include/ranking.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef enum {
    PREFEITURA = 1,
    CASA_PREFEITO,
    BANCO,
    FLORICULTURA,
    BAR,
    ESTACAO,
    BIBLIOTECA,
    TEATRO
} LocalEnum;

typedef struct {
    const char *assassino;
    const char *local;
    const char *arma;
    const char *introducao;

    const char **prefeitura;  int qtd_prefeitura;
    const char **casa;        int qtd_casa;
    const char **banco;       int qtd_banco;
    const char **floricultura;int qtd_floricultura;
    const char **bar;         int qtd_bar;
    const char **estacao;     int qtd_estacao;
    const char **biblioteca;  int qtd_biblioteca;
    const char **teatro;      int qtd_teatro;
} Historia;

typedef struct {
    char nome[64];
    int pontos;
    int movimentos;
} Jogador;

/*Jogo 1*/
static const char *J1_prefeitura_static[] = {
    "As flores na sala de João ou são compradas por Madalena, ou por Lúcia.",
    "João só vai ao bar após o trabalho quando tem reunião com Paulinho ou Lúcia à tarde.",
    "As reuniões só acontecem durante horário de trabalho.",
    "As flores da sala de João são azuis."
};
static const char *J1_casa_static[] = {
    "Se as flores da sala de João são azuis, elas não foram compradas por Madalena.",
    "Se João não tem reunião à tarde, ele vai com Madalena ao teatro após o trabalho.",
    "Olívia e Madalena foram à estação de trem na sexta-feira."
};
static const char *J1_banco_static[] = {
    "Às sextas-feiras, Paulinho só trabalha pela manhã.",
    "Se o cofre foi aberto, Paulinho ou Zé Caduco estavam no banco.",
    "Se o castiçal do banco foi emprestado a alguém, o cofre foi aberto."
};
static const char *J1_floricultura_static[] = {
    "Apenas pessoas da prefeitura podem comprar substâncias venenosas na floricultura.",
    "Se alguém da prefeitura comprou flores na sexta-feira, também comprou substância venenosa.",
    "As flores da sala de João são sempre frescas."
};
static const char *J1_bar_static[] = {
    "João esteve no bar às 20h.",
    "João nunca vai ao bar sozinho.",
    "Uma pessoa foi vista com uma mala saindo do bar."
};
static const char *J1_estacao_static[] = {
    "Se Jonas não estava distribuindo panfletos na estação, ele estava no evento da biblioteca.",
    "Se alguém da família Pífio esteve na estação de trem, Jonas não distribuiu panfletos por lá.",
    "Se a arma for o cano, o crime ocorreu na estação de trem."
};
static const char *J1_biblioteca_static[] = {
    "O castiçal do banco foi emprestado à biblioteca na sexta-feira para um evento.",
    "Todos que participaram do evento ficaram na biblioteca até 22h.",
    "Se o corpo possui hematoma na cabeça, a arma foi o castiçal ou o cano."
};
static const char *J1_teatro_static[] = {
    "João e Madalena não foram ao teatro na sexta-feira.",
    "Se João saiu na sexta-feira à noite, estava acompanhado da pessoa com quem se reuniu à tarde.",
    "O corpo não possui qualquer hematoma na cabeça."
};

/* Jogo 2 */
static const char *J2_prefeitura_static[] = {
    "Se João recebeu um panfleto na sexta-feira, então Jonas esteve na prefeitura pela manhã.",
    "Se Lúcia ficou na prefeitura após as 18h, ela não esteve na biblioteca.",
    "Alguém retirou um documento do arquivo às 17h, e só Jonas e Zé Caduco tinham autorização para isso."
};
static const char *J2_casa_static[] = {
    "Se Madalena estava preparando o jantar às 20h, então ela não saiu de casa naquela noite.",
    "Se Olívia não usou o carro na sexta, então ela não foi ao centro.",
    "Se alguém esteve na casa após as 22h, João já não estava mais vivo."
};
static const char *J2_banco_static[] = {
    "Se o cofre foi aberto na sexta, Paulinho estava no banco no horário do almoço.",
    "Se Jonas esteve no banco pela manhã, ele pediu para ver o histórico de transações da prefeitura.",
    "Se Zé Caduco entrou no banco, o gerente recebeu uma ligação anônima."
};
static const char *J2_floricultura_static[] = {
    "Se alguém comprou flores brancas na sexta, então esteve também na biblioteca durante o evento.",
    "Se Olívia comprou flores, essas flores foram entregues na prefeitura.",
    "Se as flores brancas foram entregues na biblioteca, elas estavam acompanhadas de uma mensagem escrita por Jonas."
};
static const char *J2_bar_static[] = {
    "Se Paulinho esteve no bar à tarde, então ele não foi à biblioteca.",
    "Se o bar estava lotado, Jonas não esteve lá depois das 18h.",
    "Se alguém levou uma mala ao bar, então esteve também no banco naquela tarde."
};
static const char *J2_estacao_static[] = {
    "Se Jonas não estava na estação, ele estava na biblioteca.",
    "Se Zé Caduco comprou passagem na sexta, ele não ficou na cidade à noite.",
    "Se a arma for um cano, então alguém esteve na estação antes das 19h."
};
static const char *J2_biblioteca_static[] = {
    "O castiçal da biblioteca só pode ser retirado com autorização do coordenador, e Jonas é o único que tinha essa autorização naquele dia.",
    "Se alguém participou do evento estudantil, ficou no salão principal até às 21h.",
    "Se João foi visto na biblioteca às 20h, ele estava com a pessoa que portava o castiçal."
};
static const char *J2_teatro_static[] = {
    "Se Madalena comprou ingresso, ela esteve no teatro às 20h.",
    "Se João não foi ao teatro, então o crime não ocorreu lá.",
    "Se o corpo possui hematoma na cabeça, a arma foi o castiçal ou o cano."
};

/* Jogo 3 */
static const char *J3_prefeitura_static[] = {
    "Se Paulinho não teve reunião com João naquela tarde, então João deixou o expediente mais cedo.",
    "Se Lúcia saiu da prefeitura às 17h, então ela foi diretamente para casa.",
    "Se Zé Caduco discutiu com João naquele dia, então ele esteve na prefeitura pela manhã."
};
static const char *J3_casa_static[] = {
    "Se Olívia não chegou em casa antes das 21h, então ela não foi à estação.",
    "Se Madalena convidou alguém para o jantar, então ela esteve em casa a noite inteira.",
    "Se João saiu após as 18h, então não voltou para casa antes das 22h."
};
static const char *J3_banco_static[] = {
    "Se alguém sacou dinheiro após as 17h, esse alguém esteve na estação mais tarde.",
    "Se Paulinho foi ao banco de manhã, ele estava sem acompanhante.",
    "Se o gerente recebeu duas assinaturas iguais, então o documento foi falsificado."
};
static const char *J3_floricultura_static[] = {
    "Se flores vermelhas foram compradas na sexta, elas foram entregues na estação de trem.",
    "Se Paulinho comprou flores vermelhas, ele também pediu um envelope pequeno.",
    "Se o envelope pequeno foi entregue na estação, ele estava vazio."
};
static const char *J3_bar_static[] = {
    "Se João passou pelo bar às 19h, então ele estava indo encontrar alguém.",
    "Se Paulinho estava no bar às 18h, ele foi visto carregando um objeto metálico.",
    "Se Zé Caduco esteve no bar, então ele não foi à estação naquele dia."
};
static const char *J3_estacao_static[] = {
    "Se a arma utilizada foi um cano, o crime ocorreu na estação de trem.",
    "Se Paulinho esteve na estação após as 19h, ele portava um cilindro fino de metal.",
    "Se João esteve na estação às 20h, ele estava esperando alguém."
};
static const char *J3_biblioteca_static[] = {
    "Se alguém participou do evento de leitura, ficou na biblioteca até 21h.",
    "Se Paulinho não assinou presença na biblioteca, então ele não esteve lá.",
    "Se o castiçal foi emprestado, ele não foi parar na estação."
};
static const char *J3_teatro_static[] = {
    "Se Madalena estava no teatro, ela chegou antes das 20h.",
    "Se alguém comprou ingresso na sexta, então essa pessoa não esteve na estação no período noturno.",
    "Se João não foi ao teatro, então o crime não ocorreu lá."
};

static void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int aleatorio_idx(int qtd) {
    if (qtd <= 0) return 0;
    return rand() % qtd;
}

static const char **allocar_lista_pistas(const char *estatico[], int qtd) {
    const char **lista = (const char **) malloc(sizeof(const char *) * qtd);
    if (!lista) {
        fprintf(stderr, "Erro de memória ao alocar pistas\n");
        exit(1);
    }
    for (int i = 0; i < qtd; ++i) lista[i] = estatico[i];
    return lista;
}

static Historia *inicializar_historias(int *out_qtd) {
    int total = 3;
    Historia *vec = (Historia *) malloc(sizeof(Historia) * total);
    if (!vec) { fprintf(stderr, "Erro de memória\n"); exit(1); }

    /* Jogo 1 */
    vec[0].introducao = "Jogo 1: Caso clássico. Uma rede de reuniões, flores azuis e um bar movimentado.";
    vec[0].assassino = "Lúcia Paixão";
    vec[0].local = "Bar";
    vec[0].arma  = "Veneno";
    vec[0].prefeitura   = allocar_lista_pistas(J1_prefeitura_static, 4); vec[0].qtd_prefeitura = 4;
    vec[0].casa         = allocar_lista_pistas(J1_casa_static, 3); vec[0].qtd_casa = 3;
    vec[0].banco        = allocar_lista_pistas(J1_banco_static, 3); vec[0].qtd_banco = 3;
    vec[0].floricultura = allocar_lista_pistas(J1_floricultura_static, 3); vec[0].qtd_floricultura = 3;
    vec[0].bar          = allocar_lista_pistas(J1_bar_static, 3); vec[0].qtd_bar = 3;
    vec[0].estacao      = allocar_lista_pistas(J1_estacao_static, 3); vec[0].qtd_estacao = 3;
    vec[0].biblioteca   = allocar_lista_pistas(J1_biblioteca_static, 3); vec[0].qtd_biblioteca = 3;
    vec[0].teatro       = allocar_lista_pistas(J1_teatro_static, 3); vec[0].qtd_teatro = 3;

    /* Jogo 2 */
    vec[1].introducao = "Jogo 2: Plano improvisado durante um evento estudantil na biblioteca.";
    vec[1].assassino = "Jonas Bolchevique";
    vec[1].local = "Biblioteca";
    vec[1].arma  = "Castiçal";
    vec[1].prefeitura   = allocar_lista_pistas(J2_prefeitura_static, 3); vec[1].qtd_prefeitura = 3;
    vec[1].casa         = allocar_lista_pistas(J2_casa_static, 3); vec[1].qtd_casa = 3;
    vec[1].banco        = allocar_lista_pistas(J2_banco_static, 3); vec[1].qtd_banco = 3;
    vec[1].floricultura = allocar_lista_pistas(J2_floricultura_static, 3); vec[1].qtd_floricultura = 3;
    vec[1].bar          = allocar_lista_pistas(J2_bar_static, 3); vec[1].qtd_bar = 3;
    vec[1].estacao      = allocar_lista_pistas(J2_estacao_static, 3); vec[1].qtd_estacao = 3;
    vec[1].biblioteca   = allocar_lista_pistas(J2_biblioteca_static, 3); vec[1].qtd_biblioteca = 3;
    vec[1].teatro       = allocar_lista_pistas(J2_teatro_static, 3); vec[1].qtd_teatro = 3;

    /* Jogo 3 */
    vec[2].introducao = "Jogo 3: Rastro oculto na estação de trem e contradições de horários.";
    vec[2].assassino = "Paulinho Malandro";
    vec[2].local = "Estação de Trem";
    vec[2].arma  = "Cano";
    vec[2].prefeitura   = allocar_lista_pistas(J3_prefeitura_static, 3); vec[2].qtd_prefeitura = 3;
    vec[2].casa         = allocar_lista_pistas(J3_casa_static, 3); vec[2].qtd_casa = 3;
    vec[2].banco        = allocar_lista_pistas(J3_banco_static, 3); vec[2].qtd_banco = 3;
    vec[2].floricultura = allocar_lista_pistas(J3_floricultura_static, 3); vec[2].qtd_floricultura = 3;
    vec[2].bar          = allocar_lista_pistas(J3_bar_static, 3); vec[2].qtd_bar = 3;
    vec[2].estacao      = allocar_lista_pistas(J3_estacao_static, 3); vec[2].qtd_estacao = 3;
    vec[2].biblioteca   = allocar_lista_pistas(J3_biblioteca_static, 3); vec[2].qtd_biblioteca = 3;
    vec[2].teatro       = allocar_lista_pistas(J3_teatro_static, 3); vec[2].qtd_teatro = 3;

    *out_qtd = total;
    return vec;
}

static void liberar_historias(Historia *vec, int qtd) {
    if (!vec) return;
    for (int i = 0; i < qtd; ++i) {
        free((void *) vec[i].prefeitura);
        free((void *) vec[i].casa);
        free((void *) vec[i].banco);
        free((void *) vec[i].floricultura);
        free((void *) vec[i].bar);
        free((void *) vec[i].estacao);
        free((void *) vec[i].biblioteca);
        free((void *) vec[i].teatro);
    }
    free(vec);
}


static void mostrar_menu_locais() {
    printf("\n========= LOCAIS =========\n");
    printf("1. Prefeitura\n");
    printf("2. Casa do Prefeito\n");
    printf("3. Banco\n");
    printf("4. Floricultura\n");
    printf("5. Bar\n");
    printf("6. Estação de Trem\n");
    printf("7. Biblioteca\n");
    printf("8. Teatro\n");
    printf("9. Salvar ranking\n");
    printf("L. Carregar ranking\n");
    printf("0. Fazer acusação\n");
    printf("S. Ver solução (revela)\n");
    printf("X. Sair\n");
}

static int investigar_local(Historia *h, int opcao, Jogador *p) {
    const char *pista = NULL;

    switch (opcao) {
        case PREFEITURA:    pista = h->prefeitura[aleatorio_idx(h->qtd_prefeitura)]; break;
        case CASA_PREFEITO: pista = h->casa[aleatorio_idx(h->qtd_casa)]; break;
        case BANCO:         pista = h->banco[aleatorio_idx(h->qtd_banco)]; break;
        case FLORICULTURA:  pista = h->floricultura[aleatorio_idx(h->qtd_floricultura)]; break;
        case BAR:           pista = h->bar[aleatorio_idx(h->qtd_bar)]; break;
        case ESTACAO:       pista = h->estacao[aleatorio_idx(h->qtd_estacao)]; break;
        case BIBLIOTECA:    pista = h->biblioteca[aleatorio_idx(h->qtd_biblioteca)]; break;
        case TEATRO:        pista = h->teatro[aleatorio_idx(h->qtd_teatro)]; break;
        default: return 0;
    }

    printf("\nPista encontrada: %s\n", pista);
    p->pontos += 5;
    p->movimentos += 1;
    return 1;
}

static int fazer_acusacao(Historia *h, Jogador *p) {
    char suspeito[64], local[64], arma[64];

    printf("\n--- FAZER ACUSAÇÃO ---\n");
    printf("Nome do suspeito: ");
    if (!fgets(suspeito, sizeof(suspeito), stdin)) return 0;
    suspeito[strcspn(suspeito, "\n")] = '\0';

    printf("Local do crime: ");
    if (!fgets(local, sizeof(local), stdin)) return 0;
    local[strcspn(local, "\n")] = '\0';

    printf("Arma utilizada: ");
    if (!fgets(arma, sizeof(arma), stdin)) return 0;
    arma[strcspn(arma, "\n")] = '\0';

    for (char *t = suspeito; *t; ++t) *t = (char) tolower(*t);
    for (char *t = local; *t; ++t) *t = (char) tolower(*t);
    for (char *t = arma; *t; ++t) *t = (char) tolower(*t);

    char sol_ass[64], sol_loc[64], sol_arma[64];
    strncpy(sol_ass, h->assassino, sizeof(sol_ass)-1); sol_ass[sizeof(sol_ass)-1]=0;
    strncpy(sol_loc, h->local, sizeof(sol_loc)-1); sol_loc[sizeof(sol_loc)-1]=0;
    strncpy(sol_arma, h->arma, sizeof(sol_arma)-1); sol_arma[sizeof(sol_arma)-1]=0;
    for (char *t = sol_ass; *t; ++t) *t = (char) tolower(*t);
    for (char *t = sol_loc; *t; ++t) *t = (char) tolower(*t);
    for (char *t = sol_arma; *t; ++t) *t = (char) tolower(*t);

    if (strcmp(suspeito, sol_ass) == 0 && strcmp(local, sol_loc) == 0 && strcmp(arma, sol_arma) == 0) {
        printf("\nAcusação CORRETA! Você venceu.\n");
        p->pontos += 50;
        return 1;
    } else {
        printf("\nAcusação incorreta. -10 pontos.\n");
        p->pontos -= 10;
        if (p->pontos < 0) p->pontos = 0;
        p->movimentos += 1;
        return 0;
    }
}

static void revelar_solucao(Historia *h) {
    printf("\n===== SOLUÇÃO DO CASO =====\n");
    printf("Assassino: %s\n", h->assassino);
    printf("Local: %s\n", h->local);
    printf("Arma: %s\n", h->arma);
    printf("===========================\n");
}

static void jogo_loop_rec(Historia *h, Jogador *p, int max_movimentos, int *acabou, Historia *all_hist, int qtd_hist) {
    if (*acabou) return;

    if (p->movimentos >= max_movimentos) {
        printf("\nLimite de movimentos atingido (%d). Fim do jogo.\n", max_movimentos);
        revelar_solucao(h);
        *acabou = 1;
        return;
    }

    printf("\nJogador: %s | Pontos: %d | Movimentos: %d/%d\n", p->nome, p->pontos, p->movimentos, max_movimentos);

    mostrar_menu_locais();
    printf("\nEscolha: ");

    char linha[64];
    if (!fgets(linha, sizeof(linha), stdin)) {
        jogo_loop_rec(h, p, max_movimentos, acabou, all_hist, qtd_hist);
        return;
    }
    char opc = toupper(linha[0]);

    if (opc == 'X') {
        printf("Saindo...\n");
        revelar_solucao(h);
        *acabou = 1;
        return;
    }
    if (opc == 'S') {
        revelar_solucao(h);
        *acabou = 1;
        return;
    }
    if (opc == '9') { 
        if (ranking_save("saves/ranking.txt") == 0) printf("Ranking salvo em saves/ranking.txt\n");
        else printf("Falha ao salvar ranking.\n");
        jogo_loop_rec(h, p, max_movimentos, acabou, all_hist, qtd_hist);
        return;
    }
    if (opc == 'L') { 
        if (ranking_load("saves/ranking.txt") == 0) {
            printf("Ranking carregado. Top atual:\n");
            ranking_print_recursive(0);
        } else {
            printf("Nenhum ranking salvo encontrado.\n");
        }
        jogo_loop_rec(h, p, max_movimentos, acabou, all_hist, qtd_hist);
        return;
    }
    if (opc == '0') { 
        int ac = fazer_acusacao(h, p);
        if (ac) {
            printf("Pontos finais: %d\n", p->pontos);
            *acabou = 1;
            return;
        } else {
            jogo_loop_rec(h, p, max_movimentos, acabou, all_hist, qtd_hist);
            return;
        }
    }

    int num = opc - '0';
    if (num >= 1 && num <= 8) {
        if (!investigar_local(h, num, p)) printf("Local inválido.\n");
        jogo_loop_rec(h, p, max_movimentos, acabou, all_hist, qtd_hist);
        return;
    }

    printf("Opção inválida.\n");
    jogo_loop_rec(h, p, max_movimentos, acabou, all_hist, qtd_hist);
}


int game_run(void) {
    cli_init();
    srand((unsigned int) time(NULL));

    int qtd_hist;
    Historia *historias = inicializar_historias(&qtd_hist);

    ranking_init();
    if (ranking_load("saves/ranking.txt") == 0) {
        printf("Ranking carregado (%zu entradas).\n", ranking_count());
    }

    int idx = rand() % qtd_hist;
    Historia *h = &historias[idx];

    printf("\n============== QUEM MATOU JOÃO PÍFIO? ==============\n\n");
    printf("%s\n", h->introducao);

    Jogador player;
    printf("\nDigite seu nome (ENTER para 'Jogador'): ");
    if (!fgets(player.nome, sizeof(player.nome), stdin)) {
        strncpy(player.nome, "Jogador", sizeof(player.nome)-1);
        player.nome[sizeof(player.nome)-1] = '\0';
    } else {
        player.nome[strcspn(player.nome, "\n")] = '\0';
        if (strlen(player.nome) == 0) strncpy(player.nome, "Jogador", sizeof(player.nome)-1);
    }
    player.pontos = 0;
    player.movimentos = 0;

    int acabou = 0;
    const int max_movimentos = 20;

    jogo_loop_rec(h, &player, max_movimentos, &acabou, historias, qtd_hist);

    printf("\nFim. Pontuação final: %d | Movimentos: %d\n", player.pontos, player.movimentos);

    if (ranking_add(player.nome, player.pontos) == 0) {
        ranking_sort();
        if (ranking_save("saves/ranking.txt") == 0) {
            printf("Seu score foi salvo no ranking.\n");
        } else {
            printf("Erro ao salvar ranking.\n");
        }
    } else {
        printf("Erro ao adicionar ao ranking.\n");
    }

    printf("\n=== RANKING ATUAL ===\n");
    ranking_print_recursive(0);

    ranking_free();
    liberar_historias(historias, qtd_hist);

    return 0;
}
