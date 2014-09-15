#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WordSize 300


/*  
	This program scans an entire line and puts a interger values that indicates the synonyms
	using those intergers i was able to traverse the binary tree and do the  appropriate operations
*/


struct treeNode {
	struct treeNode *leftPtr;
	char data[WordSize];
	int num;
	struct treeNode *rightPtr;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;





// function prototypes
void insertNode( TreeNodePtr *treePtr, char * value, int n);
void ChangeNumber(TreeNodePtr treePtr,int current,int new);
void WordAndSynonyms(FILE*out,TreeNodePtr treePtr);
void Synonyms(FILE*out,TreeNodePtr treePtr,char *word,int number);
void Single1(FILE*out,TreeNodePtr treePtr);
void Single2(FILE*out,TreeNodePtr treePtr,char *word,int number);

TreeNodePtr rootPtr = NULL;



int main() {
		printf("\nCOMP2000 Assignment 2\n\nStudent # : 812000767\n\n\n\n********** Thesaurus ************* \n\n\n");
		
	
	char word[WordSize];
	char tempword[WordSize];
	
	int x = 0, i = 0, j=0, k=0, count=0;
	FILE*in = fopen("input.txt","r");
	FILE*out = fopen("output.txt","w");
	

			
     while(fgets(word,WordSize,in) != NULL){
     	i=0;
     
     			x = strlen(word);

				if (word[i] != '\n' ){

					while ( i <= x && j < x ){
						if (word[i] >= 'A' && word[i] <= 'z'){
							tempword[j] = word[i];
							j++;
						}

						else {
							if (tempword[0] != '\0'){

								int x=0; 
									x = strlen(tempword);
								
								    insertNode(&rootPtr,tempword,count);

							}
								for (j=0;j<x+1;j++){
									tempword[j] = '\0';
								}
								j=0;
						}
						i++;
					}
				}

		for (i=0;i<x+1;i++){
			word[i] = '\0';
			tempword[i] = '\0';
		}

		count++;	
	}
	
	fprintf(out,"%15s       %s\n","Words","Synonyms");
		WordAndSynonyms(out,rootPtr);
		fprintf(out,"\n\n\n\n");
	fprintf(out,"%15s       %s\n","Words","Synonyms");
		Single1(out,rootPtr);
		fprintf(out,"\n");
		
	
	

	



fclose(in);
fclose(out);
system ("PAUSE");
return 0;

}


// FUNCTIONS

// insert node in to tree

void insertNode( TreeNodePtr *treePtr, char * value ,int n)
{
	// if tree is empty
	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			strcpy((*treePtr)->data,value);
			(*treePtr)->num = n;
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
			insertNode( &((*treePtr)->leftPtr),value,n);
		}
		// data to insert is greater than data in current node
		else if( strcmp(value,(*treePtr)->data) > 0 ) {
			insertNode( &((*treePtr)->rightPtr),value,n);
		}
		else{
			// this line changes the words from before in the binary tree
			// to have the same value as these words being entered
			// therefore they are synonyms
			ChangeNumber(rootPtr,(*treePtr)->num,n);
		}
	}
}


// groupping all synonyms together 

void ChangeNumber(TreeNodePtr treePtr,int current,int new)
{
	char temp[WordSize];
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		ChangeNumber(treePtr->leftPtr,current,new);
		
		strcpy(temp,treePtr->data);
		if(treePtr->num == current )
			treePtr->num = new;
	
		ChangeNumber(treePtr->rightPtr,current,new);
	}
}



// print the word and its synonyms
void WordAndSynonyms(FILE*out,TreeNodePtr treePtr)
{
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		WordAndSynonyms(out,treePtr->leftPtr);
	
		fprintf(out,"\n%15s       ",treePtr->data);
		Synonyms(out,rootPtr,treePtr->data,treePtr->num) ;
		//printf("\n");
		WordAndSynonyms(out,treePtr->rightPtr);
	}
}



// Printing out synonyms of a word

void Synonyms(FILE*out,TreeNodePtr treePtr,char *word,int number)  
{

	// if tree is not empty, traverse
	if (treePtr != NULL) {
		Synonyms(out,treePtr->leftPtr,word,number);
		
		if ( (strcmp(word,treePtr->data) != 0) && (treePtr->num == number) )
			fprintf(out,"%s ",treePtr->data);
	
		Synonyms(out,treePtr->rightPtr,word,number);
	}
}




void Single1(FILE*out,TreeNodePtr treePtr)
{
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		Single1(out,treePtr->leftPtr);
		
			if(treePtr->num != -1){
				fprintf(out,"\n%15s       ",treePtr->data);
				Single2(out,rootPtr,treePtr->data,treePtr->num) ;
			}
			
		Single1(out,treePtr->rightPtr);
	}
	
}


void Single2(FILE*out,TreeNodePtr treePtr,char *word,int number)  
{

	// if tree is not empty, traverse
	if (treePtr != NULL) {
		Single2(out,treePtr->leftPtr,word,number);
		
		if ( (strcmp(word,treePtr->data) != 0) && (treePtr->num == number) && (treePtr->num != -1)){
			fprintf(out,"%s ",treePtr->data,treePtr->num);
			treePtr->num = -1;
			
		}
		Single2(out,treePtr->rightPtr,word,number);
	}
}



