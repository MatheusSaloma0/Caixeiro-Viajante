#ifndef GRAPH_H
#define GRAPH_H
 
#include <stdbool.h>
 
typedef struct node Node;
struct node{
    float x;
    float y;
};
 
typedef struct edge Edge;
struct edge{
    bool mst;
    short int n1;
    short int n2;
    int dist;
};
 
/* Com as coordenadas de dois nós, é calculada a distancia euclidiana entre eles.
 
* inputs: vetor de nós e a posição de dois nós nesse vetor
* output: inteiro representando a distancia entre os nós
* precondition: o vetor deve estar preenchido com os nós do grafo
* post-condition: o retorno corresponde a distancia euclidiana entre os dois nós
*/
int distance(Node* nodes, int c1, int c2);
 
/* Abstraindo uma matriz em que o elem Aij corresponde à distancia entre o nó i e o nó j
a função calcula a distancia entre todos os nós do grafo armazenando os resultados em um 
vetor de arestas (A distancia de um nó para si mesmo,que seria representado por um elemento 
da diagonal principal, é sempre considerado como zero).
 
* inputs: um vetor de nós, um vetor de arestas e a dimensão do grafo 
* output: nenhum
* precondition: o vetor de nós não deve estar vazio 
* post-condition: o vetor de arestas (do tipo Edge) foi preenchido corretamente a partir do
vetor de de nós  
*/
void findEdges(Node* nodes, int dimension, Edge* edges);
 
/* Essa função, necessária para a criação da mst, consiste em receber a posição de dois 
valores de uma estrutura de union-find e verificar se eles possuem o mesmo valor, isto é,
verificar se eles estão interligados.
 
* inputs: um vetor union-find de inteiros e dois inteiros que correspondem a posições no vetor 
* output: um inteiro
* precondition: nenhuma
* post-condition: a função 1 retorna se os elementos das posições a e b estão interligados e 0, 
caso contrário
*/
int ufFind(int a, int b, int* id);
 
/* Essa função, necessária para a criação da mst, interliga o elemento na posição a ao elemento 
na posição b.
 
* inputs: um vetor union-find, seu tamanho e a posição de dois elementos nesse vetor
* output: nenhum
* precondition: a e b devem estar dentro dos limites do vetor
* post-condition: a e todos os elementos que estão ligados a ele foram ligados a b
*/
void ufUnion(int a, int b, int* id, int size);
 
/* Com o vetor de arestas propriamente ordenado a partir da distância, a função forma a 
a árvore geradora minima do grafo utilizando as funções ufFind e ufUnion.
 
* inputs: um vetor de arestas, o tamanho desse vetor e o numero de nós do grafo
* output: nenhum
* precondition: o vetor de arestas deve estar ordenado
* post-condition: a mst foi criada
*/
void mstGenerator(Edge* edges, int numEdges, int dimension);
 
/* Essa função é responsável por criar a lista de adjacências para cada nó do grafo.
Essa estrutura consiste em um vetor de vetores onde o elemento adj[i][0] sempre será
utilizado auxiliarmente para determinar em que posição o próximo elemento da lista 
de adjcência em questão deve ser armazenado.
 
* inputs: um vetor de ponteiros, a lista de arestas e o número de arestas
* output: nenhum
* precondition: a lista de arestas ja passou pela mstGenerator
* post-condition: o vetor de ponteiros foi preenchida com a lista de adjcência
*/
void createAdjList(short int** adj,Edge* edges,int numEdges);
 
/* Essa função é responsável por liberar toda a memória alocada pela lista de adjcência.
 
* inputs: um vetor de ponteiros e sua dimensão 
* output: nenhum
* precondition: a lista de adjcência não é nula
* post-condition: toda a memória foi desalocada 
*/
void freeAdj(short int** adj, int dimension);
 
/* Uma busca primeiro em profundidade é realizada na lista de adjcência para determinar o
tour para a mst. Os resulados são escritos diretamente em um arquivo.tour
 
* inputs: uma lista de adjcências, a dimensão do grafo, um vetor auxiliar de inteiros, ponteiro para um
arquivo, e um inteiro que representa a lista que deve ser acessada
* output: nenhum
* precondition: a lista de adjacência está preenchida, o valor i passado inicialmente deve pertencer ao grafo
e o arquivo deve existir
* post-condition: o tour foi armazenado no arquivo dado como parâmetro 
*/
void depthFirstSearch (short int** adj, int dimension, short int* id, FILE* archive, int i);
 
/*Função de ordenação quick-sort adaptada para o problema de tsp
 
* inputs: um vetor de arestas e a primeira e última posição 
* output: nenhum
* precondition: O vetor de arestas não é nulo
* post-condition: o vetor foi ordenado a partir da distância das arestas 
*/
void quick_sort(Edge *a, int lo, int hi);
 
#endif
