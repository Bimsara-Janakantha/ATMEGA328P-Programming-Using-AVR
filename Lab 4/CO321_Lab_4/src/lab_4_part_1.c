/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 04 - Part 1
2025/05/20
*/

#include <avr/io.h>

void generatePWM(void)
{
    // Define PWM pin (PD6) as O/P
    DDRD = DDRD | (1 << PD6);

    // Set Fast PWM mode: WGM01 = 1, WGM00 = 1
    TCCR0A = TCCR0A | (1 << WGM01) | (1 << WGM00);
    TCCR0B = TCCR0B & ~(1 << WGM02);

    // Set Non-Inverting Mode
    TCCR0A = TCCR0A | (1 << COM0A1);
    TCCR0A = TCCR0A & ~(1 << COM0A0);

    // Prescaler = 64
    TCCR0B = TCCR0B | (1 << CS01) | (1 << CS00);

    // 50% duty cycle → OCR0A = 128
    OCR0A = 64;

    while (1)
    {
    }
}