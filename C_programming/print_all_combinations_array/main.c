#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	if(argc <= 1){
		printf("Proper argument not provided..Exiting\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	if(n <= 0 || n > 100){
		printf("Please provide argument between 1 and 100 and try again..Exiting\n");
		exit(1);
	}
	
	int arr[100] = {0};	
	for(int i = 1; i <= n; ++i){
		arr[i-1] = i;
	}

	for(int i = 0; i < n-1; ++i){
		for(int j=i+1; j < n; ++j){
			printf("{%d,%d}\n", arr[i],arr[j]);
		}
	}
		
	exit(0);
}
