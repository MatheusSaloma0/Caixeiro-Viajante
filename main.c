#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph.h"
#include "file.h"
 
int main(int argc, char* argv[]){
  clock_t a;
  clock_t b;
  clock_t init = clock();
  float tempo;
 
    char name[25];
  FILE* input = fopen(argv[1],"r");
  int dimension = getName_Dimension(input,name);
 
    Node* nodes = malloc((dimension+1)*sizeof(Node));
  a = clock();
    readCoordenades(input,nodes,dimension);
  b = clock();
  tempo = (b - a) / (float)CLOCKS_PER_SEC;
  printf("LEITURA DA ENTRADA: %f s\n",tempo);
    fclose(input);
 
  int numEdges = ((dimension*dimension)-dimension)/2;
  Edge* edges = malloc(numEdges*sizeof(Edge));
  a = clock();
  findEdges(nodes,dimension,edges);
  b = clock();
  tempo = (b - a) / (float)CLOCKS_PER_SEC;
  printf("ENCONTRAR ARESTAS: %f s\n",tempo);
  free(nodes);
 
  a = clock();
  quick_sort(edges,0,numEdges-1);
  b = clock();
  tempo = (b - a) / (float)CLOCKS_PER_SEC;
  printf("QSORT: %f s\n",tempo);
 
  a = clock();
    mstGenerator(edges,numEdges,dimension);
  b = clock();
  tempo = (b - a) / (float)CLOCKS_PER_SEC;
  printf("CALCULAR MST: %f s\n",tempo);
  
  int pesomst=0;
  for(int i = 0; i<numEdges;i++){
    if(edges[i].mst == true){
      pesomst+=edges[i].dist;
    }
  }
  printf("PESO MST:%d\n",pesomst);
 
  a = clock();
  mstArchiveGenerator(name,edges,numEdges,dimension);
  b = clock();
  tempo = (b - a) / (float)CLOCKS_PER_SEC;
  printf("IMPRIMIR SAIDA MST: %f s\n",tempo);
 
  short int** adj = malloc((dimension+1)*sizeof(short int*));
 
  for(int j=0; j < dimension+1; j++){
    adj[j] = malloc(7*sizeof(short int));
        adj[j][0] = 0;
  }
 
    a = clock();
  createAdjList(adj,edges,numEdges);
    b = clock();
    tempo = (b - a) / (float)CLOCKS_PER_SEC;
    printf("MONTAR LISTAS DE ADJACENCIA: %f s\n",tempo);
 
    free(edges);
 
    a = clock();
    short int* id = calloc(dimension+1,sizeof(short int));
    id[1] = 1;
 
  strcat(name,".tour");
    FILE *t = fopen(name, "w");
    name[strlen(name)-5] = '\0';
    fprintf(t,"NAME: %s\nTYPE: TOUR\nDIMENSION: %d\nTOUR_SECTION\n1\n",name,dimension);
    depthFirstSearch (adj,dimension,id,t,1);
    fprintf(t,"EOF");
    b = clock();
    tempo = (b - a) / (float)CLOCKS_PER_SEC;
    printf("GERANDO O TOUR: %f s\n",tempo);
    fclose(t);
    free(id);
  freeAdj(adj,dimension);
  clock_t end = clock();
  tempo = (end - init) / (float)CLOCKS_PER_SEC;
  printf("\nTOTAL: %f s\n\n",tempo);
 
  return 0;
}
