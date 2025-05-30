/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 01 - Part 1
2025/05/20
*/

#include <avr/io.h>
#include <util/delay.h>

int blinkAll(void)
{
    // PORT_B define as output
    DDRB = 0x0F;

    // Init PORT_B to 0;
    PORTB = 0x00;

    // Start Blink;
    while (1)
    {
        PORTB = PORTB ^ (0x0F); // Toggle
        _delay_ms(1000);        // Wait 1s
    }
}