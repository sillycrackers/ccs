#include <stdint.h>


#ifndef __HELPERS_H__
#define __HELPERS_H__


#define REG_VAL(x) (*((volatile unsigned int*)x))

//Linked List
typedef struct node{
    struct node* next;
    int data;
} node;

extern void delayMs(uint32_t ui32Ms);
extern void delayUs(uint32_t ui32Us);
extern node* insertNodeAtTail(node* head, int data);

#endif
