#include <stdio.h>


struct test{
  char first;
  char* second;
};

int main(int argc, char *argv[])
{
  int size = sizeof(struct test);
  printf("Size is: %d \n", size);
  return 0;
}
