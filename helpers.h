#include <stdint.h>

// Copyright (c) 2022 Erik Westerveld Incorporated.  All rights reserved.
// Software License Agreement
#ifndef __HELPERS_H__
#define __HELPERS_H__


#define BIT_0  0x00000001  // BIT 0
#define BIT_1  0x00000002  // BIT 1
#define BIT_2  0x00000004  // BIT 2
#define BIT_3  0x00000008  // BIT 3
#define BIT_4  0x00000010  // BIT 4
#define BIT_5  0x00000020  // BIT 5
#define BIT_6  0x00000040  // BIT 6
#define BIT_7  0x00000080  // BIT 7

#define REG_VAL(x) (*((volatile uint32_t*)x))

//Linked List
typedef struct node{
    struct node* next;
    int data;
} node;

extern void delayMs(volatile uint32_t ui32Ms);
extern void delayUs(volatile uint32_t ui32Us);
extern node* insertNodeAtTail(node* head, int data);
extern uint32_t GetNumberOfDigits(volatile uint32_t i);

#endif
