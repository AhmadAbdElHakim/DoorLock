#ifndef UART_H_
#define UART_H_
#include "tm4c123gh6pm.h"
#include "stdint.h"
void UART_init(void);
uint8_t UART0_read (void);
#endif
