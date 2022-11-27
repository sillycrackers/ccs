// Copyright (c) 2022 Erik Westerveld Incorporated.  All rights reserved.
// Software License Agreement

#ifndef __UART_H__
#define __UART_H__


extern uint32_t _getFracDivisor(volatile uint32_t baud);
extern uint32_t _getIntDivisor(volatile uint32_t baud);
extern uint32_t _getUARTPortbase(uint8_t modNum);
extern void UartInit(volatile uint8_t modNum, volatile uint32_t baudrate);
extern void  UARTSendChar(volatile uint8_t modNum, volatile uint8_t character);
extern void UARTSendString(volatile uint8_t modNum, volatile uint8_t* string);
extern char UARTReadChar(volatile uint8_t modNum);
extern void UARTEcho(volatile uint8_t modNum, char input);



#endif
