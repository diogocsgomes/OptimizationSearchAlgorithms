//
// Created by diogo on 20/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "TrepaColinas.h"
#include "files.h"
#include "utils.h"

int trepa_colinas_prob(int *sol, int k, int **grafo, int dim, int num_iter, int prob) {
    int custo, custo_viz;
    int *nova_sol = malloc(sizeof(int) * k);
    if (nova_sol == NULL) {
        printf("[ERRO] Nao foi possivel alocar memoria (solucao)\n");
        return 0;
    }

    escreve_colunas(k);

    // Avalia solucao inicial
    custo = calcula_fit(sol, k, grafo, dim);

    for (int i = 0; i < num_iter; i++) {
        // Gera vizinho

        gera_vizinho(sol, nova_sol, k, dim);
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, k, grafo, dim);

        // Aponta no ficheiro 'log.csv'
        escreve_valores_fich(i, sol, k, custo_viz);
        // Gera numero para simular aleatoriedade
        int r = rand() % 100;

        if (r < prob) {
            copia_array(nova_sol, sol, k);
            custo = custo_viz;
        } else {
            if (custo_viz >= custo) {
                copia_array(nova_sol, sol, k);
                custo = custo_viz;
            }
        }
    }
    escreve_valores_fich(num_iter, sol, k, custo);

    free(nova_sol);
    return custo;
}

void gera_vizinho(int *sol, int *nova_sol, int tam, int lim) {

    int aux, index = rand() % tam;

    copia_array(sol, nova_sol, tam);

    do {
        aux = rand() % lim + 1;
    } while (find_element(sol, tam, aux) != -1);

    nova_sol[index] = aux;
}
