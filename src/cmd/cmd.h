#ifndef CMD_H
#define CMD_H

#include "cat.h"
#include "list.h"

int dispatch (Schedule *list , CatState *cat , int argc , char *argv[]);

int cmd_list (Schedule *list , CatState *cat ,  int argc , char *argv[]);
int cmd_add (Schedule *list , CatState *cat ,  int argc , char *argv[]);
int cmd_delete (Schedule *list , CatState *cat ,  int argc , char *argv[]);
int cmd_done (Schedule *list , CatState *cat ,  int argc , char *argv[]);
int cmd_find (Schedule *list , CatState *cat ,  int argc , char *argv[]);
int cmd_sort(Schedule *list , CatState *cat ,  int argc , char *argv[]);

int cmd_cat_wait(CatState *cat);

#endif
