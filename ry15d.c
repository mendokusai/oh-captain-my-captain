#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char *names[] = { "Ryan", "Gabriel", "Michael", "Melissa", "Taryn"};

  int i = 0;

  // iterates over arrayof names
  int names_length = 5;//sizeof(names) / sizeof(char);
  printf("Club has %d members\n", names_length);

  for(i = 0; i < names_length; i++) {
    printf("\t%s\n", names[i]);
  }

  printf("---l\n");
  /*char name_ptr = &names;*/
  /*printf("names array lives at: %p\n", name_ptr);*/

  char **names_of_malloc = malloc(5 * 20 * sizeof(char));
  names_of_malloc[1] = "Bizzaro Ryan";
  names_of_malloc[2] = "Bizzaro Gabriel";
  names_of_malloc[3] = "Bizzaro Michael";
  names_of_malloc[4] = "Bizzaro Melissa";
  names_of_malloc[5] = "Bizzaro Taryn";

  printf("---p\n");
  int malloc_length = *names_of_malloc;
  int m_length2 = sizeof(malloc_length);
  printf("Bizzaro pointer has a length of '%d'.\n", m_length2);
  printf("char size length '%d'.\n", sizeof(char));
  printf("names_of_malloc pointer '%p'.\n", names_of_malloc);
  printf("names_of_malloc meat '%s'.\n", *names_of_malloc);
  printf("*names_of_malloc size '%lu'.\n", sizeof(*names_of_malloc));
  printf("**names_of_malloc size '%lu'.\n", sizeof(**names_of_malloc));

  printf("---P\n");

  printf("Bizzaro club has %d members.\n", 5);

  for(i = 1; i < 6; i++) {
    printf("\t%s\n", names_of_malloc[i]);
  }

  return 0;
}

// So there's all sorts of things wrong with this.
// Mainly that you can't use malloc to create an array of strings and then get sizeof() and have that be meaningful.
// Spent far too long trying to get something to work there, oh well. Learn from my tribulations.
//
// The best part is upon doing all this, reading this little bit from the book (p85)
//
// > Pointers Are Not Arrays
// > No matter what, you should never think that pointers and arrays are the same thing. They are
// > not the same thing, even though C lets you work with them in many of the same ways. For
// > example, if you do sizeof(cur_age) in the code above, you would get the size of the pointer,
// > not the size of what it points at. If you want the size of the full array, you have to use the
// > array’s name, age, as I did on line 12.
