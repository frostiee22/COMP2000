#include <stdio.h>

#define xaxis 102
#define yaxis 1000000

char arr[yaxis][xaxis]; // array used to  store the maze
int temp;
int LargestSection = 0;
int NumOfSections = 0; 

void InitializeArry(int m, int n, char array[yaxis][xaxis]);
void CreateMaze(FILE*in, int m, int n, char array[yaxis][xaxis]);
void PrintArray(FILE*out, int m, int n, char array[yaxis][xaxis]);
void FillGrid(int x, int i, int j, char array[yaxis][xaxis]);
void FindPath(int i, int j,int m, int n, char array[yaxis][xaxis]);
void compute (int m,int n,char array[yaxis][xaxis]);

int main(){
	
		printf("\nCOMP2000 Assignment 4\n\nStudent # : 812000767\n\n\n\n********** Maze ************* \n\n\n");

	FILE*in = fopen("input.txt", "r");
	FILE*out = fopen("output.txt", "w");

	int m, n; // to create the array needed
	
	fscanf(in, "%d", &m);
	while (!feof (in)){
		
		fscanf(in, "%d", &n);
	
		m = m * 2;
		n = n * 2;
	
		InitializeArry(m, n, arr);
	
		CreateMaze(in, m, n, arr);
	
		PrintArray(out, m, n, arr);
	
		compute(m,n,arr);
	
		fprintf(out,"\n\nNumber of sections : %d \nLargest section : %d\n\n", NumOfSections, LargestSection);
		fprintf(out, "\n");
		fprintf(out,"----------------------------------------------------------------------------------\n\n");
		
		NumOfSections = 0;
		LargestSection = 0;
		
		
		fscanf(in, "%d", &m);
		
	}
	fclose(in);
	fclose(out);
	printf("\n\n");
	system("PAUSE");
	return 0;

}

// places * in the even places in the array 
// this is where the walls will be place 
// and inserts 0 in every other place
void InitializeArry(int m, int n, char array[yaxis][xaxis]){
	int i = 0, j = 0;

	for (i = 0; i <= m; i++){
		for (j = 0; j <= n; j++){
			array[i][j] = '0';
			if (i % 2 == 0)
				array[i][j] = '*';
			if (j % 2 == 0)
				array[i][j] = '*';
		}
	}
}

// creating by supplying the values to be used by the FillGrid function
void CreateMaze(FILE*in, int m, int n, char array[yaxis][xaxis]){
	int i, j,x;

	for (i = 1; i <= m / 2; i++){
		for (j = 1; j <= n / 2; j++){
			fscanf(in, "%d", &x);
			FillGrid(x, i, j, array);
		}
	}
}

// printing out the Maze to the output file
void PrintArray(FILE*out, int m, int n, char array[yaxis][xaxis]){
	int i = 0, j = 0;
	
	for (i = 0; i <= m; i++){
		fprintf(out, "\n");
		for (j = 0; j <= n; j++){
			if (array[i][j] == '*')
				array[i][j] = ' ';
			if (array[i][j] != '0')
				fprintf(out, "%c", array[i][j]);
			else fprintf(out," ");
			
		}
	}
}


//find the location of where to place the # sign and places it there
void FillGrid(int x, int i, int j, char array[yaxis][xaxis]) {
	i = i * 2 - 1;
	j = j * 2 - 1;

	if (x >= 8)
		array[i + 1][j] = '#';
	x = x % 8;

	if (x >= 4)
		array[i][j + 1] = '#';
	x= x % 4;

	if (x>= 2)
		array[i - 1][j] = '#';
	x = x % 2;

	if (x == 1)
		array[i][j - 1] = '#';

	// placing # on the diagonals
	array[i + 1][j + 1] = '#';
	array[i + 1][j - 1] = '#';
	array[i - 1][j + 1] = '#';
	array[i - 1][j - 1] = '#';
	return;
}

// finds the 0s in the path the get the largest section
void FindPath(int i, int j,int m,int n, char array[yaxis][xaxis]){
	if (array[i][j] != '#'){
		
		if (array[i][j] == '1'){
				return;
		}
		else if ( (m<1)||(n<1)||(i>m)||(j>n)){
				return ;
			}
		
	    else if (array[i][j] == '0'){
			array[i][j] = '1';
			temp++;
			
			if (temp > LargestSection){
				LargestSection = temp;
			}	
		}
		
			array[i][j] = '1';

			FindPath(i+1,j,m, n, array);
			FindPath(i,j+1,m, n, array);
			FindPath(i-1,j,m, n, array);
			FindPath(i,j-1,m, n, array);
	}
	else return;
}

// used to find the amount of sections there are
void compute (int m,int n,char array[yaxis][xaxis]){
		int i, j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			if (array[i][j] == '0'){
				NumOfSections++;
				FindPath(i, j,m ,n ,array);
				temp = 0;
			}
		}
	}
}


