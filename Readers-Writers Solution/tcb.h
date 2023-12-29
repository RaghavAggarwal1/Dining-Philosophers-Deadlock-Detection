#ifndef TCB_HEADER
#define TCB_HEADER

#include<ucontext.h>
#include<string.h>

typedef struct TCB_t
{
    struct TCB_t *next;
    struct TCB_t *prev;
    ucontext_t context;
}TCB_t;
//init_TCB(tcb, a, b, function, SIZE, stack);
void init_TCB(TCB_t *tcb, int no1, int no2, void *meathod1, int size, void *stackA){
    memset(tcb, '\0', sizeof(TCB_t));
    getcontext(&tcb->context);
    tcb->context.uc_stack.ss_sp = stackA;
    tcb->context.uc_stack.ss_size = (size_t) size;
    makecontext(&tcb->context, meathod1, 2, no1,no2);
}
#endif