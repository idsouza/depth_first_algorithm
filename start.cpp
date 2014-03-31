
/* 
 * Este programa implementa 
 * o algoritmo de busca em profundidade
 * estudado no campo de teoria dos grafos.
 * @author Igor Duarte de Souza
 * @data 01/03/2014
 *
 */

#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_CHILDRENS 10

enum { 
    STATE_0 = 0, STATE_1 = 1, STATE_2 = 2, STATE_3 = 3 
};

struct graph{
    char vertex;
    char adj[MAX_CHILDRENS];    
    int status = STATE_0;
};

//Obtem e retorna um grafo da pilha como parametro
graph* getVertex(const graph *gph, int size, char vertex){ 
    int flag = 0;
    graph *gph_return;
    for(int i = 0; (i < size ||flag == 0); i++){
        if((gph + i)->vertex == vertex){   
            gph_return = (graph*)(gph + i); 
            flag = 1;
        }
    }
    return gph_return;
}

//Calcula e retorna a quantidade de vertices adjacentes de um grafo
int getSizeAdj(const graph gph){
    int flag = 0;
    int sum = 0;
    for(int i = 0; (i < MAX_CHILDRENS && flag == 0); i++){
        int code_ascii = gph.adj[i];
        if(code_ascii >= 65 && code_ascii <= 90)
            sum++;
        else
            flag = 1;
    }       
    return sum;
}

void showStack(const graph *gph, const char *stack, int size){
    printf("\n\nGraph currente: %c \n", gph->vertex);
    for(int i = 0; i < size; i++){
        printf("%c ", *(stack + i));
    }
}

void alghoritmics(graph *gph, char stack[], int size_gph, int size_stack){
    char stack_backup[size_stack];
    int size_stack_final = 0;
    graph *vertex_process = getVertex(gph, size_gph, stack[0]);
    
    if(vertex_process->status == STATE_0 || vertex_process->status == STATE_2){
        vertex_process->status = STATE_3;
        
        //Copia a pilha para um vetor de backup e realoca memória para a pilha principal
        strcpy(stack_backup, stack);        
        size_stack_final = getSizeAdj(*vertex_process) + size_stack - 1;        
        stack = (char*)malloc(size_stack_final);
        
        //Captura as vertices adjacent. da vertice corrente e adiciona na pilha
        for(int i = 0, j = 0; i < getSizeAdj(*vertex_process); i++){
            graph *vertex_adj = getVertex(gph, size_gph, vertex_process->adj[i]);
            if(vertex_adj->status == STATE_0){
                stack[j] = vertex_adj->vertex;
                vertex_adj->status = STATE_2;
                j++;
            }
        }
        
        //Remove a primeira vertice da pilha de backup
        for(int i = 0; i < size_stack; i++){
            stack_backup[i] = stack_backup[i + 1]; 
        }
        strcat(stack, stack_backup);
        
        vertex_process->status = STATE_1;
        showStack(vertex_process, stack, size_stack_final);
        
        alghoritmics(gph, stack, size_gph, size_stack_final);
    }
}

void startAlghoritmics(graph *gph, int size){
    char stack[1] { gph->vertex };
    alghoritmics(gph, stack, size, sizeof(stack));
}

int main(int argc, char** argv) {
    graph gph[5], vertexA, vertexB, vertexC, vertexD, vertexE, vertexF;    
    
    vertexA.vertex = 'A';    
    vertexB.vertex = 'B';
    vertexC.vertex = 'C';
    vertexD.vertex = 'D';
    vertexE.vertex = 'E';
    vertexF.vertex = 'F';
    
    //Children's of Graph A
    vertexA.adj[0] = vertexB.vertex;
    vertexA.adj[1] = vertexC.vertex;
    
    //Children's of Graph B
    vertexB.adj[0] = vertexA.vertex;
    vertexB.adj[1] = vertexD.vertex;
    
    //Children's of Graph C
    vertexC.adj[0] = vertexA.vertex;
    vertexC.adj[1] = vertexD.vertex;
    vertexC.adj[2] = vertexF.vertex;
    
    //Children's of Graph D
    vertexD.adj[0] = vertexB.vertex;
    vertexD.adj[1] = vertexC.vertex;
    vertexD.adj[2] = vertexE.vertex;
    
    //Childrens of Graph E
    vertexE.adj[0] = vertexD.vertex;
    
    //Children's of Graph F
    vertexF.adj[0] = vertexC.vertex;
    
    //Add graphs in vector of graphs
    gph[0] = vertexA;
    gph[1] = vertexB;
    gph[2] = vertexC;
    gph[3] = vertexD;
    gph[4] = vertexE;
    gph[5] = vertexF;
  
    startAlghoritmics(gph, sizeof(gph) / sizeof((*gph)));

    return 0;
}

