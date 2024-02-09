#ifndef GENETICO_H
#define GENETICO_H
#include "TrepaColinas.h"
#include "utils.h"


typedef struct individual {
    int *solucao;
    int fitness;
} chrom, *pchrom;

typedef struct i {
    //tamanho da populacao
    int popsize;
    //numero de geracoes
    int n_gen;
    //probabilidade de mutacao
    int prob_mutation;
    //probabilidade de recombinacao
    int prob_crossover;
    //numero de vertices
    int n_vert;
    //num runs
    int k;
} info;

int innit_pop(pchrom *parents, pchrom *offspring, info d, int dim);

void calcula_fit_pop(pchrom pop, info d, int** grafo, int dim);

int algoritmo_genetico(info d, int** grafo, int dim, pchrom best_run,int escolha_crossover,int escolha_torneio, int escolha_mutacao);

void tournament(pchrom pop, info d, pchrom parents); // selecao por torneio

void tournament_by_average(pchrom pop, info d, pchrom parents); //selecao por elemento cujo fitness seja maior que  amedia de fitness's

void crossover(pchrom parents, info d, pchrom offspring); // recombinacao por "single point crossover"

void crossover2(pchrom parents, info d, pchrom offspring);// recombinacao por "two point crossover"

void mutation(pchrom offspring, info d); // mutacao por "bit flip"

void mutation_random_reset(pchrom offspring, info d); //mutacao por random resset

chrom get_best(pchrom pop, info d);

int trepa_colinas_ToHibrido(int *sol, int k, int **grafo, int dim, int num_iter);

int hibrido(info d, int** grafo, int dim, pchrom best_run, int hibrido_flag);

int hibrido_2(info d, int** grafo, int dim, pchrom best_run);

#endif