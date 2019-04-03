#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;
  while (i < 25) {
    // this prints a few different lines.
    if (i != 0 && i % 5 == 0) {
      printf("\n%d ", i);
    } else {
      printf("%d ", i);
    }
    i++;
  }
  // add a final newline
  printf("\n");

  return 0;
}
