#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MaxWords 500
#define WordSize 500
#define N 23
#define Empty ""





typedef struct {
	char word[6];
	char name[20];
	char description[30];
	double unitprice;
	int quantityinstock;
	int next;
}WordInfo;





//Function Prototypes
int search(WordInfo table[], char key[]);
int convertToNumber(char key[]);
int addToTable(WordInfo table[], char key[], char name[], char des[], double unit, int quantity, int loc, int head);
void printResults(FILE*out, WordInfo table[], int head);
int find(WordInfo table[], int head, char key[]);
void deleteEntry(FILE*out,WordInfo table[],int head,char key[]);



/////////////////////////////////////////////////////////////////////////
int first = -1;
int main() {
	
	printf("\nCOMP2000 Assignment 6\n\nStudent # : 812000767\n\n\n\n********** Hash Parts ************* \n\n\n");
	int j;

	WordInfo wordTable[N + 1];
	for (j = 1; j <= N; j++)strcpy(wordTable[j].word, Empty);

	FILE*in = fopen("input.txt", "r");
	FILE*out = fopen("output.txt", "w");

	

	static char info[WordSize], number[6], name[20], description[30];
	double unitprice;
	int quantityinstock;
	static int x, y, i, count,stop;

	
	int numWords = 0;






#pragma warning(suppress: 6054)
	while (strcmp(number, "$$$$$$") != 0)  {
	
			for (i = 0; i < 6; i++){
				number[i] = '\0';
			}
			for (i = 0; i < 20; i++){
				name[i] = '\0';
			}
			for (i = 0; i < 30; i++){
				description[i] = '\0';
			}
			for (i=0; i< WordSize; i++){
				info[i] = '\0';
			}
	
		
			
			
		

		i = count = 0;
		while (count != 6){
			fscanf(in, "%c", &info[i]);

			if (info[i] == '"'){
				count++;
			}
			else if ( info[i] == '$'){
				stop++;
			}
			if (count == 2 && stop == 6){
				count = 6;
			}
				i++;
		
			
		}
		

		x = strlen(info);
		i = count = 0;
		for (i = 0; i<x; i++){

			if (info[i] == '"'){
				count++;
				y = 0;
			}


			else if (count > 0 && count < 2){
				number[y] = info[i];
				y++;
			}

			else if (count > 2 && count < 4){
				name[y] = info[i];
				y++;

			}

			else if (count > 4 && count < 6){
				description[y] = info[i];
				y++;
			}


		}

		fscanf(in, "%lf", &unitprice);
		fscanf(in, "%d", &quantityinstock);


		if (strcmp(number, "$$$$$$") != 0) {
			int loc = search(wordTable,number);
			if (loc > 0) {
				// exist already
				}
			else
			if (numWords < MaxWords){
				first = addToTable(wordTable,number,name,description,unitprice,quantityinstock, -loc, first);
				++numWords;
			}
			else fprintf(out, "'%s' not added to table \n",number);
		}
		
			
		
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char c;
	fscanf(in, "%c", &c);
	c = tolower(c);
	while (c != 'e'){
	

		if (c == 'p'){
			for (i = 0; i < 6; i++){
				number[i] = '\0';
			}
			fscanf(in,"%s",&number);
			int x = find(wordTable,first,number);
			if (x !=0) {
				fprintf(out,"print: '%s' '%s' '%s' '%.2lf' '%d' \n",wordTable[x].word,wordTable[x].name,wordTable[x].description,wordTable[x].unitprice,wordTable[x].quantityinstock);
			}
			else if (x == 0)fprintf(out,"print: %s not present in Hash table\n",number);
		}

		else if (c == 'd'){
			for (i = 0; i < 6; i++){
				number[i] = '\0';
			}
			fscanf(in,"%s",&number);
			deleteEntry(out,wordTable,first,number);
			

		}

		else if (c == 'c'){
			for (i = 0; i < 6; i++){
				number[i] = '\0';
			}
			fscanf(in,"%s",&number);
			int x = find(wordTable,first,number);
			int n;
			fscanf(in,"%d",&n);
			if (wordTable[x].quantityinstock < n){
				fprintf(out,"item : %s NOT ORDERED - stock has %d, order is %d\n",wordTable[x].word,wordTable[x].quantityinstock,n);
			
			}
			else wordTable[x].quantityinstock = wordTable[x].quantityinstock - n;
		}

		fscanf(in, "%c", &c);
		c = tolower(c);
	}


	fprintf(out,"\n\n\n");
	fprintf(out,"\t\t-----> Parts Data <-----\n\n");
	printResults(out, wordTable, first);



	system("pause");
	return 0;

	fclose(in);
	fclose(out);
}

/////////////////////////////////////////////////////////////////////////


//Functions


int search(WordInfo table[], char key[]){
	int keyNum = convertToNumber(key);
	int loc = keyNum % N + 1;
	int k = keyNum % (N - 2) + 1;

	while ((strcmp(table[loc].word, Empty) != 0) && (strcmp(table[loc].word, key) != 0)){
		loc = loc + k;
		if (loc > N)loc = loc - N;
	}
	if (strcmp(table[loc].word, Empty) == 0) return -loc;
	return loc;
}

int convertToNumber(char key[]){
	int j = 0, keyNum = 0, w = 3;
	while (key[j] != '\0'){
		keyNum += w*key[j++];
		w = w + 2;
	}
	return keyNum;
}


int addToTable(WordInfo table[], char key[],char name[], char des[], double unit,int quantity, int loc, int head){
	strcpy(table[loc].word, key);
	strcpy(table[loc].name, name);
	strcpy(table[loc].description, des);
	table[loc].unitprice = unit;
	table[loc].quantityinstock = quantity;

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

// printing out the hash table using the next field
void printResults(FILE*out, WordInfo table[], int head){
	while (head != -1){
		fprintf(out, "'%s'  '%s'  '%s'  '$%.2lf'  '%d'\n", table[head].word,table[head].name,table[head].description,table[head].unitprice ,table[head].quantityinstock);
		head = table[head].next;
		
	}
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


// making the location empty if  stock = 0
void deleteEntry(FILE*out,WordInfo table[],int head,char key[]){
	int before;
	while (head != -1){
		
	
		 if (strcmp(table[head].word, key) == 0 ){
				if (head == first){
					if (table[head].quantityinstock == 0){
						first = table[head].next;
					}
					else if (table[head].quantityinstock > 0 ){
			 			fprintf(out,"item : %s NOT DELETED - there are %d items in stock\n",table[head].word,table[head].quantityinstock);
					}
					
				}
			
				else if (head != first){
					if (table[head].quantityinstock == 0 ){
						table[before].next = table[head].next;
						strcpy(table[head].word, Empty);
						strcpy(table[head].name, Empty);
						strcpy(table[head].description, Empty);
						table[head].unitprice = 0;
						table[head].quantityinstock = 0;
				
					}
				
					else if (table[head].quantityinstock > 0 ){
			 			fprintf(out,"item : %s NOT DELETED - there are %d items in stock\n",table[head].word,table[head].quantityinstock);
					}
			
				}
		}
		
		before = head;
		head = table[head].next;
	}
}

