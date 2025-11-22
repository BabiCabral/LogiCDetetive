#ifndef SAVE_H
#define SAVE_H

// Salva/carrega o estado do jogo (jogadores + pontuações)
// Retorna 1 em sucesso, 0 em falha
int save_game(const char *path);
int load_game(const char *path);

#endif // SAVE_H
