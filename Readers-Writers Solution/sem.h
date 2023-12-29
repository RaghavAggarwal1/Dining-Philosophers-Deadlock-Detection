#ifndef SEM_H
#define SEM_H

#include "threads.h"

struct semaphore
{
    int value;
    struct TCB_t *q;
};

void P(struct semaphore *s){
    s->value = s->value - 1;
    if(s->value < 0){
        TCB_t *a = DelQueue(&RunQ);
        AddQueue(&(s->q),a);
        while (RunQ == NULL);
        swapcontext(&(a->context),&(RunQ->context));
    }
}

void V(struct semaphore *s){
    if(s->q!=NULL){
        AddQueue(&RunQ, DelQueue(&(s->q)));
    }
    s->value = s->value + 1;
}

void initSem(struct semaphore *sem,int value){
    sem->value = value;
    InitQueue(&(sem->q));

}

#endif