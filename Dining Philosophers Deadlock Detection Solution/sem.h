#ifndef SEM_H
#define SEM_H

#include "threads.h"

struct semaphore
{
    int value;
    struct TCB_t *q;
};

void P(struct semaphore *s){
    while (1)
    {
        if(s->value <= 0)
        {
            TCB_t *a = DelQueue(&RunQ);
            AddQueue(&(s->q),a);
            if (RunQ == NULL) exit(0);
            swapcontext(&(a->context),&(RunQ->context));
        }
        else{
            s->value = s->value -1;
            return;
        }
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