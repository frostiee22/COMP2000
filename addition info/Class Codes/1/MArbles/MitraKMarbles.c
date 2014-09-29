#include <stdio.h>

#define size 26

int main(){

	FILE*in  = fopen("input.txt", "r");
	FILE*out = fopen("output.txt","w");

	int n, m;

	fscanf(in, "%d %d", &n, &m);

	static int arr[size][size], start[size];
	int a, b, c, d, i, j, k;



	i = k = 0;
	while (!feof(in)){


		fscanf(in, "%d %d %d", &a, &b, &c);
		arr[i][0] = a;
		start[i] = arr[i][1] = b;
		arr[i][2] = c;
		k = 3;

		for (j = 0; j < c; j++){
			fscanf(in, "%d", &d);
			arr[i][k] = d;
			k++;
		}
		i++;
	}


	// processing input data

	i = 0;

	while (arr[i][0] != 0){

		if (arr[i][2] != 0){
			a = arr[i][1];
			arr[i][1] = m - start[i];
			
			if (a%arr[i][2] != 0){
				arr[i][1] += a%arr[i][2];
			}
			else {
				// do nothing
			}

			b = a / arr[i][2];
		}
		else {
			a = arr[i][1];
			arr[i][1] += m - start[i];
		}





		k = 3;
		for (j = 0; j < arr[i][2]; j++){

			for (d = 0; d < size; d++){
				if (arr[i][k] == arr[d][0])
					arr[d][1] = arr[d][1] + b;
			}
			k++;
		}


		a = b = 0;
		i++;
	}



	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (arr[j][0] == i + 1){
				if (arr[j][0] != 0){
					fprintf(out,"%d %d", arr[j][0], arr[j][1]);
					fprintf(out,"\n");
				}
				else {
					j=size;
				}
			}
		}

	}


	fclose(in);
	fclose(out);
	system("PAUSE");
	return 0;
}
