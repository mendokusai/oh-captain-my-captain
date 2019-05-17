#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destroy(struct Person *who)
{
  assert(who != NULL);
  free(who->name);
  free(who);
}

void Person_print(struct Person *who)
{
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
  // make two people structures
  struct Person *jon_snow = Person_create("Jon Snow", 32, 64, 140);

  struct Person *aegon_targaren = Person_create("Aegon Targeren", 20, 72, 180);

  // Print them out
  printf("Jon is at memory location %p:\n", jon_snow);
  Person_print(jon_snow);

  printf("Aegon is at memory location %p:\n", aegon_targaren);
  Person_print(aegon_targaren);

  jon_snow->age += 20;
  jon_snow->height -= 4;
  jon_snow->weight +=40;
  
  Person_print(jon_snow);

  aegon_targaren->age += 10;
  aegon_targaren->weight -= 5;

  Person_print(aegon_targaren);

  Person_destroy(jon_snow);
  Person_destroy(aegon_targaren);

  return 0;
}
