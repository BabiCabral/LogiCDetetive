#include "../include/save.h"
#include "../include/players.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

// Cria diretório se necessário
static int ensure_dir(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0755) != 0) return 0;
    }
    return 1;
}

int save_game(const char *path) {
    // path expected like "saves/savegame.txt"; ensure "saves" exists
    char dir[512];
    strncpy(dir, path, sizeof(dir));
    dir[sizeof(dir)-1] = '\0';
    char *p = strrchr(dir, '/');
    if (p) *p = '\0'; else strcpy(dir, ".");
    if (!ensure_dir(dir)) return 0;

    FILE *f = fopen(path, "w");
    if (!f) return 0;
    size_t n = players_count();
    fprintf(f, "%zu\n", n);
    for (size_t i = 0; i < n; ++i) {
        const char *name = players_get_name(i);
        int score = players_get_score(i);
        // gravar: nome|score\n
        fprintf(f, "%s|%d\n", name ? name : "", score);
    }
    fclose(f);
    return 1;
}

int load_game(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    // reinicializa jogadores
    players_free();
    players_init();

    size_t n = 0;
    if (fscanf(f, "%zu\n", &n) != 1) { fclose(f); return 0; }

    char line[1024];
    for (size_t i = 0; i < n; ++i) {
        if (!fgets(line, sizeof(line), f)) break;
        // remove newline
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') line[len-1] = '\0';
        char *sep = strchr(line, '|');
        if (!sep) continue;
        *sep = '\0';
        const char *name = line;
        int score = atoi(sep + 1);
        if (!players_add(name)) continue;
        players_set_score(players_count() - 1, score);
    }
    fclose(f);
    return players_count() > 0;
}
