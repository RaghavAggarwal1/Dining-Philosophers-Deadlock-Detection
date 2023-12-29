#include "q.h"

#define SIZE 8192

struct TCB_t* RunQ;


void start_thread(void (*function),int a, int b){
    void *stack = (void *) malloc(SIZE);
    TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));
    init_TCB(tcb, a, b, function, SIZE, stack);
    

    AddQueue(&RunQ,tcb);
}

void run(){
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(RunQ->context));
}

void yield(){
    RotateQ(&RunQ);
    swapcontext(&(RunQ->prev->context), &(RunQ->context));
}

