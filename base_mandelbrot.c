#include <stdio.h>
#include <stdlib.h>
#include "base_mandelbrot.h"

double pixelParaReal (int coluna, int largura){
    const double minimo = -2.0;
    const double maximo = 1.0;

    double fracao = (double) coluna / (double) largura - 1;
    double valor = minimo + fracao * (maximo - minimo);
    return valor;
}

double pixelParaImagem (int linha, int altura){
    const double minimo = -1.5;
    const double maximo = 1.5;

    double fracao = (double) linha / (double) altura - 1;
    double valor = minimo + fracao * (maximo - minimo);
    return valor;
}