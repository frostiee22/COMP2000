// Number 3

// (a)(i)
depth  : CEADFBG
breath : CEGABFD

// (a)(ii)


// (b)(i)

A cant be stored in a one-dimentional array by using
A[i][j] stored at : BA + k{n(i-1) + (j-1)}
to save space a symetric metrix will be used sice the lower triangle is the same as the 
upper triangle.
(1/2)n(n-1)

// (b) (ii)


int sum(int node){
	int i,sum=0,a;
	for (i=1;i<8;i++){
		a = symetric(i,node);
		if (a != 0 && a != 999){
			sum += a;
		}
	}
	return sum;
}

int symetric(int i;int j){
	if (i==j) return 0;
	if (i > j) return B[i*(i-1)/2+j];
	return B[i*(j-1)/2+i];
}

// (c)

void acyclic (Graph G, int s){
	G->vertix[s].colour = Grey;
	GEdgePtr edge = G->vertix[s].firstEdge;
	while(edge != NULL){
		if(G->vertix[edge->child].colour == Grey){
			printf("not an acyclic graph\n");
			exit(1);
		}
		if(G->vertix[edge->child].colour == white)
			acyclic(G,edge->child);
		edge = edge->nextEdge;
	}
	G->vertex[s].colour = Black;
}