#include <stdio.h>

int atoi_fn(char* s, int *mult, int *result)
{
	if(s[i+1] == '\0'){
		return *s - '0';
	}
	
	int digit = atoi_fn(s+1, mult, result);
	*result += digit * (*mult);
	*mult *= 10;
	return result;
}

int main(int argc, int** argv){
	int mult = 1;
	int result = 0;
	
	
