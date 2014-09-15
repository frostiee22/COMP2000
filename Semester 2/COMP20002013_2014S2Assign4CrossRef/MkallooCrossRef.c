/* 
 * File:   main.c
 * Author: Mitra
 *
 * Created on March 18, 2014, 5:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLine 10000
#define MaxWordSize 100


/*
* PROBLEM :
* getting the line number of identifiers in a .c file where reserved words are not included
* Identifiers within string constants (delimited by double quotes) or comments (delimited by /*) 
* are not to be included. Identifiers within // comments are not to be included. 
* Identifiers within single quotes (character constants) are not to be included.
*
* SOLUTION :
* first is to store an entire line and check it for comments and and quotes
* on finding comments and quotes, replace item between them with a reamdom char other than an alpha char.
* Then we get the words from the line we stored and first check it against the list of reserved words.
* if the word is a reserved word we skip it and move on to the next word. if the word is not a reserved word  
* it is added to another search tree and its line number is inserted.
* when processing all the lines in the input file . Using an inorder traversal all the items and their line(s) number is printed
*/





struct treeNode {
	struct treeNode *leftPtr;
	char data[MaxLine];
	char test[MaxLine];
	int num[MaxLine];
	int pos;
	struct treeNode *rightPtr;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;



//Function prototypes
void insertNode( TreeNodePtr *treePtr, char * value, char * test);
void Wordlist(TreeNodePtr *treePtr, char * value,char * test, int line);
int Search(TreeNodePtr *treePtr, char * value);
int getWord(char line[], char str[]);
void print(FILE*,TreeNodePtr treePtr);


int main(int argc, char** argv) {
        
        TreeNodePtr rootPtr = NULL;
	TreeNodePtr wordList = NULL;

	FILE*in = fopen("input.txt","r");
	FILE*out = fopen("output.txt","w");
	
	char line[MaxLine] = {'\0'};
	char temp[MaxLine] = {'\0'};
	char word[MaxWordSize] = {'\0'};
	int i,k,l,x;

	
		fscanf(in,"%s",&line);
		while (strcmp(line,"ENDOFLIST") != 0){
			
			
		k = l = 0;
		
		x = strlen(line); // getting the length of the word
		
		for (i=0;i<x;i++){
			k = tolower(line[i]);   // converting letter to lowercase then to an integer
			
			if ( k >= 97 && k <= 122){
				temp[l] = tolower(line[i]);   // adding the letters only to a new list
					l++;
			}
			
		}
			
			// storing reserved words
			insertNode(&rootPtr,line,line);  
			
			for(i=0;i<l;i++)
				temp[i] = '\0';  //resetting temp array
			
		fscanf(in,"%s",&line);
		}
	
	
	int lineNo=1; // line starting at 1
	int multiline = 0; // no multi comment line(s) found yet
	
     while(fgets(line,MaxLine,in) != NULL){
    	
     	fprintf(out,"[%3d] %s",lineNo,line); // printing out the lines and line number to output file
     	
       x = strlen(line);
       
     	for (i=0;i<x;i++){
     		
     			int z = line[i];  // getting interger version on a char
     			
     		if (line[i] == '/' && line[i+1] == '/'){
                    i=i+2;
     			while (i<x){
     				line[i] = '/';  // putting '/' after // till the end of the line
     				i++;
     			}
     		}	
     		
     		else if (line[i] == '/' && line[i+1] == '*'){
     			if (multiline == 0)
     				multiline++;  // if /* is meet a multi line is found s
			}
    	
     		else if (line[i] == '*' && line[i+1] == '/' && multiline > 0){
    			multiline--; // if */ is meet a multi line ended
    		}
     		
     		else if (line[i] == '"'){
     			i++;
     			while (line[i] != '"'){
     				line[i] = '"';  // putting '"' between the double quotes
     				i++;
     			}
     		}
     		
     		else if (z == 39){ // 39 is the interger number for single quotes
     			z = line[i+1];
     			while (z != 39){
     				line[i] = '"'; // putting quotes between single quotes
     				i++;
     				z = line[i];
     			}
     		}
     		
     		if (multiline != 0){
     			line[i] = '*';  // to remove all the identifiers between /*..*/
     		}
     		
     	}
     	
     	
     	
		if (multiline == 0){  // when value is 0 there no no multiline comments being processed
		     	while (getWord(line,word) != 0){
		     		
		     		k = l = 0;
				
					x = strlen(word); // getting the length of the word
				
					for (i=0;i<x;i++){
						k = tolower(word[i]);   // converting letter to lowercase then to an integer
						
						if ( k >= 97 && k <= 122){
							temp[l] = tolower(word[i]);   // adding the letters only to a new list
								l++;
						}	
					}
		     		
			     	if (Search(&rootPtr,word) == 0)   // searching to see is temp is a reserved word, if it is not it returns 0
			     		Wordlist(&wordList,word,word,lineNo); // inserting identifier and its line number to wordlist search tree
		     	
		     		
		     			for(i=0;i<l;i++)
						temp[i] = '\0';  // resetting temp array
		     	}
     	
     	}
     lineNo++; // increamenting the line number
     }
	fprintf(out,"\n\n\n");
	fprintf(out,"%-20s line number(s)\n","words");
	fprintf(out,"***************************************************************************\n");
	print(out,wordList); //  printing out the list of word with their line(s) number from wordlist search tree
	
	printf("\nCOMP2000 Assignment 4\n\nStudent # : 812000767\n\n\n\n********** CrossRef ************* \n\n\n");
	
	
	fclose(in);
	fclose(out);
	
   
    
    return (EXIT_SUCCESS);
}


// FUNCTIONS

//////////////////////////////////////////////////////////////////////////////////////////////////

void insertNode( TreeNodePtr *treePtr, char * value, char * test){
	 //if tree is empty
		 
	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			strcpy((*treePtr)->data,value);
			strcpy((*treePtr)->test,test); // lower case version of word
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
			insertNode( &((*treePtr)->leftPtr),value,test);
		}
		// data to insert is greater than data in current node
		else if( strcmp(test,(*treePtr)->test) > 0 ) {
			insertNode( &((*treePtr)->rightPtr),value,test);
		}
		else{
			// word already present in the list
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////

void Wordlist(TreeNodePtr *treePtr, char * value,char * test, int line){
	// if tree is empty

	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			strcpy((*treePtr)->data,value);
			strcpy((*treePtr)->test,test);
			(*treePtr)->pos = 0; // location value
			(*treePtr)->num[0] = line; // storing first instance of a word and its line
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else {
			printf("%s not inserted, out off memory.",value);
		}
	}
	else { // tree not empty
		
		if (strcmp(test, (*treePtr)->test) < 0){
			Wordlist(&((*treePtr)->leftPtr), value,test, line);
		}
		
		else if (strcmp(test, (*treePtr)->test) > 0) {
			Wordlist(&((*treePtr)->rightPtr), value,test, line);
		}
		else{
			// word found so the line number where it is found is added to  the array
			(*treePtr)->pos++;
			int x = (*treePtr)->pos;
			(*treePtr)->num[x] = line;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////

int Search(TreeNodePtr *treePtr, char * value){
	// if tree is empty
	if (*treePtr == NULL){
		return 0;  // not found 
	}
	else { // tree not empty
		
		// value and test are both in lower case letters
		
		if (strcmp(value, (*treePtr)->test) < 0){  
			Search(&((*treePtr)->leftPtr), value);
		}
		
		else if (strcmp(value, (*treePtr)->test) > 0) {
			Search(&((*treePtr)->rightPtr), value);
		}
		else{
			
			return 1;   // found
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

int getWord(char line[], char str[]){
	static int p = 0;
	int n = 0;
	
	while (line[p] != '\0' && !isalpha(line[p])) p++;
	if (line[p] == '\0') return p = 0;
	str[n++] = (line[p++]);
	while (isalpha(line[p])){
		if (n < MaxWordSize) str[n++] = (line[p]);
		p++;
	}
	str[n] = '\0';
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////

void print(FILE*out,TreeNodePtr treePtr){
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		print(out,treePtr->leftPtr);
			fprintf(out,"%-20s  ",treePtr->data);
			int x = treePtr->pos;
			int i;
			for (i=0;i<=x;i++)
				fprintf(out,"%d ",treePtr->num[i]);
			fprintf(out,"\n");
		print(out,treePtr->rightPtr);
	}

}
