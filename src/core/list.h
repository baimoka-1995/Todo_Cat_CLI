#ifndef LIST_H
#define LIST_H

typedef struct schedule{
    char *content;

    int state; // state == 1 已完成
    int priorty; // 1,2,3,4 (1 最高)
    int date;

    struct schedule *prev;
    struct schedule *next;
} Schedule;

Schedule *init_schedule();


Schedule *find_tail(Schedule *list);
Schedule *insert_last(Schedule *tail , char *content , int priorty , int state , int date);


Schedule *find_byserial(Schedule *list , int num);
void delete_sch(Schedule *Delnode);
void done_list(Schedule *Done_node);


int trav_list(Schedule *list);


void filter_list(Schedule *list , int (* predicate)(Schedule * , void *) , void *arg);
int is_prior(Schedule *s , void *arg);


Schedule * remove_node(Schedule *node);
int sort_byprior(Schedule *list);

#endif