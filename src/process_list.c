#include "../include/process_list.h"

#include <stdlib.h>

struct process_list_item
{
  int pid;
  int gid;
  int sid;
  struct process_list_item *next;
};

struct process_list
{
  PL_item head;
  PL_item tail;
};

PL create_PL()
{
  
}

int insert_PL(int pid, int gid, int sid)
{
}

PL destroy_PL()
{
}
