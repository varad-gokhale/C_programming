#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

typedef enum{
  NO_ERROR = 0,
  ERROR_LOW_MEMORY,
  ERROR_STACK_FULL,
  ERROR_STACK_EMPTY,
  ERROR_THREAD_FAIL
}error_t;

typedef struct{
  int capacity;
  int *arr;
  int top;
  pthread_mutex_t lock;
}stack_t;

stack_t* create_stack(int capacity, error_t *err)
{
  stack_t* s = (stack_t*)malloc(sizeof(stack_t));
  if(s == NULL){
    *err = ERROR_LOW_MEMORY;
  }
  s -> capacity = capacity;
  s -> top = 0;
  s -> arr = (int*)malloc(sizeof(int)*capacity);
  
  if(pthread_mutex_init(&s->lock, NULL) != 0)
  {  
    *err = ERROR_THREAD_FAIL;
    return NULL;
  }
  
  *err = NO_ERROR;
  return s;
}

//wrapper function for pthread_mutex_lock
void Pthread_mutex_lock(pthread_mutex_t *lock){
  assert(pthread_mutex_lock(lock) == 0);  
}

//wrapper function for pthread_mutex_lock
void Pthread_mutex_unlock(pthread_mutex_t *lock){
  assert(pthread_mutex_unlock(lock) == 0);  
}

void push(stack_t* s, int a, error_t *err)
{
  Pthread_mutex_lock(&s->lock);
  
  if(s->top == s->capacity){
    *err = ERROR_STACK_FULL;    
    Pthread_mutex_unlock(&s->lock);    
    return;
  }
  s->arr[s->top++] = a;
  *err = NO_ERROR;
  
  Pthread_mutex_unlock(&s->lock);    
}

int pop(stack_t* s, error_t* err){
  Pthread_mutex_lock(&s->lock);
  
  if(s->top == 0){
    *err = ERROR_STACK_EMPTY;
    Pthread_mutex_unlock(&s->lock);    
    return 0;
  }
  s->top -= 1;
  *err = NO_ERROR;
  
  Pthread_mutex_unlock(&s->lock);  
  
  return s->arr[s->top];
}

void free_stack(stack_t *s, error_t* err){
  free(s->arr);
  if(pthread_mutex_destroy(&s->lock) != 0){
    *err = ERROR_THREAD_FAIL;
    return;
  }
  free(s);
  *err = NO_ERROR;
}
// To execute C, please define "int main()"

int main() {
  error_t err = NO_ERROR;
  
  stack_t* s = create_stack(3, &err);
  assert(err == NO_ERROR);
  
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
  
  
  free_stack(s, &err);
  assert(err == NO_ERROR);
  
  return 0;
}
