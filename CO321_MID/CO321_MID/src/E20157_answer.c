// -------------------------------------------------------------
// University of Peradeniya - Faculty of Engineering
// Mid-Semester Examination - July 2025
// CO321 Embedded Systems
// -------------------------------------------------------------
// Registration Number: E/20/157
// -------------------------------------------------------------

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// Global variables
uint8_t count0 = 0;
uint8_t shiftCount = 1;
uint8_t dir = 1; // 1 - Forward, 0 - Backward

// Timer0 initialization
void timer0_init()
{
    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x04; // Prescaler = 256
    TCNT0 = 131;   // Preload value for ~1ms at 16MHz
    TIMSK0 = 0x01; // Enable Timer0 overflow interrupt
}

void part2()
{
    // Init switch
    DDRD = DDRD & (0 << PD3);   // Definnig PD3 (INT1) as input
    PORTD = PORTD | (1 << PD3); // Enable internal pull-up resistor

    // Init LEDs
    PORTB = 0x00; // Set the pin initially to LOW

    // Init interrupts
    EICRA = 0x02;         // Falling edge
    sei();                // Enable global interrupts
    EIMSK |= (1 << INT1); // Enable interrupt 1
}

// Main function
void part1()
{
    // Set PB1, PB2, PB3 as output
    DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);

    // Set all PORTB outputs to LOW
    PORTB = 0x00;

    // Initialize Timer0 and enable global interrupts
    timer0_init();
    sei();

    while (1)
    {
    }
}

int main(void)
{
    // part1();

    part2();
}

// Timer0 Overflow Interrupt Service Routine
ISR(TIMER0_OVF_vect)
{
    if (count0 < 500)
    {
        count0++;
    }
    else
    {
        // Change direction at ends
        if (shiftCount > 3)
            dir = 0; // Move backward
        else if (shiftCount < 2)
            dir = 1; // Move forward

        // Update shift position
        shiftCount = (dir == 0) ? shiftCount - 1 : shiftCount + 1;

        // Turn on only the current LED
        PORTB = (1 << shiftCount);

        // Reset counter and reload timer
        TCNT0 = 131;
        count0 = 0;
    }
}

// External Interrupt 1 ISR (currently not used)
ISR(INT1_vect)
{
    // No functionality implemented
}
