// fixing min-heap
void heap(int A[] , int k ,int n){
	int item,i,j;
	for (k=k+1,k<=n;k++){
		item = A[k];
		i=k;
		j=i/2;
		while ((i>0) && (j>0) && (item > A[j])){
			A[i] = A[j];
			i= j;
			j = i/2;
		}
		A[i] = item;
	}
}

//////////////////////////////////////////////////////////////////////

// deleting the smallest
TreeNodePtr deleteSmallest(TreeNodePtr root){
	if (root == NULL) return NULL;
	if (root->left == NULL)
		return root->right;

	TreeNodePtr parent = NULL;
	TreeNodePtr current = root;

	while(current->left != NULL){
		parent = current;
		current = current->left;
	}
	parent->left = current->right;
	return root;
}

/////////////////////////////////////////////////////////////////////

// deleting the  largest
TreeNodePtr deleteLargest(TreeNodePtr root){
	if (root == NULL) return NULL;
	if (root->right == NULL)
		return root->left;

	TreeNodePtr parent = NULL;
	TreeNodePtr current = root;

	while(current->right != NULL){
		parent = current;
		current = current->right;
	}
	parent->right = current->left;
	return root;
}

////////////////////////////////////////////////////////////////////

// A[0] holds the number of items in the array include @ values
int inOrderSuccessor(int A[], int k){
	int i=k;

	if (i>A[0]) return -1; //  don't exist

	if (A[K*2+1] != '@' &&  (k*2+1) <= A[0]  ){
		i = k*2+1;
		while(A[i*2] != '@' && (k*2) <= A[0]) i = i*2;
			return i;
	}
	int parent = i/2;
		while (A[parent] != '@' && A[parent*2+1] == i){
			i = parent;
			parent = i/2;
		}
	return parent;
}



////////////////////////////////////////////////////////

// topological sort algorithm 
void (topologicalSort (G (V,F))){
	for each vertex v eV
		v.colour = white
	initialize stack, S 
	for each vertex v eV
		if (v.colour == white) dfTraversal(v)
	pop,S and print each item as popped
}

void dfTraversal(v){
	print v.id 
	v.colour = grey
	for each edge(v,x)
		if (x.colour == grey("No solution")) // back edge cycle
		if (x.colour == white) dfTraversal(x)
	v.colour = black
	add v to stack,S
}

//////////////////////////////////////////////////////

int sumlevels(TreeNodePtr root){
	return SumInt(0,root);
}

int SumInt(int level, TreeNodePtr P){
	if (P == NULL) return 0;
	return level + SumInt(level+1,P->left) + SumInt(level+1,P->right);
}