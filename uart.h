#ifndef __UART_H__
#define __UART_H__


extern uint32_t _getFracDivisor(volatile uint32_t baud);
extern uint32_t _getIntDivisor(volatile uint32_t baud);
extern void UartInit(uint8_t modNum, uint32_t baudrate);



#endif
