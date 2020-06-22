#include "KeyPad.h"
#include "uart.h"

int8_t validatepassword(uint8_t *input , uint8_t *rightpass);

void initportf()
{
    SYSCTL_RCGC2_R |= 0x20;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0XFF;
    GPIO_PORTF_AFSEL_R = 0;
    GPIO_PORTF_PCTL_R = 0;
    GPIO_PORTF_AMSEL_R = 0;
    GPIO_PORTF_DIR_R |= 0X02;
    GPIO_PORTF_DIR_R &= ~0X01;
    GPIO_PORTF_DEN_R |= 0X03;
    GPIO_PORTF_PUR_R |= 0X01;
    GPIO_PORTF_DATA_R &= ~0x02; // Solenoid Locked
}

int main(void)
{
    uint8_t noOfRooms = 0;
    uint8_t key;
    uint8_t counter = 0;
    uint8_t status[10];
    uint8_t roomsNo[10];
    uint8_t roomNo;
    uint8_t found = 0;
    uint8_t in[4];
    uint8_t savedpassarr[10][4];
    uint8_t setup = 0;
    uint8_t first = 0;
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    volatile uint8_t check;
    volatile uint8_t roomNumber;
    initportf();
    UART_init();
    KeyPad_init();

    for(;;)
    {
        if(setup == 0)
        {
            while(1)
            {
                roomNo = UART0_read();
                for(k = 0; k <= noOfRooms && noOfRooms != 0; k++)
                {
                    if(roomsNo[k] == roomNo)
                    {
                        // Setup finished, same room number
                        roomNumber = roomNo;
                        found = 1;
                    }
                }
                if(found == 0)
                {
                    roomsNo[noOfRooms] = roomNo;
                    noOfRooms++;
                }
                else
                {
                    break;
                }
            }
            setup = 1;
        }

        if(setup == 1)
        {
            if(first == 1)
            {
                roomNumber = UART0_read();
            }
            first = 1;
            status[roomNumber] = UART0_read();

            if(status[roomNumber] == 1)
            {
                for(j = 0; j < 4; j++)
                {
                    savedpassarr[roomNumber][j] = UART0_read();
                }

                if(counter < 4)
                {
                    key = KeyPad_getPressedKey();
                    if(key == '#' || key == '*'){continue;}
                    in[i] = key;
                    i++;
                    counter++;
                }

                if(counter >= 4)
                {
                    key = KeyPad_getPressedKey();
                    if(key == '#')
                    {
                        check = validatepassword(in,savedpassarr[roomNumber]);
                        // Correct password
                        if(check == 1)
                        {
                            GPIO_PORTF_DATA_R |= 0x02; //Solenoid open
                        }
                        i = 0;
                        counter = 0;
                     }
                }
            }
            else if(status[roomNumber] == 2)
            {
                GPIO_PORTF_DATA_R |= 0x02;
            }
            else if(status[roomNumber] == 0)
            {
                GPIO_PORTF_DATA_R &= ~0x02;
            }
        }
    }
}

int8_t validatepassword(uint8_t *input , uint8_t *rightpass)
{
    uint8_t z;
    for(z = 0; z < 4; z++)
    {
        if (input[z] != rightpass[z])
        return 0;
    }
    return 1;
}
