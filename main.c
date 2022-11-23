#include <stdint.h>
#include <stdbool.h>
#include <driverlib\sysctl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "gpio.h"
#include "tm4c123gh6pm.h"
#include "helpers.h"

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

    int delay = 1500;

    while(1)
    {
        delayMs(delay);
        SendStringLCD("Hello Erik!");
        delayMs(delay);
        SendStringLCD("What's up buttercup Ohhhhh Yeaaaaaaaa!");
        delayMs(delay);
        SendStringLCD("Everything okay?");
    }
}

void SystemInit(void){
    //Grant coprocessor access
    //This is requires since TM4C123G has a floating point coprocessor
    REG_VAL(NVIC_CPAC_R) |= 0x00F00000;
}

