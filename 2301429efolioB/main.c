#include <stdio.h>
#include <string.h>
#include "comandos.h"
#include "retangulos.h"
#include "visualizacao.h"
#include "main.h"

void imprimirLocalizacaoRetangulos() {
    int quantidadeRetangulos;
    Retangulo* retangulos = obterRetangulos(&quantidadeRetangulos);

    if (quantidadeRetangulos > 0) {
        printf("\nLocalizacao dos retangulos:\n");
        for (int i = 0; i < quantidadeRetangulos; i++) {
            Retangulo r = retangulos[i];
            printf("Retangulo %d: (%d, %d), Largura: %d, Altura: %d\n", i, r.x, r.y, r.largura, r.altura);
        }
    } else {
        printf("\nNao ha retangulos no momento.\n");
    }
    printf("\n");
}

int main() {
    char comando[100];
    
    // Loop principal para ler e interpretar os comandos até que o comando "sair" seja dado
    do {
        printf("Comandos disponiveis:\n\n");
        printf(" - create x,y+l,a: Cria um retangulo com o canto inferior esquerdo na posicao (x, y), largura 'l' e altura 'a'.\n\n");
        printf(" - moverRight x,y+p: Move o retangulo cujo canto inferior esquerdo esta na posicao (x, y) para a direita por 'p' posicoes.\n\n");
        printf(" - moverLeft x,y+p: Move o retangulo cujo canto inferior esquerdo esta na posicão (x, y) para a esquerda por 'p' posicoes.\n\n");
        printf(" - merge x1,y1+x2,y2: Une dois retangulos cujos cantos inferiores esquerdos estao nas posicoes (x1, y1) e (x2, y2).\n\n");
        
        printf("Digite um comando (ou 'sair' para encerrar): ");
        fgets(comando, sizeof(comando), stdin);
        
        comando[strcspn(comando, "\n")] = '\0';

        // Interpretar o comando
        int resultado = interpretarComando(comando);

        switch (resultado) {
            case SUCESSO:
                printf("Comando executado com sucesso.\n");
                break;
            case ERRO_ENTRADA_INVALIDA:
                printf("Erro: Posicoes fora dos limites permitidos.\n");
                break;
            case ERRO_MAXIMO_ATINGIDO:
                printf("Erro: Numero maximo de retangulos atingido.\n");
                break;
            case ERRO_RETANGULO_NAO_ENCONTRADO:
                printf("Erro: Retangulo nao encontrado na posição especificada.\n");
                break;
            case ERRO_SOBREPOSICAO:
                printf("Erro: Sobreposicao detectada com outro retangulo.\n");
                break;
            default:
                printf("Erro desconhecido.\n");
                break;
        }
        
        imprimirLocalizacaoRetangulos();
        
    } while (strcmp(comando, "sair") != 0);

    return 0;
}







