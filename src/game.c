#include "../include/game.h"
#include "../include/players.h"
#include "../include/cli_lib.h"
#include "../include/save.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void registrarJogadores(void) {
    char nome[128];
    int opcao = 0;

    cli_print("\n--- NOVO JOGO: REGISTRO ---\n");
    while (1) {
        if (players_count() >= 6) { // limite do enunciado por grupo
            printf("Limite máximo de jogadores (6) atingido.\n");
            break;
        }
        printf("Inserir nome do Jogador %zu: ", players_count()+1);
        if (cli_getline(nome, sizeof(nome)) == NULL) break;
        if (strlen(nome) == 0) { printf("Nome inválido.\n"); continue; }
        if (!players_add(nome)) { printf("Falha ao adicionar jogador.\n"); break; }

        // menu simples
        do {
            printf("\nOPÇÕES:\n1. Adicionar novos jogadores\n2. Iniciar jogo\nEscolha: ");
            if (scanf("%d", &opcao) != 1) {
                limparBufferEntrada(); opcao = 0; printf("Entrada inválida.\n");
                continue;
            }
            limparBufferEntrada();
            if (opcao == 2) return;
            if (opcao != 1) printf("Opção inválida.\n");
        } while (opcao != 1);
    }
}

static void entrarNaSala(int opcaoSala, const char *nomeJogador) {
    printf("\n>>> %s entrando na sala... ", nomeJogador);
    switch (opcaoSala) {
        case 1: printf("ESTAÇÃO DE TREM. Pista: O suspeito usava um chapéu.\n"); break;
        case 2: printf("BANCO. Pista: Pegadas de lama no chão.\n"); break;
        case 3: printf("BIBLIOTECA. Pista: Uma página foi rasgada.\n"); break;
        case 4: printf("BAR. Pista: O garçom viu alguém correr.\n"); break;
        case 5: printf("TEATRO. Pista: Um ingresso foi encontrado.\n"); break;
        case 6: printf("PARQUE. Pista: Guarda-chuva quebrado.\n"); break;
        default: printf("Sala desconhecida.\n"); break;
    }
}

int game_run(void) {
    cli_init();
    players_init();

    // Se houver save disponível, perguntar ao usuário se quer carregar
    if (load_game("saves/savegame.txt")) {
        char escolha = '\0';
        printf("Arquivo de save encontrado. Deseja carregar o último save? (s/N): ");
        if (scanf(" %c", &escolha) == 1) {
            limparBufferEntrada();
            if (escolha == 's' || escolha == 'S') {
                // já carregado por load_game acima
                printf("Save carregado.\n");
            } else {
                // usuário optou por não carregar, reiniciar jogadores
                players_free();
                players_init();
            }
        } else {
            limparBufferEntrada();
            players_free();
            players_init();
        }
    }

    // Registrar novos jogadores se não houver nenhum
    if (players_count() == 0) {
        registrarJogadores();
    }
    if (players_count() == 0) {
        printf("Nenhum jogador registrado. Encerrando.\n");
        players_free();
        return 0;
    }

    printf("\nJogadores registrados:\n");
    players_print_recursive(0); // demonstra recursividade

    int jogoRolando = 1;
    int turnoAtual = 0;
    while (jogoRolando) {
        size_t idx = turnoAtual % players_count();
        const char *nome = players_get_name(idx);
        printf("\n====================================\n");
        printf("É a vez de: %s\n", nome);
        printf("====================================\n");

        char opcaoMenu = '\0';
        int turnoValido = 0;
        do {
            printf("Aonde você quer ir investigar?\n");
            printf("1. Estação de trem\n2. Banco\n3. Biblioteca\n4. Bar\n5. Teatro\n6. Parque\nX. SAIR do jogo\nSua escolha: ");
            if (scanf(" %c", &opcaoMenu) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); continue; }
            limparBufferEntrada();
            opcaoMenu = toupper((unsigned char)opcaoMenu);
            if (opcaoMenu >= '1' && opcaoMenu <= '6') {
                int sala = opcaoMenu - '0';
                entrarNaSala(sala, nome);
                // atribuir pontos por sala (exemplo)
                int pontos = 0;
                switch (sala) {
                    case 1: pontos = 10; break;
                    case 2: pontos = 8; break;
                    case 3: pontos = 6; break;
                    case 4: pontos = 5; break;
                    case 5: pontos = 7; break;
                    case 6: pontos = 4; break;
                }
                players_add_score(idx, pontos);
                printf("%s ganhou %d pontos! Pontuação atual: %d\n", nome, pontos, players_get_score(idx));
                turnoValido = 1;
            } else if (opcaoMenu == 'X') {
                printf("\n%s decidiu sair do jogo.\n", nome);
                jogoRolando = 0; turnoValido = 1;
            } else if (opcaoMenu == 'S') {
                // salvar jogo
                if (save_game("saves/savegame.txt")) {
                    printf("Jogo salvo com sucesso em 'saves/savegame.txt'.\n");
                } else {
                    printf("Falha ao salvar o jogo.\n");
                }
                // não conta como turno completo; deixa o jogador escolher novamente
                turnoValido = 0;
            } else {
                printf("Escolha inválida. Tente novamente.\n");
            }
        } while (!turnoValido);
        if (jogoRolando) turnoAtual++;
    }

    players_free();
    return 0;
}
