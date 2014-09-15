#include <stdio.h>
#include <stdlib.h>

#define maxsize 100

struct treeNode {
	struct treeNode *leftPtr;
	int datax;
	int datay;
	int num;
	struct treeNode *rightPtr;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;


int x = 0;
int temp = 0;
int add = 0;
long int array[maxsize][maxsize];





// function prototypes
void ShortestPath(FILE*out,int M,int N,int p,int q,int X,int Y,int U,int V,long int a[maxsize][maxsize],int count,int weight);
int  findPath(FILE*out,int M,int N,int p,int q,int X,int Y,int U,int V,long int a[maxsize][maxsize],int count,int weight);
void insertNode( TreeNodePtr *treePtr, int datax,int datay ,int n);
void inOrder(FILE*out,TreeNodePtr treePtr);


 TreeNodePtr rootPtr = NULL;

int main() {
	

	printf("\nCOMP2000 Assignment 3\n\nStudent # : 812000767\n\n\n\n********** Robot ************* \n\n\n");

	
	FILE*in = fopen("input.txt","r");
	FILE*out = fopen("output.txt","w");


static int M, N, p, q, X, Y, U, V;

char c;
	
		
	fscanf(in,"%d",&M);
	while (!feof (in)){
		
	
	
		fscanf(in,"%d",&N);
		fscanf(in,"%d",&p);
		fscanf(in,"%d",&q);
		fscanf(in,"%d",&X);
		fscanf(in,"%d",&Y);
		fscanf(in,"%d",&U);
		fscanf(in,"%d",&V);
		
		M++;
		N++;
		
		
		
		x = M*N;
	
	

		int h,i;

		for (h=0; h<maxsize; h++){
	      	for (i=0; i<maxsize; i++){
         		array[h][i] = 0;
         	}
		}
			array[U][V] = 9;
	
	ShortestPath(out,M, N, p, q, X, Y, U, V,array,0,0);
		if ( temp == 0){
			fprintf(out,"\nNO SOLUTION \n");
		}
		if (temp != 0){
				for (h=0; h<maxsize; h++){
	      			for (i=0; i<maxsize; i++){
         				array[h][i] = 0;
         			}
				}
			array[U][V] = 9;
			fprintf(out," %d\n",temp);
			findPath(out,M, N, p, q, X, Y, U, V,array,0,temp);
			inOrder(out,rootPtr);
			fprintf(out,"(%d,%d)\n",U,V);
			
			rootPtr->leftPtr = NULL;
			rootPtr->leftPtr = NULL;
			rootPtr = NULL;
			
		}
			
			
	fprintf(out,"\n\n");



M=N=p=q=X=Y=U=V=0;
fscanf(in,"%d",&M);

}


printf("\n\n");
fclose(in);
fclose(out);
system ("PAUSE");
return 0;
}

// FUNCTIONS


// used to find the length os the shortest path
void ShortestPath(FILE*out,int M,int N,int p,int q,int X,int Y,int U,int V,long int a[maxsize][maxsize],int count,int weight){
	

	if (a[X][Y] != 1) {
	
			if ( (Y<1)||(X<1)||(X>M)||(Y>N)){
				return ;
			}
			else if ( (a[X][Y]) == 9) {
				// getting the shortest path and storing it in temp
				if (count < x){
					weight = count;
					temp = weight;
				}	
				return ;	
			}
			else {
			
					a[X][Y] = 1;
				//fprintf(out,"(%d,%d)\n",X,Y);
				count++;
						
						// movement conditions needed to move about the array
						
						ShortestPath(out,M,N,p,q,X+p,Y+q,U,V,a,count,weight);
					
						ShortestPath(out,M,N,p,q,X+p,Y-q,U,V,a,count,weight);
				
						ShortestPath(out,M,N,p,q,X-p,Y+q,U,V,a,count,weight);
						
						ShortestPath(out,M,N,p,q,X-p,Y-q,U,V,a,count,weight);
						
						ShortestPath(out,M,N,p,q,X+q,Y+p,U,V,a,count,weight);
						
						ShortestPath(out,M,N,p,q,X+q,Y-p,U,V,a,count,weight);
						
						ShortestPath(out,M,N,p,q,X-q,Y+p,U,V,a,count,weight);
						
						ShortestPath(out,M,N,p,q,X-q,Y-p,U,V,a,count,weight);
								
		
			}
			
	}
	return ;

}


int s = 0;
int t = 0;
int check = 0;

// uesed to find the locations of the paths that are in the shortest path
int findPath(FILE*out,int M,int N,int p,int q,int X,int Y,int U,int V,long int a[maxsize][maxsize],int count,int weight){
	 	

	if (a[X][Y] != 1) {
	
			if ( (Y<1)||(X<1)||(X>M)||(Y>N)){
				return ;
			}
			else if ( (a[X][Y]) == 9) {	
				
				
				return 1 ;	
			}
			else {
			
					a[X][Y] = 1;
				
				count++;
				check++;
			

							
					if (findPath(out,M,N,p,q,X+p,Y+q,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
							}
					if	(findPath(out,M,N,p,q,X+p,Y-q,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
						
							
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
							}
					if (findPath(out,M,N,p,q,X-p,Y+q,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
						
							
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
								}	
					if(findPath(out,M,N,p,q,X-p,Y-q,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
						
							
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
								}	
					if(findPath(out,M,N,p,q,X+q,Y+p,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
						
								
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
								}		
					if(findPath(out,M,N,p,q,X+q,Y-p,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
						
							
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
							}
					if(findPath(out,M,N,p,q,X-q,Y+p,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
						
							
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
							}
										
					if(findPath(out,M,N,p,q,X-q,Y-p,U,V,a,count,weight) == 1 && count <= weight && ((s!=X)&&(t!=Y))){
							
							
								//fprintf(out,"(%d,%d)\n",X,Y);
								insertNode(&rootPtr,X,Y,check);
								s=X;
								t=Y;
								check++;
								}		
		
				
			}
		
			
	}
	return ;

}


// insert node in to tree 

void insertNode( TreeNodePtr *treePtr, int datax,int datay ,int n)
{
	
	// if tree is empty
	if (*treePtr == NULL ){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL  ){
			(*treePtr)->datax = datax;
			(*treePtr)->datay = datay;
			(*treePtr)->num = n;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
			
		
		}
		else {
			printf("(%d,%d) not inserted, out off memory.\n",datax,datay);
		} 
	}
	else { // tree not empty
		// data to insert is less than data in current node
		if ((*treePtr)->num < n && (*treePtr)->datax != datax && (*treePtr)->datay != datay){
			insertNode( &((*treePtr)->leftPtr),datax,datay,n);
		}
		// data to insert is greater than data in current node
		else if((*treePtr)->num > n && (*treePtr)->datax != datax && (*treePtr)->datay != datay) {
			insertNode( &((*treePtr)->rightPtr),datax,datay,n);
		}
	}
	
}


// print the word and its synonyms
void inOrder(FILE*out,TreeNodePtr treePtr)
{
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		inOrder(out,treePtr->leftPtr);
	
		fprintf(out,"(%d,%d)\n",treePtr->datax,treePtr->datay);
		
		inOrder(out,treePtr->rightPtr);
	}
}






