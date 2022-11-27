// Copyright (c) 2022 Erik Westerveld Incorporated.  All rights reserved.
// Software License Agreement

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <driverlib\sysctl.h>
#include <math.h>
#include <assert.h>

#include "gpio.h"
#include "helpers.h"
#include "tm4c123gh6pm.h"
#include "timer.h"


void TimerInit(volatile uint8_t timer){

    //Enable system clock to UART
    REG_VAL(SYSCTL_RCGCUART_R) |= (1 << timer);

}
