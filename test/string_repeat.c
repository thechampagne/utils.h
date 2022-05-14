#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() 
{
  char* str = string_repeat("Hello World ", 3);
  printf("%s", str);
  free(str);
  return 0;
}