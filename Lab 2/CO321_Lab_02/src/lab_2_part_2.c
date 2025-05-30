/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 02 - Part 2
2025/05/20
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*ISR(INT0_vect)
{
    PORTB = PORTB ^ (1 << PB0);
    _delay_ms(WAIT_DELAY);
}*/

void fallingEdgDetection(void)
{
    // Init switch
    DDRD = DDRD & (0 << PD2);   // Definnig PD2 (INT0) as input
    PORTD = PORTD | (1 << PD2); // Enable internal pull-up resistor

    // Init LEDs
    DDRB = DDRB | (1 << PB0); // Definning PORT_B0 as output
    PORTB = 0x00;             // Set the pin initially to LOW

    // Init interrupts
    EICRA = 0x02;         // Falling edge
    sei();                // Enable global interrupts
    EIMSK |= (1 << INT0); // Enable interrupt 0

    while (1)
    {
    }
}