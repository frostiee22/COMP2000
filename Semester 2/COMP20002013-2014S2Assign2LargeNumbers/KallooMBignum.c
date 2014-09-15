/*
 * Author   : Mitra Kalloo
 * Student #: 812000767
 * Created on February 11, 2014, 5:33 PM
 */

#include <stdio.h>
#include <stdlib.h>

#define MaxLength 500

/*
 * this program is used to add very large integer values using link list
 * and using an integer value stored in a variable to be added to a large
 * integer stored in a linked list
 */





typedef struct NodeStruct Node;
        struct NodeStruct {
               int data;
               Node *next;
               };


// function prototypes
Node *addingTwoList(Node *top1,Node *top2,int k);
Node *addingTwoNumbers(Node *top1,int num,int k);
Node *createNode (int n);
Node *getLast(Node *top);
Node *insertAtTop(Node *top,int n);
Node *insertAtEnd(Node *top,int data);
Node *find(Node *top, int index);
int size(Node *top);
void printList (Node *top,FILE*out);
int length(char x[MaxLength]);
Node *deletelist(Node *top);

int main() {

    FILE * in = fopen("input.txt","r");
    FILE * out = fopen("output.txt","w");

    Node *top1,*top2,*top3;
    char letter;


    fscanf(in,"%c",&letter);
    while(!feof(in)){

        top1 = top2 = top3 = NULL;
    	int A,B;

        if (letter == 'A' || letter == 'a'){
        	char expressionA[MaxLength],expressionB[MaxLength];
    		int count,n,k;


			    fscanf(in,"%s %s",&expressionA,&expressionB);


		// finding the size of the list
			A = length(expressionA);
			B = length(expressionB);


		 //	finding the longest list

		            if (A >= B)
		                  k = A;
		            else
		                  k = B;




		    // inserting items into link list in reverse order from
		    // least significant to most
		    // this helps in adding them together since we add from
		    // least significant to most

		     for (count=0;count<k;count++){
		             	if (count < A){
		    				n = expressionA[count]-'0' ;
		    				top1 = insertAtTop(top1,n);
		             	}
		             	if (count < B){
		    				n = expressionB[count]-'0' ;
		    				top2 = insertAtTop(top2,n);
		             	}
		             }

		    // end inserting items into link list


		            top3 = addingTwoList(top1,top2,k);

		            fprintf(out,"A) %s + %s = ",expressionA,expressionB);
		            printList(top3,out);
		            fprintf(out,"\n");

		            // deleting the list to free memory
			        top1 = deletelist(top1);
			        top2 = deletelist(top2);
			        top3 = deletelist(top3);
		}

		//  end IF is A

        else if (letter == 'B' || letter == 'b'){
        	int number,k,count=0,n;
        	char expressionA[MaxLength];

        	fscanf(in,"%d %s",&number,&expressionA);

        	n = number;
        	// getting the length of the integer value
        	while ( n != 0){
        	 		 n = n/10;
        	 		 count++;
        	 	 }
        	 	 
        	A = length(expressionA);	 
        	B = count;
        	 
        	


        	 //	finding the longest value

        	 		            if (A >= B)
        	 		                  k = A;
        	 		            else
        	 		                  k = B;


		    // inserting items into link list in reverse order from
		    // least significant to most
		    for (count=0;count<A;count++){
		    	n = expressionA[count] - '0';
		    	top1 = insertAtTop(top1,n);
		    }

        	top2 = addingTwoNumbers(top1,number,k);

        	fprintf(out,"B) %d + %s = ",number,expressionA);
        	printList(top2,out);
		    fprintf(out,"\n");

        	// deleting the list to free memory
            top1 = deletelist(top1);
			top2 = deletelist(top2);
        }


       fscanf(in,"%c",&letter);
    }

    printf("\nCOMP2000 Assignment 2\n\nStudent # : 812000767\n\n\n\n********** Bignum ************* \n\n\n");


    fclose(in);
    fclose(out);

    system("PAUSE");
    return 0;
}



// FUNCTIONS


// adding two link list together
Node *addingTwoList(Node *top1,Node *top2,int k){

Node *n,*m,*o;
Node *temp;
temp = NULL;

int a = 1;

while (a <= k){

	// a is the location in the link list to check
	// n and m are the values stored in location a in both list
	n = find(top1,a);
	m = find(top2,a);

        int sum;


        if(n != NULL && m != NULL)
        	sum = (*n).data + (*m).data;

        else if (n != NULL && m == NULL)
        	sum = (*n).data;
        
        else if (n == NULL && m != NULL)
        	  sum = (*m).data;
        


        // carry
        if (sum >=10){
         	sum = sum%10;

		  o = find(top1,a+1); //  check is the next node in the list to check if NULL or NOT
         	if(o != NULL){
        		(*o).data = (*o).data + 1;
                        /* 1 was add because thats the biggest number that could be carried when adding 2
                         * digits
        				*/
                     }

            // check to see if the list top1 is null so the addition
            // of a new node to place the carry can be inserted at the end
            if(o == NULL ){
            	top1 = insertAtEnd(top1,1);
            		if (a==k)  // the if prevents it from increasing k many times
                       	k = k+1; // used to go one more time in the while loop
                       			// since the list got larger by one
            }
	}
        // end carry

      temp=insertAtTop(temp,sum);


a++;
}

return temp;

}

// adding a number stored in and int to a linked list
Node *addingTwoNumbers(Node *top1,int num,int k){
	Node *n,*o;
Node *temp;
temp = NULL;

int a = 1;
int data;

while (a <= k){
n = find(top1,a);

data = num % 10;
int sum;


        if(n != NULL && num != 0)
        	sum = (*n).data + data;
        
        else if (n != NULL && num == 0)
        	sum = (*n).data;
        
        else if (n == NULL && num!= 0)
        	  sum = data;
        


        // carry
        if (sum >=10){
         	sum = sum%10;

		  o = find(top1,a+1);
		    if(o != NULL){
        		(*o).data = (*o).data + 1;
                        /* 1 was add because thats the biggest number that could be carried when adding 2
                         * digits
        				*/
                     }

                      // check to see if the list top1 is null so the addition
            		// of a new node to place the carry can be inserted at the end
                    if(o == NULL ){
                        top1 = insertAtEnd(top1,1);
                        if (a==k)  // the if prevents it from increasing k many times
                       	  k = k+1; // used to go one more time in the while loop
                       			// since the list got larger by one
                        }
	}
        // end carry

      temp=insertAtTop(temp,sum);

      num = num /10;
a++;
}

return temp;
}

// creating a new node
Node* createNode (int n) {
      Node *newNode;
      newNode = (Node*)malloc(sizeof(Node));
      newNode -> data = n;
      newNode -> next = NULL;
      return newNode;
      }

// getting the address of the last node
Node *getLast(Node *top){
	Node *current;
	Node *last;
	last = current = top;

	while ( current != NULL){
		last = current;
		current = current -> next;
	}
	return last;
}

// inserting at top  of link list
Node *insertAtTop(Node *top,int n){
    Node *newNode;
    newNode = createNode(n);
    newNode -> next = top;
    top = newNode;
    return top;
}
// inserting at end of link list
Node *insertAtEnd(Node *top,int data){
	Node *newNode;
	newNode = createNode(data);
	Node *last;

	if (top == NULL){
		top = newNode;
	}
	else {
		last = getLast(top);
		last -> next = newNode;
	}
	return top;
}

//find a number in node
Node *find(Node *top, int index){
    int count;
    Node *current;
    current = top;
    count = 1;

        if(  size(top) >= index){
                while(count < index){
                 count++;
                  current = (*current).next;
                }

        return current;
        }
        else return NULL;
    }

//size of list function
int size(Node *top){
    int count;
    Node *current;
    current = top;
    count = 0;
        while (current != NULL){
            count++;
        current = (*current).next;
            }
        return count;
    }

// printing out all the items of a link list
void printList (Node *top,FILE*out){
    Node *current;
    current = top;

    while(current != NULL){
        fprintf(out,"%d",current -> data);
        current = current -> next;
    }
}

//size of enter expression
int length(char x[MaxLength]){
int i = 0;
int size=0;
while(x[i] != '\0'){
        size++;
        i++;
}
return size;
}

// delete list
Node *deletelist (Node *top){

	Node *toDelete;
	Node *current;
	current = top;
	while (current != NULL){
		toDelete = current;
		current = current -> next;
		free(toDelete);
	}
	//return NULL;
}

