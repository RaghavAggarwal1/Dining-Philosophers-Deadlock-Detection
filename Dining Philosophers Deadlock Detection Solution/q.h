#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

// struct TCB_t *first;
// struct TCB_t *last;
// int total;

// struct TCB_t *NewItem();
// void InitQueue(struct TCB_t **head);
// void AddQueue(struct TCB_t **head, struct TCB_t *item);
// struct TCB_t *DelQueue(struct TCB_t **head);
// void RotateQ(struct TCB_t **head);

struct TCB_t *NewItem(){
    TCB_t *node = (TCB_t *)malloc(sizeof(TCB_t));
    node->next = NULL;
    node->prev = NULL;
    return node;
}

struct TCB_t* DelQueue(struct TCB_t **head){

    if(head == NULL){
        return NULL;
    }

    struct TCB_t *node;
    node = *head;
    if(((*head) == (*head)->prev)&&((*head) == (*head)->next)){
        *head = NULL;
    }
    else{
        (*head)->next->prev = (*head)->prev;
        (*head)->prev->next = (*head)->next;
        *head = (*head)->next;
    }
    node->next = NULL;
    node->prev = NULL;

    return node;
}


void InitQueue(struct TCB_t **head){
    *head = NULL;
}

void RotateQ(struct TCB_t **head){
    *head = (*head)->next;
}

void AddQueue(struct TCB_t **head, struct TCB_t *item){
    if(*head != NULL){
        struct TCB_t *end = (*head)->prev;
        item->next = *head;
        item->prev = end;
        (*head)->prev = item;
        end->next = item;
    }
    
    else{
        *head = item;
        (*head)->prev = item;
        (*head)->next = item;
    }
}