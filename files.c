#include <stdlib.h>
#include <string.h>
#include "files.h"

int **innit_dados(char nome_fich[], int *k, int *vertices) {
    int **grafo, arestas, e[2];
    char edge[5], c, *p;
    char path[100] = "../";
    strcat(path, nome_fich);

    FILE *f = fopen(path, "rt");

    if (f == NULL) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    //Ler  num k vertices

    fscanf(f, "%c %d", &c, k);

    // c time elapsed
    // chat gpt
    //printf("%s %d",aux,*k);

    //Ler vertices arestas
    fscanf(f, " %c %s %d %d", &c, edge, vertices, &arestas);

    // printf("teste %d",*arestas);
    grafo = malloc(sizeof(int *) * (*vertices));
    if (grafo == NULL) {
        printf("[ERRO] Nao foi possivel alocar memoria (grafo)\n");
        return NULL;
    }

    for (int i = 0; i < *vertices; i++) {
        grafo[i] = (int *) malloc(sizeof(int) * (*vertices));
        if (grafo[i] == NULL) {
            printf("[ERRO] Nao foi possivel alocar memoria(grafo[%d])\n", i);
            return NULL;
        }

        for (int j = 0; j < *vertices; j++)
            grafo[i][j] = 0;
    }

    //    printf("grafo: \n");
    for (int i = 0; i < arestas; i++) {
        fscanf(f, " %c %d %d", &c, &e[0], &e[1]);
        //printf(" %d %d\n",e[0], e[1]);
        grafo[e[0] - 1][e[1] - 1] = 1;
        //grafo[e[1] - 1][e[0] - 1] = 1;
    }

    fclose(f);
    return grafo;
}

void escreve_valores_fich(int iter, int *arr, int tam, int count) {
    FILE *f = fopen(LOG_PATH, "a+");

    if (f == NULL) {
        printf("[ERRO][Valores] Nao foi possivel abrir o ficheiro '%s'\n", LOG_PATH);
        exit(1);
    }

    fprintf(f, "%d\t", iter);
    for (int i = 0; i < tam; i++)
        fprintf(f, "%d\t", arr[i]);
    fprintf(f, "%d\n", count);

    fclose(f);
}

void escreve_colunas(int tam) {
    FILE *f = fopen(LOG_PATH, "a+");

    if (f == NULL) {
        printf("[ERRO][Colunas] Nao foi possivel abrir o ficheiro '%s'\n", LOG_PATH);
        exit(1);
    }

    fprintf(f, "\nIteracao\t");

    for (int i = 0; i < tam; i++)
        fprintf(f, "Valor %d\t", i + 1);

    fprintf(f, "Custo\n");

    fclose(f);
}
