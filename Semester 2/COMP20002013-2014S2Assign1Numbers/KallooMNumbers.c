#include <stdio.h>


// Function Prototypes
int isPrime(int n);
int composite(int n, FILE*out);


int i;
int main() {

    FILE * test = fopen("input.txt","w");
        for(i=0;i<10000000;i++)
            fprintf(test,"%d\n",i);
        fclose(test);
        printf("*** Finish building list ***\n\n\n");

	FILE * in = fopen("input.txt", "r");
	FILE * out = fopen("output.txt", "w");

	int number;
	while (!feof(in)){
		fscanf(in, "%d", &number);
		
		if (number <= 1)
			fprintf(out, "not prime and not composite\n");
		else if (isPrime(number) == 1)
			fprintf(out, "prime\n");
		else {
			i = 0;
			composite(number, out);
			fprintf(out, "\n");
		}
		
	}

	printf("\nCOMP2000 Assignment 1\n\nStudent # : 812000767\n\n\n\n********** Numbers ************* \n\n\n");

	fclose(in);
	fclose(out);

	system("PAUSE");
	return 0;

}

// FUNCTIONS

int isPrime(int n) {
	if (n <= 1) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	int h;
	for (h = 3; h*h <= n; h += 2)
		if (n % h == 0) return 0;
	return 1;
}

int composite(int n, FILE*out){
	int h;

	if (n == 1) return i = 0;
	// using two fist since we already know its prime
	if (n % 2 == 0){
		if (i == 0){
			fprintf(out, "2");
			i = 1;
		}
		else
			fprintf(out, "*2");
	return composite(n / 2, out);
	}
	// increasing by two leaving all odd numbers out
	for (h = 3; h <= n; h+=2){
		if (n % h == 0){
			if (isPrime(h) == 1){
				if (i == 0){
					fprintf(out, "%d", h);
					i =1;
				}
				else
					fprintf(out, "*%d", h);
			return composite(n / h, out);
			}

		}
	}
}
