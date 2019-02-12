#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_MAX_LIMIT 500
#define word int
#define wsize sizeof(word)
#define wmask wsize-1

typedef enum{
  NO_ERROR=0,
  ERROR_NULL,
  ERROR_SZERO,
  ERROR_SMAX,
  ERROR_OVERLAP,
  ERROR_OVERFLOW,
}error_t;

char* strcat_s(char *d0, char *s0, size_t dmax, error_t *err)
{
  if(d0 == NULL || s0 == NULL)
  {
    *err = ERROR_NULL;
    return NULL;
  }
  else if(dmax == 0)
  {
    *err = ERROR_SZERO;
    return NULL;
  }
  else if(dmax > SIZE_MAX_LIMIT)
  {
    *err = ERROR_SMAX;
    return NULL;
  }
  *err = NO_ERROR;
  char *d = d0, *s = s0;
  if(d < s){                      //fwd-copy
    char *overlap_bumper = s;
    // go to the end of destination string
    // along the way, check if dmax reaches to 0(means buffer too small)
    // also check for overlap
    
    while(*d){
      if(d == overlap_bumper){
        *err = ERROR_OVERLAP;
        return NULL;
      }
      ++d;
      --dmax;
      if(dmax == 0){
        *err = ERROR_OVERFLOW;
        return NULL;
      }
    }
    while(dmax){
      if(d == s){
        *err = ERROR_OVERLAP;
        return NULL;
      }
      *d = *s;
      if(dmax == 0){
        *err = ERROR_OVERFLOW;
        return NULL;
      }
      ++d; 
      ++s;
      --dmax;
    }   
  }
  else{
    char *overlap_bumper = d;
    // go to the end of destination string
    // along the way, check if dmax reaches to 0(means buffer too small)
    // also check for overlap
    
    while(*d){
      ++d;
      --dmax;
      if(dmax == 0){
        *err = ERROR_OVERFLOW;
        return NULL;
      }
    }
    while(dmax){
      if(s == overlap_bumper){
        *err = ERROR_OVERLAP;
        return NULL;
      }
      *d = *s;
      if(dmax == 0){
        *err = ERROR_OVERFLOW;
        return NULL;
      }
      ++d; 
      ++s;
      --dmax;
    }   
  }
  return d0;
}

int main() {
  
  char *s2 = (char*)malloc(sizeof(char)*50);
  strcpy(s2, "Hello");
  
  
  error_t err = NO_ERROR;
  printf("%s\n", strcat_s(s2, " World", 50, &err));
  
  return 0;
}
