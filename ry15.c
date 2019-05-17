#include <stdio.h>

main(int argc, char *argv[])
{
  int numnum = 100;
  int *num_loc = &numnum;

  printf("Numnum is '%d' and lives at %p.\n", numnum, *num_loc);

  char name[] = { 'a', 'b', 'e', '\0'};

  int *name_loc = &name;

  printf("%s Froman, sausage king at %p\n", name, *name_loc);
  // I need to figure out these a bit more.
  //
  

  return 0;
}
