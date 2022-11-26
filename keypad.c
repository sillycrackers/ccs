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
        delayUs(50);
        for(int x = 0; x < 3; x++){
            if(KeyPressed(colArray[x]) == true){
                return keys[i][x];
            }
        }
    }
    return 0;
}
bool KeyPressed(uint32_t column){

    if(GPIORead(COL_PORT, column)){
        while(GPIORead(COL_PORT, column) != false){

        }
        return true;
    }

    return false;
}
