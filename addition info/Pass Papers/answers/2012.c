// Number 1

// (a)

int numLeaves(TreeNodePtr root){
	if(root == NULL) return 0;
	if(root->leftPtr == NULL && root->rightPtr == NULL)
		return 1;
	return numLeaves(root->leftPtr) + numLeaves(root->rightPtr);
}


// (b)

void Interchange(TreeNodePtr root){
	TreeNodePtr temp;

	if (root != NULL){
		Interchange(root->leftPtr);
		Interchange(root->rightPtr);

		temp = root->leftPtr;
		root->leftPtr = root->rightPtr;
		root->rightPtr = temp;
	}
}

// (c) (i)


void insertNode( TreeNodePtr *treePtr, int value){
	// if tree is empty
	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else {
			printf("%d not inserted, out off memory.\n",value);
		} 
	}

	else { // tree not empty
		// data to insert is less than data in current node
		if (value < (*treePtr)->data){
			insertNode( &((*treePtr)->leftPtr),value);
		}
		// data to insert is greater than data in current node
		else if( value > (*treePtr)->data) {
			insertNode( &((*treePtr)->rightPtr),value);
		}
		else{
			 // the value is the same so its not inserted
		}
	}
}



// (C) (ii)

int TreeSearch(TreeNodePtr root,int key){
	if (root == NULL) return NULL;

	else{
		if (root->data == key) return root;
		if (root->data > key)  return TreeSearch(root->leftPtr);
		if (root->data < key)  return TreeSearch(root->rightPtr);
	}
}




// (d) (i)

int deleteMin(TreeNodePtr root){
	Node curr = root;
	while(curr->leftPtr != NULL)
		curr = curr->leftPtr;

	int temp = curr->data;
		curr = curr->rightPtr;
		return temp;
}

// (d) (ii)




// Number 2

int search (int list[],int key){
	int loc = h1(key) , count=0,del;

	if(list[loc] == key) return loc;

	while (list[loc] != Empty){
		if (list[loc] == key) return loc;

		else if (list[loc] == Delete && count <1){
			del = loc;
			count = 1;
		}
	}

	if (count == 1){
		list[del] = key;
		return del;
	}

	else {
		list[loc] = key;
		return loc;
	}
}



