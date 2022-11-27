// Copyright (c) 2022 Erik Westerveld Incorporated.  All rights reserved.
// Software License Agreement

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <driverlib\sysctl.h>

#include "gpio.h"
#include "helpers.h"
#include "tm4c123gh6pm.h"

//Digital Input Init
//Pad Type:
//0 - Pullup Resistor
//1 - Pulldown Resistor
void DigitalInputInit(volatile uint32_t portBase, volatile uint8_t pins, volatile uint8_t padType){

    volatile uint8_t periphClock;


    //Figure out which peripheral clock to enable
    switch(portBase){
        case GPIO_PORTA_BASE:
            periphClock = 0x01;
            break;
        case GPIO_PORTB_BASE:
            periphClock = 0x02;
            break;
        case GPIO_PORTC_BASE:
            periphClock = 0x04;
            break;
        case GPIO_PORTD_BASE:
            periphClock = 0x08;
            break;
        case GPIO_PORTE_BASE:
            periphClock = 0x10;
            break;
        case GPIO_PORTF_BASE:
            periphClock = 0x20;
    }

    //Enable clock to GPIO
    if(REG_VAL(SYSCTL_RCGCGPIO_R) != periphClock){

        REG_VAL(SYSCTL_RCGCGPIO_R) |= periphClock;

        delayUs(10);
    }
    //Set Pin direction to 0 Input
    REG_VAL((portBase + GPIO_DIR_R)) &= ~pins;



    // Pullup Resistor - GPIO_PUR_R
    // Pull down resistor - GPIO_PDR_R
    // Open drain - GPIO_ODR_R
    //0 - Pullup Resistor
    //1 - Pulldown Resistor
    //3 - Open-Drain

    if(padType == 0){
        //Turn on Pullup resistor
        REG_VAL((portBase + GPIO_PUR_R)) |= pins;
    }else{
        //Turn on Pull Down resistor
        REG_VAL((portBase + GPIO_PDR_R)) |= pins;
    }

    //Enable digital pins
    REG_VAL((portBase + GPIO_DEN_R)) |= pins;
}


//openDrain 1 to enable 0 to disable
void DigitalOutputInit(volatile uint32_t portBase, volatile uint8_t pins, volatile uint8_t openDrain){

    volatile uint8_t periphClock;


    //Figure out which peripheral clock to enable
    switch(portBase){
        case GPIO_PORTA_BASE:
            periphClock = 0x01;
            break;
        case GPIO_PORTB_BASE:
            periphClock = 0x02;
            break;
        case GPIO_PORTC_BASE:
            periphClock = 0x04;
            break;
        case GPIO_PORTD_BASE:
            periphClock = 0x08;
            break;
        case GPIO_PORTE_BASE:
            periphClock = 0x10;
            break;
        case GPIO_PORTF_BASE:
            periphClock = 0x20;
    }

    //Enable clock to GPIO
    if(REG_VAL(SYSCTL_RCGCGPIO_R) != periphClock){

        REG_VAL(SYSCTL_RCGCGPIO_R) |= periphClock;

        delayUs(10);
    }

    //Set Pin direction 1 for Output
    REG_VAL((portBase + GPIO_DIR_R)) |= pins;


    if(openDrain == 1){
        //Enable Open drain
        REG_VAL((portBase + GPIO_ODR_R)) |= pins;
    }

    //Enable digital pins
    REG_VAL((portBase + GPIO_DEN_R)) |= pins;


}

void GPIOWrite(volatile uint32_t PortBase, volatile uint8_t mask, volatile uint8_t pins){

    PortBase = PortBase + (mask << 2);

    REG_VAL(PortBase) = pins;
}

bool GPIORead(volatile uint32_t PortBase, volatile uint8_t pins){

    volatile uint32_t lastState = REG_VAL((PortBase + (pins << 2)));

    if(lastState == 0){
        delayMs(20);
        if(REG_VAL((PortBase + (pins << 2))) == lastState){
            return true;
        }
    }
    return false;
}

uint32_t GPIOReadData(volatile uint32_t PortBase, volatile uint8_t pins){
    return REG_VAL((PortBase + (pins << 2)));
}

void GPIOToggle(volatile uint32_t PortBase, volatile uint8_t mask, volatile uint8_t pins){

    PortBase = PortBase + (mask << 2);

    REG_VAL(PortBase) ^= pins;
}

