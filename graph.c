#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "graph.h"
 
int distance(Node* nodes, int c1, int c2){
    int x = nodes[c1].x - nodes[c2].x;  //A diferença entre os valores de x e y
    int y = nodes[c1].y - nodes[c2].y;  //são calculadas e posteriormente utilizadas
    return round(sqrt(x*x + y*y));          // no cálculo da distância euclidiana que é arredondada 
}                                                                           // para que o valor seja sempre um inteiro
 
void findEdges(Node* nodes, int dimension, Edge* edges){
  int pos = 0;
  for (int i = 1; i < dimension; i++){               //Abstrai-se uma matriz triagular superior
    for (int j = i+1; j<=dimension; j++){            //com exceção da diagonal principal 
      edges[pos].n1 = i;                                            //o nome dos nós é adicionado a struct Edge
      edges[pos].n2 = j;                                        
      edges[pos].dist = distance(nodes,i,j);    //E a distancia entre eles é calculada
      edges[pos].mst = false;       //Inicialmente nenhum deles pertence a mst,logo, esse campo é setado com false
      pos++;    // Após uma aresta ser adicionada a variável pos é incrementada
    }
  }
}
 
int ufFind(int a, int b, int* id){
    return (id[a] == id[b]);    
}
 
void ufUnion(int a, int b, int* id, int size){
    int change = id[a];
    for (int i = 0; i <= size; i++){
        if (id[i] == change){
            id[i] = id[b];
        }
    }
}
 
void mstGenerator(Edge* edges, int numEdges, int dimension){
    int pos = 0;
  int id[dimension+1];
  for (int i = 0; i <= dimension; i++){ //Inicializando o vetor Union-Find
    id[i] = i;
  }
    for(int i = 0; i < numEdges; i++){
    if (pos >= dimension-1) break;  //A mst possui |numNos|-1 arestas
        if (!(ufFind(edges[i].n1, edges[i].n2, id))){ //Caso não exista caminho entre os nós de uma determinda
            ufUnion(edges[i].n1, edges[i].n2, id, dimension); //aresta na mst, a aresta é adicionada
      edges[i].mst = true;
            pos++;
        }
    }
}
 
void createAdjList(short int** adj,Edge* edges,int numEdges){
  for(int i = 0; i < numEdges; i++){
    if(edges[i].mst == true) {  //Caso a aresta pertença a mst a posição adj[x][0] é incrementa para indicar
            adj[edges[i].n1][0]++;      //a posição correta em que o próximo elemento deve ser inserido
        adj[edges[i].n1][adj[edges[i].n1][0]] = edges[i].n2;
         
            //Esse processo é feito considerando n2 como pertencente a lista de adjcência de n1 e vice-versa    
            adj[edges[i].n2][0]++;      
        adj[edges[i].n2][adj[edges[i].n2][0]] = edges[i].n1;
    }
  }
}
 
void freeAdj(short int** adj, int dimension){
  for(int i = 0; i <dimension+1; i++){
    free(adj[i]);   //Inicialmente cada vetor(lista de adjacência é liberada)
  }
  free(adj);        // E por fim, o vetor de ponteiros é liberado
}
 
void depthFirstSearch (short int** adj, int dimension, short int* id, FILE* archive, int i){
    short int n;
    n = adj[i][0];
    for (int j = 1; j<=n; j++){
        if (id[adj[i][j]] != 1){
            id[adj[i][j]] = 1;
            fprintf(archive,"%d\n",adj[i][j]);
            depthFirstSearch(adj,dimension,id,archive,adj[i][j]);
        }
    }
}
 
void quick_sort(Edge *a, int lo, int hi) {
  int i, j;
  Edge x, y;
      
  i = lo;
  j = hi;
  x = a[(lo + hi) / 2];
      
  while(i <= j) {
    while(a[i].dist < x.dist && i < hi) {
      i++;
    }
    while(a[j].dist > x.dist && j > lo) {
      j--;
    }
    if(i <= j) {
      y = a[i];
      a[i] = a[j];
      a[j] = y;
      i++;
      j--;
    }
  }
      
  if(j > lo) {
    quick_sort(a, lo, j);
  }
  if(i < hi) {
    quick_sort(a, i, hi);
  }
}
