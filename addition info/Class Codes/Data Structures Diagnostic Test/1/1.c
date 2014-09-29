#include <stdio.h>
#include <stdlib.h>


typedef struct NodeStruct Node;
        struct NodeStruct {
               int data;
               Node *next;
               };

// function prototypes
Node *createNode (int n);
Node *insertOrdered(Node *top, int c);
void printList(Node *top);





int main() {

	Node *top;
	
	top = NULL;

int sum = 455;
int sum1 = 999;
int sum2 = 4543; 
int sum3 = 345;





top = insertOrdered(top,sum);
top = insertOrdered(top,sum1);
top = insertOrdered(top,sum2);
top = insertOrdered(top,sum3);

printList(top);


printf("\n\n");
system ("PAUSE");
return 0;
}


// ----->  FUNCTIONS  <-----

// creation of node
Node* createNode (int n) {
      Node *newNode;
      newNode = (Node*)malloc(sizeof(Node));
      newNode -> data = n;
      newNode -> next = NULL;
      return newNode;
      }




// inserting char in order into a link list
Node *insertOrdered(Node *top, int	c){
	
	if (top == NULL){
		Node *newNode;
	    newNode = createNode(c);
	    newNode -> next = top;
	    top = newNode;
	    return top;
	}
		
	int x, y;
	Node *temp;
	
	x = c ;
	y = top->data;

	if (x <= y){
		temp = createNode(c);
		temp->next = top;
		return temp;
	}
	else {
		top->next = insertOrdered(top->next, c);
		return top;
	}
}





// printing out a list
void printList(Node *top){
	if (top == NULL)
		return;
	printf("%d \n", top->data);

	printList(top->next);

}


