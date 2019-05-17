#include <stdio.h>

int main(int argc, char *argv[])
{
  // create two arrays
  int ages[] = { 23, 43, 12, 89, 2 };
  char *names[] = {
    "Jimmy", "Jane", "Jimbo", "Jjort", "Jbarbara"
  };

  // safely get size of ages. I guess it's required.
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // loop over indexes
  for (i = 0; i < count; i++) {
    printf("%s has been alive for %d years.\n", names[i], ages[i]);
  }

  printf("---\n");

  // setup pointers to the start of the arrays
  int *cur_age = ages;
  char **cur_name = names;

  // second way
  for (i = 0; i < count; i++) {
    printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
  }

  printf("---\n");

  // third way
  for (i = count - 1; i > -1; i--) {
    printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
  }

  return 0;
}

