#include "KeyPad.h"

uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t button_number)
{
	switch(button_number)
	{
		case 10: return '*'; // ASCII Code of *
		case 11: return 0;
		case 12: return '#'; // ASCII Code of #
		default: return button_number;
	}
}

uint8_t KeyPad_getPressedKey(void)
{
	uint8_t col,row;
	while(1)
	{
		for(col = 0; col < 3; col++) /* loop for columns */
		{
            GPIO_PORTB_DATA_R |= 0xF0;           // first make all cols (PC7-PC4) as output high
            GPIO_PORTB_DATA_R &= (~(0x10<<col)); // second make one of the columns output low at each iteration in order PC4 to PC7

			for(row = 0; row < 4; row++) /* loop for rows */
			{
				if(!(GPIO_PORTB_DATA_R & (0x01<<row))) /* if the switch is press in this row */
				{
					return KeyPad_4x3_adjustKeyNumber((row*3) + col + 1);
				}
			}
		}
	}
}

// use PORT B for KeyPad
void KeyPad_init(void)
{
    volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000002;     // 1) activate clock for Port B
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
    GPIO_PORTB_AMSEL_R &= 0x00;        // 3) disable analog on PB
    GPIO_PORTB_PCTL_R &= 0x00000000;   // 4) PCTL GPIO on PB7-0
    GPIO_PORTB_DIR_R |= 0xF0 ;          // make cols as output (PB7-PB4)     5) direction of pins
    GPIO_PORTB_DIR_R &= 0xF0 ;          // make rows as input (PB3-PB0)
    GPIO_PORTB_AFSEL_R &= 0x00;        // 6) disable alt funct on PB7-0
    GPIO_PORTB_PUR_R |= 0x0F ;       // enable pull-up for (PB3-PB0)
    GPIO_PORTB_DEN_R = 0xFF;          //7) enable digital I/O on PB7-0
}
