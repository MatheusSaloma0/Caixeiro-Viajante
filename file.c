#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"
#include "file.h"
 
int getName_Dimension (FILE* input,char* name){
  char word[50];
  int dimension;
     
    do{
        fscanf(input,"%s",word); //procurando no arquivo o nome do grafo;
    }while (strcmp(word,"NAME:") != 0);
 
    fscanf(input,"%s",name);    //lendo o nome do grafo;
    printf("Nome:%s\n",name);
 
    do{
    fscanf(input, "%s", word);
    }while (strcmp(word,"DIMENSION:") != 0); //procurando no arquivo a dimensao do grafo;
 
    fscanf(input,"%d",&dimension); //lendo a dimensao do grafo;
    printf("Dimensao:%d\n",dimension);
 
  return dimension;
}
 
void readCoordenades (FILE* input, Node* nodes, int dimension){
  char word[50];
  float n;
 
    do{
    fscanf(input, "%s", word);
    }while (strcmp(word,"NODE_COORD_SECTION") != 0); //procurando o inicio da lista de coordenadas;
 
    for (int i = 1; i<=dimension; i++){
        fscanf(input,"%s",word);
        if (strcmp(word,"EOF")==0) break; //enquanto nao encontrar o EOF;
        fscanf(input,"%f",&n); //lê a coordenada de x;
    nodes[i].x = n;
        fscanf(input,"%f",&n); //lê a coordenada de y;
        nodes[i].y = n;
    }
}
 
void mstArchiveGenerator (char* name, Edge* edges, int numEdges, int dimension){
  strcat(name,".mst");
  FILE *arqMst = fopen(name,"w");
    name[strlen(name)-4] = '\0';
     
    fprintf(arqMst,"NAME: %s\n", name);
    fprintf(arqMst,"TYPE: MST\nDIMENSION: %d\nMST_SECTION\n",dimension);
 
    for (int i = 0; i < numEdges; i++){
        if (edges[i].mst == true) fprintf(arqMst,"%d %d\n",edges[i].n1,edges[i].n2);
    }
    fprintf(arqMst,"EOF\n");
    fclose(arqMst);
}
