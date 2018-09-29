#include <stdio.h>
#include <stdlib.h>

struct ListNode{
	int val;
	struct ListNode* next;
};

void delete_kth_node(struct ListNode* head, int k) 
{
	if(k <= 0)	return;
	delete_kth_node(head->next, k-1);
	if(k == 1){
		struct ListNode* del = head->next;
		head->next = head->next->next;
		free(del);
	}
}

int main(int argc, char** argv){	
	if(argc < 2){
		printf("k not provided..Exiting");
		exit(1);
	}
	if(atoi(argv[1]) > 7){
		printf("Illegal argument provided. Please input value less than or equal to 7..exiting");
		exit(1);
	}
	struct ListNode ll1,ll2,ll3,ll4,ll5,ll6,ll7;
	l1 = {1,l2};
	l2 = {2, l3};
	l3 = {
	
	printf("Number is: %d ", atoi_fn(argv[1], &mult));
	printf("\n");
	exit(0);
}
	
	
