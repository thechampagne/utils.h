#include <stdio.h>
#include "utils.h"

int main()
{
  long size;
  file_size("note.txt", &size);
  printf("note.txt size: %ld", size);
  return 0;
}