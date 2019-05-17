#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*DATE_LIMIT "2019-05-04"*/
/*TIME_LIMIT "11:03PM"*/
#define TODO_LIMIT 100
#define DATE_LIMIT 100
#define MAX_ROWS 100
#define MAX_DATA 512

struct Todo {
  int id;
  int set;
  char chore[TODO_LIMIT];
  char due_date[DATE_LIMIT];
  int completed;
};

struct Database {
  struct Todo rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Todo_print(struct Todo *tod)
{
  char *complete;
  if (tod->completed) {
    complete = "DONE";
  } else {
    complete = "Todo";
  }

  printf("%s: '%s' by %s \n", complete, tod->chore, tod->due_date);
}

void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("Error: %s\n", message);
  }

  exit(1);
}

void DatabaRse_load(struct Connection *conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn-> file);
  if (rc != 1)
    die("Database could not be loaded");
}

struct Connection *Database_open(const char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn)
    die("Memory could not be allocated");

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db)
    die("Memory could not be malloc'd");

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file)
      die("Your DB file could not be openend");

  return conn;
}

void Database_close(struct Connection *conn)
{
  if (conn) {
    if (conn->file)
      fclose(conn->file);
      if (conn->db)
        free(conn->db);
      free(conn);
  }
}

void Database_write(struct Connection *conn)
{
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1)
    die("Couldn't write to the database.");

  rc = fflush(conn->file);
  if (rc == -1)
    die("Database cannot be flushed.");
}

void Database_create(struct Connection *conn)
{
  int i = 0;

  for (i = 0; i < MAX_ROWS; i++) {
    struct Todo tod = {.id = i, .set = 0};
    conn->db->rows[i] = tod;
  }
}

void Database_set(struct Connection *conn, int id, const char *chore, const char *due_date)
{
  struct Todo *tod = &conn->db->rows[id];
  if (tod->set)
    die("ID already set, choose another or delete.");

  tod->set = 1;

  char *res = strncpy(tod->chore, chore, TODO_LIMIT);

  if (!res)
    die("Name copy failed");

  res = strncpy(tod->due_date, due_date, TODO_LIMIT); 
  if (!res)
    die("Could not copy due_date.");
}

void Database_update(struct Connection *conn, int id)
{
  struct Todo *tod = &conn->db->rows[id];
  if (tod->completed) {
    die("You finished that one.");
  } else {
    tod->completed = 1;
  }
}

void Database_get(struct Connection *conn, int id)
{
  struct Todo *tod = &conn->db->rows[id];

  if (tod->set) {
    Todo_print(tod);
  } else {
    die("ID could not be found");
  }
}

void Database_delete(struct Connection *conn, int id)
{
  struct Todo tod = {.id = id, .set = 0};
  conn->db->rows[id] = tod;
}

void Database_list(struct Connection *conn)
{
  int i = 0;
  struct Database *db = conn-> db;

  for (i = 0; i < MAX_ROWS; i++) {
    struct Todo *current = &db->rows[i];

    if (current->set) {
      Todo_print(current);
    }
  }
}
int main(int argc, char *argv[])
{
  if (argc < 3)
    die("Usage: 'ry17b <db_file> <action> [action params]'");

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);

  int id = 0;

  if (argc > 3) id = atoi(argv[3]);
  if (id >= MAX_ROWS) die("ID too high, man.");

  switch (action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 'g':
      if (argc != 4)
        die("Need an ID number to search");

      Database_get(conn, id);
      break;

    case 's':
      if (argc != 6)
        die("Need ID, chore, due date to create a record");

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'u':
      if (argc != 5)
        die("Need ID, and 1 or 0 to update a record");

      Database_update(conn, id);
      Database_write(conn);
      break;

    case 'd':
      if (argc != 4)
        die("Need an ID to delete a record");

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;

    default:
      die("Invalid action: c=create, g=get, s=set, d=delete, l=list");
  }

  Database_close(conn);

  return 0;
}

