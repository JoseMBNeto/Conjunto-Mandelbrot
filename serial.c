#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "serial.h"

int rodaSerial (ArgumentosMandel args){

    int **matriz = malloc(args.altura * sizeof(int *));
    if (matriz == NULL){
        fprintf (stderr, "Falha ao alocar memoria no serial\n");
        return -1;
    }

    for (int i = 0; i < args.altura; i++){
        matriz[i] = malloc(args.largura * sizeof(int));
        if (matriz[i] == NULL){
            fprintf(stderr, "Falha ao alocar memoria no serial\n");
            return -1;
        }
    }

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int i = 0; i < args.altura; i++){
        for (int j = 0; j < args.largura; j++){

            double cReal = pixelParaReal (j, args.largura);
            double cImagem = pixelParaImagem (i, args.altura);

            int iteracoes = calculaIteracoes(cReal, cImagem, args.maxIteracoes);

            matriz[i][j] = normaliza(iteracoes, args.maxIteracoes);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double duracao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    char nomeArquivo[100];
    sprintf(nomeArquivo, "mandelbrot_%s_serial.pgm", args.login);

    if (escreverPgm(nomeArquivo, matriz, args.largura, args.altura) != 0){
        fprintf(stderr, "Falha em escrever no arquivo pgm serial\n");
        return -1;
    }

    FILE *arquivoTempo = fopen ("times.txt", "a");
    if (arquivoTempo == NULL){
        fprintf(stderr, "Erro ao abrir o times.txt no serial\n");
        return -1;
    }

    fprintf(arquivoTempo, "Serial: %fs\n", duracao);
    fclose(arquivoTempo);

    for (int i = 0; i < args.altura; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}