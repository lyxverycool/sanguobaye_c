//
//  sem.c
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#import <Foundation/Foundation.h>

#include "sem.h"

GAM_SEM gam_sem_create()
{
    return (__bridge_retained void*)dispatch_semaphore_create(0);
}

void gam_sem_delete(GAM_SEM sem)
{
    (void)(__bridge_transfer dispatch_semaphore_t)sem;
}

void gam_sem_signal(GAM_SEM sem)
{
    dispatch_semaphore_signal((__bridge dispatch_semaphore_t)sem);
}

void gam_sem_wait(GAM_SEM sem)
{
    dispatch_semaphore_wait((__bridge dispatch_semaphore_t)sem, DISPATCH_TIME_FOREVER);
}

GAM_LOCK gam_lock_create() {
    GAM_LOCK lck = gam_sem_create();
    gam_lock_unlock(lck);
    return lck;
}
void gam_lock_delete(GAM_LOCK lck) { gam_sem_delete(lck); }
void gam_lock_lock(GAM_LOCK lck) { gam_sem_wait(lck); }
void gam_lock_unlock(GAM_LOCK lck) { gam_sem_signal(lck); }
