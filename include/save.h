#ifndef SAVE_H
#define SAVE_H

#include <stddef.h>

typedef struct {
    int historia_id;
    int score;
    int pistas_encontradas;
    char nome[128];
} SaveData;

int save_game(const char *path, SaveData *data);
int load_game(const char *path, SaveData *data);

#endif
