// Number 1

// (a) (i)

//siftdown the new root which is the last item in the heap into its correct position
int deleteMax(int key,int array[],int root,int last)
{
	if (array[0] == 0) return -1;
	int max=array[1];//save the largest item which is to be deleted
	int largest=2*root;//index of largest item(root) since it is max heap
	array[0]--;//minus 1 from the array size since we delete a value
	while(largest<=last && array[0]>0)//while the index is within the array size 
	{
		if(largest<last)//if the index of largest is less than there is another child(right child)
			if(array[largest+1]>array[largest])//check which child is larger(left or right)
				largest++;
		if(key>=array[largest])//if last item is more than the largest child then end loop
			break;
		array[root]=array[largest];//replace parent with largest child 
		root=largest;//new parent is largest child
		largest=2*root;//go down a level(eg 1->2->4->8)
	}
	array[root]=key;//place the last item into its final position
	return max;
}



// (a) (ii)

void mergeHeap(int A[],int B[])
{
	int total=A[0]+B[0]+(-1);
	int C[total];
	int count=0,x,y,max;
	max=total;


	x=deleteMax(A[A[0]],A,1,A[0]);
	y=deleteMax(B[B[0]],B,1,B[0]);
	while(count<max)
	{
		if(x>y)
		{
			if (A[0]>0)
			{
				C[total] = x;
				x=deleteMax(A[A[0]],A,1,A[0]);
			}
		}
		else if(y>x)
		{
			if (B[0]>0)
			{
				C[total]=y;
				y=deleteMax(B[B[0]],B,1,B[0]);
			}
		}
		else if (x==y)
		{
			C[total] = x;
			x=deleteMax(A[A[0]],A,1,A[0]);
			y=deleteMax(B[B[0]],B,1,B[0]);
		}
		total--;
		count++;
	}

	if (x>y)
	{
		C[1] = x;
		C[0]=y;
	}
	else if (y>x)
	{
		C[1]=y;
		C[0]=x;
	}
	

	int i;
	total=A[0]+B[0];
	printf("C: ");
	for(i=0;i<max;i++)
		printf("%i ", C[i]);
}


// (b)

void makeHeap(int array[])
{
	int i,temp,x;
	for(i=2;i<=A[0],i++){
		x=i;
		while(x/2>0 && A[x] > A[x/2]){
			temp = A[x];
			A[x] = A[x/2];
			A[x/2] = temp;
			x=x/2;
		}
	}
}

// (c)

TreeNodePtr findOrInsert(TreeNodePtr root, int  key){
	TreeNodePtr newNode(int key),curr,node;
	int cmp;
	if(root == NULL){
		node = newNode(d);
		node->parent = NULL;
		return node;
	}
	curr = root;
	while(key != curr->data){
		if(key < curr->data){ // try left
			if (curr->left == NULL){
				curr->left = newNode(key);
				curr->left->parent = curr;
				return curr->left;
			}
			curr = curr->left;
		}
		else { // try right
			if (curr->right = NULL){
				curr->right = newNode(key);
				curr->right->parent = curr;
				return curr->right;
			}
			curr = curr->right;
		}// end else
	}// end while
	// d is the tree; return pointer to the node
	return curr;
} // end findOrInsert



// Number 2

// (a)

int locationInHashTable(char key[], int max){
	int j = 0,keyNum = 0, w =3;
	while(key[j] != '\0'){
		keyNum += w * key[j++];
		w = w + 2;
	}
	return keyNum % max + 1;
}

// (b)
#define N // n is the size of table
// global variable 
int head;


int Search (HashTable table[], char key[]){
	int keyNum = H1(key);
	int loc = h1();
	int k = H2();

	while (strcmp(table[loc].data,Empty) != 0 && strcmp(table[loc]).data,key) != 0){
		loc = loc + k;
		if(loc > N) loc = loc - N;
	}

	if (strcmp(table[loc].data,Empty) == 0) return -loc; // not found
	return loc; // found
}

int AddToTable(HashTable table[], char key[],int loc, int head){
	strcmp(table[loc].data,key);
	int curr = head;
	int pre = -1;

	while(curr != -1 && strcmp(key,table[curr].data) > 0){
		pre = curr;
		curr = table[curr].next;
	}

	table[loc].next = curr;
	if (pre = -1) return loc; // new first item
	table[pre].next = loc;
	return head;
}

int check = Search(table,key);
if (check < 0){
	AddToTable(table,char,check,head);
}

// (c)

TreeNodePtr InorderPredecessor(Node root){
	if(root == NULL) return NULL;
	TreeNodePtr temp;
	temp = root;

	root = root->leftPtr
	TreeNodePtr pre;
	while (root->rightPtr !== NULL){
		pre = root;
		root = root->rightPtr;
	}
		temp->data = root->data;
		pre->leftPtr = root->leftPtr;
		pre-rightPtr = NULL;

		return temp;
}

// (d)

int SumOfLevels (TreeNodePtr root){
	return Sum(0,root);
}

int Sum(int level , TreeNodePtr r){
	if (r == NULL) return 0;
	return level + Sum(level+1,r->leftPtr) + Sum(level+1,r->rightPtr);
}