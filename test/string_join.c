#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() 
{
  char* arr[] = {"Hello", "Hola", "Bonjour"};
  char* str = string_join(arr, ", ", sizeof(arr) / sizeof(arr[0]));
  printf("%s", str);
  free(str);
  return 0;
}