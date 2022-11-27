// Copyright (c) 2022 Erik Westerveld Incorporated.  All rights reserved.
// Software License Agreement

#include <stdint.h>
#include <helpers.h>
#include <stdlib.h>
#include <driverlib\sysctl.h>

uint32_t GetNumberOfDigits(volatile uint32_t i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

void delayMs(volatile uint32_t ui32Ms) {

    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000

    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}

void delayUs(volatile uint32_t ui32Us){
    SysCtlDelay(ui32Us * (SysCtlClockGet() / 3 / 1000000));
}

node* insertNodeAtTail(node* head, int data) {

    node* temp = head;

    node* tail = malloc(sizeof(node*));
    tail->data = data;
    tail->next = NULL;

    if(head == NULL){
        head = tail;
        return head;
    }else{
        while(head->next != NULL){
        head = head->next;
        }
    }

    head->next=tail;

    return temp;
}
