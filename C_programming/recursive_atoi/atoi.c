#include <stdio.h>
#include <stdlib.h>

int atoi_fn(char* s, int *mult)
{
	if(*(s+1) == '\0'){
		return *s - '0';
	}
	
	int result = atoi_fn(s+1, mult);	
	*mult *= 10;
	return result + (*s - '0') * (*mult);
}

int main(int argc, char** argv){
	int mult = 1;
	
	if(argc < 2){
		printf("Please enter the string to be converted\nExiting..\n");
		exit(1);
	}
	printf("Number is: %d ", atoi_fn(argv[1], &mult));
	printf("\n");
	exit(0);
}
	
	
