#include <stdio.h>
#include <stdlib.h>

#define MAX_ALLOWABLE_SIZE 4096

char* strcpy_s(char* dest, char* src, size_t dmax)
{
	char* orig_dest = dest;
	char* overlap_detector;

	if(dest == NULL){
		printf("ERROR: Destination cannot be null..Exiting");
		exit(1);
	}
	if(src == NULL){
		*dest = '\0';
		printf("ERROR: SRC Cannot be Null..Exiting");
		exit(1);
	}
	if(dmax > MAX_ALLOWABLE_SIZE){
		printf("ERROR: dmax exceeds max..Exiting");
		exit(1);
	}
	if(dmax == 0){
		printf("ERROR: dmax cannot be 0..Exiting");
		exit(1);
	}
	if(dest < src){
		overlap_detector = src;
		while(dmax > 0){
			if(dest == overlap_detector){
				printf("ERROR: overlap detected..Exiting");
				*orig_dest = '\0';
				exit(1);
			}
			*dest = *src;
			if(*dest == '\0')
				return orig_dest;
			--dmax;
			++dest;
			++src;
		}
	}
	else{
		overlap_detector = dest;
		while(dmax > 0){
			if(dest == overlap_detector){
				printf("ERROR: overlap detected..Exiting");
				*orig_dest = '\0';
				exit(1);
			}
			*dest = *src;
			if(*dest == '\0')
				return orig_dest;
			--dmax;
			++dest;
			++src;
		}	
	}

	printf("String was bigger than max allowable size dmax..Exiting");
	exit(1);
}


int main(int argc, char** argv){
	if(argc <= 1){
		printf("No argument provided..bye!");
		exit(1);
	}	
	char s[100] = {'I',' ','C','a','n',' ','N','e','v','e','r',' ','C','h','a','n','g','e','\0'};
	printf("Before copying our string s is like: %s\n", s);
	strcpy_s(s, argv[1], 100);
	printf("But then life happened. New string s: %s\n", s);
}
