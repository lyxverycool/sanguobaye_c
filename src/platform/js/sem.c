//
//  sem.c
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//


#include "sem.h"
#include <stdlib.h>
#include <emscripten.h>
#include <baye/compa.h>

GAM_SEM gam_sem_create()
{
    int* p = (int*)gam_malloc(sizeof(int));
    *p = 0;
    return (GAM_SEM)p;
}

void gam_sem_delete(GAM_SEM sem)
{
    gam_free((void*)sem);
}

void gam_sem_signal(GAM_SEM sem)
{
    *((int*)sem) += 1;
}

void gam_sem_wait(GAM_SEM sem)
{
    int *p = (int*)sem;
    emscripten_sleep_with_yield(1);
    while (*p == 0) {
        emscripten_sleep_with_yield(10);
    }
    *p -= 1;
}


GAM_LOCK gam_lock_create() {
    return NULL;
}
void gam_lock_delete(GAM_LOCK lck) {}
void gam_lock_lock(GAM_LOCK lck) {}
void gam_lock_unlock(GAM_LOCK lck) {}
