#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef enum{
  NO_ERROR = 0,
  ERROR_LOW_MEMORY,
  ERROR_STACK_FULL,
  ERROR_STACK_EMPTY
}error_t;

typedef struct{
  int capacity;
  int *arr;
  int top;
}stack_t;

stack_t* create_stack(int capacity, error_t *err)
{
  stack_t* s = (stack_t*)malloc(sizeof(stack_t));
  if(s == NULL){
    *err = ERROR_LOW_MEMORY;
  }
  s -> capacity = capacity;
  s -> top = 0;
  s->arr = (int*)malloc(sizeof(int)*capacity);
  
  return s;
}

void push(stack_t* s, int a, error_t *err)
{
  if(s->top == s->capacity){
    *err = ERROR_STACK_FULL;
    return;
  }
  s->arr[s->top++] = a;
  *err = NO_ERROR;
}

int pop(stack_t* s, error_t* err){
  if(s->top == 0){
    *err = ERROR_STACK_EMPTY;
    return 0;
  }
  s->top -= 1;
  *err = NO_ERROR;
  return s->arr[s->top];
}

void free_stack(stack_t *s){
  free(s->arr);
  free(s);
}
// To execute C, please define "int main()"

int main() {
  error_t err = NO_ERROR;
  stack_t* s = create_stack(3, &err);
  
  push(s, 1, &err);
  assert(err == NO_ERROR);
  
  push(s,2,&err);
  assert(err == NO_ERROR);
  
  push(s,3,&err);
  assert(err == NO_ERROR);
  
  push(s,4,&err);
  assert(err == ERROR_STACK_FULL);
  
  assert(pop(s,&err) == 3);
  
  assert(pop(s,&err) == 2);
  
  assert(pop(s,&err) == 1);
  
  pop(s,&err);
  assert(err == ERROR_STACK_EMPTY);
  
  push(s,2,&err);
  assert(err == NO_ERROR);
  
  push(s,1,&err);
  assert(err == NO_ERROR); 
  
  assert(pop(s,&err) == 1);
  
  push(s,2,&err);
  assert(err == NO_ERROR);
  
  assert(pop(s,&err) == 2);
  
  assert(pop(s,&err) == 2);
  
  pop(s,&err);
  assert(err == ERROR_STACK_EMPTY);
  
  free_stack(s);
  
  return 0;
}
