#include <stdio.h>
#include <stdlib.h>

void display(int* arr, int n){
	for(int i = 0; i < n; ++i)	printf("%d ", arr[i]);
	printf("\n");
}

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int partition(int* arr, int s, int e)
{
	int pivot = arr[e];
	int widx = s;
	
	for(int i = widx; i < e; ++i)	
		if(arr[i] <= pivot)	swap(arr, i, widx++);
	
	swap(arr, widx, e);
	return widx;
}
	
void quicksort(int* arr, int s, int e)
{
	if(s >= e)	return;
	int p = partition(arr, s, e);
	quicksort(arr, s, p-1);
	quicksort(arr, p+1, e);

}

int main(int argc, char** argv){
	int arr[20] = {8,1,5,7,2,5,1,2,4,6,2,1,4,5,6,2,1,3,5,7};
	
	display(arr, 20);
	quicksort(arr, 0,19);
	display(arr,20);

	exit(0);
}
	
	
