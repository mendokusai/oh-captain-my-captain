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

  return arr;
}

struct Array *Create_num_array(const int *list, int count)
{
  struct Array *arr = malloc(sizeof(struct Array));
  if (!arr) die("array couldn't be created");

  arr->count = count;
  if (!arr->count) die("couldn't save count");

  int i = 1;
  for (i = 1; i < count; i++) {
    arr->list[i] = list[i];
  }

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

int Reduce(struct Array *arr)
{
  int accumulator = 0;
  int i = 1;
  for (i = 1; i < arr->count; i++) {
    accumulator = arr->list[i] + accumulator;
  }

  return accumulator;
}

// This version just blasts the existing array.
// I'm not a fan, but maybe I'm just too used to FP
void Filter_array(struct Array *arr, int value)
{
  int i = 1;
  int new_count = 0;
  int *temp[arr->count];
  for (i = 1; i < arr->count; i++) {
    if (arr->list[i] == value) {
      printf("\tMatch!\n");
      new_count++;
      temp[new_count] = arr->list[i];
      printf("new count %d\n", new_count);
    } else {
      printf("no match\n");
    }
  }

  for (i = 1; i < arr->count; i++) {
    if (arr->list[i] <= new_count) {
      arr->list[i] = temp[i];
    }
  }
  arr->count = new_count;
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

  struct Array *ar1 = Create_array(argv, count);

  // original
  printf("original array:\n");

  Print_array(ar1);

  int acc0 = Reduce(ar1);

  printf("Reduced Array: %d\n", acc0);
  printf("---\n");

  Filter_array(ar1, 2);
  printf("I've filted that down to only 2s\n");
  Print_array(ar1);
  printf("---\n");

  // mult4
  printf("Multiplied by 4:\n");

  Map_array(ar1, 4, mult);

  Print_array(ar1);
  printf("---\n");


  // Mult -4
  printf("Multiplied by -4:\n");

  Map_array(ar1, -4, mult);

  Print_array(ar1);

  int acc1 = Reduce(ar1);

  printf("Reduced Array: %d\n", acc1);
  printf("---\n");

  free(ar1);

  return 0;
}
