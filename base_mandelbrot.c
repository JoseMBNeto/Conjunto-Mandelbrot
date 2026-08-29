#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "base_mandelbrot.h"

double pixelParaReal (int coluna, int largura){
    const double minimo = -2.0;
    const double maximo = 1.0;

    double fracao = (double) coluna / ((double) largura - 1);
    double valor = minimo + fracao * (maximo - minimo);
    return valor;
}

double pixelParaImagem (int linha, int altura){
    const double minimo = -1.5;
    const double maximo = 1.5;

    double fracao = (double) linha / ((double) altura -1);
    double valor = minimo + fracao * (maximo - minimo);
    return valor;
}

int calculaIteracoes (double cReal, double cImagem, int maxIteracoes){
    double zReal = 0;
    double zImagem = 0;
    int iteracao = 0;

    while (iteracao < maxIteracoes && ((zReal * zReal) + (zImagem * zImagem)) <= 4){
        double novoReal = (zReal * zReal) - (zImagem * zImagem) + cReal;
        double novoImagem = 2 * zReal * zImagem + cImagem;

        zReal = novoReal;
        zImagem = novoImagem;
        iteracao++;
    }
    return iteracao;
}

int normaliza (int iteracoes, int maxIteracoes){
    double fracao = (double) iteracoes / (double) maxIteracoes;
    double valorQuebrado = fracao * 255;
    double valorArredondado = round(valorQuebrado);
    int valorInteiro = (int) valorArredondado;
    return valorInteiro;
}