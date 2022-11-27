#include <stdint.h>
#include <stdbool.h>
#include <driverlib\sysctl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lcd.h"
#include "gpio.h"
#include "tm4c123gh6pm.h"
#include "helpers.h"
#include "keypad.h"
#include "uart.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


int main(void)
{
    //50 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //LCDInit();
    //KeypadInit();
    UartInit(0, 115200);

    volatile uint32_t delay = 1500;
    char str[15];

    while(1){
        for(uint32_t i = 0; i < 40000000; i++){
            sprintf(str,"%u", i);
            UARTSendString(0, (uint8_t*)str);
            UARTSendChar(0, '\n');
            UARTSendChar(0, '\r');
        }
    }

}

void SystemInit(void){
    //Grant coprocessor access
    //This is required since TM4C123G has a floating point coprocessor
    REG_VAL(NVIC_CPAC_R) |= 0x00F00000;
}

