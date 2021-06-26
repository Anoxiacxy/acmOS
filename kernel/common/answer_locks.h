//
// Created by Wenxin Zheng on 2021/4/21.
//

#ifndef ACMOS_SPR21_ANSWER_LOCKS_H
#define ACMOS_SPR21_ANSWER_LOCKS_H

#include "defs.h"
#include "riscv.h"
#include "process.h"

int lock_init(struct lock *lock){
    /* Your code here */
    if(nlock >= MAXLOCKS) BUG("Max lock count reached.");
    locks[nlock++] = lock;
    lock->cpuid = cpuid();
    return 0;
}

void acquire(struct lock *lock){
    /* Your code here */
    while (try_acquire(lock) == -1);
}

// Try to acquire the lock once
// Return 0 if succeed, -1 if failed.
int try_acquire(struct lock *lock){
    /* Your code here */
    // it writes value to *ptr and returns the previous contents of *ptr
    if (__sync_lock_test_and_set(&lock->locked, 1) == 0)
        return 0;
    return -1;
}

void release(struct lock* lock){
    /* Your code here */
    // it writes 0 to *ptr
    __sync_lock_release(&lock->locked);
}

int is_locked(struct lock* lock){
    return lock->locked;
}

// private for spin lock
int holding_lock(struct lock* lock){
    /* Your code here */
    if (lock->locked && lock->cpuid == cpuid())
        return 1;
    else
        return 0;
    return -1;
}

void push_off(void) {
    int old = intr_get();

    intr_off();
    if (mycpu()->noff == 0)
        mycpu()->intena = old;
    mycpu()->noff += 1;
}

void pop_off(void) {
    struct cpu *c = mycpu();
    if(intr_get()) {
        // panic("pop_off - interruptible");
    }        
    if(c->noff < 1) {
        // panic("pop_off");
    }
    c->noff -= 1;
    if(c->noff == 0 && c->intena)
        intr_on();
}





#endif  // ACMOS_SPR21_ANSWER_LOCKS_H
