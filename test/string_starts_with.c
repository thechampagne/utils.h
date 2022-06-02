#include <stdio.h>
#include "utils.h"

int main() 
{
  char* str = "Hello World";
  int starts = string_starts_with(str, "Hello");
  printf("%d", starts);
  return 0;
}