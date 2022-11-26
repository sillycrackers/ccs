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
    KeypadInit();

    volatile uint32_t delay = 1500;
    volatile uint8_t inData;
    volatile uint8_t count = 0;
    volatile uint8_t buffer[16];
    volatile uint8_t* password = "1234";
    volatile uint8_t passCount = 4;
    volatile bool passFail = false;

    SendStringLCD("Enter password:");
    SendCommandLCD(CURSOR_HOME_SECOND);


    while(1)
    {
        inData = ScanKeypad();

        //If we pressed a key
        if(inData != 0){
            //If we pressed key other then 'Enter'
            if(inData != '#'){
                //If we haven't filled the line
                if(count < 16){
                    SendCharLCD(inData);
                    buffer[count] = inData;
                    count++;
                }

             //If 'Enter' was pressed
            }else{

                //If same length of password
                if(count == passCount){
                    passFail = true;
                    for(int x = 0; x < count; x++){
                        if(buffer[x] != password[x]){
                            passFail = false;
                        }
                    }
                   if(passFail == true){
                       break;
                   }
                }

                //Not same length or did not match password start over

                    SendCommandLCD(CLEAR_DISPLAY);
                    SendStringLCD("Incorrect!");
                    delayMs(2000);
                    SendCommandLCD(CLEAR_DISPLAY);
                    SendStringLCD("Enter password:");
                    SendCommandLCD(CURSOR_HOME_SECOND);
                    count = 0;
                }
            }
        }

        SendCommandLCD(CLEAR_DISPLAY);
        SendStringLCD("Correct!  ");

        SendCharLCD(3);
        SendCharLCD(3);
        SendCharLCD(3);





        while(1){

        }
        /*
        SendCommandLCD(CLEAR_DISPLAY);
        SendCharLCD(count + '0');
        GPIOWrite(ROW_PORT, ROW1 | ROW2 | ROW3 | ROW4, rowArray[count]);
        delayMs(5000);
        count++;
        if(count >= 4){
            count = 0;
        }
         */

}

void SystemInit(void){
    //Grant coprocessor access
    //This is required since TM4C123G has a floating point coprocessor
    REG_VAL(NVIC_CPAC_R) |= 0x00F00000;
}

