// n is the number or items in the array
int succesor (int k){
	if((k*2)+1) <= n){
		k = (k*2)+1;
	while ((k*2)<= n)
		k = k*2;
	return k;
	}
	
	int y = k/2;
	while (y > 0 && (y*2) == k){
		k=y
		y=k/2;
	}
	return y;
}

///////////////////////////////////////////////////////////////////

int partition (int num[], int lo, int hi){
	// partition num[lo] to num[hi] using num[lo] as the pivot
	int pivot = num[lo];
	int lastSmall = lo,j;
	for (j=lo+1; j<=hi; j++){
		if (num[j] < pivot){
			++lastSmall;
			swap(num,lastSmall,j);
		}
	}
	swap(num,lo,lastSmall);
	return lastSmall;
}

void swap (int array[], int i, int j){
	int hold = array[i];
	array[i] = array[j];
	array[j] = hold;
}

///////////////////////////////////////////////////////////////////

void quickSort(int num[],int lo,int hi){
	// sorts num[lo] to num[hi] in ascending order 
		if (lo < hi){
			int dp = partition(num,lo,hi);
			quickSort(num,lo,dp-1);
			quickSort(num,dp+1,hi);
		}
}

//////////////////////////////////////////////////////////////////

/ topological sort algorithm 
void (topologicalSort (G (V,F))){
	for each vertex v eV
		v.colour = white
	initialize stack, S 
	for each vertex v eV
		if (v.colour == white) dfTraversal(v)
	pop,S and print each item as popped
}

void dfTraversal(v){
	print v.id 
	v.colour = grey
	for each edge(v,x)
		if (x.colour == grey("No solution")) // back edge cycle
		if (x.colour == white) dfTraversal(x)
	v.colour = black
	add v to stack,S
}

/////////////////////////////////////////////////////////////////
