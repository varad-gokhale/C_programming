#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct NODE{
  int val;
  struct NODE* next;
}node;

typedef struct{
  node* head;
  node* tail;
}LinkedList_t;

void* Malloc(size_t x){
  void *malloc_ptr = malloc(x);
  assert(malloc_ptr != 0);
  return malloc_ptr;
}

LinkedList_t* create_LL(){
  LinkedList_t *L = (LinkedList_t*)Malloc(sizeof(LinkedList_t));
  L->head = L->tail = NULL;
  return L;
}

void add_to_tail(LinkedList_t* L, int val){
  node* new = (node*)Malloc(sizeof(node));  
  new->val = val;
  
  if(L->tail == NULL){
    L->tail = new;
    L->head = new;
    new->next = NULL;
    return;
  }
  
  new->next = NULL;
  L->tail->next = new;
  L->tail = new;
}

void add_to_head(LinkedList_t* L, int val){
  node* new = (node*)Malloc(sizeof(node));
  new ->val = val;
  new->next = L->head;
  if(L->head == NULL)
    L->tail = new;
  
  L->head = new;
}

void print_node(LinkedList_t* L){
  node* head = L->head;
  while(head){
    printf("node_val = %d\n", head->val);
    head = head->next;
  }
}

void insert_at_pos(LinkedList_t* L, int pos, int val)
{
  if(pos == 1){
    node* new = (node*)Malloc(sizeof(node));
    new->val = val;
    if(L->head == NULL){
      new->next = NULL;
      L->head = L->tail = new;
      return;
    }
    new->next = L->head;
    L->head = new;
    return;
  }
  
  node* n = L->head;
  node* prev = n;
  int i = 1;
  
  while(n && i < pos){
    prev = n;
    n = n->next;
    ++i;
  }
  assert(i == pos);
  
  node* new = (node*)Malloc(sizeof(node));
  new->val = val;
  prev->next = new;
  new->next = n;
  if(n == NULL){
    L->tail = new;
  }
}

int main() {
  
  LinkedList_t *L = create_LL();
  
  insert_at_pos(L, 1, 1);
  insert_at_pos(L, 2, 2);
  // add_to_tail(L,3);
  // add_to_tail(L,4);
  // add_to_tail(L,6);
  // add_to_tail(L,8);
  insert_at_pos(L, 3,3);
  insert_at_pos(L, 4, 4);
  
  print_node(L);
  
  return 0;
}


/* 
Your previous Plain Text content is preserved below:


 */
