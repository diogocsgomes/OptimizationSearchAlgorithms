#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void copia_matriz(int **orig, int **dest, int tam) {
    for (int i = 0; i < tam; i++)
        copia_array(orig[i], dest[i], tam);
}

void imprime_matriz(int **mat, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void copia_array(int *orig, int *dest, int tam) {
    for (int i = 0; i < tam; i++)
        dest[i] = orig[i];
}

void imprime_array(int *arr, int tam) {
    printf("{ ");
    for (int i = 0; i < tam - 1; i++)
        printf("%d, ", arr[i]);
    printf("%d }", arr[tam - 1]);
}

void innit_array(int *arr, int tam, int lim) {
    int aux;

    for (int i = 0; i < tam; i++) {
        do {
            aux = rand() % lim + 1;
        } while (find_element(arr, tam, aux) != -1);

        arr[i] = aux;
    }
}

int find_element(int *arr, int tam, int element) {
    for (int i = 0; i < tam; i++)
        if (arr[i] == element)
            return i;
    return -1;
}

int calcula_fit(const int *solucao, int n_elem, int **grafo, int dim) {
    int cont = 0;
    int e1, e2;

    for (int i = 0; i < n_elem - 1; i++) {
        e1 = solucao[i];
        for (int j = i + 1; j < n_elem; j++) {
            //e1 = solucao[i];
            e2 = solucao[j];

            if (e1 < 1 || e1 > dim ||
                e2 < 1 || e2 > dim)
                continue;

            if (grafo[e1 - 1][e2 - 1] == 1)
                cont++;
            // Equivalente a
            // cont += grafo[e1 - 1][e2 - 1];
        }
    }

    return cont;
}