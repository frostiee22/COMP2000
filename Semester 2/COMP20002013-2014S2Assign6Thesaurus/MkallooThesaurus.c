
/*
 * NAME :      Mitra Kalloo
 * Student # : 812000767
*/



/*
 * PROBLEM
 * Data for the program consists of lines of input. Each line contains a (variable) number of distinct words, all of which are synonyms
 * Words may be spelt using any combination of upper and lower case letters.  All words are to be stored in a hash table using 
 * "open addressing with double hashing".  A word can appear on more than one line, but each word must be inserted only once in the table.  
 * If a word appears on more than one line then all words on those lines are considered synonyms.
 *
 *
 *
 *
 *
 * SOLUTION
 * first is to create a interget value in a struct so it can whole number. this number will be used to distinguish between synonyms of words.
 * then when a word is scanned it is then converted to a number value to be used for hashing. 
 * on the second part to print a word and a synonyms we find the line number of the word we inputed then search for words that have the same line number.
 * In adding a new word to be a synonym of another word we first check to see if the synonym exist. then we check the word to be added if it exit that word
 * and its synonyms are synonyms to the second scann word.
 * lastly in deleting a word we first unlink it for the next field from the struct then put the word value to '*' and the line number to -3
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MaxWords 500
#define WordSize 500
#define N 499
#define Empty ""
#define Deleted "*"   // to show a word was deleted from the hashtable
#define unlink -3    // used to remove a word from a list of synonyms when deleting



typedef struct {
    char word[WordSize];  // store a word
    int lineNo;			  // store indicator for synonyms
    int next;             // store an interger for a location to another position in the hashtable
}WordInfo;



// Function Prototypes
int search(WordInfo table[], char key[]);
int convertToNumber(char key[]);
int addToTable(WordInfo table[], char key[],int lineNo, int loc, int head);
int find( WordInfo table[], int head, char key[]);
void printResults(FILE*out, WordInfo table[],int lineNo, int head);
void changer(WordInfo table[],int pre,int curr,int head);
void un_link(WordInfo table[],char key[],int head);



int first = -1;
int numWords = 0;
int main(){


    int j;
    WordInfo wordTable[N + 1];
        for (j = 0; j <= N; j++)strcpy(wordTable[j].word, Empty);

        FILE*in = fopen("input.txt", "r");
        FILE*out = fopen("output.txt", "w");

        char word[WordSize];
        char tempword[WordSize];

            int x = 0, i = 0, count=0;
			j=0;
			int stop = 0;

                    while(stop != 1){
                    	fgets(word,WordSize,in);
                            i=0;

                                    x = strlen(word);

                                    if (word[i] != '\0' ){

                                        while ( i <= x){
                                            if (word[i] >= 'A' && word[i] <= 'z'){
                                                tempword[j] = word[i];   // getting only the letters and storing it in and array

                                                j++;
                                            }

                                            else {

                                                if (tempword[0] != '\0'){

                                                	if (strcmp(tempword,"ENDOFSYNONYMS") == 0)
                                                		stop  = 1;       // checking for stopping condition

													else {

                                                        int loc = search(wordTable,tempword);

															if (loc > 0) {
																// exist already
																// word of this line are synonyms or words of another line
																changer(wordTable,wordTable[loc].lineNo,count,first);

																}
															else
															if (numWords < MaxWords){
																first = addToTable(wordTable,tempword,count,-loc, first);
																++numWords;
															}
															else fprintf(out, "'%s' not added to table \n",tempword);
													}
                                                }
                                                int y = strlen(tempword);
                                                for (j=0;j<=y;j++)
                                                        tempword[j] = '\0';
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


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

        char choice;
        fscanf(in,"%c",&choice);

        while (choice != 'E'){

            if (choice == 'P'){
                char word[WordSize];
                fscanf(in,"%s",word);
                int post;
                 int loc = search(wordTable,word);
				if (loc > 0) {
					 post = wordTable[loc].lineNo;

		                int head = first;
		        	fprintf(out,"%-13s : ",word);

		                while (head != -1){
							if (wordTable[head].lineNo == post && strcmp(wordTable[head].word,word) !=0)
								fprintf(out,"%s ",wordTable[head].word);
							head = wordTable[head].next;
						}

		                fprintf(out,"\n");
				}
				else {
					fprintf(out,"'%s' not present in table\n",word);
				}
            }

            else if (choice == 'A'){
            	char present[WordSize];
            	char add[WordSize];
            	fscanf(in,"%s %s",add,present);
            	int post;
            	int loc = search(wordTable,present);
				if (loc > 0) {
					 post = wordTable[loc].lineNo;

					 loc = search(wordTable,add);
						if (loc > 0) {
							// if a word to be added exist already then that word and its words are add to the other word
							changer(wordTable,wordTable[loc].lineNo,post,first);

						}
						else {
							 if (numWords < MaxWords){
								first = addToTable(wordTable,add,post,-loc, first);
								++numWords;
							}
							else fprintf(out, "'%s' not added to table \n",add);
					 	}
            	}


            	else fprintf(out, "'%s' was not found therefore '%s' was not added \n",present,add);

            }
            else if (choice == 'D'){
            	char word[WordSize];
                fscanf(in,"%s",word);
                un_link(wordTable,word,first);

            }
           fscanf(in,"%c",&choice);
        }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

printf("\nCOMP2000 Assignment 6\n\nStudent # : 812000767\n\n\n\n********** Thesaurus ************* \n\n\n");

        fclose(in);
        fclose(out);
        system("PAUSE");
        return 0;

}






// FUNCTIONS


// searching for a hash location or finding if a word is present already
int search(WordInfo table[], char key[]){
    int keyNum = convertToNumber(key);
    int loc = keyNum % N + 1;
    int k = keyNum % (N - 2) + 1;
	int post,check = 0;

    while ((strcmp(table[loc].word, Empty) != 0) && (strcmp(table[loc].word, key) != 0)){
    	
    	if (strcmp(table[loc].word, Deleted) == 0 && check == 0){ // looking for a deleted location
    		post = loc;
    		check = 1;
    	}

	    	if (check == 1){
	    		loc = loc + k;
	        	if (loc > N)loc = loc - N;
	    	}

	    	else {
		        loc = loc + k;
		        if (loc > N)loc = loc - N;
		    }

    }
    if (strcmp(table[loc].word, Empty) == 0  && check == 1) return -post; // return the postion of a deleted word so it can be used
    if (strcmp(table[loc].word, Empty) == 0) return -loc;
    return loc;
}

// making a word to a number so it can be use for hashing
int convertToNumber(char key[]){
    int j = 0, keyNum = 0, w = 3;
    while (key[j] != '\0'){
        keyNum += w*key[j++];
        w = w + 2;
    }
    return keyNum;
}

// adding item to hash table and sorting the key values in alpha ordering
int addToTable(WordInfo table[], char key[],int lineNo, int loc, int head){
    strcpy(table[loc].word, key);
    table[loc].lineNo = lineNo;

    int curr = head;
    int prev = -1;
    while (curr != -1 && (strcmp(key, table[curr].word) > 0)){
        prev = curr;
        curr = table[curr].next;
    }
    table[loc].next = curr;
    if (prev == -1) return loc;
    table[prev].next = loc;
    return head;
}


// finding the item in part2 of question and returning its location
int find( WordInfo table[], int head, char key[]){
    while (head != -1){
        if (strcmp(table[head].word, key) == 0){
            return head;
        }
        head = table[head].next;
    }

    return 0;
}


// printing out the hash table using the next field
void printResults(FILE*out, WordInfo table[],int lineNo, int head){
    while (head != -1 ){
        printf("%s  %d %d\n", table[head].word,table[head].lineNo,table[head].next);
        head = table[head].next;

    }
}

// changing words of a certain line number to a different number
void changer(WordInfo table[],int pre,int curr,int head){
	while (head != -1){
		if (table[head].lineNo == pre)
			table[head].lineNo = curr;
		head = table[head].next;
	}
}


// deleting a word from the hash table
void un_link(WordInfo table[],char key[],int head){

	int curr,next;
	curr = next = head;

	if (strcmp(key,table[head].word) == 0 ){
         strcpy(table[head].word,Deleted);
         table[head].lineNo = unlink ;
         first = table[head].next;
         numWords--;
	}

	else{

		while (strcmp(key,table[head].word) != 0 && head != -1){
			curr = next;
			next = table[head].next ;
			head = table[head].next;
		}

		table[curr].next = table[next].next;
		table[next].lineNo = unlink ;
		strcpy(table[next].word,Deleted);
		numWords--;
	}

}
