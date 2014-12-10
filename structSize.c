
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

size_t isLittle(void){
  unsigned int x = 1;
  return (int) (((char *)&x)[0]);
}

size_t max(size_t a, size_t b){
  if(a>b) return a;
  return b;
}

size_t structSizeFromString(char *layout) {
  size_t res = 0;
  size_t align = 1; //Largest alignment.
  int i = 0;
  char c = *layout;
  while (c) {
    c = *(layout + i);
    switch (c) {
    case 'c':
      res += sizeof(char);
      break;
    case '*':
      if(res % sizeof(void*) != 0){
        res += sizeof(void*) - res % sizeof(void*);
      }
      align = max(align, sizeof(void*));
      res += sizeof(void*);
      break;
    case 'i':
      if(res % sizeof(int) != 0){
        res += sizeof(int) - res % sizeof(int);
      }
      align = max(align, sizeof(int));
      res += sizeof(int);
      break;
    case 'f':
      if(res % sizeof(float) != 0){
        res += sizeof(float) - res % sizeof(float);
      }
      align = max(align, sizeof(float));
      res += sizeof(float);
      break;
    case 'd':
      if(isLittle() && res % sizeof(void*) != 0){
        res += sizeof(void*) - res % sizeof(void*);
        align = max(align, sizeof(void*));
      }else if(res % sizeof(double) != 0){
        res += sizeof(double) - res % sizeof(double);
        align = max(align, sizeof(double));
      }
      res += sizeof(double);
      break;
    case 'l':
      if(res % sizeof(long) != 0){
        res += sizeof(long) - res % sizeof(long);
      }
      align = max(align, sizeof(long));
      res += sizeof(long);
      break;
    }
    i++;
  }
  if(res % align != 0){
    res += align - res % align;
  }
  return res;
}

int main(int argc, char *argv[])
{
  char *string = malloc(10);
  string = "cdic*";
  size_t test = structSizeFromString(string);
  printf("Size is: %d \n", (int)test);

  string = "cdi";
  test = structSizeFromString(string);
  printf("Size is: %d \n", (int)test);
  return 0;
}
