/**
 * Algoritmo Trepa-Colinas
 * @param sol Array onde vai ficar guardada a solução
 * @param k Número de elementos da solução
 * @param grafo Grafo com as arestas que ligam a cada vértice
 * @param dim Dimensões do grafo
 * @param num_iter Número de iterações
 * @param prob Probabilidade de mutação
 * @return Devolve o custo da melhor solução encontrada
 */
int trepa_colinas_prob(int *sol, int k, int **grafo, int dim, int num_iter, int prob);

/**
 * Gera um novo vizinho aleatório
 * @param sol Solução original
 * @param nova_sol Solução a ser gerada
 * @param tam Tamanho dos arrays sol e nova_sol
 */
void gera_vizinho(int *sol, int *nova_sol, int tam, int lim);
