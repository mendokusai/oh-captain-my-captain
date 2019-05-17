#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("ERR: %s\n", message);
  }
  exit(1);
}


typedef int(*funct_cb) (int a, int b);

int *map_by(int *list, int factor, funct_cb f)
{
    int i = 0;
    int length = sizeof(list);
    int *target = malloc(length * sizeof(int));

    for(i = 0; i < length; i++) {
      target[i] = f(list[i], factor);
    }
    return target;
}

void print_results(int *numbers, int factor, funct_cb func)
{
  int i = 0;
  int *result = map_by(numbers, factor, func);
  int size = sizeof(result) - 2;

  if (!result) die("Failed to run map function");

  for (i = 0; i < size; i++) {
    printf("%d ", result[i]);
  }
  printf("\n");

  free(result);
}

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

int main(int argc, char *argv[])
{
  if (argc < 2) die("Usage ex18a 1 2 3 4 5");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv +1;

  int *numbers = malloc(count * sizeof(int));
  if (!numbers) die("Memory Error.");

  for (i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }
  print_results(numbers, 2, add);
  print_results(numbers, 3, add);
  print_results(numbers, 2, mult);
  print_results(numbers, 2, sub);
  print_results(numbers, 7, sub);
  print_results(numbers, 2, divd);

  return 0;
}
