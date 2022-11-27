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

//modNum: Select which UART module to enable from 0 - 7
//portBase: Base address of the UART port ex.. UART0 = UART0_DR_R  = 0x4000C000
//baudrate: baudRate of UART ex.. 4800, 9600, 57600, 115200
void UartInit(uint8_t modNum, uint32_t portBase, uint32_t baudrate){

    assert(modNum < 8);

    if(modNum < 8){
    //Enable clock to UART
    REG_VAL(SYSCTL_RCGCUART_R) |= (1 << modNum);
    }

    delayUs(10);

    //Disable UART Port so we can edit port values
    REG_VAL((portBase + UART_CTL_R)) = 0;

    //Set Baudrate Integer Divisor
    REG_VAL((portBase + UART_IBRD_R)) = _getIndDivisor(baudrate);

    //Set Baudrate Integer Divisor
    REG_VAL((portBase + UART_FBRD_R)) = _getFracDivisor(baudrate);
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
