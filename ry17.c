#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("\t* Woah there cool guy, you've done goofed *\n %s\n", message);
  }

  exit(1);
}

void Address_print(struct Address *addr)
{
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc !=1)
    die("Database could not be loaded.");
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
    // mae a prototype to initialize
    struct Address addr = {.id = i, .set = 0 };
    // now assign it
    conn->db->rows[i] = addr;
  }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  struct Address *addr = &conn->db->rows[id];
  if (addr->set)
    die("Given ID is already assigned. To set data, delete the current record");

  addr->set = 1;

  char *new_name = NULL;
  char *catstring = strcpy(new_name, name);
  char *res = strncpy(addr->name, catstring, MAX_DATA);

  // demo the strncpy bug
  if (!res)
    die("Name copy failed");

  res = strncpy(addr->email, email, MAX_DATA);
  if (!res)
    die("Attempt to copy Email has failed.");
}

void Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID could not be found.");
  }
}

void Database_delete(struct Connection *conn, int id)
{
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
  int i = 0;
  struct Database *db = conn->db;

  for (i = 0; i < MAX_ROWS; i++) {
    // <cur> at address of db at row i is with an Address struct.
    struct Address *cur = &db->rows[i];

    if (cur->set) {
      Address_print(cur);
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 3)
    die("Usage: 'ry17 <db_file> <action> [action params]'");

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);

  int id = 0;

  if (argc > 3) id = atoi(argv[3]);
  if (id >= MAX_ROWS) die("ID is beyond records max.");

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
        die("Need ID, name, email to create a record");

      Database_set(conn, id, argv[4], argv[5]);
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
