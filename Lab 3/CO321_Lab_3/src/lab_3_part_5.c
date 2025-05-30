/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 03 - Part 5
2025/05/20
*/

#include <avr/io.h>
#include <avr/interrupt.h>

int8_t count0 = 0;

// Setup Timer0
void timer0_init()
{
    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x04; // 256 prescaling
    TCNT0 = 131;   // Load timer0 counter register with 131
    TIMSK0 = 0x01; // Enable overflow interrupt
}

// Interrupt Service Routine for Timer0 Overflow
/* ISR(TIMER0_OVF_vect)
{
    if (count0 < 50)
    {
        count0++;
    }
    else
    {
        PORTB ^= (1 << 5); // Toggle PB5
        TCNT0 = 131;       // Load timer0 counter register with 131
        count0 = 0;
    }
}
 */
void blinkWithLargerDelay(void)
{
    DDRB = DDRB | (1 << 5); // PB5 mark as O/P

    PORTB = 0x00; // Set PORTB to 0

    timer0_init();

    sei(); // Enable global intrrupts

    while (1)
    {
    }
}