#include <stdio.h>
#include <string.h>
#include "utils.h"

int main()
{
  char* content = "This is my note";
  file_write("note.txt", content, strlen(content));
  return 0;
}