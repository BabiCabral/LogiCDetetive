#include "../include/save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(a,b) _mkdir(a)
#endif

static int ensure_dir(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0755) != 0) return 0;
    }
    return 1;
}

int save_game(const char *path, SaveData *data) {
    if (!path || !data) return 0;

    char dir[512];
    strncpy(dir, path, sizeof(dir));
    dir[sizeof(dir)-1] = '\0';
    char *p = strrchr(dir, '/');
    if (!p) p = strrchr(dir, '\\');
    if (p) *p = '\0'; else strcpy(dir, ".");

    if (!ensure_dir(dir)) return 0;

    FILE *f = fopen(path, "w");
    if (!f) return 0;

    fprintf(f, "%d\n", data->historia_id);
    fprintf(f, "%d\n", data->score);
    fprintf(f, "%d\n", data->pistas_encontradas);
    fprintf(f, "%s\n", data->nome);

    fclose(f);
    return 1;
}

int load_game(const char *path, SaveData *data) {
    if (!path || !data) return 0;

    FILE *f = fopen(path, "r");
    if (!f) return 0;

    if (fscanf(f, "%d\n", &data->historia_id) != 1) { fclose(f); return 0; }
    if (fscanf(f, "%d\n", &data->score) != 1) { fclose(f); return 0; }
    if (fscanf(f, "%d\n", &data->pistas_encontradas) != 1) { fclose(f); return 0; }

    if (!fgets(data->nome, sizeof(data->nome), f)) {
        data->nome[0] = '\0';
    } else {
        size_t len = strlen(data->nome);
        if (len > 0 && data->nome[len-1] == '\n') data->nome[len-1] = '\0';
    }

    fclose(f);
    return 1;
}

