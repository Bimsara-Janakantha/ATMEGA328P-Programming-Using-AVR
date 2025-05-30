/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 01 - Part 2
2025/05/20
*/

#include <avr/io.h>
#include <avr/delay.h>

#define WAIT_DELAY 100

int knightRider_V1(void)
{
    // PORT_B define as O/P
    DDRB = 0x0F;

    // Init PORT_B to 0
    PORTB = 0x00;

    // Define Count
    uint8_t count = 0;

    while (1)
    {
        PORTB = PORTB ^ (1 << count);
        count++;

        if (count > 3)
        {
            count = 0;
        }

        _delay_ms(WAIT_DELAY);
    }
}

int knightRider_V2(void)
{
    // PORT_B define as O/P
    DDRB = 0x0F;

    // Init PORT_B to 0
    PORTB = 0x00;

    // Define Count
    uint8_t count = 0;
    uint8_t dir = 1; // 1 - FWD, 0 - BWD

    while (1)
    {
        // Turn On
        PORTB = PORTB ^ (1 << count);

        // Wait
        _delay_ms(WAIT_DELAY);

        // Turn Off
        PORTB = PORTB ^ (1 << count);

        // Update Direction
        if (count > 2)
            dir = 0;
        else if (count < 1)
            dir = 1;

        // Shift
        count = dir == 1 ? count + 1 : count - 1;
    }
}