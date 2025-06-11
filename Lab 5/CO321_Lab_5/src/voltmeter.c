#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

void init_ADC(void)
{
    // AVCC ref, left align, ADC1
    ADMUX = ADMUX | (1 << REFS0) | (1 << ADLAR) | (1 << MUX0);

    // Enable ADC
    ADCSRA = ADCSRA | (1 << ADEN);

    // Set prescaler 128
    ADCSRA = ADCSRA | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint8_t adc_read(void)
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

void voltmeter(void)
{
    // ADC1 as input
    DDRC = DDRC & ~(1 << PC1);

    // PORTD as output and initaly set it to 0
    DDRD = 0xFF;
    PORTD = 0x00;

    // Initiate ADC
    init_ADC();

    // Read and Output the result
    while (1)
    {
        uint8_t adc_value = ADC_read(); // Read value
        PORTD = adc_value;              // Write value
    }
}
