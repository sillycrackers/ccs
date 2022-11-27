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

    LCDInit();
    //KeypadInit();
    UartInit(0, 115200);

    volatile uint32_t delay = 1500;
    char input;
    uint8_t count = 0;

    UARTSendChar(0,'>');

    while(1){
        input = UARTReadChar(0);
        UARTSendChar(0, input);
        if(count == 16){
            SendCommandLCD(CURSOR_HOME_SECOND);
        }
        count++;
        if(count > 32){
            SendCommandLCD(CLEAR_DISPLAY);
            SendCommandLCD(CURSOR_HOME_FIRST);
            count = 0;
        }
        SendCharLCD(input);

    }

}

void SystemInit(void){
    //Grant coprocessor access
    //This is required since TM4C123G has a floating point coprocessor
    REG_VAL(NVIC_CPAC_R) |= 0x00F00000;
}

