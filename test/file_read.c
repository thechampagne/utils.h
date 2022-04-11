#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main()
{
  char* content = file_read("note.txt");
  printf("%s", content);
  free(content);
  return 0;
}