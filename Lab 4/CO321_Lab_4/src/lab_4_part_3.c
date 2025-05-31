/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 04 - Part 3
2025/05/20
*/

#include <avr/io.h>
#include <util/delay.h>

#define PLAY_DELAY 2000
#define PAUSE_DELAY 1000

// Function to initialize PWM with selected prescaler
void setupPWM(uint8_t prescaler_bits)
{
    // Set PD6 (OC0A) as output
    DDRD |= (1 << PD6);

    // Fast PWM mode: WGM02 = 0, WGM01 = 1, WGM00 = 1
    TCCR0A = (1 << WGM01) | (1 << WGM00);
    TCCR0A &= ~(1 << WGM02);

    // Non-inverting mode
    TCCR0A |= (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);

    // Load prescaler bits
    TCCR0B = (TCCR0B & 0xF8) | prescaler_bits;

    // 50% duty cycle
    OCR0A = 128;
}

// Function to stop PWM
void stopPWM()
{
    TCCR0B &= 0xF8;       // Stop timer
    PORTD &= ~(1 << PD6); // Ensure buzzer is low
}

// Main tone generation loop
void piezoBuzzer(void)
{
    DDRB = 0x0F;

    PORTB = 0x00;

    while (1)
    {
        // Frequency 1: ~61 Hz (Prescaler = 1024)
        setupPWM(0x05);
        PORTB = PORTB ^ (1 << PB0);
        _delay_ms(PLAY_DELAY);
        PORTB = PORTB ^ (1 << PB0);

        // Frequency 2: ~244 Hz (Prescaler = 256)
        setupPWM(0x04);
        PORTB = PORTB ^ (1 << PB1);
        _delay_ms(PLAY_DELAY);
        PORTB = PORTB ^ (1 << PB1);

        // Frequency 3: ~977 kHz (Prescaler = 64)
        setupPWM(0x03);
        PORTB = PORTB ^ (1 << PB2);
        _delay_ms(PLAY_DELAY);
        PORTB = PORTB ^ (1 << PB2);

        // Frequency 4: ~7.8 kHz (Prescaler = 8)
        setupPWM(0x02);
        PORTB = PORTB ^ (1 << PB3);
        _delay_ms(PLAY_DELAY);
        PORTB = PORTB ^ (1 << PB3);
    }
}
