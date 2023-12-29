#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int reader_waiting;
int writer_waiting;
int reader_reading;
int writer_writing;

struct semaphore* Sem_Reader;
int i =0;
struct semaphore* Sem_Writer;

void reader(int readerID){
    if(writer_waiting > 0 || writer_writing > 0){
        reader_waiting = reader_waiting + 1;
        P(Sem_Reader);
        reader_waiting = reader_waiting - 1;
    }
    reader_reading = reader_reading + 1;

    printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
    yield();
    printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);

    reader_reading = reader_reading -1;

    if(writer_waiting > 0 && reader_reading == 0){
        V(Sem_Writer);
    }

    TCB_t* t = DelQueue(&RunQ);

    if(RunQ!=NULL){
        swapcontext(&(t->context),&(RunQ->context));

    }
}

void writer(int writerID){

    if(writer_waiting > 0 || writer_writing > 0 || reader_reading > 0 || reader_waiting > 0){
        writer_waiting = writer_waiting + 1;
        P(Sem_Writer);
        writer_waiting = writer_waiting - 1;
    }

    writer_writing = writer_writing + 1;
    i = i +1;

    printf("\n This is the %d th writer writing value i = %d \n", writerID, i );
    yield();
    printf("\n This is the %d th writer verifying value i = %d \n", writerID, i );

    writer_writing = writer_writing -1;
    if(reader_waiting > 0){
            for(int h= 0; h<reader_waiting;h++)
                V(Sem_Reader);
        }
    else if(writer_waiting > 0){
        V(Sem_Writer);
    }


    TCB_t* t = DelQueue(&RunQ);

    if(RunQ!=NULL){
        swapcontext(&(t->context),&(RunQ->context));
    }
}

int main(){
    int W;
    int R;

    scanf("%d, %d",&R,&W);
    Sem_Writer = (struct semaphore *)malloc(sizeof(struct semaphore));
    
    Sem_Reader = (struct semaphore *)malloc(sizeof(struct semaphore));

    initSem(Sem_Reader,0);
    initSem(Sem_Writer,0);
    InitQueue(&RunQ);

    for(int r=0;r<W+R; r++){
        int no;
        scanf("%d",&no);

        if(no < 0){
            no = no * -1;
            start_thread(&writer, no, 0);
            
        }
        else{
            start_thread(&reader, no, 0);
        }
    }
    run();
    return 0;
}