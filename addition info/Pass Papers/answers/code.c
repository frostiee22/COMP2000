// shell sort

void hsort(int A[],int n,in h){
	int j;
	for (j=h+1;j<=n;j++){
		int k = j-h;
		int key = A[j];
		while(k>0 && key < A[k]){
			A[k+h] = A[k];
			k = k-h;
		}
		A[k+h] = key;
	}
}

// gerating the keys and calling the function hsort

int n = 13, arr[n],values[n/4],h=1,i=0;

while(h<n){
	values[i++] = h;
	h = 3h+1;
}

while(i >= 0){
	int value = values[i--];
	hsort(arr[],n,value);
}