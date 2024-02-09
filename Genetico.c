#include "Genetico.h"
#include "utils.h"
#include "files.h"
#include <stdlib.h>
#include <stdio.h>


int innit_pop(pchrom *parents, pchrom *offspring, info d, int dim) {
    // Inicialisar memória
    *parents = malloc(sizeof(chrom) * d.popsize);
    if (*parents == NULL) {
        printf("[ERRO] Nao foi possivel alocar memoria (*parents)\n");
        return 0;
    }

    *offspring = malloc(sizeof(chrom) * d.popsize);
    if (*offspring == NULL) {
        printf("[ERRO] Nao foi possivel alocar memoria (*offspring)\n");
        return 0;
    }

    for (int i = 0; i < d.popsize; i++) {
        (*offspring)[i].solucao = malloc(sizeof(int) * d.k);
        if ((*offspring)[i].solucao == NULL) {
            printf("[ERRO] Nao foi possivel alocar memoria ((*offspring)[%d])\n", i);
            return 0;
        }
        innit_array((*offspring)[i].solucao, d.k, dim);

        (*parents)[i].solucao = malloc(sizeof(int) * d.k);
        if ((*parents)[i].solucao == NULL) {
            printf("[ERRO] Nao foi possivel alocar memoria (*parents)[%d])\n", i);
            return 0;
        }
    }

    return 1;
}

void calcula_fit_pop(pchrom pop, info d, int **grafo, int dim) {
    for (int i = 0; i < d.popsize; i++)
        pop[i].fitness = calcula_fit(pop[i].solucao, d.k, grafo, dim);
}

int algoritmo_genetico(info d, int **grafo, int dim, pchrom best_run,int escolha_crossover,int escolha_torneio, int escolha_mutacao) {
    pchrom parents = NULL, offspring = NULL;
    chrom new_run;

    if (!innit_pop(&parents, &offspring, d, dim))
        return -1;

    escreve_colunas(d.k);

    calcula_fit_pop(offspring, d, grafo, dim); //calcular o fitness do filho
    *best_run = offspring[0];
    escreve_valores_fich(0, best_run->solucao, d.k, best_run->fitness);

    for (int i = 1; i <= d.n_gen; i++) {
        if(escolha_torneio == 1)
            tournament(offspring, d, parents);
        else
            tournament_by_average(offspring, d, parents);

        // genetic operations
        if(escolha_crossover == 1)
            crossover(parents, d, offspring);//single point
        else
            crossover2(parents, d, offspring); //double point

        if(escolha_mutacao == 1)
            mutation(offspring, d);
        else
            mutation_random_reset(offspring,d);


        calcula_fit_pop(offspring, d, grafo, dim);
//        best_run = get_best(offspring, d);
        // Para não obter um best_run pior do que o anteriormente guardado
        new_run = get_best(offspring, d);


        if (new_run.fitness > best_run->fitness) {
            copia_array(new_run.solucao, best_run->solucao, d.k);
            best_run->fitness = new_run.fitness;
        }

        escreve_valores_fich(i, best_run->solucao, d.k, best_run->fitness);
    }

    // Libertar memória
    free(parents);
    free(offspring);

    return best_run->fitness;
}

void tournament(pchrom pop, info d, pchrom parents) {
    int i, x1, x2;

    // Realiza popsize torneios
    for (i = 0; i < d.popsize; i++) {
        x1 = rand() % d.popsize;
        do
            x2 = rand() % d.popsize;
        while (x1 == x2);
        if (pop[x1].fitness > pop[x2].fitness)        // Problema de maximizacao
            parents[i] = pop[x1];
        else
            parents[i] = pop[x2];
    }
}

void tournament_by_average(pchrom pop, info d, pchrom parents){
    //avalia a media de fitness, seleciona um pop aleatorio desde que o seu fitness seja maior que a media
    int avg = 0;
    int indice_pop;
    for(int i = 0; i < d.popsize; i++)
    {
        avg += pop->fitness;
    }
    avg = avg/d.popsize;
    for(int i = 0; i < d.popsize; i++) {
        do {
            indice_pop = rand() % d.popsize;
        } while (pop[indice_pop].fitness < avg);
        parents[i] = pop[indice_pop];
    }


}

void crossover(pchrom parents, info d, pchrom offspring) {
    for (int i = 0; i < d.popsize; i += 2) {
        if (rand() % 100 < d.prob_crossover) {
            int index = (rand() % d.k - 2) + 1;

            // Copiar primeira parte da solução do 1o pai para o 1o filho
            // Copiar primeira parte da solução do 2o pai para o 2o filho
            for (int j = 0; j < index; ++j) {
                offspring[i].solucao[j] = parents[i].solucao[j];
                offspring[i + 1].solucao[j] = parents[i + 1].solucao[j];
            }

            // Copiar segunda parte da solução do 2o pai para o 1o filho
            // Copiar segunda parte da solução do 1o pai para o 2o filho
            for (int j = index; j < d.k; ++j) {
                offspring[i].solucao[j] = parents[i + 1].solucao[j];
                offspring[i + 1].solucao[j] = parents[i].solucao[j];
            }
        } else {
            /*for (int j = 0; j < d.k; ++j) {
                //offspring[i].solucao[j] = parents[i].solucao[j];
                //offspring[i + 1].solucao[j] = parents[i + 1].solucao[j];}*/
                offspring[i] = parents[i];
                offspring[i + 1] = parents[i];




        }
    }
}

void crossover2(pchrom parents, info d, pchrom offspring){
    int point1,point2,dummy;
    for(int i = 0; i < d.popsize; i += 2)
    {
        if(rand() % 100 < d.prob_crossover)
        {
            point1 = rand() % d.popsize;
            point2 = rand() % d.popsize;
            while (point2 == point1)
            {
                point2 = rand() % d.popsize;
            }
            if(point2 < point1)
            {
                dummy = point1;
                point1 = point2;
                point2 = dummy;
            }
            //inicializa os filhos iguais ao pais
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];

            //altera  aparte central
            for(int j = point1; j < point2; j++)
            {

                offspring[i].solucao[j] = parents[i + 1].solucao;
                offspring[i + 1].solucao[j] = parents[i].solucao[j];
            }

        } else
        {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}

void mutation(pchrom offspring, info d) {
    int aux;

    for (int i = 0; i < d.popsize; i++) {
        for (int j = 0; j < d.k; j++) {
            if (rand() % 100 < d.prob_mutation) {
                do {
                    aux = rand() % d.n_vert + 1;
                } while (find_element(offspring[i].solucao, d.k, aux) != -1);

                offspring[i].solucao[j] = aux;
            }
        }
    }
}

void mutation_random_reset(pchrom offspring, info d){
    int aux;
    int x1,x2;

    for(int i = 0; i < d.popsize; i++)
    {
        int x1 = rand() % d.popsize;
        if (rand() % 100 < d.prob_mutation) {

            do {
                x2 = rand() % d.n_vert + 1;
            } while (find_element(offspring[i].solucao, d.k, x2) != -1);
        }

            offspring[i].solucao[x1] = x2;
    }
}


chrom get_best(pchrom pop, info d) {
    int bestfit = -1;
    chrom best;

    for (int i = 0; i < d.popsize; i++) {
        if (bestfit < pop[i].fitness)
            best = pop[i];
    }
    return best;
}

int hibrido(info d, int** grafo, int dim, pchrom best_run, int hibrido_flag){
    pchrom parents = NULL, offspring = NULL;
    chrom new_run;

    if (!innit_pop(&parents, &offspring, d, dim))
        return -1;

    escreve_colunas(d.k);

    calcula_fit_pop(offspring, d, grafo, dim); //calcular o fitness do filho
    if(hibrido_flag == 1)
    {
        for(int i = 0; i < d.popsize; i++)
        {
            offspring[i].fitness = trepa_colinas_prob(offspring[i].solucao, d.k, grafo, dim, 100, 0);
        }
    }
    *best_run = offspring[0];
    escreve_valores_fich(0, best_run->solucao, d.k, best_run->fitness);

    for (int i = 1; i <= d.n_gen; i++) {

            tournament(offspring, d, parents);


        // genetic operations

            crossover(parents, d, offspring);//single point



            mutation(offspring, d);



        calcula_fit_pop(offspring, d, grafo, dim);
//        best_run = get_best(offspring, d);
        // Para não obter um best_run pior do que o anteriormente guardado
        new_run = get_best(offspring, d);


        if (new_run.fitness > best_run->fitness) {
            copia_array(new_run.solucao, best_run->solucao, d.k);
            best_run->fitness = new_run.fitness;
        }

        escreve_valores_fich(i, best_run->solucao, d.k, best_run->fitness);
    }
    if(hibrido_flag == 2) {
        for (int i = 0; i < d.popsize; i++) {
            int aux = trepa_colinas_prob(offspring[i].solucao, d.k, grafo, dim, 100, 0);
            if (aux > best_run->fitness) {
                best_run->fitness = aux;
                copia_array(offspring[i].solucao, best_run->solucao, d.k);
            }

        }
    }

    // Libertar memória
    free(parents);
    free(offspring);



    return best_run->fitness;
}

int hibrido_2(info d, int** grafo, int dim, pchrom best_run){}

int trepa_colinas_ToHibrido(int *sol, int k, int **grafo, int dim, int num_iter){
    return 0;
}