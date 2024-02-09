#include <stdio.h>

#define LOG_PATH "../log.txt"

/**
 * Converte informação de um ficheiro numa matriz de binarios representativos das ligações entre os vértices
 * @param nome_fich Nome do ficheiro a ser lido
 * @param k Tamanho da solução final
 * @param vertices Número de vértices
 * @return Devolve uma matriz v*v com 1's e 0's representativos das ligações de cada vértice; ou NULL em caso de erro
 */
int **innit_dados(char nome_fich[], int *k, int *vertices);

/**
 * Escreve os titulos das colunas da tabela no ficheiro 'log.csv'
 * @param tam Tamanho da solução
 */
void escreve_colunas(int tam);

/**
 * Escreve os valores conseguidos numa iteracao
 * @param iter Número da iteração
 * @param arr Array com os valores
 * @param tam Tamanho do array
 */
void escreve_valores_fich(int iter, int *arr, int tam, int count);