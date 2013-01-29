
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#define BSIZE 1<<15

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

unsigned long long int sum ;
unsigned long int V ; 
// a structure to represent a weighted edge in graph
struct Edge
{
    unsigned long int src, dest ;
    int weight;
};

// a structure to represent a connected, undirected and weighted graph
struct Graph
{
    struct Edge* edge;
};

struct Graph* createGraph()
{
    long int i ;
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );

    graph->edge = (struct Edge*) malloc( (V-1) * sizeof( struct Edge ) );
    for (i = 0; i < (V-1); i++) {
		graph->edge[i].src = readLong();
		graph->edge[i].dest = readLong();
		graph->edge[i].weight = readLong();
    }
    return graph;
}

// A structure to represent a subset for union-find
struct subset
{
    long int parent;
    long int rank;
    unsigned long long int vertex;
};

// A utility function to find set of an element i
// (uses path compression technique)
long int find(struct subset subsets[], long int i)
{
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[],long int x,long int y)
{
    long int xroot = find(subsets, x);
    long int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank){
        subsets[xroot].parent = yroot;
        subsets[yroot].vertex += subsets[xroot].vertex;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank){
        subsets[yroot].parent = xroot;
        subsets[xroot].vertex += subsets[yroot].vertex;
    }
    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
        subsets[xroot].vertex += subsets[yroot].vertex;
    }
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int comp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return (a1->weight - b1->weight);
}
void KruskalMST(struct Graph* graph)
{
    long int x,y,i;
	int wght;
    struct Edge next_edge ;
    qsort(graph->edge, (V-1), sizeof(graph->edge[0]), comp);
    // Allocate memory for creating V subsets
    struct subset *subsets = (struct subset*) malloc( V * sizeof(struct subset) );
    // Create V subsets with single elements
    for (i = 0; i < V; ++i)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
        subsets[i].vertex = 1 ; 
    }
    i = 0 ; 
    while (i < V -1)
    {
        next_edge = graph->edge[i++];
        x = find(subsets, next_edge.src);
        y = find(subsets, next_edge.dest);
        wght = next_edge.weight;
        sum += wght + (wght+1)*imaxabs((subsets[x].vertex * subsets[y].vertex - 1));
        Union(subsets, x, y);
    }
    return;
}


int main()
{
    struct Graph* graph ;
   	V = readLong();
    graph = createGraph();
    KruskalMST(graph);
    printf("%llu\n",sum);
    return 0 ;
}
