#include <stdio.h>

int main() {

	FILE*in = fopen("input.txt","r");
	FILE*out = fopen("output.txt","w");

	static int i, j, start, length, k, numbers = 1;
    static float arr[1000];
	float x, mult = 1,big = 0;
	

	// finding the number of values to be used
	fscanf(in, "%f", &x);

	// storing the values into an array
	for (i = 0; i < x; i++)
		fscanf(in, "%f",&arr[i]);
	

	
	// searching for largest number combination
		for (i = 0; i < x; i++){
					mult = mult * arr[i];

					while (numbers< x){

						for (j = i + 1; j < i + numbers; j++){
							if (j < x){
								mult = mult * arr[j];
							}
						}

						if (mult > big){
							big = mult;
							start = i;
							length = numbers;
						}

						mult = arr[i];
						numbers++;

					}// end while loop
					
						numbers = 1;
		} // end for loop
		
		
	
	
	fprintf(out,"%.3f\n", big);

	for (i = start; i < (start + length); i++){
		fprintf(out,"%.1f\n", arr[i]);
	}

	fclose(in);
	fclose(out);

	system("PAUSE");
	return 0;

}

