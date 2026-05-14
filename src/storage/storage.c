#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "storage.h"
#include "list.h"

void all_save_file(Schedule *list){
    Schedule *temp = list->next;

    char dir[256];

    snprintf(
        dir,
        sizeof(dir),
        "%s/Documents/.todo_data",
        getenv("HOME")
    );

    mkdir(dir, 0755);

    char path[256];

    snprintf(
    path,
    sizeof(path),
    "%s/Documents/.todo_data/MYLIST.txt",
    getenv("HOME")
    );
        
    FILE *fp = fopen(path , "w");

    if (fp == NULL){
        return;
    }

    while (temp != NULL){
        fprintf(
            fp, "%s|%d|%d|%d\n" , 
            temp->content , temp->priorty , temp->state , temp->date
        );
        temp = temp->next;
    }
    fclose(fp);
}

void load_file(Schedule *list){
    char dir[256];

    snprintf(
        dir,
        sizeof(dir),
        "%s/Documents/.todo_data",
        getenv("HOME")
    );

    mkdir(dir, 0755);
        
    char path[256];
    
    snprintf(
    path,
    sizeof(path),
    "%s/Documents/.todo_data/MYLIST.txt",
    getenv("HOME")
    );
    
    FILE *fp = fopen(path , "r");

    if (fp == NULL){
        return;
    }

    Schedule *tail = list;
    char content[100];
    int priorty , state , date;

    while (
        fscanf(fp ,
            "%[^|]|%d|%d|%d\n",
            content , &priorty , &state , &date
        ) == 4
    ){
        tail = insert_last(tail, content, priorty , state , date);
    }

    fclose(fp);
}

void storage_cleanup_expired(Schedule *list){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int date = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;

    Schedule *temp = list->next;
    Schedule *next = NULL;
    while (temp != NULL){
        if (date != temp->date){
            next = temp->next;
            delete_sch(temp);
        } else {
            next = temp->next;
        }

        temp = next;
    }
}