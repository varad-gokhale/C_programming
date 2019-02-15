#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct{
  int capacity;
  int size;
  int *arr;
}heap_t;

int get_leftchild_index(int parent_index) {return 2*parent_index+1;}
int get_rightchild_index(int parent_index) {return 2*parent_index+2;}
int get_parent_index(int child_index) {return (child_index-1)/2;}

int has_leftchild(heap_t* h, int index){  return (index*2+1 < h->size);}
int has_rightchild(heap_t* h, int index){  return (index*2+2 < h->size);}
int has_parent(heap_t* h, int index){  return (get_rightchild_index(index) >= 0);  }

int leftchild(heap_t* h, int index){  return h->arr[get_leftchild_index(index)];  }
int rightchild(heap_t* h, int index){  return h->arr[get_rightchild_index(index)];  }
int parent(heap_t* h, int index){  return h->arr[get_parent_index(index)];  }

void* Malloc(size_t x){
  void* ret = malloc(x);
  assert(ret != NULL);
  return ret;
}

heap_t* create_heap(int capacity){
  heap_t* h = (heap_t*)(Malloc(sizeof(heap_t)));
  h->capacity = capacity;
  h->size = 0;
  h->arr = (int*)Malloc(sizeof(int) * capacity);
  return h;
}

void destroy_heap(heap_t* h){
  free(h->arr);
  free(h);
}

int peek(heap_t* h){
  assert(h->size > 0);
  return h->arr[0];
}

void swap(int* a, int* b){
  int t = *a;
  *a = *b;
  *b = t;
}

void heapify_up(heap_t* h)
{
  int index = h->size-1;
  
  while(has_parent(h, index) && parent(h, index) > h->arr[index])
  {
    int pi = get_parent_index(index);
    swap(&h->arr[index], &h->arr[pi]);
    index = pi;
  }
}

void add(heap_t* h, int val){
  h->size += 1;
  assert(h->size <= h->capacity);
  h->arr[h->size-1] = val;
  
  heapify_up(h);
}

void heapify_down(heap_t* h){
  assert(h->size >= 0);
  int index = 0;
  
  while(has_leftchild(h, index)){
    int smaller_index = get_leftchild_index(index);
    if(has_rightchild(h, index) && rightchild(h, index) < leftchild(h, index))
      smaller_index = get_rightchild_index(index);
    
    if(h->arr[smaller_index] < h->arr[index])
      swap(&h->arr[smaller_index], &h->arr[index]);
    else
      return;
    index = smaller_index;
  }
}

int pop(heap_t* h)
{
  assert(h->size > 0);
  int ret = h->arr[0];
  
  h->arr[0] = h->arr[h->size-1];
  h->size -= 1;
  heapify_down(h);
  
  return ret;
}

void print_arr(int *arr, int size){
  for(int i = 0; i < size; ++i)
    printf("%d ", arr[i]);
}

int main(){
  heap_t* h = create_heap(20);
  
  add(h, 9);
  add(h, 4);
  add(h, 8);  
  add(h,19);
  add(h, -9);
  add(h,6);
  add(h, -19);
  
  printf("%d\n",pop(h));
  printf("%d\n",pop(h));
  printf("%d\n",pop(h));
  printf("%d\n",pop(h));
  printf("%d\n",pop(h));
  printf("%d\n",pop(h));
  printf("%d\n",pop(h));  
  
  destroy_heap(h);
  return 0;
}
