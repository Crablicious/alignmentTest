#include <stdio.h>


struct test{
  char first;
  double second;
  int third;
  //char fourth;
  //char* fifth;
};

int main(int argc, char *argv[])
{
  int size = sizeof(struct test);
  printf("Size is: %d \n", size);
  return 0;
}
