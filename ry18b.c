#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LIST_MAX 10
/*typedef (*function)();*/

struct Array {
    int list[LIST_MAX];
    int count;
};

void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("NOPE! %s\n", message);
  }
  exit(1);
}

void Print_list(struct Array *arr)
{
  /*int i = 0;*/
  printf("Count is %u ", arr->count);

  /*for (i = 0; i < arr->count; i++) {*/
    /*printf("%d ", arr->list[i]);*/
  /*}*/
  printf("\n");
}

/*int map(int *list, int counter, function fn)*/
/*{*/

/*}*/

struct Array *Array_prepare(char **numbers_array, int count)
{
  struct Array *arr = malloc(sizeof(struct Array));

  /*if (!numbers) die("Could not create 'numbers' array");*/
  if (!arr) die("Could not create 'numbers' array");
  
  arr->count = count;
  /*arr->list = malloc(sizeof(int) * count);*/
  int i = 1;

  // just tried to see if putting 1 in here helped. na.
  for (i = 1; i < count; i++) {
    arr->list[i] = atoi(numbers_array[i]);
  }
};


int main(int argc, char *argv[])
{
  if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  if (count > LIST_MAX) die("List to friggin huge");

  printf("hi");
  char **inputs = argv + 1;
  struct Array *numbers_array = Array_prepare(inputs, count);

  Print_list(numbers_array);

  free(numbers_array);

  return 0;
}
