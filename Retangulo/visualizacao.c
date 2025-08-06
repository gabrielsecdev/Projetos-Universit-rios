#include <stdio.h>
#include "retangulos.h"
#include "visualizacao.h"
#include "main.h"

#define LARGURA_TELA 81
#define ALTURA_TELA 26

void desenharMundo()
{
    char tela[ALTURA_TELA][LARGURA_TELA + 1];
    int quantidadeRetangulos;
    Retangulo *retangulos = obterRetangulos(&quantidadeRetangulos);

    // inicializa a tela com espaços em branco
    for (int y = 0; y < ALTURA_TELA; y++)
    {
        for (int x = 0; x < LARGURA_TELA; x++)
        {
            tela[y][x] = ' ';
        }
        tela[y][LARGURA_TELA] = '\0';
    }

    // desenha os retângulos
    for (int i = 0; i < quantidadeRetangulos; i++)
    {
        Retangulo r = retangulos[i];
        for (int y = r.y; y < r.y + r.altura; y++)
        {
            for (int x = r.x; x < r.x + r.largura; x++)
            {
                if (y >= 0 && y < ALTURA_TELA && x >= 0 && x < LARGURA_TELA)
                {
                    if (y == r.y || y == r.y + r.altura - 1 || x == r.x || x == r.x + r.largura - 1)
                    {
                        tela[y][x] = 'x'; // borda
                    }
                    else
                    {
                        tela[y][x] = 'O'; // interior
                    }
                }
            }
        }
    }

    // imprime os números do eixo Y
    for (int y = ALTURA_TELA - 1; y >= 0; y--)
    {
        printf("%2d ", y); // imprime a coordenada Y
        printf("%s\n", tela[y]);
    }

    // imprime os números do eixo X
    printf("  "); // Adiciona espaço para alinhar com os números do eixo Y
    for (int x = 0; x < LARGURA_TELA; x++)
    {
        if (x % 10 == 0)
        {
            printf("%2d", x); // imprime a coordenada X
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}
