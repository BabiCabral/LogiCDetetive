#ifndef RANKING_H
#define RANKING_H

#include <stddef.h>

typedef struct {
    char nome[50];
    int pontos;
} RankingEntry;

void ranking_init();
void ranking_free();
int ranking_add(const char *nome, int pontos);
int ranking_save(const char *filename);
int ranking_load(const char *filename);
void ranking_sort();
void ranking_print_recursive(size_t idx);
size_t ranking_count();

#endif
