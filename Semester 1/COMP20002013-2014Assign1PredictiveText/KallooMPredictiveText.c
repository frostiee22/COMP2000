#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WordSize 300

//this program stores the words in the dictionary in alpha ordering into a Linked List
// before storing it , the word is converted to a number and both the worn and number are stored
//in MyList.
//the Numbers from the input file is readed and is compared to the MyList->num
// if the numbers are the same it is printed.



struct ListItem {
	char Item[WordSize];
	char num[WordSize];
	struct ListItem *Next;
};

struct ListItem *MyList = 0 ;
struct ListItem *MyList2 = 0;



// Function prototypes

void WordList1(char *word , char *a);
void deletelist (struct ListItem *top);



int main () {

	//Node * top;

	FILE*in = fopen("input.txt","r");
	FILE*out = fopen("output.txt","w");

	char word[WordSize];
	char a[WordSize];
	char c[WordSize];



	printf("\nCOMP2000 Assignment 1\n\nStudent # : 812000767\n\n\n\n********** Predictive Text ************* \n\n\n");

	printf("-----> Pre-Loading WordList <-----\n");
	printf("\n  PLEASE WAIT ... \n");
	int x = 0, i = 0, j=0, insert;
	char tempword[WordSize];

	for (i=0;i<WordSize;i++){
			word[i] = '\0';
			tempword[i] = '\0';}

	fgets(word,WordSize,in);
     while(word[0] != '$'){
     	i=0;
     			x = strlen(word);

				if (word[i] != '\n'){

					while ( i < x && j < x ){
						if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
							tempword[j] = word[i];
							j++;
						}

						else {
							if (tempword[0] != '\0'){


								int x=0, i=0;
								strcpy(c,tempword);

									x = strlen(tempword);

											for (i=0;i<=x;i++){
												a[i] = '\0';
											}

									// converting the letters into numbers for easy searching and comparing
									for (i=0;i<x;i++){
										if (c[i] == 'a'|| c[i] == 'b'|| c[i] == 'c' || c[i] == 'A' || c[i] == 'B' || c[i] == 'C')
											a[i] = '2';
										else if (c[i] == 'd' || c[i] == 'e' || c[i] == 'f' || c[i] == 'D' || c[i] == 'E' || c[i] == 'F')
											a[i] = '3';
										else if (c[i] == 'g' || c[i] == 'h' || c[i] == 'i' || c[i] == 'G' || c[i] == 'H' || c[i] == 'I')
											a[i] = '4';
										else if (c[i] == 'j' || c[i] == 'k' || c[i] == 'l' || c[i] == 'J' || c[i] == 'K' || c[i] == 'L')
											a[i] = '5';
										else if (c[i] == 'm' || c[i] == 'n' || c[i] == 'o' || c[i] == 'M' || c[i] == 'N' || c[i] == 'O')
											a[i] = '6';
										else if (c[i] == 'P' || c[i] == 'Q' || c[i] == 'R' || c[i] == 'S' || c[i] == 'p' || c[i] == 'q' || c[i] == 'r' || c[i] == 's')
											a[i] = '7';
										else if (c[i] == 't' || c[i] == 'u' || c[i] == 'v' || c[i] == 'T' || c[i] == 'U' || c[i] == 'V')
											a[i] = '8';
										else if (c[i] == 'w' || c[i] == 'x' || c[i] == 'y' || c[i] == 'z' || c[i] == 'W' || c[i] == 'X' || c[i] == 'Y' || c[i] == 'Z')
											a[i] = '9';

									}
									(WordList1(tempword,a));




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

		fgets(word,WordSize,in);
	}

    printf("\nFinish Pre-Loading WordList\n\n");





    printf("\nSearching for Possible words...\n");



		fgets(word,WordSize,in);
			while (word[0] != '0'){

				if (word[0] != '\n'){

						fprintf(out,"%s",word);
						x = strlen(word);

						word[x-1] = '\0';

									MyList2 = MyList;
									while(MyList2 != NULL){

											// complaring the number string to see if present
										if (strcmp(MyList2->num,word) == 0){

									 		fprintf(out,"%s \n",MyList2->Item);
									 	}
									 	MyList2 = MyList2->Next;


								} // end while
								fprintf(out,"\n");

				} // end if



		fgets(word,WordSize,in);
			}// end main while

    printf("\nSearch finish check output file for data\n\n");

		deletelist(MyList);
		deletelist(MyList2);

		fclose(in);
		fclose(out);





	system ("PAUSE");
	return 0;
}


// -----> FUNCTIONS <-----



// adding words in order to the linked list

void WordList1(char *word, char *a)
	{ struct ListItem *item,*next,*temp;
	item = (struct ListItem *) malloc(sizeof(struct ListItem));
	if ( item==0 ) { printf ("Malloc Failed \n");  return ; }
	strcpy(item->Item,word);
	strcpy(item->num,a);
	item->Next = 0;

	if ( MyList == 0 ) // If List is Empty, make this the first item
		{ MyList = item; return ; }

	if(strcmp(word,MyList->Item) < 0 ) // Check if the new item comes before the first item in old list
		{ item->Next = MyList; MyList = item; return ; }

	// Check to see if an item is inserted before the next item
	for ( next = MyList ; next ->Next != 0 ; next = next ->Next )
		{
		if (strcmp (word, next->Next->Item) < 0 )
			{ // Insert Item before the next Item.
			item ->Next = next->Next;
			next->Next = item ; return;
			}
		}

	// There are no more items ! Add to end
	next ->Next = item;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// deleting the linked list after use

void deletelist (struct ListItem *top){
	struct ListItem *toDelete;
	while (top != NULL){
		toDelete = top;
		top = top -> Next;
		free(toDelete);
	}
}

