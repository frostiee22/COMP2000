/*
* NAME      : Mitra Kalloo
* STUDENT # : 812000767
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WordSize 500  //  max size of a word/phrase



/*
*  My method of solving this anagram probem is first,
*  getting only the letter from the word/phrases and checking the amount of letters in them.
*  Then if the amount of letter match up the amount of letter of another word/phrase,
*  the letters are sorted from each word and compared.
*  at this point if there is one mismatch in the letter their are not anagrams
*  if they do math up their are anagrams 
*/ 






struct treeNode {
	struct treeNode *leftPtr;
	char data[WordSize];
	char test[WordSize];
	int num;
	struct treeNode *rightPtr;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;
TreeNodePtr rootPtr = NULL;


// Function Prototypes
void insertNode( TreeNodePtr *treePtr, char * value ,char * test,int n);
int compare(char *first, char *second);
void selectionSorting (char* arr, int size);
void FindWord(FILE*out,TreeNodePtr treePtr,int count);
void search(FILE*out,TreeNodePtr treePtr,char * data,int count);




int main() {


	FILE*in  = fopen("input.txt","r");
	FILE*out = fopen("output.txt","w");

	char word[WordSize];
	char temp[WordSize];
	
		
	while(fgets(word,WordSize,in) != NULL){	
		
		int i,k =0,l=0,x;
		
		x = strlen(word); // getting the length of the word
		
		for (i=0;i<x;i++){
			k = tolower(word[i]);   // converting letter to lowercase then to an integer
			
			if ( k >= 97 && k <= 122){
				temp[l] = tolower(word[i]);   // adding the letters only to a new list
					l++;
			}
			
		}
	
		// inserting the word and its lowcase version
		// the lower case version is used to sort the words
		// in the binary search tree
		// and 0 isused to set the word to not seen 
		insertNode(&rootPtr,word,temp,0);  
		
	}
		
	FindWord(out,rootPtr,1);
	fclose(in);
	fclose(out);



		printf("\nCOMP2000 Assignment 3\n\nStudent # : 812000767\n\n\n\n********** Anagrams ************* \n\n\n");

	system("PAUSE");
	return 0;

}


// FUNCTIONS

// insert node in to tree

void insertNode( TreeNodePtr *treePtr, char * value, char * test,int n){
	 //if tree is empty
		 
	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			strcpy((*treePtr)->data,value);
			strcpy((*treePtr)->test,test); // lower case version of word
			(*treePtr)->num = n; // seen or not seen value
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else {
			printf("%s not inserted, out off memory.",value);
		}
	}
	else { // tree not empty
		// data to insert is less than data in current node
		if (strcmp(test,(*treePtr)->test) < 0){
			insertNode( &((*treePtr)->leftPtr),value,test,n);
		}
		// data to insert is greater than data in current node
		else if( strcmp(test,(*treePtr)->test) > 0 ) {
			insertNode( &((*treePtr)->rightPtr),value,test,n);
		}
		else{
			// word already present in the list
		}
	}
}

int compare(char *first, char *second){
	int x,y,z,i,k;
	int space1=0,space2=0;

	x = strlen(first);  // getthing the size on word/phrase
	y = strlen(second);   // getthing the size on word/phrase
	
	char temp1[WordSize];  // temp word/phrase storage
	char temp2[WordSize];
	
		if (x >= y)  // finding the bigger string 
			z = x;
		else 
			z = y;
		   
	
		x = y = 0;
		for (i=0;i<z;i++){
			k = tolower(first[i]) - 0;   // converting letter to lowerCase then to an integer
			if ( k >= 97 && k <= 122){
				temp1[x] = tolower(first[i]);   // adding the letters only to a new list
					space1++; // checking length of word
					x++;
			}
			
			k = tolower(second[i]) - 0;  // converting letter to lowercase then to an integer
			if (k >= 97 && k <= 122){
				temp2[y] = tolower(second[i]);  // adding the letters only to a new list
					space2++; // checking length of word
					y++;
			}
		}
		
	
	if (space1 == space2){  // checking to see if words are of same size
	
		selectionSorting(temp1,space1);	 // sorting the letter from a-z
		selectionSorting(temp2,space2);   // sorting the letter from a-z
		
		for (i=0;i<space1;i++){
			if ((temp1[i]) == (temp2[i])){   // comparing each letter as we go along
			        // do nothing 
			}
			else 
				return 0; // found a miss match therefore not an anagram
		}
		return 1;	// is a anagram
	}
	return 0; // not an anagram since words are not of same size
}


// selection sort an array of char 
void selectionSorting (char* arr, int size){
	int i=0,y=0;
	char temp;
	for (i=0; i < size - 1; i++){
		int smallest = i;
	 	for (y = i+1; y < size; y++){
			if (arr[y] < arr[smallest])
			smallest = y;
		}
		
		temp = arr[smallest];                     
		arr[smallest] = arr[i];                          
		arr[i] = temp;
	}	
}


// used to get the first word in order and pass it into the search function 
void FindWord(FILE*out,TreeNodePtr treePtr,int count){
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		FindWord(out,treePtr->leftPtr,count);
		if (treePtr->num == 0){
			search(out,rootPtr,treePtr->data,count); // passing the first unseen word to the search function and so on
			fprintf(out,"\n");
		}
		FindWord(out,treePtr->rightPtr,count);
	}

}

// this functions compares all the words in the list that have a data of 0 
// and check to see if it has the same number of letters as the word that cam from
// the FindWord unction
void search(FILE*out,TreeNodePtr treePtr,char * data,int count){
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		search(out,treePtr->leftPtr,data,count);
				if (treePtr->num == 0 && compare(data,treePtr->data) == 1){
				fprintf(out,"%s",treePtr->data);
					treePtr->num = count; // data set to count since the word is seen 
				}                         // so it wont be processes a next time
		search(out,treePtr->rightPtr,data,count);
	}

}





