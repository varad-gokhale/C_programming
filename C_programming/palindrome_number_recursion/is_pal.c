/* Checks if number is palindrome or not using recursion */
#include <stdio.h>
#define FALSE 0

char is_pal(int num, int* copy)
{
	if(num >= 0 && num <= 9)
		return (num == *copy%10);
	
	if(!is_pal(num/10, copy))	return FALSE;
	*copy /= 10;
	return (num%10 == *copy%10);
}

int main(int argc, char** argv)
{   
	int n = 12321;
	int copy = n; 
	is_pal(n,&copy)? printf("Yes\n"): printf("No\n"); 

	n = 12; 
	copy = n;
	is_pal(n, &copy)? printf("Yes\n"): printf("No\n"); 
  
	n = 88; 
	copy = n;
	is_pal(n, &copy)? printf("Yes\n"): printf("No\n"); 
  
	n = 8999;
	copy = n; 
	is_pal(n, &copy)? printf("Yes\n"): printf("No\n"); 
	return 0; 
}
