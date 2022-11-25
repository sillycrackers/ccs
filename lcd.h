
#ifndef __LCD_H__
#define __LCD_H__

#define DATA_PORT   GPIO_PORTB_BASE
#define CMD_PORT    GPIO_PORTA_BASE
#define RS          GPIO_PIN_5
#define RW          GPIO_PIN_6
#define EN          GPIO_PIN_7


//LCD Commands
#define CLEAR_DISPLAY           0x00000001
#define SHIFT_CURSOR_RIGHT      0x00000014
#define DISPLAY_ON_CURSOR_BLINK 0x0000000F
#define CURSOR_HOME_FIRST       0x00000080
#define CURSOR_HOME_SECOND      0x000000C0
#define EIGHT_BIT               0x00000038
#define FOUR_BIT                0x00000028
#define CGRAM_START             0x00000040
#define CGRAM_0                 0x00000000
#define CGRAM_1                 0x00000008
#define CGRAM_2                 0x00000010
#define CGRAM_3                 0x00000018
#define CGRAM_4                 0x00000020
#define CGRAM_5                 0x00000028
#define CGRAM_6                 0x00000030
#define CGRAM_7                 0x00000038


extern void SendCommandLCD(volatile uint8_t command);
extern void SendCharLCD(volatile uint8_t character);
extern void LCDInit();
extern void SendStringLCD(volatile uint8_t* string);
extern void CheckBusy();
extern uint8_t ReadCommandLCD();
extern void SendCustomCharLCD(volatile uint8_t location, volatile uint8_t* data);



#endif
