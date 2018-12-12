#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int s, int m, int e)
{
	int n1 = m-s+1;
	int n2 = e-m;

	int l1[n1], r1[n2];
	for(int i = 0; i < n1; ++i)	
		l1[i] = arr[s+i];
	for(int j = 0; j < n2; ++j)
		r1[j] = arr[m+j+1];

	int i, j, k;
	i = j = 0;
	k = s;

	while(i < n1 && j < n2)
	{
		if(l1[i] <= r1[j])	
			arr[k++] = l1[i++];
		else
			arr[k++] = r1[j++];
	}
	while(i < n1)
		arr[k++] = l1[i++];
	while(j < n2)
		arr[k++] = r1[j++];
}
void merge_sort(int* arr, int s, int e)
{
	if(s >= e)	return;
	int m = s + (e-s)/2;
	
	merge_sort(arr, s, m);
	merge_sort(arr, m+1, e);
	merge(arr, s, m, e);
}
void display(int* arr, int size)
{
	for(int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("\n");
}

int main(int argc, char** argv){
	int arr[4] = {2,5,6,1};
	
	display(arr, 4);

	merge_sort(arr, 0, 3);
	
	display(arr, 4);

	exit(0);
}
	
	
