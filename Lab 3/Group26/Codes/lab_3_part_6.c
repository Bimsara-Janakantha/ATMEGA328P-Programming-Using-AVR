/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 03 - Part 6
2025/05/20
*/

#include <avr/io.h>
#include <avr/interrupt.h>

int8_t count = 0;

// Setup Timer0
void timer_50ms_init()
{
    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x04; // 256 prescaling
    TCNT0 = 131;   // Load timer0 counter register with 131
    TIMSK0 = 0x01; // Enable overflow interrupt
}

// Setup Timer1
void timer_500ms_init()
{
    TCCR1A = 0x00; // Normal mode
    TCCR1B = 0x04; // 256 prescaling
    TCNT1 = 34286; // Load timer1 counter register with 34286
    TIMSK1 = 0x01; // Enable overflow interrupt
}

// Interrupt Service Routine for Timer0 Overflow
ISR(TIMER0_OVF_vect)
{
    if (count < 25)
    {
        count++;
    }
    else
    {
        PORTB ^= (1 << 5); // Toggle PB5
        TCNT0 = 131;       // Load timer0 counter register with 131
        count = 0;
    }
}

// Interrupt Service Routine for Timer1 Overflow
ISR(TIMER1_OVF_vect)
{
    PORTB ^= (1 << 1); // Toggle PB1
    TCNT1 = 34286;     // Reset
}

void blinkTwoLEDsWithDiffDelays(void)
{
    DDRB = DDRB | (1 << 5); // PB5 mark as O/P
    DDRB = DDRB | (1 << 1); // PB1 mark as O/P

    PORTB = 0x00; // Set PORTB to 0

    timer_50ms_init();
    timer_500ms_init();

    sei(); // Enable global intrrupts

    while (1)
    {
    }
}