#ifndef PLAYERS_H
#define PLAYERS_H

#include <stddef.h>

typedef struct {
    char *nome; // alocado dinamicamente
    int score;  // pontuação do jogador
} Player;

// Inicializa a estrutura de jogadores
void players_init(void);
// Libera memória usada por jogadores
void players_free(void);
// Adiciona um jogador (duplica nome internamente)
int players_add(const char *nome);
// Retorna número de jogadores registrados
size_t players_count(void);
// Retorna ponteiro para nome do jogador (não modificar)
const char *players_get_name(size_t idx);
// Imprime todos jogadores usando recursão (exemplo de recursividade)
void players_print_recursive(size_t idx);

// Pontuação: getters/setters
int players_get_score(size_t idx);
int players_set_score(size_t idx, int score);
int players_add_score(size_t idx, int delta);

#endif // PLAYERS_H
