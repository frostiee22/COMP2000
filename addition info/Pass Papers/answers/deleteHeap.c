[#include <stdio.h>

void deleteMax2(int array[],int i);
int deleteMax(int key,int array[],int root,int last);
void print(int array[]);
void mergeHeap(int A[],int B[]);
int deleteRoot(int array[]);
void makeHeap(int array[]);

int main(int argc, char const *argv[])
{
	//all arrays listed are arranged in max heap 
	int array[13]={12,84,79,73,65,69,43,37,18,25,56,48,32};
	int array2[13]={12,85,80,74,66,70,44,38,19,26,57,49,33};
	// int array2[6]={5,11,5,8,3,4};
	int array3[13]={12,32,84,65,79,25,37,18,73,56,43,48,69};

	
	// makeHeap(array3);

	// mergeHeap(array,array2);
	int count=0;
	// while(count<12)
	// {
	// 	printf("Delete:%i\n", deleteMax(array[array[0]],array,1,array[0]));
	// 	print(array);
	// 	count++;
	// 	system("pause");
	// }

	// mergeHeap(array,array2);

	system("pause");
	return 0;
}

//siftdown the new root which is the last item in the heap into its correct position
int deleteMax(int key,int array[],int root,int last)
{
	if (array[0] == 0) return -1;
	int max=array[1];//save the largest item which is to be deleted
	int largest=2*root;//index of largest item(root) since it is max heap
	array[0]--;//minus 1 from the array size since we delete a value
	while(largest<=last && array[0]>0)//while the index is within the array size 
	{
		if(largest<last)//if the index of largest is less than there is another child(right child)
			if(array[largest+1]>array[largest])//check which child is larger(left or right)
				largest++;
		if(key>=array[largest])//if last item is more than the largest child then end loop
			break;
		array[root]=array[largest];//replace parent with largest child 
		root=largest;//new parent is largest child
		largest=2*root;//go down a level(eg 1->2->4->8)
	}
	array[root]=key;//place the last item into its final position
	return max;
}

/*same siftdown method but using a for loop but must delete the root using deleteRoot()
before calling deleteMax2()*/
void deleteMax2(int array[],int i)
{
	int child;
	int tmp=array[i];
	for(i;i*2<=array[0];i=child)
	{
		child=i*2;
		if(child!=array[0]&&array[child+1]>array[child])
			child++;
		if(array[child]>tmp)
			array[i]=array[child];
		else 
			break;
	}
	array[i]=tmp;
}

int deleteRoot(int array[])
{
	int max=array[1];
	array[1]=array[array[0]];
	array[0]--;
	return max;
}

void print(int array[])
{
	int i;
	for (i = 1; i <=array[0]; ++i)
	{
		printf("Location:%i\tvalue:%i\n",i, array[i]);
	}
}

void mergeHeap(int A[],int B[])
{
	int total=A[0]+B[0]+(-1);
	printf("%i\n", total);
	int C[total];
	int count=0,x,y,max;
	max=total;
	x=deleteMax(A[A[0]],A,1,A[0]);
	y=deleteMax(B[B[0]],B,1,B[0]);
	while(count<max)
	{
		if(x>y)
		{
			if (A[0]>0)
			{
				C[total] = x;
				int a =x;
				printf("%i\n", x);
				x=deleteMax(A[A[0]],A,1,A[0]);
			}
		}
		else if(y>x)
		{
			if (B[0]>0)
			{
				C[total]=y;
				int b = y;
				printf("%i\n", y);
				y=deleteMax(B[B[0]],B,1,B[0]);
			}
		}
		else if (x==y)
		{
			printf("%i\n", x);
			x=deleteMax(A[A[0]],A,1,A[0]);
			y=deleteMax(B[B[0]],B,1,B[0]);
			C[total] = x;
		}
		total--;
		// printf("X:%i  Y:%i\n", x,y);
		// system("pause");
		count++;
	}
	printf("X:%i  Y:%i\n", x,y);
	if (x>y)
	{
		C[1] = x;
		C[0]=y;
	}
	else if (y>x)
	{
		C[1]=y;
		C[0]=x;
	}
	printf("\n\n");
	int i;
	total=A[0]+B[0];
	printf("C:");
	for(i=0;i<max;i++)
		printf("%i\n", C[i]);
}

void makeHeap(int array[])
{
	int ,temp,x;
	for(i=2;i<=A[0],i++){
		x=i;
		while(x/2>0; && A[x] > A[x/2]){
			temp = A[x];
			A[x] = A[x/2];
			A[x/2] = temp;
			x=x/2;
		}
	}
}
