// Copyright (c) 2022 Erik Westerveld Incorporated.  All rights reserved.
// Software License Agreement

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <driverlib\sysctl.h>
#include <math.h>
#include <assert.h>

#include "gpio.h"
#include "helpers.h"
#include "tm4c123gh6pm.h"
#include "uart.h"



//modNum: Select which UART module to enable from 0 - 7
//baudrate: baudRate of UART ex.. 4800, 9600, 57600, 115200
void UartInit(volatile uint8_t modNum, volatile uint32_t baudrate){

    assert(modNum < 8);

    //Base address of the UART port ex.. UART0 = UART0_DR_R  = 0x4000C000
    volatile uint32_t portBase;

    //Set UART port base based ON modNum and Enable corresponding GPIO system clock
    switch(modNum){
    case 0:
        //Port A
        portBase = UART0_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_0;
        delayUs(10);
        break;
    case 1:
        //Port B
        portBase = UART1_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_1;
        delayUs(10);
        break;
    case 2:
        //Port D
        portBase = UART2_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_3;
        delayUs(10);
        break;
    case 3:
        //Port C
        portBase = UART3_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_2;
        delayUs(10);
        break;
    case 4:
        //Port C
        portBase = UART4_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_2;
        delayUs(10);
        break;
    case 5:
        //Port E
        portBase = UART5_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_4;
        delayUs(10);
        break;
    case 6:
        //Port D
        portBase = UART6_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_3;
        delayUs(10);
        break;
    case 7:
        //Port E
        portBase = UART7_DR_R;
        REG_VAL(SYSCTL_RCGCGPIO_R) |= BIT_4;
        delayUs(10);
    }

    //Enable system clock to UART
    REG_VAL(SYSCTL_RCGCUART_R) |= (1 << modNum);


    delayUs(10);

    //Disable UART Control Register so we can edit register values
    REG_VAL((portBase + UART_CTL_R)) = 0;

    //Set Baudrate Integer Divisor
    REG_VAL((portBase + UART_IBRD_R)) = _getIntDivisor(baudrate);

    //Set Baudrate Fractional Divisor
    REG_VAL((portBase + UART_FBRD_R)) = _getFracDivisor(baudrate);

    //Select System Clock as UART clock source
    REG_VAL((portBase + UART_CC_R)) = 0;

    //Setup UART Line Control Registor, data length, parity, # of stop bits, and fifo
    REG_VAL((portBase + UART_LCRH_R)) = UART_LCRH_WLEN_8;

    //Enable UART, TXE, RXE
    REG_VAL((portBase + UART_CTL_R)) = UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;

    //Enable digital pin, Setup GPIO Alternate function, Configure GPIO pins for UART
    switch(modNum){
    case 0:
        //Port A pins 0 and 1
        REG_VAL((GPIO_PORTA_BASE + GPIO_DEN_R)) |= GPIO_PIN_0 | GPIO_PIN_1;
        REG_VAL((GPIO_PORTA_BASE + GPIO_AFSEL_R)) = GPIO_PIN_0 | GPIO_PIN_1;
        REG_VAL((GPIO_PORTA_BASE + GPIO_PCTL_R)) = 0x11;
        break;
    case 1:
        //Port B pins 0 and 1
        REG_VAL((GPIO_PORTB_BASE + GPIO_DEN_R)) |= GPIO_PIN_0 | GPIO_PIN_1;
        REG_VAL((GPIO_PORTB_BASE + GPIO_AFSEL_R)) |= GPIO_PIN_0 | GPIO_PIN_1;
        REG_VAL((GPIO_PORTB_BASE + GPIO_PCTL_R)) = 0x11;
        break;
    case 2:
        //Port D pins 6 and 7
        REG_VAL((GPIO_PORTD_BASE + GPIO_DEN_R)) |= GPIO_PIN_6 | GPIO_PIN_7;
        REG_VAL((GPIO_PORTD_BASE + GPIO_AFSEL_R)) |= GPIO_PIN_6 | GPIO_PIN_7;
        REG_VAL((GPIO_PORTD_BASE + GPIO_PCTL_R)) = 0x11000000;
        break;
    case 3:
        //Port C pins 6 and 7
        REG_VAL((GPIO_PORTC_BASE + GPIO_DEN_R)) |= GPIO_PIN_6 | GPIO_PIN_7;
        REG_VAL((GPIO_PORTC_BASE + GPIO_AFSEL_R)) |= GPIO_PIN_6 | GPIO_PIN_7;
        REG_VAL((GPIO_PORTC_BASE + GPIO_PCTL_R)) = 11000000;
        break;
    case 4:
        //Port C pins 4 and 5
        REG_VAL((GPIO_PORTC_BASE + GPIO_DEN_R)) |= GPIO_PIN_4 | GPIO_PIN_5;
        REG_VAL((GPIO_PORTC_BASE + GPIO_AFSEL_R)) |= GPIO_PIN_4 | GPIO_PIN_5;
        REG_VAL((GPIO_PORTC_BASE + GPIO_PCTL_R)) = 110000;
        break;
    case 5:
        //Port E pins 4 and 5
        REG_VAL((GPIO_PORTE_BASE + GPIO_DEN_R)) |= GPIO_PIN_4 | GPIO_PIN_5;
        REG_VAL((GPIO_PORTE_BASE + GPIO_AFSEL_R)) |= GPIO_PIN_4 | GPIO_PIN_5;
        REG_VAL((GPIO_PORTE_BASE + GPIO_PCTL_R)) = 110000;
        break;
    case 6:
        //Port D pins 4 and 5
        REG_VAL((GPIO_PORTD_BASE + GPIO_DEN_R)) |= GPIO_PIN_4 | GPIO_PIN_5;
        REG_VAL((GPIO_PORTD_BASE + GPIO_AFSEL_R)) |= GPIO_PIN_4 | GPIO_PIN_5;
        REG_VAL((GPIO_PORTD_BASE + GPIO_PCTL_R)) =110000 ;
        break;
    case 7:
        //Port E pins 0 and 1
        REG_VAL((GPIO_PORTE_BASE + GPIO_DEN_R)) |= GPIO_PIN_0 | GPIO_PIN_1;
        REG_VAL((GPIO_PORTE_BASE + GPIO_AFSEL_R)) |= GPIO_PIN_0 | GPIO_PIN_1;
        REG_VAL((GPIO_PORTE_BASE + GPIO_PCTL_R)) = 0x11;
    }

    delayMs(1);
}

void UARTSendChar(volatile uint8_t modNum, volatile uint8_t character){

    volatile uint32_t portBase = _getUARTPortbase(modNum);

    //Wait until Tx buffer not full
    while(REG_VAL((portBase + UART_FR_R)) & 0x20){}

    REG_VAL(portBase) = character;
}

char UARTReadChar(volatile uint8_t modNum){

    volatile uint32_t portBase = _getUARTPortbase(modNum);

    //Wait until Rx buffer not full
    while(REG_VAL((portBase + UART_FR_R)) & 0x10){}

    return(REG_VAL(portBase));
}

void UARTEcho(volatile uint8_t modNum, char input){
    UARTSendChar(0, input);
}

void UARTSendString(volatile uint8_t modNum, volatile uint8_t* string){

    volatile uint8_t i = 0;

    while(string[i] != NULL){
        UARTSendChar(modNum, string[i]);
        i++;
    }
}

uint32_t _getUARTPortbase(uint8_t modNum){

    assert(modNum < 8);

    //Base address of the UART port ex.. UART0 = UART0_DR_R  = 0x4000C000
    volatile uint32_t portBase;

    //Set UART port base based ON modNum and Enable corresponding GPIO system clock
    switch(modNum){
    case 0:
        //Port A
        portBase = UART0_DR_R;
        break;
    case 1:
        //Port B
        portBase = UART1_DR_R;
        break;
    case 2:
        //Port D
        portBase = UART2_DR_R;
        break;
    case 3:
        //Port C
        portBase = UART3_DR_R;
        break;
    case 4:
        //Port C
        portBase = UART4_DR_R;
        break;
    case 5:
        //Port E
        portBase = UART5_DR_R;
        break;
    case 6:
        //Port D
        portBase = UART6_DR_R;
        break;
    case 7:
        //Port E
        portBase = UART7_DR_R;
    }

    return portBase;
}

//Calculate Integer Baud-Rate Divisor for register UARTIBRD
uint32_t _getIntDivisor(volatile uint32_t baud){

    return (SysCtlClockGet()/16)/baud;
}

//Calculate Fractional Baud-Rate Divisor for register UARTFBRD
uint32_t _getFracDivisor(volatile uint32_t baud){

    double intPart, fracPart;

    double i = (SysCtlClockGet()/16)/9600.0;

    fracPart = modf(i, &intPart);

    return (fracPart * 64) + 0.5;
}
