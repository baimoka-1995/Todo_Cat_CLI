#ifndef CAT_H
#define CAT_H

typedef struct {
    int mood;
    int streak;

    int last_open_date;
    int last_done_date;
} CatState;

CatState *cat_init();

void cat_load(CatState *cat);
void cat_save(CatState *cat);

void cat_on_open(CatState *cat);
void cat_on_add(CatState *cat);
void cat_on_done(CatState *cat);
void cat_on_incorrect(CatState *cat);
void cat_wait(CatState *cat);

#endif