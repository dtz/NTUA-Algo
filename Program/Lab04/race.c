/* 
 * Dijkstra's implementation (source code/comments) using binary heap was taken from  
 * http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/
 * and was adjusted to satify the problem's constraints 
 */



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define BSIZE 1<<15
long int K , L ,cnt;
long int  *time ; 
int * city,*aux;
// A structure to represent a node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency liat
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
int i ;
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    for  (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 int compare(const void *a, const void *b)
{
    const long int *ia = (const long int *)a; // casting pointer types
    const long int *ib = (const long int *)b;
    if (*ia > *ib)
        return 1 ;
    else
        return (*ia < *ib) ? -1:0 ;
}
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};
 
// Structure to represent a min heap
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
 
// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
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

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap * minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if ((left < minHeap->size) && (minHeap->array[left]->dist < minHeap->array[smallest]->dist))
      smallest = left;
 
    if ((right < minHeap->size) && (minHeap->array[right]->dist < minHeap->array[smallest]->dist))
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode * smallestNode = minHeap->array[smallest];
        struct MinHeapNode * idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)
{
	int i ;
    printf("Vertex   Distance from Source\n");
    for (i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(struct Graph* graph, int B)
{
    int V = graph->V;// Get the number of vertices in graph
    int dist[V];      // dist values used to pick minimum weight edge in cut
    int i,v ;
    int next,curr,remain,done;
    int A ; 
    long int total;
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
    struct AdjListNode* tmp ;
    // Initialize min heap with all vertices. dist value of all vertices
    for ( v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    for (i=0 ; i < B ; i++){
        A = readLong(); 
        dist[A] = 0;
    	decreaseKey(minHeap, A, 0);
    }
        
    minHeap->size = V;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
        if (aux[u] == 1){
            time[cnt] = dist[u];
            cnt++;
        }
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjListNode* ptr = graph->array[u].head;
        while (ptr != NULL)
        {
            int v = ptr->dest;
 
            // If shortest distance to v is not finalized yet, and weight of u-v
            // plus dist of u from src is less than dist value of v, then update
            // distance value of v
            if ((isInMinHeap(minHeap, v)) && (ptr->weight + dist[u] < dist[v]))
            {
                dist[v] = dist[u] + ptr->weight;
                
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            ptr = ptr->next;
        }
    }
 	total = 0 ; 
    for (i=0 ; i < L;i++){
        total += time[i];
    }    
    remain = 1 ;
    done = 0 ; 
    next = city[0];
     
    while (remain <= K){
        curr = next ;
        next = city[remain];
        
        tmp = graph->array[curr].head;
        
        while ((tmp)&&(!done)){
            if (tmp->dest == next){
                total += tmp->weight;
                done = 1 ;
            }
            tmp = tmp->next;
        }
        remain++;
        done = 0 ;
    }
    printf("%lu\n",total);

}
// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V,M,B,i,src,dst,weight,A;
	V = readLong()+1;
    
    struct Graph* graph = createGraph(V);
    M = readLong();
    K = readLong();	    
    L = readLong();
    B = readLong();
    city = (int*) malloc(K*sizeof(int));
    aux = (int*) malloc(V*sizeof(int));
    for (i=0 ; i < V  ; i++){
        aux[i] = 0 ;
    }

    for (i=0 ; i< M ; i++){
        src = readLong();
        dst = readLong();
        weight = readLong();
        addEdge(graph,src,dst,weight);
    }
    A = readLong();
    city[0] = A ; 
    for (i=1 ; i < K-1 ; i++){
        A = readLong();
        aux[A] = 1 ;
        city[i]= A ; 
    }
    A = readLong();
    city[K-1] = A ; 
    cnt = 0 ; 
    time = (long int*) malloc (K * sizeof(long int ));
    dijkstra(graph, B);
    
    return 0;
}


