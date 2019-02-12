#include <stdio.h>
#include <assert.h>
#include <string.h>

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

void* memcpy_s(void *d0, void *s0, size_t smax, size_t dmax, error_t *err)
{   
  // printf("dmax = %d\n",(size_t)dmax > (size_t)SIZE_MAX_LIMIT);
  char *d = (char*)d0, *s = (char*)s0;
  
  if(d0 == NULL || s0 == NULL)
  {
    *err = ERROR_NULL;
    return NULL;
  }
  else if(dmax == 0 || smax == 0)
  {
    *err = ERROR_SZERO;
    return NULL;
  }
  else if(dmax > SIZE_MAX_LIMIT)
  {
    *err = ERROR_SMAX;
    return NULL;
  }
  else if(((d < s) && (s < d+dmax)) || ((s < d) && (d < s+smax)))
  {
    *err = ERROR_OVERLAP;
    return NULL;
  }
  else if(dmax < smax)
  {
    *err = ERROR_OVERFLOW;
    return NULL;
  }
  
  *err = NO_ERROR;
  if(d == s)  return d;
  
  size_t t = (size_t)s;
  size_t temp = 0;
  
  if((((size_t)s) | ((size_t)d)) & (wmask)){               // if not word-aligned
        // if last 2 bits are not the same, can't align, or if dmax < wsize, no need to
    if(((((size_t)s)&(wmask)) ^ (((size_t)d)&(wmask))) || dmax < (wsize))
    {
      t = dmax;
      temp = t;
      while(t){*d++ = *s++; --t;}
      return d0;
    }
    else
    {
      t = wsize - ((size_t)s & (wmask));
      temp = t;
      while(t){*d++ = *s++; --t;}
    }
  }
  dmax -= temp;
  t = dmax/wsize;
  while(t){
    *((word*)d) = *((word*)s); 
    d += wsize; 
    s += wsize;
    --t;
  }
  t = dmax & wsize;
  while(t){*d++ = *s++; --t;}
  
  return d0;
  
}
void test_memcpy()
{
  char s1[] = "Goliath";
  char s2[] = "David";
  
  int len1 = strlen(s1);
  int len2 = strlen(s2);
    
  error_t err = NO_ERROR;
  
  //test case 1: destination is null
  memcpy_s(NULL, s1, len1+1, len2+1, &err);
  assert(err == ERROR_NULL);
  
  //test case 1: source is null
  memcpy_s(s2, NULL, len1+1, len2+1, &err);
  assert(err == ERROR_NULL);
  
  //dmax = 0
  memcpy_s(s2,s1,len1+1, 0 ,&err);
  assert(err == ERROR_SZERO);
  
  //smax = 0
  memcpy_s(s2,s1,0, len2+1,&err);
  assert(err == ERROR_SZERO);
  
  //dmax is too big
  memcpy_s(s2,s1,len1+1, 700,&err);
  assert(err == ERROR_SMAX);

  //overlap(dest < src)
  memcpy_s(s2,s2+1,len2,len2-1,&err);
  assert(err == ERROR_OVERLAP);
  
  //overlap(dest > src)
  memcpy_s(s1+3,s1,len1,len1-3,&err);
  assert(err == ERROR_OVERLAP);
  
  //overflow -> dest < src
  memcpy_s(s2,s1,len1+1,len2+1,&err);
  assert(err == ERROR_OVERFLOW);
  
  //wmask bits not the same(cannot align)
  memcpy_s(s1, s2+1, len2, len1+1, &err);
  assert(err == NO_ERROR);
  
  //wmask bits the same but don't start at word boundary
  memcpy_s(s1+2, s2+2, len2-1, len1-1, &err);
  assert(err == NO_ERROR);
  
  //normal case
  memcpy_s(s1, s2, len2+1, len1+1, &err);
  assert(err == NO_ERROR);
  
  
  printf("And the winner is - %s \n", s1);
  
}
int main() {
  test_memcpy();
  return 0;
}
