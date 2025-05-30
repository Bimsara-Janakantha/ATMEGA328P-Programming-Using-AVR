/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 02 - Part 3
2025/05/20
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t count = 0;

/*ISR(INT0_vect)
{
    count = (count + 1) & 0x3F; // Increase count and limit to 6 Bits
    PORTB = count;              // Display Count
}*/

void fallingEdgCounter(void)
{
    // Init switch
    DDRD = DDRD & (0 << PD2); // Definnig PD2 (INT0) as input

    // Init LEDs
    DDRB = 0x3F;  // Definning PORT_B0 as output
    PORTB = 0x00; // Set the pin initially to LOW

    // Init interrupts
    EICRA = 0x02;         // Falling Edge
    sei();                // Enable global interrupts
    EIMSK |= (1 << INT0); // Enable interrupt 0

    while (1)
    {
    }
}