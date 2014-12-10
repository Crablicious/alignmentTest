
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


size_t structSizeFromString(char *layout) {
  size_t res = 0;
  int i = 0;
  char c = *layout;
  while (c) {
    c = *(layout + i);
    switch (c) {
    case 'c':
      res += sizeof(char);
      break;
    case '*':
      res += sizeof(void*) - res % sizeof(void*);
      res += sizeof(void*);
      break;
    case 'i':
      res += sizeof(int);
      break;
    case 'f':
      res += sizeof(float);
      break;
    case 'd':
      res += sizeof(double);
      break;
    case 'l':
      res += sizeof(long);
      break;
    }
    i++;
  }
  return res;
}

int main(int argc, char *argv[])
{
  char *string = malloc(10);
  string = "c*";
  size_t test = structSizeFromString(string);
  printf("Size is: %d \n", (int)test);
  return 0;
}
