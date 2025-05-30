/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 02 - Part 4
2025/05/20
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Add 1 to the sequence
ISR(INT0_vect)
{
    PORTB = (PORTB << 1) | (1); // Add 1 to the end and shift sequence by one
}

// Add 0 to the sequence
ISR(INT1_vect)
{
    PORTB = (PORTB << 1); // Shift sequence by one
}

void bitSequenceGenerator(void)
{
    // Init switch
    DDRD = DDRD & (0 << PD2); // Definnig PD2 (INT0) as input
    DDRD = DDRD & (0 << PD3); // Definnig PD3 (INT1) as input

    // Init LEDs
    DDRB = 0x3F;  // Definning PORT_B0 as output
    PORTB = 0x00; // Set the pin initially to LOW

    // Init interrupts
    EICRA = 0x0A;                              // Falling Edge for both (0bXXXX1010)
    sei();                                     // Enable global interrupts
    EIMSK = EIMSK | (1 << INT1) | (1 << INT0); // Enable interrupt 1 and 0

    while (1)
    {
    }
}