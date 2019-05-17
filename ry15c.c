#include <stdio.h>

int main(int argc, char *argv[])
{
  char *string[] = { "I am but a humble string", "narf" };

  char **string_pointer = string;

  printf("This should just be the first string: %s\n", string[0]);
  printf("This should just be the second string: %s\n", string[1]);
  printf("%s and I live at %p\n", *(string_pointer), string_pointer);

  char *str_p = string[0];
  char *line = str_p;

  printf("This should just be the pointer for first string: %p\n", str_p);
  printf("This should just be the line itself: %s\n", line);
  printf("This should be the address for the line: %p\n", &line);

  printf("This should be a char: %c, and another: %c\n", line[0], line[11]);
  return 0;
}
