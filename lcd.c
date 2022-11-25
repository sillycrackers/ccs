#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <driverlib\sysctl.h>

#include "helpers.h"
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "lcd.h"


/*
    Sending Commands to LCD

    Place data on DATA_PORT, make RS = 0, RW = 0, and then write 1 then 0 to EN.

    Sending Characters to LCD

    Place data on DATA_PORT, make RS = 1, RW = 0, and then write 1 then 0 to EN.

*/

void LCDInit(){

    DigitalOutputInit(DATA_PORT, 0x000000FF);
    DigitalOutputInit(CMD_PORT, RS | RW | EN);


    SendCommandLCD(0x30); //8 Bit
    SendCommandLCD(0x30);
    SendCommandLCD(0x30);
    SendCommandLCD(0x38); //Set 2-line, (5x7 font by default)
    SendCommandLCD(0x06); //Set Cursor move direction to right
    SendCommandLCD(CLEAR_DISPLAY); //Clear Screen, move cursor to home
    SendCommandLCD(0x0E); //Turn on display, cursor not blinking
    SendCommandLCD(CURSOR_HOME_FIRST);

}
void CheckBusy(){

    GPIOWrite(CMD_PORT, RW, RW);
    GPIOWrite(CMD_PORT, RS, 0);
    DigitalInputInit(DATA_PORT, GPIO_PIN_7);
    GPIOWrite(CMD_PORT, EN, 0);
    GPIOWrite(CMD_PORT, EN, EN);

    while(ReadGPIOData(DATA_PORT, GPIO_PIN_7) == GPIO_PIN_7){

    }
    GPIOWrite(CMD_PORT, EN, 0);
    DigitalOutputInit(DATA_PORT, 0xFF);

}

void SendCommandLCD(volatile uint8_t command){

    GPIOWrite(CMD_PORT, RS | RW, 0x00);
    GPIOWrite(DATA_PORT, 0xFF, command);
    GPIOWrite(CMD_PORT, EN, EN);
    GPIOWrite(CMD_PORT, EN, 0x0);
    CheckBusy();
}

uint8_t ReadCommandLCD(){

    volatile uint8_t data = 0;

    GPIOWrite(CMD_PORT, RW, RW);
    GPIOWrite(CMD_PORT, RS, 0);
    GPIOWrite(CMD_PORT, EN, 0);
    DigitalInputInit(DATA_PORT, 0x000000FF);
    delayUs(10);
    GPIOWrite(CMD_PORT, EN, EN);
    delayUs(10);

    data = ReadGPIOData(DATA_PORT, 0xFF);
    delayUs(10);
    GPIOWrite(CMD_PORT, EN, 0);


    DigitalOutputInit(DATA_PORT, 0x000000FF);

    return data;
}

void SendCharLCD(volatile uint8_t character){

    GPIOWrite(CMD_PORT, RS, RS);
    GPIOWrite(CMD_PORT, RW, 0x0);
    GPIOWrite(DATA_PORT, 0xFF, character);
    GPIOWrite(CMD_PORT, EN, EN);
    GPIOWrite(CMD_PORT, EN, 0x0);
    CheckBusy();
}

void SendStringLCD(volatile uint8_t* string){

    uint16_t i;

    SendCommandLCD(CLEAR_DISPLAY);

    for(i = 0; string[i] != NULL && i <= 15; i++){
        SendCharLCD(string[i]);
    }

    if(i >= 15){

        SendCommandLCD(CURSOR_HOME_SECOND);

        for(int x = i; string[x] != NULL && x <= 31; x++){
            SendCharLCD(string[x]);
        }
    }
}
