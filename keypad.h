#ifndef __KEYPAD_H__
#define __KEYPAD_H__




//Inputs
#define COL_PORT    GPIO_PORTC_BASE
#define COL1        GPIO_PIN_4
#define COL2        GPIO_PIN_5
#define COL3        GPIO_PIN_6

//Outputs
#define ROW_PORT    GPIO_PORTE_BASE
#define ROW1        GPIO_PIN_0
#define ROW2        GPIO_PIN_1
#define ROW3        GPIO_PIN_2
#define ROW4        GPIO_PIN_3

extern void KeypadInit();
extern uint8_t ScanKeypad();
bool KeyPressed(uint32_t column);

extern volatile uint32_t rowArray[4];

#endif
