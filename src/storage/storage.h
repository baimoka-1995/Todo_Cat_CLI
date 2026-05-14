#ifndef STORAGE_H
#define STORAGE_H
#include "list.h"

void all_save_file(Schedule *list);
void load_file(Schedule *list);

void storage_cleanup_expired(Schedule *list);

#endif