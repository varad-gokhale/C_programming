#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char** argv){
	time_t max_time = INT_MAX;	
	
	printf("%s\n", ctime(&max_time));
	exit(0);
}
