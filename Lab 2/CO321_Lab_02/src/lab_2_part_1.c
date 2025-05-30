/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 02 - Part 1
2025/05/20
*/

#include <avr/io.h>
#include <util/delay.h>

#define WAIT_DELAY 100

void polling(void)
{
    // Init switch
    DDRD = DDRD & (0 << PD7);   // Definnig PD7 as input
    PORTD = PORTD | (1 << PD7); // Enable internal pull-up resistor

    // Init LEDs
    DDRB = 0x3F;  // Definning PORT_B as output
    PORTB = 0x00; // Set the pin initially to LOW

    uint8_t count = 0;     // Number of times the button is pressed
    uint8_t prevState = 0; // 0 - Not pressed , 1 - Pressed

    while (1)
    {
        uint8_t btnPressed = (PIND & (1 << PD7)) == 0;

        if (btnPressed && !prevState) // Rising edge triggered
        {
            count = (count + 1) & 0x3F; // Increase count & Limit to 6 LEDs
            PORTB = count;              // Update Port
            prevState = 1;              // Mark button is pressed
        }
        else if (!btnPressed)
        {
            prevState = 0; // Ready for next press
        }
    }
}