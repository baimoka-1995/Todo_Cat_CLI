#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "search.h"

int substring_search(char *big , char *small){
    if (strstr(big , small) != NULL){
        return 1;
    }
    return 0;
}

int split_string(char *big , char *arg){
    char buf[100];
    strcpy(buf , (char *)arg);

    char *token;
    token = strtok(buf , " ");

    while (token != NULL){
        if (!substring_search(big, token)){
            return 0;
        }

        token = strtok(NULL, " ");
    }

    return 1;
}