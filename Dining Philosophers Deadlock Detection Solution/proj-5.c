#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

struct semaphore** array;

void philosopher(int id, int no);

int main(){
    int num1,num2;

    scanf("%d, %d", &num1, &num2);

    array = (struct semaphore**) malloc(num1*sizeof(struct semaphore));

    for(int i=0; i<num1; i++){
        array[i] = (struct semaphore*) malloc(sizeof(struct semaphore));
        initSem(array[i],1);

    }

    InitQueue(&RunQ);

    for(int j=0;j<num2;j++){
        int num3;
        scanf("%d", &num3);
        start_thread(&philosopher, num3, num1);
    }

    run();
    return 0;
}

void philosopher(int id, int no){
    P(array[(id - 1) % no]);
    yield();
    P(array[(id) % no]);
    yield();

    printf("\n Philosopher %d is eating \n", id);

    V(array[(id - 1) % no]);
    V(array[(id) % no]);

    TCB_t* t = DelQueue(&RunQ);

    if(RunQ != NULL){
        swapcontext(&(t->context), &(RunQ->context));
    }
}