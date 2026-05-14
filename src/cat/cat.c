#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "cat.h"
#include "cat_assets.h"

static const char *cat_pick(const char *lines[]){
    int count = 0;

    while (lines[count] != NULL){
        count++;
    }

    if (count == 0){
        return "";
    }

    return lines[rand() % count];
}

CatState * cat_init(){
    CatState *cat = (CatState *)malloc(sizeof(CatState));
    
    cat->mood = 100;
    cat->streak = 0;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int date = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;

    cat->last_done_date = date;
    cat->last_open_date = date;

    return cat;
}


void cat_on_open(CatState *cat){
    if (cat->mood <= 95){
        cat->mood+= 5;
    }

    printf("\n%s " , cat_pick(happy_face));
    printf("%s\n" , cat_pick(open_lines));

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int date = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;

    cat->last_open_date = date;
}


void cat_on_add(CatState *cat){
    if (cat->mood > 5){
        cat->mood-= 5;
    }

    printf("\n%s " , cat_pick(happy_face));
    printf("%s\n" , cat_pick(add_lines));
}


void cat_on_done(CatState *cat){
    if (cat->mood <= 90){
        cat->mood += 10;
    }

    printf("\n%s " , cat_pick(happy_face));
    printf("%s\n" , cat_pick(done_lines));

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int date = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;

    cat->last_done_date = date;
}


void cat_on_incorrect(CatState *cat){
    if (cat->mood >= 5){
        cat->mood -= 5;
    }

    printf("\n%s " , cat_pick(depress_face));
    printf("%s\n" , cat_pick(incorrect_lines));
}

void cat_save(CatState *cat){
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
    "%s/Documents/.todo_data/MYCAT.txt",
    getenv("HOME")
    );
        
    FILE *fp = fopen(path , "w");

    if (fp == NULL){
        return;
    }

    fprintf(
        fp, "%d|%d|%d|%d\n" , 
        cat->mood , cat->streak , cat->last_done_date , cat->last_open_date
    );

    fclose(fp);
}

void cat_load(CatState *cat){
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
    "%s/Documents/.todo_data/MYCAT.txt",
    getenv("HOME")
    );
        
    FILE *fp = fopen(path , "r");
    if (fp == NULL){
        return;
    }

    int mood , streak , last_done_date , last_open_date;

    fscanf(
        fp, "%d|%d|%d|%d\n" , 
        &mood , &streak , &last_done_date , &last_open_date
    );

    cat->mood = mood;
    cat->streak = streak;
    cat->last_done_date = last_done_date;
    cat->last_open_date = last_open_date;

    fclose(fp);
}

void cat_wait(CatState *cat){
    if (cat->mood >= 1){
        cat->mood--;
    }
    
    printf("\n%s " , cat_pick(lonely_face));
    printf("%s\n" , cat_pick(undone_lines));
}