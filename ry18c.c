#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define  LIST_MAX 20

void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("NOPE! %s\n", message);
  }
  exit(1);
}

struct Array{
  int list[LIST_MAX];
  int count;
};

struct Array *Create_array(const char **list, int count)
{
  struct Array *arr = malloc(sizeof(struct Array));
  if (!arr) die("array couldn't be created");

  arr->count = count;
  if (!arr->count) die("couldn't save count");

  int i = 1;
  for (i = 1; i < count; i++) {
    arr->list[i] = atoi(list[i]);
  }
  if (!arr->list || !arr->list[1]) die("couldn't save list");

  return arr;
}

typedef int(*funct_cb) (int a, int b);

int mult(int a, int b)
{
  return a * b;
}

int sub(int a, int b)
{
  return a - b;
}

int add(int a, int b)
{
  return a + b;
}

int divd(int a, int b)
{
  return a / b;
}

void Map_array(struct Array *arr, int val, funct_cb fn)
{
  int i = 1;

  for (i= 1; i < arr->count; i++) {
    int return_val = fn(arr->list[i], val);
    arr->list[i] = return_val;
  }
}

void Print_array(struct Array *arr)
{
  int i = 1;
  for (i = 1; i < arr->count; i++) {
    printf("%d ", arr->list[i]);
  }
  printf("\n");
}


int main(int argc, char *argv[])
{
  if (argc < 2) die("USAGE: ex18 4 3 1 5 6");
  if (argc > 20) die("Array won't save above 20");

  int count = argc;

  int i = 1;
  int *array[count];

  struct Array *ar1 = Create_array(argv, count);

  printf("hi\n");
  // prints original arra**y
  Print_array(ar1);

  Map_array(ar1, 4, mult);
  Print_array(ar1);

  Map_array(ar1, -4, mult);
  Print_array(ar1);

  free(ar1);

  return 0;
}
