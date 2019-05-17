#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* yes_or_no(bool boolean)
{
  if (boolean)
    return "yes";
  else
    return "no";
}

struct Todo {
  char *title;
  int tedium;
  char *due_date;
  bool complete;
};

struct Todo *Todo_create(char *title, int tedium, char *due_date, bool complete)
{
  struct Todo *event = malloc(sizeof(struct Todo));
  assert(event != NULL);

  event->title = strdup(title);
  event->tedium = tedium;
  event->due_date = due_date;
  event->complete = complete;

  return event;
}

void Todo_destroy(struct Todo *event)
{
  assert(event != NULL);
  free(event->title);
  free(event);
}

void Todo_print(struct Todo *event)
{
  char *complete = yes_or_no(event->complete);
  printf("%s\n", event->title);
  printf("\tTedium level: %d. | Due by: %s\n", event->tedium, event->due_date);
  printf("\tCompleted: %s\n", complete);
  /*if (event->complete == 1)*/
    /*printf("\tCompleted: Yes\n");*/
  /*else*/
    /*printf("\tCompleted: No\n");*/
}

int main(int argc, char *argv[])
{
  struct Todo *study = Todo_create("Study CLANG", 2, "Friday", false);

  printf("Here's my first todo:\n");
  Todo_print(study);

  study->complete = true;

  printf("The study is complete?\n");
  Todo_print(study);

  Todo_destroy(study);

  return 0;
}
