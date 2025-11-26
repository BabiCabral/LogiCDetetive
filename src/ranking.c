#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ranking.h"

static RankingEntry *ranking = NULL;
static size_t ranking_sz = 0;

void ranking_init() {
    ranking = NULL;
    ranking_sz = 0;
}

void ranking_free() {
    free(ranking);
    ranking = NULL;
    ranking_sz = 0;
}

size_t ranking_count() {
    return ranking_sz;
}

int ranking_add(const char *nome, int pontos) {
    RankingEntry novo;

    strncpy(novo.nome, nome, sizeof(novo.nome) - 1);
    novo.nome[sizeof(novo.nome) - 1] = '\0';

    novo.pontos = pontos;

    RankingEntry *tmp = realloc(ranking, sizeof(RankingEntry) * (ranking_sz + 1));
    if (!tmp) return -1;

    ranking = tmp;
    ranking[ranking_sz] = novo;
    ranking_sz++;
    return 0;
}

void ranking_sort() {
    if (ranking_sz < 2) return;

    for (size_t i = 0; i < ranking_sz - 1; i++) {
        for (size_t j = i + 1; j < ranking_sz; j++) {
            if (ranking[j].pontos > ranking[i].pontos) {
                RankingEntry temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}

int ranking_save(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;

    for (size_t i = 0; i < ranking_sz; i++) {
        fprintf(f, "%s;%d\n", ranking[i].nome, ranking[i].pontos);
    }

    fclose(f);
    return 0;
}

int ranking_load(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    ranking_free();
    ranking_init();

    char linha[128];

    while (fgets(linha, sizeof(linha), f)) {
        char nome[50];
        int pontos;

        char *sep = strchr(linha, ';');
        if (!sep) continue;

        *sep = '\0';
        strncpy(nome, linha, sizeof(nome) - 1);
        nome[sizeof(nome) - 1] = '\0';

        pontos = atoi(sep + 1);

        ranking_add(nome, pontos);
    }

    fclose(f);
    ranking_sort();
    return 0;
}

void ranking_print_recursive(size_t idx) {
    if (idx >= ranking_sz) return;

    printf("%zu) %s - %d pontos\n", idx + 1, ranking[idx].nome, ranking[idx].pontos);

    ranking_print_recursive(idx + 1);
}
