// Copyright (c) 2022 Erik Westerveld Incorporated.  All rights reserved.
// Software License Agreement

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <driverlib\sysctl.h>

#include "helpers.h"
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"

volatile uint32_t rowArray[4] = {
                        0x0E,
                        0x0D,
                        0X0B,
                        0X07
};
volatile uint32_t colArray[3] = {
                        COL1,
                        COL2,
                        COL3
};
volatile uint8_t keys[4][3] = {
                        {'1','2','3'},
                        {'4','5','6'},
                        {'7','8','9'},
                        {'*','0','#'}
};

void KeypadInit(){

    DigitalOutputInit(ROW_PORT, ROW1 | ROW2 | ROW3 | ROW4, 1);
    DigitalInputInit(COL_PORT, COL1 | COL2 | COL3, 0);

}

uint8_t ScanKeypad(){

    for(int i = 0; i < 4; i++){
        GPIOWrite(ROW_PORT, ROW1 | ROW2 | ROW3 | ROW4, rowArray[i]);
        delayUs(10);
        for(int x = 0; x < 3; x++){
            if(KeyPressed(colArray[x]) == true){
                return keys[i][x];
            }
        }
    }
    return 0;
}
bool KeyPressed(volatile uint32_t column){

    if(GPIORead(COL_PORT, column)){
        while(GPIORead(COL_PORT, column) != false){

        }
        return true;
    }

    return false;
}

void Password(){
    volatile uint8_t inData;
    volatile uint8_t count = 0;
    volatile uint8_t buffer[16];
    volatile uint8_t* password = "1234";
    volatile uint8_t passCount = 4;
    volatile bool passFail = false;


    while(1){
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
            SendStringLCD("Correct!");
            SendCommandLCD(CURSOR_HOME_SECOND);
            SendCharLCD(0);
            SendCharLCD(1);
            SendCharLCD(2);
            SendCharLCD(3);
            delayMs(2000);
            SendCommandLCD(CLEAR_DISPLAY);
            count = 0;

    }
}
