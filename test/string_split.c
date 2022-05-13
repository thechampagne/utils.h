#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() 
{
  char* str = "Collection of utility for C.";
  int length;
  
  char** arr = string_split(str, " ", &length);
  
  for(int i = 0; i < length; i++)
  {
    printf("%s\n", arr[i]);
  }

  for(int i = 0; i < length; i++)
  {
    free(arr[i]);
  }
  free(arr);
  
  return 0;
}