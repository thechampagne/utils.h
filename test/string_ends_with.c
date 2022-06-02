#include <stdio.h>
#include "utils.h"

int main() 
{
  char* str = "Hello World";
  int ends = string_ends_with(str, "World");
  printf("%d", ends);
  return 0;
}