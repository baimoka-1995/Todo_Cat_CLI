#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "storage.h"
#include "cmd.h"
#include "cat.h"

int main(int argc, char *argv[]){
    // 初始化
    Schedule *list = init_schedule();
    srand((unsigned int)time(NULL));
    CatState *cat = cat_init();
    load_file(list);
    cat_load(cat);
    storage_cleanup_expired(list);

    if (dispatch(list , cat , argc , argv) == 0){
        all_save_file(list);
        cat_save(cat);
    }
}