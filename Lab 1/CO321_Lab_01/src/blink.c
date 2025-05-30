/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 01 - Example
2025/05/20
*/

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int blink_led(void)
{
  DDRB |= (1 << PB5); // Set pin 13 (PB5) as output

  while (1)
  {
    PORTB ^= (1 << PB5); // Toggle LED
    _delay_ms(BLINK_DELAY_MS);
  }
}
