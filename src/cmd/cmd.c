/*
0   → 成功
1   → 一般错误
2   → 参数错误
3   → 未知命令
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cmd.h"
#include "list.h"
#include "search.h"
#include "cat.h"

int dispatch(Schedule *list , CatState *cat ,  int argc , char *argv[]){

    if (argc == 1) {
        printf("no command\n");

        cat_on_incorrect(cat);
        return 1;
    }

    // argv[1] 是命令名
    char *cmd = argv[1];

    if (!strcmp(cmd, "today")){

        return cmd_list(list , cat , argc , argv);
    }

    else if (!strcmp(cmd, "add")){

        return cmd_add (list , cat , argc , argv);
    } 
    
    else if (!strcmp(cmd , "delete")){

        return cmd_delete(list , cat , argc , argv);
    } 
    
    else if (!strcmp(cmd, "done")){

        return cmd_done(list , cat , argc , argv);
    } 
    
    else if (!strcmp(cmd , "find")){

        return cmd_find(list , cat , argc , argv);
    } 
    
    else if (!strcmp(cmd , "sort")){

        return cmd_sort(list , cat , argc , argv);
    } 

    else if (!strcmp(cmd, "cat-wait")){
        
        return cmd_cat_wait(cat);
    }

    else if (!strcmp(cmd, "time-check")){
        
        return cmd_time_check(cat);
    }



    return 3;
}

int cmd_list(Schedule *list , CatState *cat ,  int argc , char *argv[]){
    if (!trav_list(list)){
        printf("还没有任务\n");
        return 1;
    }

    cat_on_open(cat);

    (void)argv;
    (void)argc;
    return 0;
}

int cmd_add (Schedule *list , CatState *cat ,  int argc , char *argv[]){
    if (argc < 4){
        return 1;
    }

    char content[100] = "";

    for (int i = 2 ; i < argc - 1 ; i++){
        strncat(content , argv[i] , sizeof(content) - strlen(content) - 1);

        if (i < argc - 2 && (sizeof(content) - strlen(content) - 1) > 0) {
            strncat(content, " ", sizeof(content) - strlen(content) - 1);
        }
    }

    int priorty = atoi(argv[argc - 1]);

    if (priorty > 4 || priorty < 1){
        printf("参数不合法");
        return 2;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int date = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;

    Schedule *tail = find_tail(list);
    tail = insert_last(tail, content, priorty, 0 , date);

    cat_on_add(cat);
    return 0;
}

int cmd_delete(Schedule *list , CatState *cat ,  int argc , char *argv[]){
    Schedule *temp = list;

    char buf[256] = {0};
    for (int i = 2; argv[i]; i++) {
        strncat(buf, argv[i], sizeof(buf) - strlen(buf) - 1);
        strncat(buf, " ", sizeof(buf) - strlen(buf) - 1);

        if (argv[i+1] == NULL){
            break;
        }
    }

    int count = 0;

    while (temp != NULL){
        if (split_string(temp->content, buf)){
            count++;
        }

        temp = temp->next;
    }

    temp = list->next;
    int serial = 1;
    while (temp != NULL){
        if (count == 1){
            if (split_string(temp->content, buf)){
                delete_sch(temp);
                return 0;
            }
        } else if (count > 1){
            if (split_string(temp->content, buf)){
                printf("%d. %s\n" , serial , temp->content);
                serial++;
            }
        }

        temp = temp->next;
    }

    printf("请输入要删除的序号：\n");

    char stuff[100];
    fgets(stuff , sizeof(stuff) , stdin);
    if (sscanf(stuff , "%d" , &serial) != 1 || serial < 1){
        printf("参数不合法\n");
        return 2;
    }

    temp = list->next;
    count = 1;

    while (temp != NULL){
        if (split_string(temp->content, buf)){
            if (serial == count){
                delete_sch(temp);
                return 0;
            }
            count++;
        }

        temp = temp->next;
    }

    (void)argc;
    (void)cat;
    printf("找不到任务");
    return 1;
}


int cmd_done(Schedule *list , CatState *cat ,  int argc , char *argv[]){
    Schedule *temp = list->next;

    char buf[256] = {0};
    for (int i = 2; argv[i]; i++) {
        strncat(buf, argv[i], sizeof(buf) - strlen(buf) - 1);
        strncat(buf, " ", sizeof(buf) - strlen(buf) - 1);

        if (argv[i+1] == NULL){
            break;
        }
    }

    int count = 0;

    while (temp != NULL){
        if (split_string(temp->content, buf)){
            count++;
        }

        temp = temp->next;
    }

    temp = list->next;
    int serial = 1;
    while (temp != NULL){
        if (count == 1){
            if (split_string(temp->content, buf)){
                done_list(temp);
                cat_on_done(cat);
                return 0;
            }
        } else if (count > 1){
            if (split_string(temp->content, buf)){
                printf("%d. %s\n" , serial , temp->content);
                serial++;
            }
        }

        temp = temp->next;
    }

    printf("请输入要完成的序号：\n");

    char stuff[100];
    fgets(stuff , sizeof(stuff) , stdin);
    if (sscanf(stuff , "%d" , &serial) != 1 || serial < 1){
        printf("参数不合法\n");
        return 2;
    }

    temp = list->next;
    count = 1;

    while (temp != NULL){
        if (split_string(temp->content, buf)){
            if (serial == count){
                done_list(temp);
                cat_on_done(cat);
                return 0;
            }
            count++;
        }

        temp = temp->next;
    }

    (void)argc;
    printf("找不到任务");
    return 1;
}

int cmd_find(Schedule *list , CatState *cat ,  int argc , char *argv[]){
    Schedule *temp = list;

    char buf[256] = {0};
    for (int i = 2; argv[i]; i++) {
        strncat(buf, argv[i], sizeof(buf) - strlen(buf) - 1);
        strncat(buf, " ", sizeof(buf) - strlen(buf) - 1);

        if (argv[i+1] == NULL){
            break;
        }
    }

    int count = 0;

    while (temp != NULL){
        if (split_string(temp->content, buf)){
            count++;
        }

        temp = temp->next;
    }

    temp = list->next;
    int serial = 1;
    while (temp != NULL){
        if (count == 1){
            if (split_string(temp->content, buf)){
                printf("%s\n" , temp->content);
                return 0;
            }
        } else if (count > 1){
            if (split_string(temp->content, buf)){
                printf("%d. %s\n" , serial , temp->content);
                serial++;
            }
        }

        temp = temp->next;
    }

    if (!count){
        printf("找不到任务");
        return 1;
    }

    (void)argc;
    (void)cat;
    return 0;
}

int cmd_sort (Schedule *list , CatState *cat ,  int argc , char *argv[]){
    sort_byprior(list);
   
    (void)argv;
    (void)argc;
    (void)cat;
    return 0;
}

int cmd_cat_wait(CatState *cat){
    int r = rand() % 100;
    if (r > 30) {
        cat_wait(cat);
    } else if (r < 2){
        cat_random(cat);
    }
    return 0;
}

int cmd_time_check(CatState *cat){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int hour = t->tm_hour;

    if ((hour >= 0 && hour <= 4) || hour >= 23){
        cat_is_night(cat);
    } else if (hour <= 11 && hour >= 7){
        cat_is_morning(cat);
    }

    return 0;
}