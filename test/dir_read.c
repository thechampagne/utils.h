#include <stdio.h>
#include "utils.h"

int main() 
{
  dir_read_t dir;
  dir_read(&dir,".");
  for (int i = 0; i < dir.size; i++)
  {
    printf("%s: %u\n", dir.names[i], dir.types[i]);
  }
  dir_read_clean(&dir);
  return 0;
}