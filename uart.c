#include "uart.h"

void UART_init(void)
{
    SYSCTL_RCGCUART_R |= 0x0001;
    SYSCTL_RCGCGPIO_R |= 0x0001;
    UART0_CTL_R &= ~ 0x0001;
    UART0_IBRD_R = 104; //9600
    UART0_FBRD_R = 11;
    UART0_LCRH_R = 0x0070;
    UART0_CTL_R = 0x0301;
    UART0_CC_R = 0x05;  //16MHz

    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00010001;
    GPIO_PORTA_DEN_R |= 0x03;
    GPIO_PORTA_AMSEL_R &= ~0x03;
}

uint8_t UART0_read (void)
{
    while((UART0_FR_R & 0x0010) != 0) {}
    return (uint8_t)(UART0_DR_R & 0xFF);
}
