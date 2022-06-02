#include <stdio.h>
#include <string.h>
#include "utils.h"

int main() 
{
  char* str = "Hello World";
  char rand = random_char(str, strlen(str));
  printf("%c", rand);
  return 0;
}