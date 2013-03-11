#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define BSIZE 1<<15

// A structure to represent a node in adjacency list
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct VertexNode
{
    int index;
    int lowlink;
    int visited;
};

// A structure to represent an adjacency liat
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};


struct Graph
{
    int V;
    struct AdjList* array;
};


struct VertexNode ** mat ;
int * stack , * sp;
int tos,total,v,indx,visit ;

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
    (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    int i ;
    graph->V = V;
    
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    for  (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    
    return graph;
}

// Adds an edge to a directed graph
void addEdge(struct Graph* graph, int src, int dest)
{
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

int min ( int a , int b){
    if ( a < b )
        return a ;
    else
        return b ; 
}
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong()
{
	long d = 0L, x = 0L;
	char c;
    
	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}

void tarjan(struct Graph * graph , int i){
    
    struct AdjListNode* tmp;
    tmp = graph->array[i].head ;
    mat[i]->index = indx ;
    mat[i]->lowlink = indx;
    indx++;
    stack[tos] = i ;
    sp[i] = tos;
    tos++;
    while (tmp){
        if (mat[tmp->dest]->index == -1 ){
            tarjan(graph,tmp->dest) ;
            if (mat[i]->lowlink > mat[tmp->dest]->lowlink) {
                mat[i]->lowlink = mat[tmp->dest]->lowlink;
            }
        }
        else if ((mat[i]->index > mat[tmp->dest]->visited) && (sp[tmp->dest] != -1))
        {
            if (mat[i]->lowlink > mat[tmp->dest]->index) {
                    mat[i]->lowlink = mat[tmp->dest]->index;
                }
        }
        tmp = tmp->next;
    }
    
    if (mat[i]->index == mat[i]->lowlink){
        total = 0 ;
        do{
            tos--;
            v = stack[tos];
            sp[v] = -1;
            total++;
        }while (i != v);
    }
    
    
}
void check(struct Graph * graph , int i){
    
    struct AdjListNode* tmp;
    tmp = graph->array[i].head ;
    mat[i]->visited = 1 ; 
    visit+=1;
    while (tmp){
        if (mat[tmp->dest]->visited == 0 ){
            check(graph,tmp->dest) ;
        }
        tmp = tmp->next;
    }
}
int main()
{
    indx = 1;
    visit = 0 ;
    int V,i,j,dst,A;
	V = readLong()+1;
    struct Graph* graph = createGraph(V);
    mat = (struct VertexNode **)malloc(V * sizeof( struct VertexNode*));
    stack = (int *)malloc(V*sizeof(int));
    sp = (int *)malloc(V*sizeof(int));
    for (i = 1 ; i < V ; i++){
        A = readLong();
        for (j = 0 ; j < A ; j++){
            dst = readLong();
            addEdge(graph,dst,i);
        }
        mat[i] = (struct VertexNode *)malloc(sizeof(struct VertexNode));
        mat[i]->index = -1 ;
        mat[i]->lowlink = INT_MAX ;
        mat[i]->visited = 0 ;
        stack[i] = 0 ;
        sp[i]= -1 ; //undefined
    }
    tos = 0 ; 
    for ( i = 1 ; i < V ; i++){
        if (mat[i]->index == -1){
            tarjan(graph,i);
        }
    }
    check(graph,v);
    if (visit != V-1)
        total = 0 ; 
    printf("%d\n",total);
    free(mat);
    free(stack);
    free(sp);
         return 0;
}


