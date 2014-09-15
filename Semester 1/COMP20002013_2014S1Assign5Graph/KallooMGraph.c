#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxWordSize 17
#define MaxVertices 9999
#define INFINITY 9999
#define White 'w'
#define Grey 'g'
#define Black 'b'


typedef struct gEdge{
	int child, weight;
	struct gEdge *nextEdge;
}GEdge, *GEdgePtr;


typedef struct gvertex{
	char id[MaxWordSize + 1], colour;
	int parent, cost, discover, finish, inDegree;
	GEdgePtr firstEdge;
}GVertex;

typedef struct graph {
	int numV;
	GVertex vertex[MaxVertices + 1];
} *Graph;

struct treeNode {
	struct treeNode *leftPtr;
	char data[MaxWordSize];
	int num;
	struct treeNode *rightPtr;
};




// QUEUE CODE

typedef struct queuedata{
	int nv;
}QueueData;

typedef struct node {
	QueueData data;
	struct node *next;
} Node, *NodePtr;

typedef struct queueType {
	NodePtr head, tail;
} QueueType, *Queue;

Queue initQueue() {
	Queue qp = (Queue)malloc(sizeof(QueueType));
	qp->head = NULL;
	qp->tail = NULL;
	return qp;
}
int empty(Queue Q) {
	return (Q->head == NULL);
}
void enqueue(Queue Q, QueueData d) {
	NodePtr np = (NodePtr)malloc(sizeof(Node));
	np->data = d;
	np->next = NULL;
	if (empty(Q)) {
		Q->head = np;
		Q->tail = np;
	}
	else {
		Q->tail->next = np;
		Q->tail = np;
	}
}
QueueData dequeue(Queue Q) {
	if (empty(Q)) {
		printf("\nAttempt to remove from an empty queue\n");
		exit(1);
	}
	QueueData hold = Q->head->data;
	NodePtr temp = Q->head;
	Q->head = Q->head->next;
	if (Q->head == NULL) Q->tail = NULL;
	free(temp);
	return hold;
}


// End QUEUE CODE









typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;



//Function prototypes
void insertNode(TreeNodePtr *treePtr, char * value);
void InOrder(TreeNodePtr treePtr, Graph G);
void search(TreeNodePtr treePtr, char c[]);
GVertex newGVertex(char name[]);
GEdgePtr newGEdge(int c, int w);
Graph newGraph(int n);
void buildGraph(FILE*in, Graph G);
void addEdge(char X[], char Y[], int weight, Graph G);
void printGraph(FILE*out, Graph G);
void depthFirstTraversal(FILE*out, Graph G, int s);
void dfTraverse(FILE*out, Graph G, int s);
void printPath(FILE*out, Graph G, char D[]);
void followPath(FILE*out, Graph G, int c);
QueueData newQueueData(int n);
void breadthFirstTraversal(FILE*out, Graph G, int s);
void Dijkstra(FILE*out, Graph G, int s, char c[]);
void initSingleSource(Graph G, int s);
void printCostPath(FILE*out, Graph G, char c[]);
void siftUp(Graph G, int heap[], int n, int heapLoc[]);
void siftDown(Graph G, int key, int heap[], int root, int last, int heapLoc[]);

// Global variables
TreeNodePtr rootPtr = NULL;
int Placement, j, order = 0;


int main() {
	printf("\nCOMP2000 Assignment 5\n\nStudent # : 812000767\n\n\n\n********** Graph ************* \n\n\n");

	FILE*in = fopen("input.txt", "r");
	FILE*out = fopen("output.txt", "w");


	// part (a)
	char word[MaxWordSize] = { '\0' };
	int numVertices = 0;
	fscanf(in, "%s", &word);


	while (strcmp(word,"END") != 0){
		numVertices++; //  getting the number of vertices's
		insertNode(&rootPtr, word);
		fscanf(in, "%s", &word);
	}

	Graph G = newGraph(numVertices);
	buildGraph(in, G);
	printGraph(out, G);

	// end part (a)
	printf("-> Part (a) finished ... \n\n");
	// part b
	fscanf(in, "%s", &word);
	search(rootPtr, word);
	depthFirstTraversal(out, G, Placement);
	breadthFirstTraversal(out, G, Placement);

	fscanf(in, "%s", &word);
	search(rootPtr, word);
	depthFirstTraversal(out, G, Placement);
	breadthFirstTraversal(out, G, Placement);
	fprintf(out, "\n");
	fprintf(out, "\n");
	// end part b
	printf("-> Part (b) finished ... \n\n");
	// part (c)
	fscanf(in, "%s", &word);
	while (strcmp(word, "END") != 0){
		search(rootPtr, word);
		fprintf(out, "Minimal cost path from %s:\n", word);
		Dijkstra(out, G, Placement, word);
		fscanf(in, "%s", &word);
		Placement = 0;
		fprintf(out, "\n");
	}
	// end part (c)
	printf("-> Part (c) finished ... \n\n");

	Placement = j = order = 0;


	fclose(in);
	fclose(out);

	printf("********* Finished ***********\n\n");

	system("PAUSE");
	return 0;

}


// FUNCTIONS


// BST
void insertNode(TreeNodePtr *treePtr, char * value){
	// if tree is empty
	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));

		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			strcpy((*treePtr)->data, value);
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else {
			printf("%d not inserted, out off memory.\n", value);
		}
	}
	else { // tree not empty
		// data to insert is less than data in current node
		if (strcmp(value, (*treePtr)->data) < 0){
			insertNode(&((*treePtr)->leftPtr), value);
		}
		// data to insert is greater than data in current node
		else if (strcmp(value, (*treePtr)->data) > 0) {
			insertNode(&((*treePtr)->rightPtr), value);
		}
		else{
			// Already exist so skip it
		}
	}
}


//  used to create the vertex using the nodes from the BST
void InOrder(TreeNodePtr treePtr, Graph G)  {
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		InOrder(treePtr->leftPtr, G);
		j++;
		order++;
		G->vertex[j] = newGVertex("");
		strcpy(G->vertex[j].id, treePtr->data);
		treePtr->num = order; // gives the words a number
		InOrder(treePtr->rightPtr, G);

	}

}

// searching for the number to be used as Placement
void search(TreeNodePtr treePtr, char c[]){
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		search(treePtr->leftPtr, c);

		if (strcmp(treePtr->data, c) == 0)
			Placement = treePtr->num;// gets a number to be used by other functions

		search(treePtr->rightPtr, c);

	}
}


GVertex newGVertex(char name[]){
	GVertex temp;
	strcmp(temp.id, name);
	temp.firstEdge = NULL;
	return temp;
}


GEdgePtr newGEdge(int c, int w){
	GEdgePtr p = (GEdgePtr)malloc(sizeof(GEdge));
	p->child = c;
	p->weight = w;
	p->nextEdge = NULL;
	return p;
}

Graph newGraph(int n){
	if (n > MaxVertices){
		printf("\n Too big Only %d vertices's allowed. \n", MaxVertices);
		system("pause");
		exit(1);
	}
	Graph p = (Graph)malloc(sizeof(struct graph));
	p->numV = n;
	return p;
}



// build graph

void buildGraph(FILE*in, Graph G){
	int k, numEdges, weight;
	char nodeID[MaxWordSize + 1], adjID[MaxWordSize + 1];
	InOrder(rootPtr, G);

	fscanf(in, "%s", &nodeID);
	while (strcmp(nodeID, "END") != 0){
		fscanf(in, "%d", &numEdges);

		for (k = 1; k <= numEdges; k++){
			fscanf(in, "%s %d", &adjID, &weight);
			addEdge(nodeID, adjID, weight, G);
		}
		fscanf(in, "%s", &nodeID);
	}
}


// AddEdge

void addEdge(char X[], char Y[], int weight, Graph G){
	int j, k;
	for (j = 1; j <= G->numV; j++){
		if (strcmp(X, G->vertex[j].id) == 0) break;
	}
	for (k = 1; k <= G->numV; k++){
		if (strcmp(Y, G->vertex[k].id) == 0) break;
	}
	if (j > G->numV || k > G->numV){
		printf("No Such edge: %s -> %s\n", X, Y);
		system("pause");
		exit(1);
	}

	GEdgePtr ep = newGEdge(k, weight);
	GEdgePtr prev, curr;
	prev = curr = G->vertex[j].firstEdge;
	while (curr != NULL && strcmp(Y, G->vertex[curr->child].id) > 0){
		prev = curr;
		curr = curr->nextEdge;
	}
	if (prev == curr){
		ep->nextEdge = G->vertex[j].firstEdge;
		G->vertex[j].firstEdge = ep;
	}
	else {
		ep->nextEdge = curr;
		prev->nextEdge = ep;
	}
}

// printing out the graph
void printGraph(FILE*out, Graph G){
	int j;
	for (j = 1; j <= G->numV; j++){
		fprintf(out, "%-16s : ", G->vertex[j].id);
		GEdgePtr p = G->vertex[j].firstEdge;
		while (p != NULL){
			fprintf(out, "%s %d ", G->vertex[p->child].id, p->weight);
			p = p->nextEdge;
		}
		fprintf(out, "\n");
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// part (b)

// depth first traversal
void depthFirstTraversal(FILE*out, Graph G, int s){
	int j;
	for (j = 1; j <= G->numV; j++){
		G->vertex[j].colour = White;
		G->vertex[j].parent = 0;
	}
	fprintf(out, "\nDepth-first   : ");
	dfTraverse(out, G, s);
	for (j = 1; j <= G->numV; j++)
	if (G->vertex[j].colour == White)dfTraverse(out, G, j);

}

void dfTraverse(FILE*out, Graph G, int s){
	static int time = 0;
	fprintf(out, "%s ", G->vertex[s].id);
	G->vertex[s].colour = Grey;
	G->vertex[s].discover = ++time;
	GEdgePtr edge = G->vertex[s].firstEdge;
	while (edge != NULL){
		if (G->vertex[edge->child].colour == White){
			G->vertex[edge->child].parent = s;
			dfTraverse(out, G, edge->child);
		}
		edge = edge->nextEdge;
	}
	G->vertex[s].colour = Black;
	G->vertex[s].finish = ++time;
}


void printPath(FILE*out, Graph G, char D[]){
	int j;
	for (j = 1; j <= G->numV; j++)
	if (strcmp(D, G->vertex[j].id) == 0)break;
	if (j > G->numV) fprintf(out, "\nNo such node %s\n", D);
	else{
		fprintf(out, "\nPath to %s: ", D);
		followPath(out, G, j);
		fprintf(out, "\n");
	}

}

void followPath(FILE*out, Graph G, int c){
	if (c != 0){
		followPath(out, G, G->vertex[c].parent);
		fprintf(out, "%s ", G->vertex[c].id);
	}
}


QueueData newQueueData(int n){
	QueueData temp;
	temp.nv = n;
	return temp;
}


void breadthFirstTraversal(FILE*out, Graph G, int s){
	int j;
	for (j = 1; j <= G->numV; j++){
		G->vertex[j].colour = White;
		G->vertex[j].parent = 0;
	}
	G->vertex[s].colour = Grey;
	G->vertex[s].parent = 0;
	Queue Q = initQueue();
	enqueue(Q, newQueueData(s));
	fprintf(out, "\nBreadth-first : ");

	while (!empty(Q)){
		int aParent = dequeue(Q).nv;
		fprintf(out, "%s ", G->vertex[aParent].id);
		GEdgePtr edge = G->vertex[aParent].firstEdge;
		while (edge != NULL){
			if (G->vertex[edge->child].colour == White){
				G->vertex[edge->child].colour = Grey;
				G->vertex[edge->child].parent = aParent;
				enqueue(Q, newQueueData(edge->child));
			}
			edge = edge->nextEdge;
		}
		G->vertex[aParent].colour = Black;
	}
	fprintf(out, "\n");
}





/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

// PART (c)

//Dijkstra

void Dijkstra(FILE*out, Graph G, int s, char c[]){
	int j, heap[MaxVertices + 1], heapLoc[MaxVertices + 1];
	initSingleSource(G, s);
	for (j = 1; j <= G->numV; j++)heap[j] = heapLoc[j] = j;
	heap[1] = s; heap[s] = 1; heapLoc[s] = 1; heapLoc[1] = s;
	int heapSize = G->numV;
	while (heapSize > 0){
		int u = heap[1];
		if (G->vertex[u].cost == INFINITY)break;
		siftDown(G, heap[heapSize], heap, 1, heapSize - 1, heapLoc);
		GEdgePtr p = G->vertex[u].firstEdge;
		while (p != NULL){
			if (G->vertex[u].cost + p->weight < G->vertex[p->child].cost){
				G->vertex[p->child].cost = G->vertex[u].cost + p->weight;
				G->vertex[p->child].parent = u;
				siftUp(G, heap, heapLoc[p->child], heapLoc);
			}
			p = p->nextEdge;
		}
		--heapSize;
	}
	printCostPath(out, G, c);
}



void initSingleSource(Graph G, int s){
	int j;
	for (j = 1; j <= G->numV; j++){
		G->vertex[j].cost = INFINITY;
		G->vertex[j].parent = 0;
	}
	G->vertex[s].cost = 0;
}

void printCostPath(FILE*out, Graph G, char c[]){
	int j;
	for (j = 1; j <= G->numV; j++){
		if (strcmp(G->vertex[j].id, c) != 0){
			fprintf(out, " to %-16s: %4d, Path: ", G->vertex[j].id, G->vertex[j].cost);
			if (G->vertex[j].cost != INFINITY)
				followPath(out, G, j);
			else fprintf(out, "unreachable");
			fprintf(out, "\n");
		}
	}
}


void siftUp(Graph G, int heap[], int n, int heapLoc[]){
	int siftItem = heap[n];
	int child = n;
	int parent = child / 2;
	while (parent > 0){
		if (G->vertex[siftItem].cost >= G->vertex[heap[parent]].cost)break;
		heap[child] = heap[parent];
		heapLoc[heap[parent]] = child;
		child = parent;
		parent = child / 2;
	}
	heap[child] = siftItem;
	heapLoc[siftItem] = child;
}

void siftDown(Graph G, int key, int heap[], int root, int last, int heapLoc[]){
	int smaller = 2 * root;
	while (smaller <= last){
		if (smaller < last)
		if (G->vertex[heap[smaller + 1]].cost < G->vertex[heap[smaller]].cost)
			smaller++;
		if (G->vertex[key].cost <= G->vertex[heap[smaller]].cost)break;
		heap[root] = heap[smaller];
		heapLoc[heap[smaller]] = root;
		root = smaller;
		smaller = 2 * root;
	}
	heap[root] = key;
	heapLoc[key] = root;
}
