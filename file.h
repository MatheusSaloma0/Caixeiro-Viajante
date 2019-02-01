#ifndef FILE_H
#define FILE_H
 
/* Função responsável por ler a dimensão do grafo e seu nome
 
* inputs: o ponteiro para um arquivo e uma string
* output: um inteiro
* precondition: o arquivo existe
* post-condition: o inteiro corresponde a dimensão do grafo e a string foi alterada com o nome da cidade
*/
int getName_Dimension (FILE* input,char* name);
 
/* A função lê um arquivo e armazena seus nós e suas coordenadas (x,y).
 
* inputs: ponteiro para um arquivo, lista de nós e a dimensão do grafo
* output: nenhum
* precondition: o arquivo existe
* post-condition: as coordenadas foram armazenadas corretamente no vetor de nós
*/
void readCoordenades (FILE* input, Node* nodes, int dimension);
 
/* Gera o arquivo .mst inicializando seu cabeçalho e imprimindo o conjunto de arestas.
 
* inputs: o nome do arquivo, um vetor de arestas e seu tamanho, a dimensão do grafo 
* output: nenhum
* precondition: o vetor de arestas está preenchido
* post-condition: um arquivo do tipo .mst foi criado
*/
void mstArchiveGenerator (char* name, Edge* edges, int numEdges, int dimension);
 
#endif
