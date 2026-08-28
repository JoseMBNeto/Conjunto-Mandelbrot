#ifndef BASE_MANDELBROT_H
#define BASE_MANDELBROT_H

typedef struct ArgumentosMandel{
    int largura;
    int altura;
    int maxIteracoes;
    int numeroThreads;
    const char *login;
}ArgumentosMandel;

double pixelParaReal (int coluna, int largura);
double pixelParaImagem (int linha, int altura);
int calculaIteracoes (double cReal, double cImagem, int maxIteracoes);
int normaliza (int iteracoes, int maxIteracoes);
int escreverPgm (const char *nomeArquivo, int **matriz, int largura, int altura);

#endif