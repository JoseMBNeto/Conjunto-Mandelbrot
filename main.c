#include <stdio.h>
#include <stdlib.h>
#include "base_mandelbrot.h"
#include "serial.h"

#define LOGIN "jmbn"


int main(int argc, char *argv[]) {

    if (argc != 5){
        fprintf(stderr, "Digite uma quantidade válida de valores\n");
        return 1;
    }

    int largura = atoi(argv[1]);
    int altura = atoi(argv[2]);
    int maxIteracoes = atoi(argv[3]);
    int nummeroThreads = atoi(argv[4]);
    
    if (largura <= 0){
        fprintf(stderr, "O valor digitado precisa ser positivo e maior que 0\n");
        return 1;
    }

    if (altura <= 0){
        fprintf(stderr, "O valor digitado precisa ser positivo e maior que 0\n");
        return 1;
    }

    if (maxIteracoes <= 0){
        fprintf(stderr, "O valor digitado precisa ser positivo e maior que 0\n");
        return 1;
    }

    if (nummeroThreads <= 0){
        fprintf(stderr, "O valor digitado precisa ser positivo e maior que 0\n");
        return 1;
    }

    ArgumentosMandel argumentos;
    argumentos.largura = largura;
    argumentos.altura = altura;
    argumentos.maxIteracoes = maxIteracoes;
    argumentos.numeroThreads = nummeroThreads;
    argumentos.login = LOGIN;

    if (rodaSerial(argumentos) != 0){
        fprintf(stderr, "Não pode fazer a implementacao serial\n");
        return 1;
    }
    
    return 0;
}