#include <stdio.h>
#include <stdlib.h>


typedef struct NodeStruct Node;
        struct NodeStruct {
               int data;
               Node *next;
               };


//Function Prototypes
Node *insertAtTail(Node *top,int c);
Node* createNode (int n);



int main() {
	
	int x;
	printf("please enter a number \n");
	scanf("%d",&x);






system("PAUSE");
return 0;
}


// -----> FUNCTIONS <-----

Node *



Node *insertAtTail(Node *top,int c){
	if (top == NULL)
		return createNode(c);
	else 
		top->next = insertAtTail(top->next,c);	
	
	return top;
}


// creation of node
Node* createNode (int n) {
      Node *newNode;
      newNode = (Node*)malloc(sizeof(Node));
      newNode -> data = n;
      newNode -> next = NULL;
      return newNode;
      }
