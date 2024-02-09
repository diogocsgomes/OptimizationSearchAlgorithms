//
// Created by diogo on 20/12/2022.
//

#include "TrepaColinas.h"
#include "Genetico.h"
#include "utils.h"
#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void testes(){

}


int main(int argc, char *argv[]) {
    char nome_fich[100];
    int k, custo, vertices, opcao, prob, num_runs, num_iter;
    int escolha_crossover; // para escolher o crossover a usar
    int escolha_torneio; // para escolher o torneio a usar
    int escolha_mutacao; // para  escolher a mutacao
    int hibrdo_flag; //para escolher a posicao  do hibrido
    float mbf = 0.0f;
    int **grafo, *solucao;
    info d = {0};
    pchrom best_run = NULL;

    remove(LOG_PATH);
    // Inicializar random
    srand(time(NULL));

    printf("Nome do ficheiro: ");
    scanf("%99[^\n]", nome_fich);

    // Inicializar grafo (através do ficheiro)
    grafo = innit_dados(nome_fich, &k, &vertices);
    if (grafo == NULL) {
        printf("[ERRO] Nao foi possivel alocar memoria (grafo)\n");
        return 0;
    }

    // Inicializar solucao
    solucao = malloc(sizeof(int) * k);
    if (solucao == NULL) {
        printf("[ERRO] Nao foi possivel alocar memoria (solucao)\n");
        return 0;
    }
    innit_array(solucao, k, vertices);

//    printf("Grafo:\n");
//    imprime_matriz(grafo, vertices);
//    printf("\nSolucao inicial: ");
//    imprime_array(solucao, k);
//    printf("\n\n");

    // Menu
    do {
        printf(" 1- Algoritmo Trepa Colinas\n 2- Algoritmo Trepa Colinas Probabilistico\n 3- Algoritmo Genetico\n 4- Algoritmo Hibrido\n opcao: ");
        scanf("%d", &opcao);
    } while (opcao < 1 || opcao > 4);


    do {
        printf("Numero de testes: ");
        scanf("%d", &num_runs);
    } while (opcao <= 0);

    do {
        printf("Quantas iteracoes deseja fazer: ");
        scanf("%d", &num_iter);
    } while (opcao <= 0);

    if (opcao == 2) { // Probabilistico
        do {
            printf("Qual a probabilidade de evoluir (0 - 100%%): ");
            scanf("%d", &prob);
        } while (prob < 0 || prob >= 100);
    } else if (opcao == 3 || opcao == 4) { // Genetico
        best_run = malloc(sizeof(chrom));
        if (best_run == NULL) {
            printf("[ERRO] Nao foi possivel alocar memoria (best_run)\n");
            return 0;
        }

        do {
            printf("Qual o tamanho da populacao: ");
            scanf("%d", &d.popsize);
        } while (d.popsize <= 0);
        do {
            printf("Qual o numero de geracoes: ");
            scanf("%d", &d.n_gen);
        } while (d.n_gen <= 0);
        do {
            printf("Qual a probabilidade de recombinacao (0 - 100%%): ");
            scanf("%d", &d.prob_crossover);
        } while (d.prob_crossover < 0 || d.prob_crossover >= 100);
        do {
            printf("Qual a probabilidade de mutacao (0 - 100%%): ");
            scanf("%d", &d.prob_mutation);
        } while (d.prob_mutation < 0 || d.prob_mutation >= 100);


        if(opcao == 3) {
            do {
                printf("\nQual algoritmo de recombinacao gostaria de utilizar: \n1- Single point crossover\n2- Two point crossover");
                scanf("%d", &escolha_crossover);
            } while (escolha_crossover < 1 || escolha_crossover > 2);
            do {
                printf("\nQual o torneio que deseja usar: \n1- Torenio de concorrecnia entre dois elementos\n2- Torneio que escolha um elemento cujo fitness seja superio a media");
                scanf("%d", &escolha_torneio);
            } while (escolha_torneio < 1 || escolha_torneio > 2);
            do {
                printf("\nQue tipo de mutacao vai desejar:\n1- Mutacao bit flip\n2- Muracao random reset ");
                scanf("%d", &escolha_mutacao);
            } while (escolha_mutacao < 1 || escolha_mutacao > 2);
        }

        if(opcao == 4)
        {
            do {
                printf("\nOnde deseja que o trepa colinas acione:\n1- Inicio do genetico \n2- Fim do genetico");
                scanf("%d",&hibrdo_flag);
            } while (hibrdo_flag < 1 || hibrdo_flag > 2);
        }
        d.k = k;
        d.n_vert = vertices;
    }
    //int array_solucoes[num_runs][d.k];
    //int indicie_mais_alto = 0;
    //int custo_aux = 0;
    for (int i = 0; i < num_runs; i++) {
        switch (opcao) {
            case 1:
                //Funcao Trepa Colinas

                custo = trepa_colinas_prob(solucao, k, grafo, vertices, num_iter, 0);
                mbf += (float)custo;
                break;
            case 2:
                //Funcao Trepa Colinas Probabilistico
                if(num_runs == 0)
                    prob = 5;
                if(num_runs == 1)
                    prob = 10;
                if(num_runs == 2)
                    prob = 15;
                if(num_runs == 3)
                    prob = 20;
                if(num_runs == 4)
                    prob = 50;

                custo = trepa_colinas_prob(solucao, k, grafo, vertices, num_iter, prob);
                mbf += (float)custo;
                innit_array(solucao, k, vertices);
                break;
            case 3:
                if(num_runs == 0)
                {
                    d.prob_crossover = 80;
                    d.prob_mutation = 20;
                }
                if(num_runs == 1)
                {
                    d.prob_crossover = 20;
                    d.prob_mutation = 80;
                }
                if(num_runs == 3)
                {
                    d.prob_crossover = 50;
                    d.prob_mutation = 50;
                }
                if(num_runs == 4)
                {
                    d.prob_crossover = 25;
                    d.prob_mutation = 25;
                }
                if(num_runs == 5)
                {
                    d.prob_crossover = 75;
                    d.prob_mutation = 75;
                }


                //Algorimto Genetico
                custo = algoritmo_genetico(d, grafo, vertices, best_run,escolha_crossover,escolha_torneio,escolha_mutacao);
                mbf += (float)custo;

                break;
            case 4:
                //Algoritmo Hibrido
               custo = hibrido(d,grafo,vertices,best_run,hibrdo_flag);
               mbf += (float)custo;
                break;
        }
        if (opcao == 3 || opcao == 4)
            copia_array(best_run->solucao, solucao, k);

        printf("Solucao %d: ", i + 1);
        imprime_array(solucao, k);
        printf(", numero de arestas = %d\n", custo);

        /*for(int j = 0; j < d.k; j++)
        {
            array_solucoes[i][j] = *(solucao)+ j;
        }
        if(custo > custo_aux)
        {
            custo_aux = custo;
            indicie_mais_alto = i;
        }*/
    }

    mbf /= (float) num_runs;
    printf("\nMBF = %.2f\n", mbf);

    /*printf("\nMelhor solucao encontrada: ");
    for(int i = 0; i < d.k; i++)
    {
        printf(" %d",array_solucoes[indicie_mais_alto][i]);
    }*/


    if (opcao == 3 || opcao == 4)
        free(best_run);
    free(solucao);

    return 0;
}




/*
 * TREPA COLINAS
 *
 * VARIAVEIS:
 *  vertice   numero_iteracoes   k   runs    custo   melhor_custo  MBF(media best fitness)
 *
 *
 * PONTEIROS(variaveis):
 *  grafo(array dinamico)2colunas e x linhas         solucao(array dinamico)2colunas e x linhas     melhor_solucao(array dinamico)2colunas e x linhas
 *
 *
 * Estrategia do Algoritmo
 *  1 Preencher o grafo atraves do ficheiro de texto
 *  2 Gerar uma solucao inicial (colocar a mesma no array solucao) copiar valores para melhor_solucao (1 ITERACAO)
 *  3 Avaliar o custo ###
 *  4 Incrementar o MBF
 *  5 No final do ciclo avaliar se o best custo e melhor que o novo custo(custo)
 *  6 Dispor a informacao Final
 *  7 Desalocar a memoria alocada
 *
 * Funcoes necessarias
 * Ponto 1: funcao para ler o ficheiro de texto e armazenar a info no array grafo;
 * Ponto 2: funcao para gerar um solucao inical
 * Ponto 3: funcao trepaColinas (toda esta funcao tem mais funcoes associadas, gera vizinho,por exemplo, as mesmas irao ser faladas mais abaixo)###
 * Ponto 5: funcao para substituir os valores do array best_custo pelos valores do array custo
 * Ponto 6: funcao para dispor a informacao
 *
 *
 *
 *  FUNCAO TREPA COLINAS ###
 *  Variaveis: array nova_sol   custo   custo_vizinho
 *
 *  Estrategia
 *  1 alocar a nova_sol
 *  2 avaliar o custo da solucao inicial (calcular o fitness)
 *  3 Criar um ciclo  com n repeticoes {
 *  4 Gerar vizinho
 *  5 Avaliar o custo deste vizinho
 *  6 Comparar o custo_vizinho com o custo, caso o custo vizinho seja maior o nosso custo sera igual ao custo vizinho
 *  8 Desalocar a memoria
 *  toda esta funcao retorna o custo
 *
 *
 *  Funcoes necessarias
 *  Ponto 2: funcao para calcular o fitness
 *  Ponto 4: Funcao para gerar vizinho
 *  Ponto 6: Funcao para substituir o grafo inicial pelo grafo vizinho
 *
 * */

/*
  a b c d
a 0 1 1 0
b 1 0 0 1
c 1 0 0 0
d 0 1 0 0
 */