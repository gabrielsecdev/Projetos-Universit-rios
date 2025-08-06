#include <stdio.h>
#include <stdlib.h>
#include "retangulos.h"
#include "main.h"


static Retangulo retangulos[MAX_RETANGULOS];
static int quantidadeRetangulos = 0;


int criarRetangulo(int x, int y, int largura, int altura) {
    if (x < 1 || y < 1 || x + largura - 1 > 80 || y + altura - 1 > 25) {
        printf("Erro: Posicoes fora dos limites permitidos.\n");
        return ERRO_ENTRADA_INVALIDA;
    }
    // Verificar sobreposição com retângulos existentes
    for (int i = 0; i < quantidadeRetangulos; i++) {
        Retangulo r = retangulos[i];
        printf("Comparando novo retangulo (%d, %d, %d, %d) com retangulo existente %d (%d, %d, %d, %d)\n", 
               x, y, largura, altura, i, r.x, r.y, r.largura, r.altura);

        // Verificar se os retângulos se sobrepõem nas coordenadas x e y
        if (x < r.x + r.largura && x + largura > r.x && y < r.y + r.altura && y + altura > r.y) {
            printf("Erro: Sobreposicao detectada com o retangulo %d.\n", i);
            return ERRO_SOBREPOSICAO;
        }
    }
    // Se não houver sobreposição, criar o retângulo
    if (quantidadeRetangulos < MAX_RETANGULOS) {
        Retangulo novoRetangulo = {x, y, largura, altura};
        retangulos[quantidadeRetangulos] = novoRetangulo;
        quantidadeRetangulos++;

        // Chamar alertaSobreposicao após criar o retângulo
        alertaSobreposicao();

        // Aplicar gravidade apenas ao retângulo recém-criado
        aplicarGravidade(&retangulos[quantidadeRetangulos - 1]);

        return SUCESSO;
    } else {
        // Número máximo de retângulos atingido
        printf("Erro: Numero maximo de retangulos atingido.\n");
        return ERRO_MAXIMO_ATINGIDO;
    }
}



int moverDireita(int x, int y, int posicoes) {
    for (int i = 0; i < quantidadeRetangulos; i++) {
        Retangulo r = retangulos[i];

        // Verificar se as coordenadas x e y correspondem ao canto inferior esquerdo do retângulo
        if (x >= r.x && x < r.x + r.largura && y >= r.y && y <= r.y + r.altura - 1) {

            // Verificar se a nova posição está dentro dos limites
            if (r.x + posicoes + r.largura - 1 > 1000) {
                printf("Erro: Nova posiçao fora do limite.\n");
                return ERRO_ENTRADA_INVALIDA;
            }
            retangulos[i].x += posicoes;
            aplicarGravidade();
            return SUCESSO;
        }
    }
    printf("Erro: Retangulo nao encontrado na posição especificada.\n");
    return ERRO_RETANGULO_NAO_ENCONTRADO;
}

int moverEsquerda(int x, int y, int posicoes) {
    for (int i = 0; i < quantidadeRetangulos; i++) {
        Retangulo r = retangulos[i];
        // Verificar se as coordenadas x e y correspondem ao canto inferior esquerdo do retângulo
        if (x == r.x && y == r.y) {
            // Verificar se a nova posição está dentro dos limites
            if (r.x - posicoes < 0) {
                return ERRO_ENTRADA_INVALIDA;
            }
            retangulos[i].x -= posicoes;
            aplicarGravidade();
            return SUCESSO;
        }
    }
    return ERRO_RETANGULO_NAO_ENCONTRADO;
}





void aplicarGravidade() {
    // Aplicar gravidade a todos os retângulos
    for (int i = 0; i < quantidadeRetangulos; i++) {
        Retangulo *r = &retangulos[i];

        // Calcular a nova coordenada y após aplicar a gravidade
        while (r->y > 1) {
            int indiceAbaixo = encontrarRetangulo(r->x, r->y - 1);

            // Verificar se há um retângulo abaixo
            if (indiceAbaixo == -1) {
                r->y -= 1;
            } else {
                break;
            }
        }
    }
}

// Função para obter os retângulos
Retangulo* obterRetangulos(int* quantidade) {
    *quantidade = quantidadeRetangulos;
    printf("Quantidade de retangulos obtida: %d\n", *quantidade); // Debugging message
    return retangulos;
}


void alertaSobreposicao() {
    // Verificar todas as combinações possíveis de pares de retângulos
    for (int i = 0; i < quantidadeRetangulos; i++) {
        for (int j = i + 1; j < quantidadeRetangulos; j++) {
            Retangulo r1 = retangulos[i];
            Retangulo r2 = retangulos[j];

            // Verificar se os retângulos se sobrepõem e podem ser unidos
            if (mergePossivel(r1.x, r1.y, r2.x, r2.y)) {
                printf("Alerta: Os retangulos %d e %d se sobrepoem e podem ser unidos.\n", i, j);
            }
        }
    }
}

int mergePossivel(int x1, int y1, int x2, int y2) {
    // encontrar os índices dos retângulos
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < quantidadeRetangulos; i++) {
        if (retangulos[i].x == x1 && retangulos[i].y == y1) {
            index1 = i;
        }
        if (retangulos[i].x == x2 && retangulos[i].y == y2) {
            index2 = i;
        }
    }

    // verificar se ambos os retângulos existem
    if (index1 == -1 || index2 == -1) {
        return 0;
    }

    Retangulo r1 = retangulos[index1];
    Retangulo r2 = retangulos[index2];

    // verificar se os retângulos podem ser unidos
    if (r1.largura == r2.largura && 
        (r1.y + r1.altura == r2.y || r2.y + r2.altura == r1.y)) {
        return 1;
    }

    if (r1.altura == r2.altura && 
        (r1.x + r1.largura == r2.x || r2.x + r2.largura == r1.x)) {
        return 1;
    }

    return 0;
}

void mergeRetangulos(int x1, int y1, int x2, int y2) {
    // encontrar os índices dos retângulos
    int index1 = encontrarRetangulo(x1, y1);
    int index2 = encontrarRetangulo(x2, y2);

    // verificar se ambos os retângulos existem e podem ser unidos
    if (index1 != -1 && index2 != -1 && mergePossivel(x1, y1, x2, y2)) {
        Retangulo* r1 = &retangulos[index1];
        Retangulo* r2 = &retangulos[index2];

        // unir os retângulos com base em seu alinhamento
        if (r1->largura == r2->largura) {
            // unir verticalmente
            if (r1->y + r1->altura == r2->y) {
                r1->altura += r2->altura;
            } else if (r2->y + r2->altura == r1->y) {
                r1->y = r2->y;
                r1->altura += r2->altura;
            }
        } else if (r1->altura == r2->altura) {
            // unir horizontalmente
            if (r1->x + r1->largura == r2->x) {
                r1->largura += r2->largura;
            } else if (r2->x + r2->largura == r1->x) {
                r1->x = r2->x;
                r1->largura += r2->largura;
            }
        }

        // remover o segundo retângulo
        retangulos[index2] = retangulos[--quantidadeRetangulos];
        aplicarGravidade();
    } else {
        printf("Erro: Nao foi possível unir os retangulos.\n");
    }
}


int encontrarRetangulo(int x, int y) {
    for (int i = 0; i < quantidadeRetangulos; i++) {
        Retangulo r = retangulos[i];
        if (x >= r.x && x < r.x + r.largura && y >= r.y && y < r.y + r.altura) {
            return i;
        }
    }
    return -1; 
}
