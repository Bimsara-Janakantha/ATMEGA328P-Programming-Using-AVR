/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 03 - Part 4
2025/05/20
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define WAIT_DELAY 100

// Setup Timer0
void timer1_init()
{
    TCCR1A = 0x00; // Normal mode
    TCCR1B = 0x04; // 256 prescaling
    TCNT1 = 3036;  // Load timer0 counter register with 131
    TIMSK1 = 0x01; // Enable overflow interrupt
}

// Interrupt Service Routine for Timer0 Overflow
/* ISR(TIMER1_OVF_vect)
{
    PORTB ^= (1 << 5); // Toggle PB5
    TCNT1 = 3036;      // Load timer0 counter register with 131
} */

void knightRiderWithInterrupts(void)
{
    DDRB = 0xff; // PB5 mark as O/P

    PORTB = 0x00; // Set PORTB to 0

    timer1_init();

    sei(); // Enable global intrrupts

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