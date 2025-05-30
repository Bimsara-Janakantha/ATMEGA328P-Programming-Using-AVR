/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 03 - Part 1
2025/05/20
*/

#include <avr/io.h>

void delay_timer0_2ms()
{
    TCNT0 = 131; // Load timer counter register with 0

    // Setup Timer
    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x01; // No prescaling

    while ((TIFR0 & 0x01) == 0)
    {
    };

    // Clear Timer (Stop)
    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x00; // No Clock Source

    TIFR0 = 0x01;
}

void blinkWithTimers(void)
{
    // Set PB5 as O/P
    DDRB = DDRB | (1 << PB5);

    PORTB = 0x00; // Set PORTB to 0

    while (1)
    {
        PORTB = PORTB ^ (1 << PB5); // Toggle PB5
        delay_timer0_2ms();
    }
}