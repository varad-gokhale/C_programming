#include <stdio.h>
#include <stdlib.h>

struct ListNode{
	int val;
	struct ListNode* next;
};

void delete_LL(struct ListNode* head) 
{
	if(head->next == NULL)	return;
	delete_LL(head->next);	
	struct ListNode* del = head->next;
	printf("Node %d being deleted..\n", del->val);
	head->next = del->next;
	free(del);
}

/*Driver and util functions from www.geeksforgeeks.org/recursive-function-delete-k-th=node-linked-list/*/
/* Utility function to insert a node at the beginning */
void push(struct ListNode **head_ref, int new_data) 
{ 
    struct ListNode *new_node = (struct ListNode*)malloc(sizeof(struct ListNode)); 
    new_node->val = new_data; 
    new_node->next = *head_ref; 
    *head_ref = new_node; 
} 
   
/* Utility function to print a linked list */
void printList(struct ListNode *head) 
{ 
    while (head!=NULL) 
    {
		printf("%d ",head->val); 
        head = head->next; 
    } 
    printf("\n"); 
} 
   
/* Driver program to test above functions */
int main() 
{ 
    struct ListNode *head = NULL; 
   
    /* Create following linked list 
      12->15->10->11->5->6->2->3 */
    push(&head,3); 
    push(&head,2); 
    push(&head,6); 
    push(&head,5); 
    push(&head,11); 
    push(&head,10); 
    push(&head,15); 
    push(&head,12); 
  
	printf("LinkedList before modification\n"); 
	printList(head);

	struct ListNode dummy = {-1,head}; 
    delete_LL(&dummy); 
   
    printf("\nModified Linked List: "); 
    printList(head->next); 
   
    return 0; 
} 
