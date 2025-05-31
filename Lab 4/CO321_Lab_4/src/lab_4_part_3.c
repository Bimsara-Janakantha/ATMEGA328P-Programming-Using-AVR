/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 04 - Part 3
2025/05/20
*/

#include <avr/io.h>
#include <util/delay.h>

#define DELAY 1000

// Function to set PWM frequency on Timer0 (OC0A - PB3)
void set_pwm_frequency(uint16_t frequency)
{
    // Calculate the TOP value for OCR0A
    // Fast PWM formula: F_pwm = F_CPU / (N * 256)
    // For sound, we set TOP based on OCR0A value and match frequency.
    // We’ll approximate frequency via prescaler and OCR0A value.

    TCCR0A = (1 << COM0A0) | (1 << WGM01) | (1 << WGM00); // Toggle OC0A, Fast PWM
    TCCR0B = 0;

    if (frequency < 31)
    {
        // Too low for Timer0 with reasonable resolution
        frequency = 31;
    }

    // Prescaler options: 1, 8, 64, 256, 1024
    uint16_t prescaler;
    uint8_t cs_bits;

    if (frequency > 4000)
    {
        prescaler = 8;
        cs_bits = (1 << CS01); // prescaler = 8
    }
    else if (frequency > 1000)
    {
        prescaler = 64;
        cs_bits = (1 << CS01) | (1 << CS00); // prescaler = 64
    }
    else
    {
        prescaler = 256;
        cs_bits = (1 << CS02); // prescaler = 256
    }

    // Calculate the OCR0A value to set frequency
    uint16_t ocr_val = (F_CPU / (2UL * prescaler * frequency)) - 1;

    if (ocr_val > 255)
        ocr_val = 255;
    OCR0A = (uint8_t)ocr_val;

    // Set prescaler
    TCCR0B |= cs_bits;
}

void piezoBuzzer(void)
{
    // Define PWM pin (PD6) as O/P
    DDRD = DDRD | (1 << PD6);

    // 4 sound frequencies (in Hz)
    uint16_t tones[] = {440, 880, 1760, 3520};

    // Set Fast PWM mode: WGM01 = 1, WGM00 = 1
    TCCR0A = TCCR0A | (1 << WGM01) | (1 << WGM00);
    TCCR0B = TCCR0B & ~(1 << WGM02);

    // Set Non-Inverting Mode
    TCCR0A = TCCR0A | (1 << COM0A1);
    TCCR0A = TCCR0A & ~(1 << COM0A0);

    while (1)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            set_pwm_frequency(tones[i]);
            _delay_ms(DELAY);
        }
    }
}
