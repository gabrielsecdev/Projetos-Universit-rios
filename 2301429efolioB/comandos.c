#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulos.h"
#include "visualizacao.h"
#include "comandos.h"
#include "main.h"

int interpretarComando(const char *comando) {
    if (strcmp(comando, "sair") == 0) {
        return SUCESSO; // Returning success as the command "sair" was successful
    }

    int x, y, l, a, p;
    int x1, y1, x2, y2;

    if (sscanf(comando, "create %d,%d+%d,%d", &x, &y, &l, &a) == 4) {
        if (criarRetangulo(x, y, l, a) == 0) {
            alertaSobreposicao();
        }
    } else if (sscanf(comando, "moveRight %d,%d+%d", &x, &y, &p) == 3) {
        moverDireita(x, y, p);
    } else if (sscanf(comando, "moveLeft %d,%d+%d", &x, &y, &p) == 3) {
        moverEsquerda(x, y, p);
    } else if (sscanf(comando, "merge %d,%d+%d,%d", &x1, &y1, &x2, &y2) == 4) {
        mergeRetangulos(x1, y1, x2, y2);
    } else {
        printf("Comando invalido: %s\n", comando);
    }
    desenharMundo();
    return SUCESSO;
}

