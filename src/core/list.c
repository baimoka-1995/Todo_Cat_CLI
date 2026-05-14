#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Schedule *init_schedule(){
    Schedule *list = (Schedule *)malloc(sizeof(Schedule));

    list->content = malloc(100);
    strcpy(list->content, "无");

    list->priorty = -1;
    list->state = -1;
    list->date = -1;

    list->prev = NULL;
    list->next = NULL;

    return list;
}

Schedule *find_tail(Schedule *list){
    Schedule *temp = list;

    while (temp->next != NULL){
        temp = temp->next;
    }

    return temp;
}

Schedule *insert_last(Schedule *tail , char *content , int priorty , int state , int date){
    if (tail == NULL){
        return NULL;
    }

    Schedule *new_node = (Schedule *)malloc(sizeof(Schedule));

    new_node->content = malloc(100);
    strcpy(new_node->content, content);

    new_node->priorty = priorty;
    new_node->state = state;
    new_node->date = date;

    new_node->prev = tail;
    new_node->next = NULL;
    tail->next = new_node;

    return new_node;
}

Schedule *find_byserial(Schedule *list , int num){
    Schedule *temp = list->next;

    if (num < 1){
        return NULL;
    }

    for (int i = 1 ; i < num ; i++){
        if (temp == NULL){
            return NULL;
        }

        temp = temp->next;
    }

    if (temp == NULL) {
        return NULL;
    }

    return temp;
}

void delete_sch(Schedule *Delnode){
    (Delnode->prev)->next = Delnode->next;

    if (Delnode->next != NULL) {
        Delnode->next->prev = Delnode->prev;
    }

    free(Delnode->content);
    free(Delnode);
}

void done_list(Schedule *Done_node){
    Done_node->state = 1;
}

int trav_list(Schedule *list){
    if (list->next == NULL){
        return 0;
    }

    Schedule *temp = list->next;
    int i = 1;

    while (temp != NULL){
        if (temp->state == 0){            
            printf("[ ] %d.%s , prior : %d\n" , i , temp->content , temp->priorty);
            i++;
        }
        temp = temp->next;
    }

    temp = list->next;
    while (temp != NULL){
        if (temp->state == 1){            
            printf("[√] %d.%s , prior : %d\n" , i , temp->content , temp->priorty);
            i++;
        }
        temp = temp->next;
    }
    
    return 1;
}

void filter_list(Schedule *list , int (* predicate)(Schedule *, void *) , void *arg){
    if (list->next == NULL){
        return;
    }

    Schedule *temp = list->next;
    while (temp != NULL){
        if (predicate(temp , arg) == 1){
            printf("%s\n" , temp->content);
        }

        temp = temp->next;
    }
}

int is_prior(Schedule *s , void *arg){
    int *d = (int *)arg;

    return *d == s->priorty;
}

Schedule * remove_node(Schedule *node){
    if (node == NULL) return NULL;

    if (node->next == NULL && node->prev == NULL){
        return node;
    } if (node->next == NULL){
        node->prev->next = NULL;
    } else if (node->prev == NULL){
        node->next->prev = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    node->next = NULL;
    node->prev = NULL;
    return node;
}

int sort_byprior(Schedule *list){
    if (list->next->next == NULL){
        return 0;
    }

    Schedule *temp = list->next->next;
    Schedule *node = NULL;

    while (temp != NULL){
        if (temp->priorty < temp->prev->priorty){
            // 开始向前遍历直到头节点
            Schedule *rep = temp->prev->prev;
            while (rep != list){
                if (rep->priorty <= temp->priorty){
                    node = temp;
                    node = remove_node(node);
                    
                    rep->next->prev = node;
                    node->next = rep->next;
                    rep->next = node;
                    node->prev = rep;
                }

                rep = rep->prev;
            }
        }

        temp = temp->next;
    }

    return 1;
}