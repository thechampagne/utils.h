#include <stdio.h>
#include "utils.h"

int main() 
{
  int arr[] = {
    25,
    69,
    34,
    57,
    11
  };
  int max = array_max(arr, sizeof(arr) / sizeof(arr[0]));
  printf("Max number: %d", max);
  return 0;
}