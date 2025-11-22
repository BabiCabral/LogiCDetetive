#include "../include/players.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Player *g_players = NULL;
static size_t g_capacity = 0;
static size_t g_count = 0;

void players_init(void) {
    g_players = NULL;
    g_capacity = 0;
    g_count = 0;
}

void players_free(void) {
    if (!g_players) return;
    for (size_t i = 0; i < g_count; ++i) {
        free(g_players[i].nome);
    }
    free(g_players);
    g_players = NULL;
    g_capacity = g_count = 0;
}

static int ensure_capacity(void) {
    if (g_count < g_capacity) return 1;
    size_t newcap = (g_capacity == 0) ? 4 : g_capacity * 2;
    Player *p = realloc(g_players, newcap * sizeof(Player));
    if (!p) return 0;
    g_players = p;
    g_capacity = newcap;
    return 1;
}

int players_add(const char *nome) {
    if (!ensure_capacity()) return 0;
    char *dup = strdup(nome);
    if (!dup) return 0;
    g_players[g_count].nome = dup;
    g_players[g_count].score = 0; // inicializa pontuação
    g_count++;
    return 1;
}

size_t players_count(void) {
    return g_count;
}

const char *players_get_name(size_t idx) {
    if (idx >= g_count) return NULL;
    return g_players[idx].nome;
}

// recursão simples para imprimir nomes: imprime do idx até o fim
void players_print_recursive(size_t idx) {
    if (idx >= g_count) return;
    printf("Jogador %zu: %s (pontuação: %d)\n", idx+1, g_players[idx].nome, g_players[idx].score);
    players_print_recursive(idx + 1);
}

int players_get_score(size_t idx) {
    if (idx >= g_count) return 0;
    return g_players[idx].score;
}

int players_set_score(size_t idx, int score) {
    if (idx >= g_count) return 0;
    g_players[idx].score = score;
    return 1;
}

int players_add_score(size_t idx, int delta) {
    if (idx >= g_count) return 0;
    g_players[idx].score += delta;
    return 1;
}
