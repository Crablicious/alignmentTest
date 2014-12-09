#include <stdio.h>


struct test{
  char first;
  double second;
  int third;
  char fourth;
  char* fifth;
};

int main(int argc, char *argv[])
{
  int size = sizeof(struct test);
  printf("Size is: %d \n", size);
  printf("Size is: %d \n", (int)sizeof(double));
  printf("Size is: %d \n", (int)sizeof(char*));
  return 0;
}
