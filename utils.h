void copia_matriz(int** orig, int** dest, int tam);
void imprime_matriz(int **mat, int tam);

void copia_array(int* orig, int* dest, int tam);
void imprime_array(int* arr, int tam);

/**
 * Inicializa um array com valores aleatórios no intervalo [1, lim]
 * @param arr Array a inicializar
 * @param tam Tamanho do array
 * @param lim Limite superior dos valores a gerar
 */
void innit_array(int* arr, int tam, int lim);

int find_element(int* arr, int tam, int element);

/**
 * Calcula o número de arestas num conjunto de vértices
 * @param solucao Conjunto de vértices a considerar
 * @param n_elem Número de elementos da solução
 * @param grafo Grafo com as arestas que ligam a cada vértice
 * @param dim Dimensões do grafo
 * @return Devolve o número de arestas que ligam os vétices da soluçao
 */
int calcula_fit(const int *solucao, int n_elem, int **grafo, int dim);

