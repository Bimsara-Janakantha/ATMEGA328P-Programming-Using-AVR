/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 05 - Part 2
2025/06/11
*/

#include <avr/io.h>

#define DARK_THRESHOLD 50

void ADC_init(void)
{
    // AREF ref, left align, ADC1
    ADMUX = ADMUX | (1 << REFS1) | (1 << REFS0) | (1 << ADLAR) | (1 << MUX0);

    // Enable ADC
    ADCSRA = ADCSRA | (1 << ADEN);

    // Set prescaler 128
    ADCSRA = ADCSRA | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint8_t ADC_read(void)
{
    // Start Conversion
    ADCSRA = ADCSRA | (1 << ADSC);

    // Wait for conversion
    while (!(ADCSRA & (1 << ADIF)))
        ;

    // Clear ADIF by writing 1 to it
    ADCSRA = ADCSRA | (1 << ADIF);

    // Read 8 MSBs (left justified)
    return ADCH;
}

void LDR(void)
{
    // ADC1 as input
    DDRC = DDRC & ~(1 << PC1);

    // PB5 as output
    DDRB = DDRB | (1 << PB5);

    // Initiate PORT_B to LOW
    PORTB = 0x00;

    // Initiate ADC
    ADC_init();

    // Control LED
    while (1)
    {
        uint8_t ldrValue = ADC_read();

        // Trun On
        if (ldrValue < DARK_THRESHOLD)
        {
            PORTB = PORTB | (1 << PB5);
        }

        // Turn Off
        else
        {
            PORTB = PORTB & ~(1 << PB5);
        }
    }
}