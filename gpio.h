#include <stdint.h>
#include <stdbool.h>


#ifndef __GPIONEW_H__
#define __GPIONEW_H__



void DigitalOutputInit(volatile uint32_t portBase, volatile uint8_t pins);
void DigitalInputInit(volatile uint32_t portBase, volatile uint8_t pins);
void GPIOWrite(volatile uint32_t PortBase, volatile uint8_t mask, volatile uint8_t pins);
bool GPIORead(volatile uint32_t PortBase, volatile uint8_t pins);
void GPIOToggle(volatile uint32_t PortBase, volatile uint8_t mask, volatile uint8_t pins);
void SendStringLCD(volatile uint8_t* string);

#endif
