#include "../include/cli_lib.h"
#include <stdio.h>

int game_run(void);

int main(void) {
    cli_init();
    printf("LogiC Game - iniciando...\n\n");

    game_run();

    printf("\nPrograma encerrado.\n");
    return 0;
}
