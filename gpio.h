#include <stdint.h>
#include <stdbool.h>


#ifndef __GPIONEW_H__
#define __GPIONEW_H__



extern void DigitalOutputInit(volatile uint32_t portBase, volatile uint8_t pins);
extern void DigitalInputInit(volatile uint32_t portBase, volatile uint8_t pins, volatile uint8_t padType);
extern void GPIOWrite(volatile uint32_t PortBase, volatile uint8_t mask, volatile uint8_t pins);
extern bool GPIORead(volatile uint32_t PortBase, volatile uint8_t pins);
extern uint32_t ReadGPIOData(volatile uint32_t PortBase, volatile uint8_t pins);
extern void GPIOToggle(volatile uint32_t PortBase, volatile uint8_t mask, volatile uint8_t pins);
extern void SendStringLCD(volatile uint8_t* string);

#endif
