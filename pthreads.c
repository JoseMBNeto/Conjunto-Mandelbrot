#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "pthreads.h"

typedef struct DadosThread {
    int linhaInicio;
    int linhaFim;
    int passo;
    ArgumentosMandel args;
    int **matriz;
}DadosThread;

void *calculaBloco (void *arg){
    DadosThread *dados = (DadosThread *) arg;

    for (int i = dados->linhaInicio; i < dados->linhaFim; i++){
        for (int j = 0; j < dados->args.largura; j++){
            double cReal = pixelParaReal(j, dados->args.largura);
            double cImagem = pixelParaImagem(i, dados->args.altura);
            int iteracoes = calculaIteracoes(cReal, cImagem, dados->args.maxIteracoes);
            dados->matriz[i][j] = normaliza(iteracoes, dados->args.maxIteracoes);
        }
    }
    return NULL;
}

void *calculaIntercalado (void *arg){
    DadosThread *dados = (DadosThread *) arg;

    for (int i = dados->linhaInicio; i< dados->args.altura; i += dados->passo){
        for (int j = 0; j < dados->args.largura; j++){
            double cReal = pixelParaReal(j, dados->args.largura);
            double cImagem = pixelParaImagem(i, dados->args.altura);
            int iteracoes = calculaIteracoes(cReal, cImagem, dados->args.maxIteracoes);
            dados->matriz[i][j] = normaliza(iteracoes, dados->args.maxIteracoes);
        }
    }
    return NULL;
}

int rodaPthreads1 (ArgumentosMandel args){
    int **matriz = malloc(args.altura * sizeof(int *));
    if (matriz == NULL){
        fprintf (stderr, "Falha ao alocar memoria no Pthread1\n");
        return -1;
    }

    for (int i = 0; i < args.altura; i++){
        matriz[i] = malloc(args.largura * sizeof(int));
        if (matriz[i] == NULL){
            fprintf(stderr, "Falha ao alocar memoria no Pthread1\n");
            return -1;
        }
    }

    pthread_t thread[args.numeroThreads];
    DadosThread dados[args.numeroThreads];
    int linhasPThread = args.altura / args.numeroThreads;
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int t = 0; t < args.numeroThreads; t++){
        dados[t].linhaInicio = t * linhasPThread;

        if (t == args.numeroThreads -1){
            dados[t].linhaFim = args.altura;
        }else {
            dados[t].linhaFim = (t + 1) * linhasPThread;
        }
        
        dados[t].args = args;
        dados[t].matriz = matriz;
        pthread_create(&thread[t], NULL, calculaBloco, &dados[t]);
    }

    for (int t = 0; t < args.numeroThreads; t++){
        pthread_join(thread[t], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double duracao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    char nomeArquivo[100];
    sprintf(nomeArquivo, "mandelbrot_%s_pthreads1.pgm", args.login);

    if (escreverPgm(nomeArquivo, matriz, args.largura, args.altura) != 0){
        fprintf(stderr, "Falha em escrever no arquivo pgm Pthread1\n");
        return -1;
    }

    FILE *arquivoTempo = fopen ("times.txt", "a");
    if (arquivoTempo == NULL){
        fprintf(stderr, "Erro ao abrir o times.txt no Pthreads1\n");
        return -1;
    }

    fprintf(arquivoTempo, "Pthreads1: %fs\n", duracao);
    fclose(arquivoTempo);

    for (int i = 0; i < args.altura; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

int rodaPthreads2 (ArgumentosMandel args){
    int **matriz = malloc(args.altura * sizeof(int *));
    if (matriz == NULL){
        fprintf (stderr, "Falha ao alocar memoria no Pthread2\n");
        return -1;
    }

    for (int i = 0; i < args.altura; i++){
        matriz[i] = malloc(args.largura * sizeof(int));
        if (matriz[i] == NULL){
            fprintf(stderr, "Falha ao alocar memoria no Pthread2\n");
            return -1;
        }
    }

    pthread_t thread[args.numeroThreads];
    DadosThread dados[args.numeroThreads];
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int t = 0; t < args.numeroThreads; t++){
        dados[t].linhaInicio = t;
        dados[t].passo = args.numeroThreads;
        dados[t].args = args;
        dados[t].matriz = matriz;
        pthread_create(&thread[t], NULL, calculaIntercalado, &dados[t]);
    }

    for (int t = 0; t < args.numeroThreads; t++){
        pthread_join(thread[t], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double duracao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    char nomeArquivo[100];
    sprintf(nomeArquivo, "mandelbrot_%s_pthreads2.pgm", args.login);

    if (escreverPgm(nomeArquivo, matriz, args.largura, args.altura) != 0){
        fprintf(stderr, "Falha em escrever no arquivo pgm Pthread2\n");
        return -1;
    }

    FILE *arquivoTempo = fopen ("times.txt", "a");
    if (arquivoTempo == NULL){
        fprintf(stderr, "Erro ao abrir o times.txt no Pthreads2\n");
        return -1;
    }

    fprintf(arquivoTempo, "Pthreads2: %fs\n", duracao);
    fclose(arquivoTempo);

    for (int i = 0; i < args.altura; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}