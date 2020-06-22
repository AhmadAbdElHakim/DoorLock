#include "IO_ports.h"


void PortF_Init(unsigned long direction,unsigned long pull_up)
{
	volatile unsigned long delay;
  direction &= 0x1F;
  pull_up &= 0x1F;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  // do we have to be sure of the last bits
  GPIO_PORTF_DIR_R = direction;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  // same problem (rest)
  GPIO_PORTF_PUR_R = pull_up;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}

void PortA_Init(unsigned long direction , unsigned long pull_up)
{
	volatile unsigned long delay;
  direction &= 0xFF;
  pull_up &= 0xFF;
  SYSCTL_RCGC2_R |= 0x00000001;     // 1) activate clock for Port A
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTA_CR_R = 0xFF;           // allow changes to PA7-0
  GPIO_PORTA_AMSEL_R = 0x00;        // 3) disable analog on PA
  GPIO_PORTA_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PA7-0
  // rest
  GPIO_PORTA_DIR_R = direction;     // 5) direction of pins
  GPIO_PORTA_AFSEL_R = 0x00;        // 6) disable alt funct on PA0-0
  // rest
  GPIO_PORTA_PUR_R = pull_up;       // enable pull-up
  GPIO_PORTA_DEN_R = 0xFF;          //7) enable digital I/O on PA7-0
}

void PortB_Init(unsigned long direction , unsigned long pull_up)
{
	volatile unsigned long delay;
  direction &= 0xFF;
  pull_up &= 0xFF;
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) activate clock for Port B
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTB_CR_R = 0xFF;           // allow changes to PB7-0
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog on PB
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PB7-0
  // rest
  GPIO_PORTB_DIR_R = direction;     // 5) direction of pins
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) disable alt funct on PB0-0
  // rest
  GPIO_PORTB_PUR_R = pull_up;       // enable pull-up
  GPIO_PORTB_DEN_R = 0xFF;          //7) enable digital I/O on PB7-0
}


void PortD_Init(unsigned long direction , unsigned long pull_up)
{
	volatile unsigned long delay;
  direction &= 0xFF;
  pull_up &= 0xFF;
  SYSCTL_RCGC2_R |= 0x00000008;     // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   // PD7 unlock
  // be carfull with PD7 here
  GPIO_PORTD_CR_R = 0xFF;           // allow changes to PD7-0
  GPIO_PORTD_AMSEL_R = 0x00;        // 3) disable analog on PD
  GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PD7-0
  // rest
  GPIO_PORTD_DIR_R = direction;     // 5) direction of pins
  GPIO_PORTD_AFSEL_R = 0x00;        // 6) disable alt funct on PD0-0
  // rest
  GPIO_PORTD_PUR_R = pull_up;       // enable pull-up
  GPIO_PORTD_DEN_R = 0xFF;          //7) enable digital I/O on PD7-0
}

void PortE_Init(unsigned long direction , unsigned long pull_up)
{
	volatile unsigned long delay;
  direction &= 0x3F;
  pull_up &= 0x3F;
  SYSCTL_RCGC2_R |= 0x00000010;     // 1) activate clock for Port E
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTE_CR_R = 0x3F;           // allow changes to PE5-0
  GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog on P5
  GPIO_PORTE_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PE5-0
  // rest
  GPIO_PORTE_DIR_R = direction;     // 5) direction of pins
  GPIO_PORTE_AFSEL_R = 0x00;        // 6) disable alt funct on PE5-0
  // rest
  GPIO_PORTE_PUR_R = pull_up;       // enable pull-up
  GPIO_PORTE_DEN_R = 0x3F;          //7) enable digital I/O on PE5-0
}

// not sure about it at all ***************************************************

// ********************************************************8
void PortC_Init(unsigned long direction , unsigned long pull_up)
{
	volatile unsigned long delay;
  direction &= 0xF0;
  pull_up &= 0xF0;
  SYSCTL_RCGC2_R |= 0x00000004;     // 1) activate clock for Port C
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  //GPIO_PORTD_LOCK_R = 0x4C4F434B;   // unlock PC3-PC0 but don't do it
  GPIO_PORTC_CR_R = 0xF0;           // allow changes to PC7-PC4
  GPIO_PORTC_AMSEL_R = 0x00;        // 3) disable analog on PE
  GPIO_PORTC_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PC7-PC4
  // rest
  GPIO_PORTC_DIR_R = direction;     // 5) direction of pins
  GPIO_PORTC_AFSEL_R = 0x00;        // 6) disable alt funct on PC7-PC4
  // rest
  GPIO_PORTC_PUR_R = pull_up;       // enable pull-up
  GPIO_PORTC_DEN_R = 0xF0;          //7) enable digital I/O on PC7-PC4
}

void Delay1ms(unsigned long msec){
// write this function
	unsigned long i;
	while(msec > 0)
	{
		i = 13333;
		while(i > 0)
		{
			i--;
		}
		msec--;
	}
}


// actual proper method for init

// void PortF_Init(void){ volatile unsigned long delay;
//   SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
//   delay = SYSCTL_RCGC2_R;           // delay
//   GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
//   GPIO_PORTF_CR_R |= 0x1F;           // allow changes to PF4-0
//   GPIO_PORTF_AMSEL_R &= 0x00;        // 3) disable analog function
//   GPIO_PORTF_PCTL_R &= 0x00000000;   // 4) GPIO clear bit PCTL
//   GPIO_PORTF_DIR_R &= ~0x11;          // 5.1) PF4,PF0 input,
//   GPIO_PORTF_DIR_R |= 0x08;          // 5.2) PF3 output
//   GPIO_PORTF_AFSEL_R &= 0x00;        // 6) no alternate function
//   GPIO_PORTF_PUR_R |= 0x11;          // enable pullup resistors on PF4,PF0
//   GPIO_PORTF_DEN_R |= 0x1F;          // 7) enable digital pins PF4-PF0
// }
