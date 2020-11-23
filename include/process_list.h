#ifndef __PROCESS_LIST_H
#define __PROCESS_LIST_H

typedef struct process_list_item *PL_item;

typedef struct process_list *PL;

PL create_PL();
int insert_PL(int pid, int gid, int sid);
PL destroy_PL();

#endif
