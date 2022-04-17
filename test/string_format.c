#include <stdio.h>
#include "utils.h"

int main() 
{
  char* str = string_format("Hello %s", "World");
  printf("%s\n", str);
  free(str);
  return 0;
}