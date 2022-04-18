#include <stdio.h>
#include "utils.h"

void divide(int a, int b)
{
  if (a == 0 && b == 0)
  {
    throws(700, "zero divided by zero not permitted");
  }

  if (b == 0)
  {
    throw(1);
  }

  printf("%d\n", a / b);
}

int main(void) {

  try {

    divide(0,0);

  } catches(700) {

    printf("Error: %s", errormessage);

  } catch {

    printf("Error: %s",errormessage);

  }
  return 0;
}