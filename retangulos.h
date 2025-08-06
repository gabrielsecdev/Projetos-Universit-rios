#ifndef RETANGULOS_H
#define RETANGULOS_H

typedef struct {
    int x;       // Coordenada x do canto inferior esquerdo
    int y;       // Coordenada y do canto inferior esquerdo
    int largura;   // Largura do retângulo
    int altura;  // Altura do retângulo
} Retangulo;

void inicializarRetangulos();
int criarRetangulo(int x, int y, int largura, int altura);
int moverDireita(int x, int y, int posicoes);
int moverEsquerda(int x, int y, int posicoes);
void aplicarGravidade();
Retangulo* obterRetangulos(int* quantidade);
void alertaSobreposicao();
int mergePossivel(int x1, int y1, int x2, int y2);
void mergeRetangulos(int x1, int y1, int x2, int y2);
int encontrarRetangulo(int x, int y);

#endif // RETANGULOS_H