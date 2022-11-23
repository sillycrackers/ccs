#include <stdint.h>


#ifndef __HELPERS_H__
#define __HELPERS_H__


#define REG_VAL(x) (*((volatile unsigned int*)x))

//Linked List
typedef struct node{
    struct node* next;
    int data;
} node;

void delayMs(unsigned int n);
node* insertNodeAtTail(node* head, int data);





#endif
