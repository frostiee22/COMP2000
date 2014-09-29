  // finding the number of nodes in a tree
int numNode (TreeNodePtr root){
	if(root == NULL) return 0;
	return 1 + numNode(root->leftPtr) + numNode(root->rightPtr);
}

/////////////////////////////////////////////////////////////////////////////

	// finding the number of leaves in a tree
int numLeaves(TreeNodePtr root){
	if(root == NULL) return 0;
	if(root->leftPtr == NULL && root->rightPtr == NULL)
		return 1;
	return numLeaves(root->leftPtr) + numLeaves(root->rightPtr);
}

/////////////////////////////////////////////////////////////////////////////

	// height of a tree
#define max(a,b)((a)>(b)?(a):(b))

int height(TreeNodePtr root){
	if (root == NULL) return 0;
	return 1 + max(height(root->leftPtr),height(root->rightPtr)); // compares the values for left and right and 
																 // takes the larger one where it is then added to 
																// 1 which is th root of the tree
}

//////////////////////////////////////////////////////////////////////////////

int sumOfLevels(TreeNodePtr root){
	return SumInt(0,root);
}

int SumInt(int level,TreeNodePtr p){
	if (p == NULL) return 0;
	return level + SumInt(level+1,p->leftPtr) + SumInt(level+1,p->rightPtr);
}

///////////////////////////////////////////////////////////////////////////////

// A[0] size of array
// inode starts at 1
void postOrder(int inode, int A[]){
	if ( inode <= A[0]){
		postOrder(2*inode,A[]);
		postOrder(2*inode+1,A[]);
		printf("%d",A[inode]);
	}
}

// move the print statement to get IN-ORDER and PRE-ORDER

///////////////////////////////////////////////////////////////////////////////

void levelOrder(TreeNodePtr root){
	QueueData newQueueData(TreeNodePtr);
	Queue Q = initQueue();
	enqueue(Q,newQueueData(root));

	while(!empty(Q)){
		QueueData temp = dequeue(Q);
		printf("%s",temp.tnode->data.word);
		if(temp.tnode->left != NULL)
			enqueue(Q,newQueueData(temp.tnode->left));
		if(temp.tnode->right != NULL)
			enqueue(Q,newQueueData(temp.tnode->right));
	}// end while
}// end levelOrder


/////////////////////////////////////////////////////////////////////////////////

int successor (int k){
	// assume num[0] holds size
	if(2*k < num[0]) return 2*k;
	int i = 2*k+1;
	if(i > num[0]) return k;
		while(i < num[0])
			i = i*2;
	return i/2;
}


////////////////////////////////////////////////////////////////////////////////////

TreeNodePtr inOrderSuccessor(TreeNodePtr node){
	if(node->right != NULL){
		node = node->right;
		while(node->left != NULL) node = node->left;
		return node;
	}

	//node has no right subtree; search for the lowest ancestor of the 
	//node for which the node is in the ancestor's left subtree
	//return NULL if there is no successor (node is the last in in-order)
	TreeNodePtr parent = node->parent;
	while(parent != NULL && parent->right == node){
		node = parent;
		parent = node->parent;
	}
	return parent;
}



///////////////////////////////////////////////////////////////////////////////////

  // If the node does not have a pointer that points to its parents node. 
struct Node {
    int data;
    Node * left;
    Node * right;
};


/*   
 *  assume that 'node' is in the tree
 */
Node * find_successor(Node * root, Node * node){
    Node * y = root, * c = NULL;
 
    if (node->right != NULL){
       y = node->right; 
       while (y->left != NULL) y = y->left;
       return y;
    }
 
    while ( y != node && y != NULL ){
      if ( node->data < y->data ){
         c = y; 
         y = y->left;
      }
      else{
         y = y->right;
      }
    }
    return c;
}
 
Node * find_predecessor(Node * root, Node * node){
    Node * y = root, *c = NULL;
    if (node->left != NULL){
       y = node->left;
       while (y->right != NULL) y = y->right;
       return y;
    }
 
    while ( y != node ){
       if (node->data < y->data){
         y = y->left;  
       }
       else {
         c = y;
         y = y->right;
       }
    }
    return c;
}



/////////////////////////////////////////////////////////////////////////////////

 // successor using arrays
int successor (int k){
	// assume num[0] holds size
	if(2*k < num[0]) return 2*k;  // check for if left child is present and returns it
	int i = 2*k+1;
	if(i > num[0]) return k; // check for if right child is present
		while(i < num[0])
			i = i*2;
	return i/2;
}


////////////////////////////////////////////////////////////////////////////////////

void insertNode( TreeNodePtr *treePtr, char * value){
	// if tree is empty
	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			strcpy((*treePtr)->data,value);
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
			
		
		}
		else {
			printf("%d not inserted, out off memory.\n",value);
		} 
	}
	else { // tree not empty
		// data to insert is less than data in current node
		if (strcmp(value,(*treePtr)->data) < 0){
			insertNode( &((*treePtr)->leftPtr),value);
		}
		// data to insert is greater than data in current node
		else if( strcmp(value,(*treePtr)->data) > 0 ) {
			insertNode( &((*treePtr)->rightPtr),value);
		}
		else{
			 // the value is the same so its not inserted
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

/*
*	algorithm for deletion
* 1) the node is a leaf
* 2) (a) the node has no left subtree
*    (b) the node has no right subtree
* 3) the node has non-empty left and right subtrees
*/

deletNode(TreeNode T){
	if(T == NULL) return NULL
	if(right(T) == NULL) return left(T) // cases 1 and 2b
	R = right(T)
	if (left(T) == NULL) return R // case 2b
	if (left(R) == NULL) {
		left(R) == left(T)
		return R
	}

	while (left(R) != NULL){ // will be executed at least once
		P = R
		R = left(R)
	}
	// R is pointing to the in-order successor of T;
	// P is its parent 
	left(R) = left(T)
	left(P) = right(R)
	right(R) = right(T)
	return R
} // end deleteNode

//////////////////////////////////////////////////////////////////////////////////////